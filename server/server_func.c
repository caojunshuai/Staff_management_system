/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date: 2020-07-11 10:47:02
 * @LastEditTime 2020-09-17 16:06:38
 */
#include "server_func.h"
#include "sqlite_func.h"
#include "server_init.h"
#include "../include/proto.h"
#include <sys/socket.h>

extern FILE *fp;
/* 将新连接的套接字添加到集合表中 */
int add_fds(int listenfd, fd_set *rfds)
{
	struct sockaddr_in client;
	socklen_t len = sizeof(client);

	/* 接收新的连接请求 */
	int connfd = accept(listenfd, (struct sockaddr *)&client, &len);
	/* 将新的读写套接字添加到集合表中 */
	FD_SET(connfd, rfds);
	get_time();
	fprintf(fp, "accept success connfd=%d ", connfd);
	fprintf(fp, "ip:%s--port:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
	fflush(fp);
	return connfd;
}

int recv_clidata(int connfd, sqlite3 *db)
{
	CTP client_data;
	int ret = 0;
	char select_buf[DATASIZE + 10] = {0};
	/* 非阻塞接收 */
	ret = recv(connfd, &client_data, sizeof(CTP), MSG_DONTWAIT);
	/* 日志信息，可省略 */
	get_time();
	fprintf(fp, "recv from client: %d,%s,%s,%d,%s,%s,%s,%s,%s,%s,%s,%s\n", client_data.cli_msgstat,
			client_data.usrid, client_data.usrpasswd, client_data.datainfo.staff_msgstat,
			client_data.datainfo.jobnumber, client_data.datainfo.name, client_data.datainfo.age,
			client_data.datainfo.phone, client_data.datainfo.address, client_data.datainfo.position,
			client_data.datainfo.department, client_data.datainfo.salary);
	fflush(fp);
	/* 当客户端退出时 */
	if (ret == 0) /* 当返回值为0，则客户端关闭 */
	{
		return 1;
	}
	/* 当正常接收到数据时 */
	switch (client_data.cli_msgstat)
	{
	case REGISTER:
		query_sqlite(db, &client_data, select_buf);
		if (!strlen(select_buf))
		{
			insert_sqlite(db, &client_data);
			send_serdata(connfd, REGISTER_SUCCESS, NULL);
		}
		else
		{
			send_serdata(connfd, REGISTER_FAILED, NULL);
		}
		break;
	case LOGIN:
		/*  去对应login表中比对ID和passwd*/
		query_sqlite(db, &client_data, select_buf);
		/* ID密码输入正确 */
		if (strlen(select_buf))
		{
			send_serdata(connfd, LOGIN_SUCCESS, select_buf);
		}
		/* ID密码不匹配 */
		else
		{
			send_serdata(connfd, LOGIN_FAILED, NULL);
		}
		break;
	case CMD:
		switch (client_data.datainfo.staff_msgstat)
		{
		case QUERY:
			query_sqlite(db, &client_data, select_buf);
			if (strlen(select_buf) != 0)
			{
				send_serdata(connfd, EXECUTE_SUCCESS, select_buf);
			}
			else
			{
				/* 默认发送执行失败信息 */
				send_serdata(connfd, EXECUTE_FAILED, NULL);
			}
			break;
		case DELETE:
			// printf("%s,%s,%d", __FILE__, __func__, __LINE__);
			if (delete_sqlite(db, &client_data) == -1)
			{
				send_serdata(connfd, EXECUTE_FAILED, NULL);
			}
			else
			{
				send_serdata(connfd, EXECUTE_SUCCESS, select_buf);
			}
			break;
		case MODIFY:
			if (modify_sqlite(db, &client_data) == -1)
			{
				send_serdata(connfd, EXECUTE_FAILED, NULL);
			}
			else
			{
				query_sqlite(db, &client_data, select_buf);
				send_serdata(connfd, EXECUTE_SUCCESS, select_buf);
			}
			break;
		case INSERT:
			query_sqlite(db, &client_data, select_buf);
			if (!strlen(select_buf) && insert_sqlite(db, &client_data) == -1)
			{
				send_serdata(connfd, EXECUTE_FAILED, NULL);
			}
			else if (insert_sqlite(db, &client_data) == -1)
			{
				send_serdata(connfd, EXECUTE_FAILED, NULL);
			}
			else
			{
				query_sqlite(db, &client_data, select_buf);
				send_serdata(connfd, EXECUTE_SUCCESS, select_buf);
			}
			break;
		}
		break;
	}
	return 0;
}
/* 发送服务端数据 */
int send_serdata(int connfd, int ser_msgstat, char *buf)
{
	STP server_data;
	char temp_1[USRID_SIZE];
	char temp_2[USRPASSWD];
	switch (ser_msgstat)
	{
	case REGISTER_FAILED:
		server_data.ser_msgstat = REGISTER_FAILED;
		strcpy(server_data.backmsg, "注册失败,请重试!\n");
		send(connfd, &server_data, sizeof(STP), MSG_DONTWAIT);
		break;
	case REGISTER_SUCCESS:
		server_data.ser_msgstat = REGISTER_SUCCESS;
		strcpy(server_data.backmsg, "注册成功!\n");
		send(connfd, &server_data, sizeof(STP), MSG_DONTWAIT);
		break;
	case LOGIN_FAILED:
		server_data.ser_msgstat = LOGIN_FAILED;
		strcpy(server_data.backmsg, "登录失败,请检查账号或密码!\n");
		send(connfd, &server_data, sizeof(STP), MSG_DONTWAIT);
		break;
	case LOGIN_SUCCESS:
		server_data.ser_msgstat = LOGIN_SUCCESS;
		strcpy(server_data.backmsg, "登录成功!\n");
		sscanf(buf, "\n%s\n%s\n%s", temp_1, temp_2, server_data.identify);
		send(connfd, &server_data, sizeof(STP), MSG_DONTWAIT);
		break;
	case EXECUTE_FAILED:
		server_data.ser_msgstat = EXECUTE_FAILED;
		strcpy(server_data.backmsg, "未查询到内容!\n");
		send(connfd, &server_data, sizeof(STP), MSG_DONTWAIT);
		break;
	case EXECUTE_SUCCESS:
		server_data.ser_msgstat = EXECUTE_SUCCESS;
		strcpy(server_data.backmsg, "查询到以上内容!\n");
		sscanf(buf, "\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", server_data.datainfo.name, server_data.datainfo.address,
			   server_data.datainfo.age, server_data.datainfo.phone, server_data.datainfo.salary,
			   server_data.datainfo.department, server_data.datainfo.position, server_data.datainfo.jobnumber);
		send(connfd, &server_data, sizeof(STP), MSG_DONTWAIT);
		break;
	}
	return 0;
}
/* 获取时间 */
void get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	uint64_t sec = tv.tv_sec;
	uint64_t min = tv.tv_sec;
	struct tm cur_tm;
	localtime_r((time_t *)&sec, &cur_tm);
	char cur_time[32] = {0};
	sprintf(cur_time, "%d-%02d-%02d-%02d:%02d:%02d", cur_tm.tm_year + 1900, cur_tm.tm_mon + 1,
			cur_tm.tm_mday, cur_tm.tm_hour, cur_tm.tm_min, cur_tm.tm_sec);
	fprintf(fp, "%s ", cur_time);
	fflush(fp);
}
void my_fprintf(char *format, char *argv)
{
	get_time();
	fprintf(fp, format, argv);
	fflush(fp);
}
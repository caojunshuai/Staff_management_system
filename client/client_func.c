/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date: 2020-07-13 00:47:20
 * @LastEditTime 2020-09-17 14:59:29
 */

#include "client_func.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int client_init(const char ip[])
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in seraddr;
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(8888);
	seraddr.sin_addr.s_addr = inet_addr(ip);

	if (connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) == -1)
	{
		close(sockfd);
		return -1;
	}
	return sockfd;
}


CTP *pakgage_clidata(short cli_msgstat, short staff_msgstat, const char cmd[], CTP *client_data)
{
	client_data->cli_msgstat = cli_msgstat;
	strcpy(client_data->cmd, cmd);
	client_data->datainfo.staff_msgstat = staff_msgstat;
	return client_data;
}

void log_page(int log_stat)
{
	switch (log_stat)
	{
	case UNLOGIN:
		printf("============员工管理系统============\n");
		printf("=============1.注册账号=============\n");
		printf("=============2.登录系统=============\n");
		printf("=============0.关闭系统=============\n");
		printf("====================================\n");
		break;
	case LOGIN:
		printf("============员工管理系统============\n");
		printf("=============1.查询信息=============\n");
		printf("=============2.修改信息=============\n");
		printf("=============3.退出账号=============\n");
		printf("=============0.关闭系统=============\n");
		printf("====================================\n");
		break;
	case LOGIN_R:
		printf("============员工管理系统============\n");
		printf("=============1.查询信息=============\n");
		printf("=============2.修改信息=============\n");
		printf("=============3.添加用户=============\n");
		printf("=============4.删除信息=============\n");
		printf("=============5.退出账号=============\n");
		printf("=============0.关闭系统=============\n");
		printf("====================================\n");
		break;
	}
}

/**
 * @brief 检查用户输入的选项是否合法
 * @param {min} 选项的最小值 
 * @param {max} 选项的最大值 
 * @return {int} 返回用户输入的选项 
 */
int sel_number(int min, int max)
{
	int sel_num;
	while (1)
	{
		printf("请输入选项：");
		scanf("%d", &sel_num);
		if (sel_num >= min && sel_num <= max)
		{
			return sel_num;
		}
		else
		{
			printf("请输入正确的选项！\n");
			while (getchar() != '\n')
				;
		}
	}
}

int sel_number_pro(int logstat)
{
	switch (logstat)
	{
	case UNLOGIN:
		sel_number(0, 2);
		break;
	case LOGIN:
		sel_number(0, 3);
		break;
	case LOGIN_R:
		sel_number(0, 5);
		break;
	default:
		break;
	}
}
int sel_number_switch(int sel_number, int logstat)
{
	int temp_selnum;
	/* 将用户界面输入的选项转换到main函数中switch语句中的选项 */
	int usrlog_selnum[USRLOG_NUM] = {0, 4, 5, 7};
	int root_selnum[ROOT_NUM] = {0, 4, 5, 3, 6, 7};
	switch (logstat)
	{
	case UNLOGIN:
		temp_selnum = sel_number;
		break;
	case LOGIN:
		/* 将用户界面输入的选项转换到main函数中switch语句中的选项 */
		temp_selnum = usrlog_selnum[sel_number];
		break;
	case LOGIN_R:
		/* 将用户界面输入的选项转换到main函数中switch语句中的选项 */
		temp_selnum = root_selnum[sel_number];
		break;
	}
	return temp_selnum;
}
int log_stat_page(int log_stat,int sockfd, char *usrid)
{
	if (sockfd==-1)
	{
		printf("============未连接服务器============\n");
		return 0;
	}

	if (log_stat == LOGIN)
	{
		printf("============已连接服务器============\n");
		printf("普通用户: %s \n", usrid);
		printf("====================================\n");
	}
	else if (log_stat == LOGIN_R)
	{
		printf("============已连接服务器============\n");
		printf("管理员用户: %s \n", usrid);
		printf("====================================\n");
	}
	else
	{
		printf("============已连接服务器============\n");
		printf("未登录账号！\n");
		printf("====================================\n");
	}
	return 0;
}
/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date 2020-09-16 18:52:45
 * @LastEditTime 2020-09-17 14:23:00
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "client_func.h"
#include "operat_func.h"
#include "staffinfo_io.h"
void cli_register(STP *server_data, CTP *temp_clidata, int *sockfd)
{
	char temp_data[128] = {0};
	staffInfo_init(&temp_clidata->datainfo);
	input_info_sub(temp_clidata->usrid,"账号", USRID_SIZE);
	input_info_sub(temp_clidata->usrpasswd,"密码", USRPASSWD);
	pakgage_clidata(REGISTER, EMPTY, "0", temp_clidata);
	write(*sockfd, temp_clidata, sizeof(CTP));
	int ret = read(*sockfd, server_data, sizeof(STP));
	if (ret == 0)
	{
		close(*sockfd);
		*sockfd = -1;
		printf("与服务器断开连接，请重试！\n");
		while (getchar() != '\n')
		{
		}
	}
	printf("系统消息：%s", server_data->backmsg);
}
void cli_login(STP *server_data, CTP *client_data, int *sockfd, int *log_stat)
{
	char temp_data[128] = {0};
	staffInfo_init(&client_data->datainfo);
	input_info_sub(client_data->usrid,"账号", USRID_SIZE);
	input_info_sub(client_data->usrpasswd,"密码", USRPASSWD);
	pakgage_clidata(LOGIN, EMPTY, "NULL", client_data);
	write(*sockfd, client_data, sizeof(CTP));
	int ret = read(*sockfd, server_data, sizeof(STP));
	if (ret == 0)
	{
		close(*sockfd);
		*sockfd = -1;
		printf("\n与服务器断开连接，请重试！\n");
		while (getchar() != '\n')
		{
		}
	}
	if (server_data->ser_msgstat == LOGIN_SUCCESS)
	{
		if (!strcmp(server_data->identify, USER))
		{
			*log_stat = LOGIN;
		}
		else if (!strcmp(server_data->identify, ROOT))
		{
			*log_stat = LOGIN_R;
		}
	}
	printf("系统消息:%s", server_data->backmsg);
}
int cli_query_staffinfo(STP *server_data, CTP *client_data, int *sockfd)
{
	staffInfo_init(&client_data->datainfo);
	input_info(&client_data->datainfo, JOBNUMBER);
	pakgage_clidata(CMD, QUERY, "NULL", client_data);
	write(*sockfd, client_data, sizeof(CTP));
	int ret = read(*sockfd, server_data, sizeof(STP));
	if (ret == 0)
	{
		close(*sockfd);
		*sockfd = -1;
		printf("\n与服务器断开连接，请重试！\n");
		while (getchar() != '\n')
		{
		}
	}
	else if (server_data->ser_msgstat == EXECUTE_SUCCESS)
	{
		print_staffInfo(&server_data->datainfo, ALL);
		return 0;
	}
	else
	{
		printf("\n系统消息：%s\n", server_data->backmsg);
	}
	return -1;
}
void cli_insert_staffinfo(STP *server_data, CTP *client_data, int *sockfd)
{
	staffInfo_init(&client_data->datainfo);
	input_info(&client_data->datainfo, ALL);
	pakgage_clidata(CMD, INSERT, "NULL", client_data);
	write(*sockfd, client_data, sizeof(CTP));
	int ret = read(*sockfd, server_data, sizeof(STP));
	if (ret == 0)
	{
		close(*sockfd);
		*sockfd = -1;
		printf("与服务器断开连接，请重试！\n");
		while (getchar() != '\n')
		{
		}
	}
	if (server_data->ser_msgstat == EXECUTE_SUCCESS)
	{
		printf("\n插入信息成功!\n");
	}
	else
	{
		printf("\n插入信息失败!\n");
	}
}
int cli_modify_staffinfo(STP *server_data, CTP *client_data, int *sockfd)
{
	staffInfo_init(&client_data->datainfo);
	if (cli_query_staffinfo(server_data, client_data, sockfd) == -1)
	{
		return 0;
	}
	printf("\n提示：输入新内容进行修改，不需要修改的部分可按enter跳过\n");
	input_info_nojobnum(&client_data->datainfo);
	pakgage_clidata(CMD, MODIFY, "NULL", client_data);
	write(*sockfd, client_data, sizeof(CTP));
	int ret = read(*sockfd, server_data, sizeof(STP));
	if (ret == 0)
	{
		close(*sockfd);
		*sockfd = -1;
		printf("\n与服务器断开连接，请重试！\n");
		while (getchar() != '\n')
		{
		}
	}
	else if (server_data->ser_msgstat == EXECUTE_SUCCESS)
	{
		printf("\n修改完成!\n");
	}
	else
	{
		printf("\n修改失败，请重试!\n");
	}
	return 0;
}
int cli_delete_staffinfo(STP *server_data, CTP *client_data, int *sockfd)
{
	char temp_str[10] = {0};
	staffInfo_init(&client_data->datainfo);
	if (cli_query_staffinfo(server_data, client_data, sockfd) == -1)
	{
		return 0;
	}
	printf("\n请输入(yes/no)进行删除或取消:");
	fgets(temp_str, 10, stdin);
	temp_str[strlen(temp_str) - 1] = 0;
	if (!strcmp(temp_str, "yes"))
	{
		pakgage_clidata(CMD, DELETE, "NULL", client_data);
		write(*sockfd, client_data, sizeof(CTP));
		int ret = read(*sockfd, server_data, sizeof(STP));
		if (ret == 0)
		{
			close(*sockfd);
			*sockfd = -1;
			printf("\n与服务器断开连接，请重试！\n");
			while (getchar() != '\n')
			{
			}
		}
		else if (server_data->ser_msgstat == EXECUTE_SUCCESS)
		{
			printf("\n已删除!\n");
		}
		else
		{
			printf("\n删除失败，请重试!\n");
		}
	}
	return 0;
}
void cli_close(CTP *client_data, int *sockfd, int *log_stat)
{
	staffInfo_init(&client_data->datainfo);
	pakgage_clidata(QUIT, EMPTY, "NULL", client_data);
	write(*sockfd, &client_data, sizeof(CTP));
	*log_stat = QUIT;
}

void cli_quit(CTP *client_data, int *sockfd, int *log_stat)
{
	staffInfo_init(&client_data->datainfo);
	*log_stat = UNLOGIN;
	pakgage_clidata(QUIT, EMPTY, "NULL", client_data);
	write(*sockfd, client_data, sizeof(CTP));
	printf("\n账号已退出!\n");
}
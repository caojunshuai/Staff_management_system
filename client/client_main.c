/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date: 2020-07-11 10:35:24
 * @LastEditTime 2020-09-17 15:59:33
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "client_func.h"
#include "staffinfo_io.h"
#include "operat_func.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage:%s <ip> <port>\n", argv[0]);
		return -1;
	}

	CTP client_data, temp_clidata;  		/* 客户端发出的数据包 */
	staffInfo_init(&client_data.datainfo);
	staffInfo_init(&temp_clidata.datainfo);
	STP server_data;			    		/*接收服务器发出的数据包 */
	static int log_stat = UNLOGIN;  		/* 登录状态 */
	int sel_num; 							/* 主界面功能选项 */
	char cmd[CMD_SIZE] = {0};	    		/* 用户指令 */

	int sockfd;			/* 通信套接字 */	
RE_CONNECT:
	sockfd = client_init(argv[1]);
	
	while (1)
	{
		system("clear");
		log_page(log_stat);
		log_stat_page(log_stat, sockfd, client_data.usrid);
		sel_num = sel_number_switch(sel_number_pro(log_stat), log_stat);
		getchar();
		switch (sel_num)
		{
		case 1: //注册
			cli_register(&server_data, &client_data, &sockfd);
			break;
		case 2: //登录
			cli_login(&server_data, &client_data, &sockfd, &log_stat);
			break;
		case 3: //插入
			cli_insert_staffinfo(&server_data, &client_data, &sockfd);
			break;
		case 4: //查询
			cli_query_staffinfo(&server_data, &client_data, &sockfd);
			break;
		case 5: // 修改
			cli_modify_staffinfo(&server_data, &client_data, &sockfd);
			break;
		case 6: //删除
			cli_delete_staffinfo(&server_data, &client_data, &sockfd);
			break;
		case 7: //退出账号
			cli_quit(&client_data, &sockfd, &log_stat);
			break;
		case 0: //关闭系统
			cli_close(&client_data, &sockfd, &log_stat);
			break;
		}
		memset(server_data.backmsg, 0, BACKMSG_SIZE);
		if (log_stat == QUIT)
		{
			printf("系统退出成功！\n");
			break;
		}
		if (sockfd == -1)
		{
			printf("请按enter键尝试重新连接网络\n");
			goto RE_CONNECT;
		}
		printf("\n请按enter键进行下一步操作\n");
		getchar();
	}
	close(sockfd);
	return 0;
}

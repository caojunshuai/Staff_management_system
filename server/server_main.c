/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date: 2020-07-11 10:35:16
 * @LastEditTime 2020-09-17 16:06:21
 */

#include "../include/proto.h"
#include "close_fd.h"
#include "server_init.h"
#include "sqlite_func.h"
#include "server_func.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>
FILE *fp;
int main(int argc, char *argv[])
{
	int nrfds = 0;						  /* 接收select的返回值 */
	int i = 0;							  /* 用于遍历描述符集合表 */
	int maxfds = 0;						  /* 集合表中最大的描述符加1 */
	int port = 8888;					  /* 端口号 */
	 /* 接受查询到的数据 */
	staffInfo staffInfo_buf;
	/* 创建数据库 */
	sqlite3 *db = create_db();

	/* 创建日志文件 */
	fp = fopen("../log/sys_log", "a+");
	if (fp == NULL)
	{
		fprintf(stderr, "fopen failed\n");
	}

	/* 得到监听套接字 */
	int listenfd = server_init(port, 1024);
	if (0 > listenfd)
	{
		return -1;
	}
	
	/*创建文件描述符集合表*/
	fd_set rfds, tmpfds;
	FD_ZERO(&rfds); //清空
	FD_SET(listenfd, &rfds);
	maxfds = listenfd + 1;

	while (1)
	{
		tmpfds = rfds;
		nrfds = select(maxfds, &tmpfds, NULL, NULL, NULL);
		if (0 > nrfds)
		{
			perror("select()");
			return -1;
		}
		for (i = 0; i < maxfds; i++)
		{
			/* 遍历出集合表中存在的描述符 */
			if (FD_ISSET(i, &tmpfds) == 1)
			{
				if (i == listenfd)
				{
					/* 当监听套接字状态变化时，调用accept接受请求 */
					/* 并将新的读写套接字添加到描述符表中 */
					int connfd = add_fds(listenfd, &rfds);
					/* 当新的套接字是否为集合表中最大的文件描述符 */
					/* 更新maxfds */
					if (maxfds <= connfd)
					{
						maxfds = connfd + 1;
					}
				}
				else
				{
					/* 当读写套接字状态变化时，对该套接字进行读写操作 */
					int ret = recv_clidata(i, db);
					/* 并更新maxfds */
					if (ret)
					{
						close_fd(i, &rfds, maxfds);
					}
				}
			}
		}
	}

	return 0;
}

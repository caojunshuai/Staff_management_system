/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date: 2020-09-15 15:11:39
 * @LastEditTime 2020-09-17 14:42:39
 */
#include "close_fd.h"

#include <stdio.h>
#include <unistd.h>
extern FILE *fp;
int close_fd(int connfd, fd_set *rfds, int maxfds)
{
	/* 将该套接字从列表中清除 */
	FD_CLR(connfd, rfds);
	/* 必须关闭该套接字 */
	close(connfd);
	fflush(fp);
	/* 当清除的套接字为集合中最大的文件描述符时，更新maxfds */
	if ((connfd + 1) == maxfds)
	{
		maxfds--;
	}
	return maxfds;
}
/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date: 2020-09-15 15:16:38
 * @LastEditTime 2020-09-17 14:42:58
 */
#ifndef CLOSE_FD_H__
#define CLOSE_FD_H__i
#include <sys/socket.h>
/**
 * @brief: 关闭套接字，并从监听套接字中删除
 * @param {connfd} 读写套接字
 * @param {rfds} 文件描述符表
 * @param {maxfds} 文件描述符表中最大的文件描述符
 * @return {int} 错误判断
 */
int close_fd(int connfd, fd_set *rfds, int maxfds);
#endif

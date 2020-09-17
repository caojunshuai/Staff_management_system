/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date 2020-09-17 14:30:17
 * @LastEditTime 2020-09-17 16:10:07
 */
#ifndef SERVER_FUNC_H__
#define SERVER_FUNC_H__
#include <sqlite3.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
/**
 * @brief: 将新连接的套接字添加到集合表中
 * @param {listenfd} 监听套接字
 * @param {rfds} 文件描述符集合表
 * @return {int} 读写套接字
 */
int add_fds(int listenfd, fd_set *rfds);
/**
 * @brief: 接收客户端数据
 * @param {connfd} 读写套接字
 * @param {db} 数据库文件
 * @param {select} 数据库文件
 * @return {int} 状态判断
 */
int recv_clidata(int connfd, sqlite3 *db);
/* 发送服务端数据 */
/**
 * @brief: 发送服务端数据
 * @param {connfd} 读写套接字
 * @param {ser_msgstat} 发送的消息状态
 * @param {cmd} 其它指令
 * @return {int} 状态判断
 */
int send_serdata(int connfd, int ser_msgstat, char cmd[]);
/**
 * @brief: 获取时间并输出到sys_log文件
 * @return {int} 状态判断
 */
void get_time();
/* 格式化输出到文件(带时间戳、刷新文件流) */
/**
 * @brief: 格式化输出到sys_log文件(带时间戳、刷新文件流)
 * @param {format} 输出格式
 * @param {argv} 变量
 * @return {void} 
 */
void my_fprintf(char *format, char *argv);
#endif

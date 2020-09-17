/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date 2020-09-16 18:47:22
 * @LastEditTime 2020-09-17 14:23:14
 */
#ifndef OPERAT_FUNC_H__
#define OPERAT_FUNC_H__
#include "../include/proto.h"
/**
 * @brief 客户端发起查询请求函数
 * @param {server_data} 客户端发送的数据结构体指针
 * @param {client_data} 客户端接受的数据结构体指针
 * @param {sockfd} 客户端通信套接字
 * @return {int} 0：查询到数据，1：未查询到数据
 */
int cli_query_staffinfo(STP *server_data, CTP *client_data, int *sockfd);
/**
 * @brief 客户端发起插入数据请求
 * @param {server_data} 客户端发送的数据结构体指针
 * @param {client_data} 客户端接受的数据结构体指针
 * @param {sockfd} 客户端通信套接字
 * @return {void} 
 */
void cli_insert_staffinfo(STP *server_data, CTP *client_data, int *sockfd);
/**
 * @brief 客户端发起修改数据请求
 * @param {server_data} 客户端发送的数据结构体指针
 * @param {client_data} 客户端接受的数据结构体指针
 * @param {sockfd} 客户端通信套接字
 * @return {void} 
 */
int cli_modify_staffinfo(STP *server_data, CTP *client_data, int *sockfd);
/**
 * @brief 客户端发起删除数据请求
 * @param {server_data} 客户端发送的数据结构体指针
 * @param {client_data} 客户端接受的数据结构体指针
 * @param {sockfd} 客户端通信套接字
 * @return {void} 
 */
int cli_delete_staffinfo(STP *server_data, CTP *client_data, int *sockfd);

/**
 * @brief 客户端发起注册账号请求
 * @param {server_data} 客户端发送的数据结构体指针
 * @param {client_data} 客户端接受的数据结构体指针
 * @param {sockfd} 客户端通信套接字
 * @return {void} 
 */
void cli_register(STP *server_data, CTP *client_data, int *sockfd);

/**
 * @brief 客户端发起登录账号请求
 * @param {server_data} 客户端发送的数据结构体指针
 * @param {client_data} 客户端接受的数据结构体指针
 * @param {sockfd} 客户端通信套接字
 * @return {void} 
 */
void cli_login(STP *server_data, CTP *client_data, int *sockfd, int *log_stat);

/**
 * @brief 客户端关闭函数
 * @param {server_data} 客户端发送的数据结构体指针
 * @param {client_data} 客户端接受的数据结构体指针
 * @param {sockfd} 客户端通信套接字
 * @return {void} 
 */
void cli_close(CTP *client_data, int *sockfd, int *log_stat);
/**
 * @brief 账号退出函数
 * @param {server_data} 客户端发送的数据结构体指针
 * @param {client_data} 客户端接受的数据结构体指针
 * @param {sockfd} 客户端通信套接字
 * @return {void} 
 */
void cli_quit(CTP *client_data, int *sockfd, int *log_stat);

#endif
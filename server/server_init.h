/*
 * @Descripttion: 创建数据库表，初始化监听套接字
 * @version: V1.0
 * @Author: caojunshuai
 * @Date: 2020-09-15 14:16:34
 * @LastEditTime: 2020-09-15 17:59:13
 */
#ifndef SERVER_INIT_H__
#define SERVER_INIT_H__
#include<sqlite3.h>
/* 创建数据表 */
sqlite3 *create_db(void);
/* 初始化监听套接字 */
int server_init(int port, int max);

#endif
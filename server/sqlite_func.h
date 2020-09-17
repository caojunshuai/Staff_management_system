/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date: 2020-09-15 15:41:42
 * @LastEditTime 2020-09-17 16:18:10
 */
#ifndef SQLITE_FUNC_H__
#define SQLITE_FUNC_H__
#include"../include/proto.h"
#include<stdio.h>
#define SQLITE_EXEC ({if (sqlite3_exec(db, sql_cmd, NULL, NULL, &msg) != 0) goto ERR;})
#define SQLITE_EXEC_BUF ({if (sqlite3_exec(db, sql_cmd, callback, buf, &msg) != 0) goto ERR; })
#define JUDGE_RET ({if(-1==ret)goto ERR; })

/**
 * @brief: 向数据库表中插入信息
 * @param {db} 数据库文件
 * @param {client_data} 接收到的客户端数据结构体指针
 * @return {int} 错误判断
 */
int insert_sqlite(sqlite3 *db, CTP *client_data);
/**
 * @brief: 在数据库中查询信息
 * @param {db} 数据库文件
 * @param {client_data} 接收到的客户端数据结构体指针
 * @param {buf} 存储查询到的数据
 * @return {int} 错误判断
 */
int query_sqlite(sqlite3 *db, CTP *client_data, char buf[]);
/**
 * @brief: 查询指令的回调函数
 */
int callback(void *para, int f_num, char **f_value, char **f_name);
/**
 * @brief: 在数据库中删除指定信息
 * @param {db} 数据库文件
 * @param {client_data} 接收到的客户端数据结构体指针
 * @return {int} 错误判断
 */
int delete_sqlite(sqlite3 *db, CTP *client_data);
/**
 * @brief: 在数据库中修改信息
 * @param {db} 数据库文件
 * @param {client_data} 接收到的客户端数据结构体指针
 * @return {int} 错误判断
 */
int modify_sqlite(sqlite3 *db, CTP *client_data);
/**
 * @brief: 在数据库中修改信息函数子函数
 * @param {db} 数据库文件
 * @param {data} 新值
 * @param {para} 要更改的项目
 * @param {jobnumber} 工号
 * @return {int} 错误判断
 */
int modify_sqlite_sub(sqlite3 *db,char *data, char *para,char *jobnumber);

#endif
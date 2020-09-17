/*
 * @Descripttion:  
 * @version: V1.0
 * @Author: caojunshuai
 * @Date: 2020-09-15 14:14:46
 * @LastEditTime 2020-09-17 19:36:03
 */
#include "server_init.h"
#include "server_func.h"
#include "../include/proto.h"
#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

extern FILE *fp;

//初始化监听套接字IPv4
int server_init(int port, int max)
{
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == s)
	{
		my_fprintf("socket fail: %s\n", strerror(errno));
		return -1;
	}
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr = {
			.s_addr = INADDR_ANY,
		},
	};
	socklen_t len = sizeof(addr);
	if (0 > bind(s, (struct sockaddr *)&addr, len))
	{
		my_fprintf("bind fail: %s\n", strerror(errno));
		goto ERR_STEP;
	}
	if (0 > listen(s, max))
	{
		my_fprintf("listen fail: %s\n", strerror(errno));
		goto ERR_STEP;
	}
	return s;
ERR_STEP:
	close(s);
	return -1;
}

/* 创建数据表 */
sqlite3 *create_db(void)
{
	sqlite3 *db;
	char sql[256] = {0};
	if (sqlite3_open("../sqlite/my.db", &db) != 0)
	{
		get_time();
		fprintf(fp, "open error! %s\n", sqlite3_errmsg(db));
		fflush(fp);
		return NULL;
	}
	char *errmsg;
	//创建账户信息表
	strcpy(sql, "create table if not exists accountInfo(id text,passwd text,\
	identify text,UNIQUE(id,passwd,identify));");
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0)
	{
		my_fprintf("create table error! %s\n", errmsg);
		return NULL;
	}
	//insert or ignore into table_name (id,type) values (2,0);
	strcpy(sql, "insert or ignore into accountInfo values('admin', '0000','1');");
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0)
	{
		my_fprintf("insert admin info error! %s\n", errmsg);
		return NULL;
	}
	//创建员工信息表
	strcpy(sql, "create table if not exists staffInfo(name text,address text,age text,phone text,salary text,\
	department text,position text,jobnumber text,UNIQUE(jobnumber));");
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0)
	{
		my_fprintf("create table error! %s\n", errmsg);
		return NULL;
	}
	return db;
}
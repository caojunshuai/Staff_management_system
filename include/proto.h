/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date: 2020-09-15 17:53:59
 * @LastEditTime 2020-09-17 14:14:57
 */
#ifndef PROTO_H_
#define PROTO_H_
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>

#define USRID_SIZE 16	/* 用户ID长度 */
#define USRPASSWD 8		/* 用户密码长度 */
#define CMD_SIZE 128	/* 用户指令长度 */
#define BACKMSG_SIZE 64 /* 服务器返回消息长度 */
#define IDENTIFYSIZE 2	/* 账户标识长度 */

/* 用户身份标识 */
#define USER "0" /* 普通用户 */
#define ROOT "1" /* 管理员用户 */

/* 各种状态下界面功能个数 */
#define UNLOG_NUM 3	 /* 未登录界面3个功能 */
#define USRLOG_NUM 4 /* 普通用户界面4个功能 */
#define ROOT_NUM 6	 /* 管理员用户界面6个功能 */

/* 客户端发出消息状态 */
#define REGISTER 0 /* 注册 */
#define LOGIN 1	   /* 普通用户登陆 */
#define LOGIN_R 2  /* 管理员登录 */
#define UNLOGIN 3  /* 未登录 */
#define CMD 4	   /* 指令 */
#define QUIT 5	   /* 退出 */
#define HISTROY 6  /* 历史记录 */

/* 服务器返回消息状态 */
#define REGISTER_FAILED 0  /* 注册失败 */
#define REGISTER_SUCCESS 1 /* 注册成功 */
#define LOGIN_FAILED 2	   /* 登陆失败 */
#define LOGIN_SUCCESS 3	   /* 登陆成功 */
#define EXECUTE_FAILED 4   /* 执行命令失败 */
#define EXECUTE_SUCCESS 5  /* 执行命令成功 */

/* 员工信息数据长度 */
#define DATASIZE (sizeof(staffInfo))

/* 员工信息数据包状态标识 */
#define QUERY 0	 /* 查询数据 */
#define INSERT 1 /* 插入数据 */
#define DELETE 2 /* 删除数据 */
#define MODIFY 3 /* 修改数据 */
#define EMPTY 4	 /* 空 */

/* 员工各种信息数据的大小 */
#define NAMESIZE 32
#define ADDRESSSIZE 128
#define AGESIZE 4
#define PHONESIZE 12
#define SALARYSIZE 8
#define DEPARTMENTSIZE 64
#define POSITSIZE 64
#define JOBNUMSIZE 12

/* 员工信息标识 */
#define ALL 0
#define NAME 1
#define ADDRESS 2
#define AGE 3
#define PHONE 4
#define SALARY 5
#define DEPARTMENT 6
#define POSITION 7
#define JOBNUMBER 8

/* 员工信息数据 */
typedef struct
{
	char name[NAMESIZE];
	char address[ADDRESSSIZE];
	char age[AGESIZE];
	char phone[PHONESIZE];
	char salary[SALARYSIZE];
	char department[DEPARTMENTSIZE];
	char position[POSITSIZE];
	char jobnumber[JOBNUMSIZE];
	short staff_msgstat;
} staffInfo;
/* 客户端发出的数据包 */
typedef struct ctp
{
	short cli_msgstat; /* 客户端发送的消息类型 */

	char usrid[USRID_SIZE];	   /* 客户端ID */
	char usrpasswd[USRPASSWD]; /* 客户端密码 */
	char cmd[CMD_SIZE];		   /* 客户端发出的指令 */
	staffInfo datainfo;
} CTP;

/* 服务器发出的数据包 */
typedef struct stp
{
	short ser_msgstat;			 /* 服务器返回的消息类型 */
	char identify[IDENTIFYSIZE]; /* 账号标识 */
	char backmsg[BACKMSG_SIZE];	 /* 服务器返回的消息内容 */
	staffInfo datainfo;
} STP;

#endif
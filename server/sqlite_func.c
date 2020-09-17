/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date: 2020-09-15 15:49:47
 * @LastEditTime 2020-09-17 14:41:11
 */
#include <sqlite3.h>
#include "sqlite_func.h"
#include "../include/proto.h"
#include "server_func.h"
/* 向数据库中插入数据 */
int insert_sqlite(sqlite3 *db, CTP *client_data)
{
	char *msg;
	char sql_cmd[512] = {0};

	if (client_data->cli_msgstat == REGISTER)
	{
		/* 请求注册：向accountInfo表中添加账号和密码信息 */
		sprintf(sql_cmd, "insert or ignore into accountInfo values('%s', '%s','%s');",
				client_data->usrid, client_data->usrpasswd, client_data->cmd);
		SQLITE_EXEC;
	}
	else
	{
		/* 请求插入员工信息 */
		sprintf(sql_cmd, "insert or ignore into staffInfo values('%s','%s','%s','%s','%s','%s','%s','%s');",
				client_data->datainfo.name, client_data->datainfo.address,
				client_data->datainfo.age, client_data->datainfo.phone,
				client_data->datainfo.salary, client_data->datainfo.department,
				client_data->datainfo.position, client_data->datainfo.jobnumber);
		SQLITE_EXEC;
	}
	return 0;
ERR:
	my_fprintf(" sqlite error!%s\n", msg);
	return -1;
}
/* 在数据库中修改信息 */
int modify_sqlite(sqlite3 *db, CTP *client_data)
{
	int ret = 0;
	ret = modify_sqlite_sub(db, client_data->datainfo.name, "name", client_data->datainfo.jobnumber);
	JUDGE_RET;
	ret = modify_sqlite_sub(db, client_data->datainfo.age, "age", client_data->datainfo.jobnumber);
	JUDGE_RET;
	ret = modify_sqlite_sub(db, client_data->datainfo.address, "address", client_data->datainfo.jobnumber);
	JUDGE_RET;
	ret = modify_sqlite_sub(db, client_data->datainfo.department, "department", client_data->datainfo.jobnumber);
	JUDGE_RET;
	ret = modify_sqlite_sub(db, client_data->datainfo.phone, "phone", client_data->datainfo.jobnumber);
	JUDGE_RET;
	ret = modify_sqlite_sub(db, client_data->datainfo.position, "position", client_data->datainfo.jobnumber);
	JUDGE_RET;
	ret = modify_sqlite_sub(db, client_data->datainfo.salary, "salary", client_data->datainfo.jobnumber);
	JUDGE_RET;
	return 0;
ERR:
	return -1;
}
int modify_sqlite_sub(sqlite3 *db, char *data, char *para, char *jobnumber)
{
	char *msg;
	char sql_cmd[256] = {0};
	if (strlen(data))
	{
		sprintf(sql_cmd, "update staffInfo set %s='%s' where jobnumber='%s';", para,
				data, jobnumber);
		SQLITE_EXEC;
	}
	return 0;
ERR:
	my_fprintf(" sqlite error!%s\n", msg);
	return -1;
}
/* 在数据库中删除指定信息 */
int delete_sqlite(sqlite3 *db, CTP *client_data)
{
	char *msg;
	// printf("%s,%s,%d", __FILE__, __func__, __LINE__);
	char sql_cmd[256] = {0};
	sprintf(sql_cmd, "delete from staffInfo where jobnumber='%s';", client_data->datainfo.jobnumber);
	SQLITE_EXEC;
	return 0;
ERR:
	my_fprintf(" sqlite error!%s\n", msg);
	return -1;
}
/* 在数据库中查询信息 */
int query_sqlite(sqlite3 *db, CTP *client_data, char buf[])
{
	int ret;
	char sql_cmd[256] = {0};
	char *msg;
	switch (client_data->cli_msgstat)
	{
	case LOGIN:
		sprintf(sql_cmd, "select * from accountInfo where id='%s' and passwd='%s';", client_data->usrid, client_data->usrpasswd);
		SQLITE_EXEC_BUF;
		break;
	case REGISTER:
		sprintf(sql_cmd, "select * from accountInfo where id='%s';", client_data->usrid);
		SQLITE_EXEC_BUF;
		break;
	case CMD:
		sprintf(sql_cmd, "select * from staffInfo where jobnumber='%s';", client_data->datainfo.jobnumber);
		SQLITE_EXEC_BUF;
		break;
	}
	return 0;
ERR:
	my_fprintf(" sqlite error!%s\n", msg);
	return -1;
}
/* 回调函数 */
int callback(void *para, int f_num, char **f_value, char **f_name)
{
	int i;
	/* 将查询到的内容以换行符隔开，放入para中 */
	for (i = 0; i < f_num; i++)
	{
		strcat((char *)para, "\n");
		strcat((char *)para, f_value[i]);
	}
	return 0;
}
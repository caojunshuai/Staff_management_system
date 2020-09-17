/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date 2020-09-16 11:55:38
 * @LastEditTime 2020-09-17 14:23:59
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "staffinfo_io.h"
/**
 * @brief 输入信息函数
 * @param {data} 存储输入内容的字符数组
 * @param {temp_data} 临时字符数组
 * @param {type} 打印的内容
 * @param {len} 最大长度
 * @return {void} 
 */
void input_info_sub(char *data, char *type, int len)
{
	char temp_data[128] = {0};
	do
	{
		if (strlen(temp_data) >= len)
		{
			printf("输入长度不能超过%d个字符\n", len);
		}
		printf("请输入%s:", type);
		fgets(temp_data, 128, stdin);

	} while (strlen(temp_data) > len);
	strcpy(data, temp_data);
	data[strlen(data) - 1] = 0;
}
/**
 * @brief 输入员工信息
 * @param {staff_data} 员工信息结构体指针
 * @param {option} 指明要输入哪条信息
 * @return {void} 
 */
void input_info(staffInfo *staff_data, int option)
{
	char temp_data[128] = {0};
	switch (option)
	{
	case ALL:
		input_info_sub(staff_data->name, "姓名", NAMESIZE);
		input_info_sub(staff_data->jobnumber, "工号", JOBNUMSIZE);
		input_info_sub(staff_data->age, "年龄", AGESIZE);
		input_info_sub(staff_data->phone, "电话", PHONESIZE);
		input_info_sub(staff_data->address, "住址", ADDRESSSIZE);
		input_info_sub(staff_data->position, "职位", POSITSIZE);
		input_info_sub(staff_data->department, "部门", DEPARTMENTSIZE);
		input_info_sub(staff_data->salary, "薪资", SALARYSIZE);
		break;
	case NAME:
		input_info_sub(staff_data->name, "姓名", NAMESIZE);
		break;
	case JOBNUMBER:
		input_info_sub(staff_data->jobnumber, "工号", JOBNUMSIZE);
		break;
	case AGE:
		input_info_sub(staff_data->age, "年龄", AGESIZE);
		break;
	case PHONE:
		input_info_sub(staff_data->phone, "电话", PHONESIZE);
		break;
	case ADDRESS:
		input_info_sub(staff_data->address, "住址", ADDRESSSIZE);
		break;
	case POSITION:
		input_info_sub(staff_data->position, "职位", POSITSIZE);
		break;
	case DEPARTMENT:
		input_info_sub(staff_data->department, "部门", DEPARTMENTSIZE);
		break;
	case SALARY:
		input_info_sub(staff_data->salary, "薪资", SALARYSIZE);
		break;
	}
}
void input_info_nojobnum(staffInfo *staff_data)
{
	char temp_data[128] = {0};
	input_info_sub(staff_data->name, "姓名", NAMESIZE);
	input_info_sub(staff_data->age, "年龄", AGESIZE);
	input_info_sub(staff_data->phone, "电话", PHONESIZE);
	input_info_sub(staff_data->address, "住址", ADDRESSSIZE);
	input_info_sub(staff_data->position, "职位", POSITSIZE);
	input_info_sub(staff_data->department, "部门", DEPARTMENTSIZE);
	input_info_sub(staff_data->salary, "薪资", SALARYSIZE);
}
/**
 * @brief 打印员工信息
 * @param {staff_data} 员工信息结构体指针
 * @param {option} 指明要打印哪条信息
 * @return {void} 
 */
void print_staffInfo(staffInfo *staff_data, int option)
{
	switch (option)
	{
	case ALL:
		printf("工号：%s\n", staff_data->jobnumber);
		printf("姓名：%s\n", staff_data->name);
		printf("年龄：%s\n", staff_data->age);
		printf("电话：%s\n", staff_data->phone);
		printf("地址：%s\n", staff_data->address);
		printf("职位：%s\n", staff_data->position);
		printf("部门：%s\n", staff_data->department);
		printf("薪资：%s\n", staff_data->salary);
		break;
	case NAME:
		printf("姓名：%s\n", staff_data->name);
		break;
	case JOBNUMBER:
		printf("工号：%s\n", staff_data->jobnumber);
		break;
	case AGE:
		printf("年龄：%s\n", staff_data->age);
		break;
	case PHONE:
		printf("电话：%s\n", staff_data->phone);
		break;
	case ADDRESS:
		printf("地址：%s\n", staff_data->address);
		break;
	case POSITION:
		printf("职位：%s\n", staff_data->position);
		break;
	case DEPARTMENT:
		printf("部门：%s\n", staff_data->department);
		break;
	case SALARY:
		printf("薪资：%s\n", staff_data->salary);
		break;
	}
}
void staffInfo_init(staffInfo *staff_data)
{
	memset(staff_data->address, 0, ADDRESSSIZE);
	memset(staff_data->name, 0, NAMESIZE);
	memset(staff_data->phone, 0, PHONE);
	memset(staff_data->jobnumber, 0, JOBNUMSIZE);
	memset(staff_data->position, 0, POSITSIZE);
	memset(staff_data->department, 0, DEPARTMENTSIZE);
	memset(staff_data->salary, 0, SALARYSIZE);
	memset(staff_data->age, 0, AGESIZE);
}
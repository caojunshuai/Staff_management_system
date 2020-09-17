/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date 2020-09-17 14:17:02
 * @LastEditTime 2020-09-17 16:00:46
 */
#ifndef CLIENT_FUNC_H__
#define CLIENT_FUNC_H__

#include "../include/proto.h"

/**
 * @brief 获取通信套接字 
 * @param {ip} 服务器ip地址
 * @return {int} 通信套接字 
 */
int client_init(const char ip[]);
/**
 * @brief 登录界面
 * @param {log_stat} 登录状态
 * @return {void} 
 */
void log_page(int log_stat);
/**
 * @brief 登录状态指示界面
 * @param {void} 
 * @return {void} 
 */
int log_stat_page(int log_stat, int sockfd, char *usrid);
/**
 * @brief 检查用户输入的选项是否合法
 * @param {min} 选项的最小值 
 * @param {max} 选项的最大值 
 * @return {int} 返回用户输入的选项 
 */
int sel_number(int min, int max);

/**
 * @brief 将用户在不同界面下输入的功能选项转换为main函数中对应的选项
 * @param {cli_msgstat} 客户端要发送的消息状态 
 * @param {staff_msgstat} 要对员工信息执行的操作 
 * @param {cmd} 其它指令 
 * @param {client_data} 客户端发送数据的结构体指针 
 * @return {CTP*} 返回客户端发送数据的结构体指针
 */
CTP *pakgage_clidata(short cli_msgstat, short staff_msgstat, const char cmd[], CTP *client_data);
/**
 * @brief 处理不同用户输入的选项
 * @param {sel_number} 输入的选项 
 * @param {logstat} 登录状态 
 * @return {int} 返回main函数switch中对应的选项
 */
int sel_number_pro(int logstat);
/**
 * @brief 将用户在不同界面下输入的功能选项转换为main函数中对应的选项
 * @param {sel_number} 输入的选项 
 * @param {logstat} 登录状态 
 * @return {int} 返回main函数switch中对应的选项
 */
int sel_number_switch(int sel_number, int logstat);
#endif

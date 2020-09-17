/*
 * @Descripttion: 
 * @version: V1.0
 * @Author: caojunshuai
 * @Date 2020-09-16 11:53:21
 * @LastEditTime 2020-09-17 14:24:56
 */
#ifndef STAFFINFO_IO_H__
#define STAFFINFO_IO_H__
#include "../include/proto.h"
/**
 * @brief 输入信息函数
 * @param {data} 存储输入内容的字符数组
 * @param {temp_data} 临时字符数组
 * @param {type} 打印的内容
 * @return {void} 
 */
void input_info_sub(char *data,char *type,int len);
/**
 * @brief 输入员工信息
 * @param {staff_data} 员工信息结构体指针
 * @param {option} 指明要输入哪条信息
 * @return {void} 
 */
void input_info(staffInfo *staff_data, int option);
/**
 * @brief 输入员工信息(去除工号)
 * @param {staff_data} 员工信息结构体指针
 * @param {option} 指明要输入哪条信息
 * @return {void} 
 */
void input_info_nojobnum(staffInfo *staff_data);
/**
 * @brief 打印员工信息
 * @param {staff_data} 员工信息结构体指针
 * @param {option} 指明要打印哪条信息
 * @return {void} 
 */
void print_staffInfo(staffInfo *staff_data, int option);
/**
 * @brief 初始化员工信息结构体数组
 * @param {staff_data} 员工信息结构体指针
 * @return {void} 
 */
void staffInfo_init(staffInfo *staff_data);

#endif

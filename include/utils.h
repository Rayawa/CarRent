#ifndef UTILS_H
#define UTILS_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 提供日期处理、用户输入、格式化输出、模糊匹配等通用工具函数声明
 */

#include "common.h"

/*
 * 函数作用: 获取当前系统日期，格式为YYYY-MM-DD
 * 入参: buffer - 用于存储日期字符串的缓冲区
 * 返回值: 无
 * 异常提示: 无
 */
void getCurrentDate(char* buffer);

/*
 * 函数作用: 获取当前系统日期时间，格式为YYYY-MM-DD HH:MM:SS
 * 入参: buffer - 用于存储日期时间字符串的缓冲区
 * 返回值: 无
 * 异常提示: 无
 */
void getCurrentDateTime(char* buffer);

/*
 * 函数作用: 比较两个日期字符串的大小
 * 入参: date1 - 第一个日期字符串；date2 - 第二个日期字符串
 * 返回值: date1<date2返回-1，相等返回0，date1>date2返回1
 * 异常提示: 无
 */
int compareDate(const char* date1, const char* date2);

/*
 * 函数作用: 计算两个日期间隔的天数
 * 入参: date1 - 起始日期字符串；date2 - 结束日期字符串
 * 返回值: 两个日期之间的天数差
 * 异常提示: 无
 */
int daysBetween(const char* date1, const char* date2);

/*
 * 函数作用: 验证日期字符串是否为合法日期
 * 入参: date - 待验证的日期字符串
 * 返回值: 合法返回1，非法返回0
 * 异常提示: 无
 */
int isValidDate(const char* date);

/*
 * 函数作用: 判断指定年份是否为闰年
 * 入参: year - 年份
 * 返回值: 是闰年返回1，否则返回0
 * 异常提示: 无
 */
int isLeapYear(int year);

/*
 * 函数作用: 验证日期范围是否合法，即起始日期不晚于结束日期
 * 入参: startDate - 起始日期字符串；endDate - 结束日期字符串
 * 返回值: 合法返回1，非法返回0
 * 异常提示: 无
 */
int isValidDateRange(const char* startDate, const char* endDate);

/*
 * 函数作用: 清空标准输入缓冲区
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void clearInputBuffer();

/*
 * 函数作用: 从标准输入获取一个在指定范围内的整数
 * 入参: prompt - 提示信息；min - 最小值；max - 最大值
 * 返回值: 用户输入的合法整数
 * 异常提示: 无
 */
int getIntInput(const char* prompt, int min, int max);

/*
 * 函数作用: 从标准输入获取一个在指定范围内的浮点数
 * 入参: prompt - 提示信息；min - 最小值；max - 最大值
 * 返回值: 用户输入的合法浮点数
 * 异常提示: 无
 */
double getDoubleInput(const char* prompt, double min, double max);

/*
 * 函数作用: 从标准输入获取一个字符串
 * 入参: prompt - 提示信息；buffer - 存储输入的缓冲区；maxLen - 缓冲区最大长度
 * 返回值: 无
 * 异常提示: 无
 */
void getStringInput(const char* prompt, char* buffer, int maxLen);

/*
 * 函数作用: 从标准输入获取一个在有效集合内的字符
 * 入参: prompt - 提示信息；validChars - 包含所有有效字符的字符串
 * 返回值: 用户输入的有效字符
 * 异常提示: 无
 */
char getCharInput(const char* prompt, const char* validChars);

/*
 * 函数作用: 弹出确认对话框，等待用户确认操作
 * 入参: prompt - 确认提示信息
 * 返回值: 用户确认返回1，取消返回0
 * 异常提示: 无
 */
int confirmAction(const char* prompt);

/*
 * 函数作用: 在控制台显示进度条
 * 入参: label - 进度条标签；current - 当前进度值；total - 总量
 * 返回值: 无
 * 异常提示: 无
 */
void showProgressBar(const char* label, int current, int total);

/*
 * 函数作用: 打印由指定字符组成的水平分隔线
 * 入参: ch - 用于组成分隔线的字符；count - 字符重复次数
 * 返回值: 无
 * 异常提示: 无
 */
void printSeparator(char ch, int count);

/*
 * 函数作用: 在指定宽度内居中打印文本
 * 入参: text - 待打印的文本；width - 总宽度
 * 返回值: 无
 * 异常提示: 无
 */
void printCentered(const char* text, int width);

/*
 * 函数作用: 暂停屏幕，等待用户按回车继续
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void pauseScreen();

/*
 * 函数作用: 对文本进行模糊匹配，判断是否包含指定模式
 * 入参: text - 待搜索的文本；pattern - 匹配模式
 * 返回值: 匹配成功返回1，否则返回0
 * 异常提示: 无
 */
int fuzzyMatch(const char* text, const char* pattern);

/*
 * 函数作用: 获取整数输入，提供分类错误提示
 * 入参: prompt - 提示信息；min - 最小值；max - 最大值
 * 返回值: 用户输入的合法整数
 * 异常提示: 分类提示（空输入/格式错误/数值过小/数值超出范围）
 */
int getIntInputWithHint(const char* prompt, int min, int max);

/*
 * 函数作用: 获取菜单选项输入
 * 入参: prompt - 提示信息；min - 最小值；max - 最大值
 * 返回值: 用户选择的菜单项序号
 * 异常提示: 无
 */
int getChoiceInput(const char* prompt, int min, int max);

/*
 * 函数作用: 在现有记录中查找匹配前缀的候选项，用于输入自动补全
 * 入参: hint - 已输入的前缀；target - 候选目标字符串
 * 返回值: 前缀匹配成功返回1，否则返回0
 * 异常提示: 无
 */
int matchPrefix(const char* hint, const char* target);

#endif

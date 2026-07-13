/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 工具类实现，提供日期处理、输入验证、界面辅助、模糊匹配等通用功能
 */

#include "utils.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>

/*
 * 函数作用: 获取当前系统日期，格式化为 YYYY-MM-DD
 * 入参: buffer - 字符缓冲区指针，长度至少为 MAX_DATE_LEN
 * 返回值: 无
 * 异常提示: 无
 */
void getCurrentDate(char* buffer) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    snprintf(buffer, MAX_DATE_LEN, "%04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
}

/*
 * 函数作用: 获取当前系统日期时间，格式化为 YYYY-MM-DD HH:MM:SS
 * 入参: buffer - 字符缓冲区指针，长度至少为 MAX_DATE_LEN + 12
 * 返回值: 无
 * 异常提示: 无
 */
void getCurrentDateTime(char* buffer) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    snprintf(buffer, MAX_DATE_LEN + 12, "%04d-%02d-%02d %02d:%02d:%02d",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
}

/*
 * 函数作用: 判断给定年份是否为闰年
 * 入参: year - 待判断的年份
 * 返回值: 1 表示闰年，0 表示平年
 * 异常提示: 无
 */
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/*
 * 函数作用: 验证日期字符串是否为合法的 YYYY-MM-DD 格式
 * 入参: date - 待验证的日期字符串
 * 返回值: 1 表示合法日期，0 表示不合法
 * 异常提示: 无
 */
int isValidDate(const char* date) {
    if (date == NULL) return 0;
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0; // 检查分隔符位置
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue; // 跳过分隔符位置
        if (!isdigit((unsigned char)date[i])) return 0; // 非数字字符不合法
    }
    int year = atoi(date);
    int month = atoi(date + 5);
    int day = atoi(date + 8);
    if (year < 2000 || year > 2100) return 0;
    if (month < 1 || month > 12) return 0;
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year)) daysInMonth[1] = 29; // 闰年二月有29天
    if (day < 1 || day > daysInMonth[month - 1]) return 0;
    return 1;
}

/*
 * 函数作用: 比较两个日期字符串的大小
 * 入参: date1 - 第一个日期字符串, date2 - 第二个日期字符串
 * 返回值: 负数表示 date1 < date2，0 表示相等，正数表示 date1 > date2
 * 异常提示: 无
 */
int compareDate(const char* date1, const char* date2) {
    return strcmp(date1, date2);
}

/*
 * 函数作用: 将日期字符串转换为从公元0年开始的绝对天数
 * 入参: date - 日期字符串 (YYYY-MM-DD)
 * 返回值: 从公元0年1月1日算起的绝对天数
 * 异常提示: 无
 */
static int dateToDays(const char* date) {
    int y = atoi(date);
    int m = atoi(date + 5);
    int d = atoi(date + 8);
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = 0;
    // 累加从公元0年到目标年份之前所有年份的天数
    for (int i = 0; i < y; i++) {
        days += isLeapYear(i) ? 366 : 365;
    }
    // 累加目标年份中从1月到目标月份之前所有月份的天数
    for (int i = 1; i < m; i++) {
        days += daysInMonth[i - 1];
        if (i == 2 && isLeapYear(y)) days++; // 如果当年是闰年且已过2月，额外加1天
    }
    // 加上当月已经过的天数（不含当天）
    days += d - 1;
    return days;
}

/*
 * 函数作用: 计算两个日期之间相差的天数
 * 算法: 将两个日期分别转换为绝对天数后取差值的绝对值
 * 入参: date1 - 第一个日期字符串, date2 - 第二个日期字符串
 * 返回值: 两个日期相差的天数（非负整数）
 * 异常提示: 无
 */
int daysBetween(const char* date1, const char* date2) {
    // 将两个日期转换为绝对天数
    int d1 = dateToDays(date1);
    int d2 = dateToDays(date2);
    // 返回差值的绝对值，确保结果为非负数
    return d1 > d2 ? d1 - d2 : d2 - d1;
}

/*
 * 函数作用: 验证日期区间是否合法，即开始日期不晚于结束日期
 * 入参: startDate - 开始日期, endDate - 结束日期
 * 返回值: 1 表示区间合法，0 表示不合法
 * 异常提示: 无
 */
int isValidDateRange(const char* startDate, const char* endDate) {
    return compareDate(startDate, endDate) <= 0;
}

/*
 * 函数作用: 清空标准输入缓冲区中的残留内容
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * 函数作用: 获取用户输入的整数，自动校验范围
 * 入参: prompt - 提示信息, min - 最小值, max - 最大值
 * 返回值: 用户输入的有效整数
 * 异常提示: 无
 */
int getIntInput(const char* prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
            clearInputBuffer();
            return value;
        }
        printf("输入无效，请输入 %d 到 %d 之间的整数\n", min, max);
        clearInputBuffer();
    }
}

/*
 * 函数作用: 获取用户输入的双精度浮点数，自动校验范围
 * 入参: prompt - 提示信息, min - 最小值, max - 最大值
 * 返回值: 用户输入的有效浮点数
 * 异常提示: 无
 */
double getDoubleInput(const char* prompt, double min, double max) {
    double value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &value) == 1 && value >= min && value <= max) {
            clearInputBuffer();
            return value;
        }
        printf("输入无效，请输入 %.2f 到 %.2f 之间的数值\n", min, max);
        clearInputBuffer();
    }
}

/*
 * 函数作用: 获取用户输入的字符串
 * 入参: prompt - 提示信息, buffer - 存储输入内容的缓冲区, maxLen - 缓冲区最大长度
 * 返回值: 无
 * 异常提示: 无
 */
void getStringInput(const char* prompt, char* buffer, int maxLen) {
    printf("%s", prompt);
    fgets(buffer, maxLen, stdin);
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

/*
 * 函数作用: 获取用户输入的单个字符，限定在有效字符集合内
 * 入参: prompt - 提示信息, validChars - 有效字符集合字符串
 * 返回值: 用户输入的有效字符
 * 异常提示: 无
 */
char getCharInput(const char* prompt, const char* validChars) {
    char ch;
    while (1) {
        printf("%s", prompt);
        scanf(" %c", &ch);
        clearInputBuffer();
        if (strchr(validChars, ch) != NULL) {
            return ch;
        }
        printf("输入无效，请输入 [%s] 中的一个字符\n", validChars);
    }
}

/*
 * 函数作用: 要求用户确认某个操作
 * 入参: prompt - 确认提示信息
 * 返回值: 1 表示用户确认，0 表示用户取消
 * 异常提示: 无
 */
int confirmAction(const char* prompt) {
    char ch;
    printf("%s 确认? (y/n): ", prompt);
    scanf(" %c", &ch);
    clearInputBuffer();
    return (ch == 'y' || ch == 'Y') ? 1 : 0;
}

/*
 * 函数作用: 用字符绘制一个分隔线
 * 入参: ch - 分隔线字符, count - 字符重复次数
 * 返回值: 无
 * 异常提示: 无
 */
void showProgressBar(const char* label, int current, int total) {
    if (total == 0) return;
    int percent = current * 100 / total;
    int barLen = 20;
    int filled = current * barLen / total;
    printf("%s [", label);
    for (int i = 0; i < filled; i++) printf("=");
    if (filled < barLen) printf(">");
    for (int i = filled + 1; i < barLen; i++) printf(" ");
    printf("] %d%%\n", percent);
}

/*
 * 函数作用: 用指定字符绘制一条分隔线
 * 入参: ch - 分隔线使用的字符, count - 分隔线长度
 * 返回值: 无
 * 异常提示: 无
 */
void printSeparator(char ch, int count) {
    for (int i = 0; i < count; i++) {
        putchar(ch);
    }
    putchar('\n');
}

/*
 * 函数作用: 在指定宽度内居中打印文本
 * 入参: text - 要打印的文本, width - 显示宽度
 * 返回值: 无
 * 异常提示: 无
 */
void printCentered(const char* text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    if (padding < 0) padding = 0;
    for (int i = 0; i < padding; i++) putchar(' ');
    printf("%s\n", text);
}

/*
 * 函数作用: 暂停程序执行，等待用户按回车键继续
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void pauseScreen() {
    printf("按回车键继续...");
    getchar();
}

/*
 * 函数作用: 在文本中进行不区分大小写的子串模糊匹配
 * 入参: text - 源文本, pattern - 搜索模式
 * 返回值: 1 表示匹配成功，0 表示匹配失败
 * 异常提示: 无
 */
int fuzzyMatch(const char* text, const char* pattern) {
    if (text == NULL || pattern == NULL) return 0;
    if (strlen(pattern) == 0) return 1;
    int textLen = strlen(text);
    int patLen = strlen(pattern);
    for (int i = 0; i <= textLen - patLen; i++) {
        int match = 1;
        for (int j = 0; j < patLen; j++) {
            if (tolower((unsigned char)text[i + j]) != tolower((unsigned char)pattern[j])) {
                match = 0;
                break;
            }
        }
        if (match) return 1;
    }
    return 0;
}

/*
 * 函数作用: 获取用户输入的整数并提供分类错误提示，使用 fgets+sscanf 方式解析，
 *           能区分空输入、非数字、数值过小、数值过大等不同错误类型
 * 入参: prompt - 提示信息, min - 最小值, max - 最大值
 * 返回值: 用户输入的有效整数
 * 异常提示: 无
 */
int getIntInputWithHint(const char* prompt, int min, int max) {
    int value;
    char line[256];
    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            continue;
        }
        int len = strlen(line);
        if (len <= 1) {
            printf("错误：输入不能为空，请输入有效的数值\n");
            continue;
        }
        char ch;
        if (sscanf(line, "%d %c", &value, &ch) == 1) {
            if (value < min) {
                printf("错误：数值过小，请输入 %d 到 %d 之间的数值\n", min, max);
            } else if (value > max) {
                printf("错误：数值超出范围，请输入 %d 到 %d 之间的数值\n", min, max);
            } else {
                return value;
            }
        } else {
            printf("错误：输入格式错误，请确保输入了有效的数字\n");
        }
    }
}

/*
 * 函数作用: 获取用户输入的菜单选项，基于 getIntInputWithHint 实现，
 *           提供更友好的菜单选择体验
 * 入参: prompt - 提示信息, min - 最小选项值, max - 最大选项值
 * 返回值: 用户选择的有效选项编号
 * 异常提示: 无
 */
int getChoiceInput(const char* prompt, int min, int max) {
    return getIntInputWithHint(prompt, min, max);
}

/*
 * 函数作用: 前缀匹配，判断target是否以hint开头（不区分大小写）
 * 入参: hint - 前缀模式, target - 目标字符串
 * 返回值: 匹配成功返回1，否则返回0
 * 异常提示: 无
 */
int matchPrefix(const char* hint, const char* target) {
    if (hint == NULL || target == NULL) {
        return 0;
    }
    if (strlen(hint) == 0) {
        return 0;
    }
    int hintLen = strlen(hint);
    int targetLen = strlen(target);
    if (hintLen > targetLen) {
        return 0;
    }
    for (int i = 0; i < hintLen; i++) {
        if (tolower((unsigned char)hint[i]) != tolower((unsigned char)target[i])) {
            return 0;
        }
    }
    return 1;
}

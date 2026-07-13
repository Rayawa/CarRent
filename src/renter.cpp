/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: renter data structure implementations
 */

#include "renter.h"

/*
 * 函数作用: 初始化租车人结构体，将所有字段设置为默认值
 * 入参: r - 指向待初始化的租车人结构体的指针
 * 返回值: 无
 * 异常提示: 无
 */
void initRenter(Renter* r) {
    r->id = 0;
    r->name[0] = '\0';
    r->age = 0;
    r->gender = '\0';
    r->phone[0] = '\0';
    r->licenseNo[0] = '\0';
    r->idCard[0] = '\0';
    r->drivingYears = 0;
    r->rentCount = 0;
}

/*
 * 函数作用: 以详细格式打印单个租车人的全部信息
 * 入参: r - 指向待打印的租车人结构体的指针
 * 返回值: 无
 * 异常提示: 无
 */
void renterPrint(const Renter* r) {
    printf("编号: %d\n", r->id);
    printf("姓名: %s\n", r->name);
    printf("年龄: %d\n", r->age);
    printf("性别: %c\n", r->gender);
    printf("电话: %s\n", r->phone);
    printf("驾照号: %s\n", r->licenseNo);
    printf("身份证号: %s\n", r->idCard);
    printf("驾龄: %d\n", r->drivingYears);
    printf("租车次数: %d\n", r->rentCount);
}

/*
 * 函数作用: 打印租车人列表的表头（栏位标题行）
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void renterPrintHeader() {
    printf("%-6s %-8s %-6s %-6s %-15s %-20s %-20s %-6s %-8s\n",
           "编号", "姓名", "年龄", "性别", "电话", "驾照号", "身份证号", "驾龄", "租车次数");
}

/*
 * 函数作用: 以表格行格式打印单个租车人的信息（与renterPrintHeader配合使用）
 * 入参: r - 指向待打印的租车人结构体的指针
 * 返回值: 无
 * 异常提示: 无
 */
void renterPrintRow(const Renter* r) {
    printf("%-6d %-8s %-6d %-6c %-15s %-20s %-20s %-6d %-8d\n",
           r->id,
           r->name,
           r->age,
           r->gender,
           r->phone,
           r->licenseNo,
           r->idCard,
           r->drivingYears,
           r->rentCount);
}

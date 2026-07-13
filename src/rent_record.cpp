/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: rent_record data structure implementations
 */

#include "rent_record.h"

/*
 * 函数作用: 初始化租车记录结构体，将所有字段设置为默认值
 * 入参: r - 指向待初始化的租车记录结构体的指针
 * 返回值: 无
 * 异常提示: 无
 */
void initRentRecord(RentRecord* r) {
    r->id = 0;
    r->vehicleId = 0;
    r->renterId = 0;
    r->rentDate[0] = '\0';
    r->expectedReturnDate[0] = '\0';
    r->actualReturnDate[0] = '\0';
    r->deposit = 0;
    r->dailyRate = 0;
    r->totalFee = 0;
    r->status = RENT_ACTIVE;
    r->vehicleBrand[0] = '\0';
    r->vehiclePlate[0] = '\0';
    r->renterName[0] = '\0';
    r->renterLicense[0] = '\0';
}

/*
 * 函数作用: 将租车记录状态码转换为对应的中文字符串描述
 * 入参: status - 租车记录状态码（RENT_ACTIVE / RENT_RETURNED）
 * 返回值: 状态码对应的中文字符串，未知状态返回"未知"
 * 异常提示: 无
 */
const char* rentStatusStr(int status) {
    switch (status) {
        case RENT_ACTIVE:   return "租用中"; // 租约有效，车辆尚未归还
        case RENT_RETURNED: return "已归还"; // 车辆已归还，租约结束
        default:            return "未知";   // 未知状态，理论上不会出现
    }
}

/*
 * 函数作用: 以详细格式打印单条租车记录的全部信息
 * 入参: r - 指向待打印的租车记录结构体的指针
 * 返回值: 无
 * 异常提示: 无
 */
void rentRecordPrint(const RentRecord* r) {
    printf("编号: %d\n", r->id);
    printf("车辆编号: %d\n", r->vehicleId);
    printf("租车人编号: %d\n", r->renterId);
    printf("车牌号: %s\n", r->vehiclePlate);
    printf("品牌: %s\n", r->vehicleBrand);
    printf("租车人: %s\n", r->renterName);
    printf("驾照号: %s\n", r->renterLicense);
    printf("租车日期: %s\n", r->rentDate);
    printf("预计归还: %s\n", r->expectedReturnDate);
    printf("实际归还: %s\n", r->actualReturnDate[0] ? r->actualReturnDate : "未归还");
    printf("押金: %.2f\n", r->deposit);
    printf("日租金: %.2f\n", r->dailyRate);
    printf("总费用: %.2f\n", r->totalFee);
    printf("状态: %s\n", rentStatusStr(r->status));
}

/*
 * 函数作用: 打印租车记录列表的表头（栏位标题行）
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void rentRecordPrintHeader() {
    printf("%-4s %-8s %-8s %-10s %-10s %-8s %-12s %-12s %-12s %-8s %-8s %-8s %-6s\n",
           "编号", "车辆编号", "租车人编号", "车牌号", "品牌", "租车人",
           "租车日期", "预计归还", "实际归还", "押金", "日租金", "总费用", "状态");
}

/*
 * 函数作用: 以表格行格式打印单条租车记录的信息（与rentRecordPrintHeader配合使用）
 * 入参: r - 指向待打印的租车记录结构体的指针
 * 返回值: 无
 * 异常提示: 无
 */
void rentRecordPrintRow(const RentRecord* r) {
    printf("%-4d %-8d %-8d %-10s %-10s %-8s %-12s %-12s %-12s %-8.2f %-8.2f %-8.2f %-6s\n",
           r->id,
           r->vehicleId,
           r->renterId,
           r->vehiclePlate,
           r->vehicleBrand,
           r->renterName,
           r->rentDate,
           r->expectedReturnDate,
           r->actualReturnDate[0] ? r->actualReturnDate : "",
           r->deposit,
           r->dailyRate,
           r->totalFee,
           rentStatusStr(r->status));
}

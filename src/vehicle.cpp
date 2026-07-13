/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: vehicle data structure implementations
 */

#include "vehicle.h"

/*
 * 函数作用: 初始化车辆结构体，将所有字段设置为默认值
 * 入参: v - 指向待初始化的车辆结构体的指针
 * 返回值: 无
 * 异常提示: 无
 */
void initVehicle(Vehicle* v) {
    v->id = 0;
    v->plateNo[0] = '\0';
    v->brand[0] = '\0';
    v->type[0] = '\0';
    v->color[0] = '\0';
    v->purchaseDate[0] = '\0';
    v->status = STATUS_AVAILABLE;
    v->dailyRate = 0;
    v->mileage = 0;
    v->insurance[0] = '\0';
}

/*
 * 函数作用: 将车辆状态码转换为对应的中文字符串描述
 * 入参: status - 车辆状态码（STATUS_AVAILABLE / STATUS_RENTED / STATUS_MAINTENANCE）
 * 返回值: 状态码对应的中文字符串，未知状态返回"未知"
 * 异常提示: 无
 */
const char* vehicleStatusStr(int status) {
    switch (status) {
        case STATUS_AVAILABLE:   return "可租";   // 车辆空闲，可被租赁
        case STATUS_RENTED:      return "已租";   // 车辆已被租出
        case STATUS_MAINTENANCE: return "维修";   // 车辆正在维修保养中
        default:                 return "未知";   // 未知状态，理论上不会出现
    }
}

/*
 * 函数作用: 以详细格式打印单辆车的全部信息
 * 入参: v - 指向待打印的车辆结构体的指针
 * 返回值: 无
 * 异常提示: 无
 */
void vehiclePrint(const Vehicle* v) {
    printf("编号: %d\n", v->id);
    printf("车牌号: %s\n", v->plateNo);
    printf("品牌: %s\n", v->brand);
    printf("类型: %s\n", v->type);
    printf("颜色: %s\n", v->color);
    printf("购买日期: %s\n", v->purchaseDate);
    printf("状态: %s\n", vehicleStatusStr(v->status));
    printf("日租金: %.2f\n", v->dailyRate);
    printf("里程: %.1f\n", v->mileage);
    printf("保险信息: %s\n", v->insurance);
}

/*
 * 函数作用: 打印车辆列表的表头（栏位标题行）
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void vehiclePrintHeader() {
    printf("%-4s %-10s %-10s %-10s %-8s %-12s %-6s %-8s %-10s\n",
           "编号", "车牌号", "品牌", "类型", "颜色", "购买日期", "状态", "日租金", "里程");
}

/*
 * 函数作用: 以表格行格式打印单辆车的信息（与vehiclePrintHeader配合使用）
 * 入参: v - 指向待打印的车辆结构体的指针
 * 返回值: 无
 * 异常提示: 无
 */
void vehiclePrintRow(const Vehicle* v) {
    printf("%-4d %-10s %-10s %-10s %-8s %-12s %-6s %-8.2f %-10.1f\n",
           v->id,
           v->plateNo,
           v->brand,
           v->type,
           v->color,
           v->purchaseDate,
           vehicleStatusStr(v->status),
           v->dailyRate,
           v->mileage);
}

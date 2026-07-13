#include "vehicle.h"

void vehicleInit(Vehicle* v) {
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

const char* vehicleStatusStr(int status) {
    switch (status) {
        case STATUS_AVAILABLE:   return "可租";
        case STATUS_RENTED:      return "已租";
        case STATUS_MAINTENANCE: return "维修";
        default:                 return "未知";
    }
}

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

void vehiclePrintHeader() {
    printf("%-4s %-10s %-10s %-10s %-8s %-12s %-6s %-8s %-10s\n",
           "编号", "车牌号", "品牌", "类型", "颜色", "购买日期", "状态", "日租金", "里程");
}

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

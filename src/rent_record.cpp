#include "rent_record.h"

void rentRecordInit(RentRecord* r) {
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

const char* rentStatusStr(int status) {
    switch (status) {
        case RENT_ACTIVE:   return "租用中";
        case RENT_RETURNED: return "已归还";
        default:            return "未知";
    }
}

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

void rentRecordPrintHeader() {
    printf("%-4s %-8s %-8s %-10s %-10s %-8s %-12s %-12s %-12s %-8s %-8s %-8s %-6s\n",
           "编号", "车辆编号", "租车人编号", "车牌号", "品牌", "租车人",
           "租车日期", "预计归还", "实际归还", "押金", "日租金", "总费用", "状态");
}

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

#include "receipt.h"
#include "utils.h"

void Receipt::printRentReceipt(int rentId, int vehicleId, const char* brand,
                                const char* plate, const char* type,
                                const char* renterName, const char* licenseNo,
                                const char* rentDate, const char* expectedReturnDate,
                                double deposit, double dailyRate) {
    char currentDate[32];
    getCurrentDate(currentDate);

    printf("\n");
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║       汽车租赁公司租车票据                       ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  租车编号：%-6d                                ║\n", rentId);
    printf("║  车辆编号：%-6d                                ║\n", vehicleId);
    printf("║  车辆品牌：%-20s                  ║\n", brand);
    printf("║  车牌号码：%-20s                  ║\n", plate);
    printf("║  车辆类型：%-20s                  ║\n", type);
    printf("║  租车人：  %-20s                  ║\n", renterName);
    printf("║  驾照号码：%-20s                  ║\n", licenseNo);
    printf("║  租车日期：%-20s                  ║\n", rentDate);
    printf("║  预计归还：%-20s                  ║\n", expectedReturnDate);
    printf("║  押金金额：%-10.2f 元                        ║\n", deposit);
    printf("║  日租金额：%-10.2f 元                        ║\n", dailyRate);
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  公司名称：汽车租赁有限公司                     ║\n");
    printf("║  打印日期：%-20s                  ║\n", currentDate);
    printf("╚══════════════════════════════════════════════════╝\n");
    printf("\n");
}

void Receipt::printReturnReceipt(int rentId, int vehicleId, const char* brand,
                                  const char* plate, const char* renterName,
                                  const char* rentDate, const char* returnDate,
                                  int days, double dailyRate, double deposit,
                                  double totalFee, double refund) {
    char currentDate[32];
    getCurrentDate(currentDate);

    printf("\n");
    printf("╔══════════════════════════════════════════════════╗\n");
    printf("║       汽车租赁公司退车费用收据                   ║\n");
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  租车编号：%-6d                                ║\n", rentId);
    printf("║  车辆编号：%-6d                                ║\n", vehicleId);
    printf("║  车辆品牌：%-20s                  ║\n", brand);
    printf("║  车牌号码：%-20s                  ║\n", plate);
    printf("║  租车人：  %-20s                  ║\n", renterName);
    printf("║  租车日期：%-20s                  ║\n", rentDate);
    printf("║  归还日期：%-20s                  ║\n", returnDate);
    printf("║  租用天数：%-6d 天                             ║\n", days);
    printf("║  日租金额：%-10.2f 元                        ║\n", dailyRate);
    printf("║  押金金额：%-10.2f 元                        ║\n", deposit);
    printf("║  总费用：  %-10.2f 元                        ║\n", totalFee);
    printf("║  退还金额：%-10.2f 元                        ║\n", refund);
    printf("╠══════════════════════════════════════════════════╣\n");
    printf("║  公司名称：汽车租赁有限公司                     ║\n");
    printf("║  打印日期：%-20s                  ║\n", currentDate);
    printf("╚══════════════════════════════════════════════════╝\n");
    printf("\n");
}

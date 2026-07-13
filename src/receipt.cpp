/*
 * 程序功能: 汽车租赁管理系统 - receipt implementation
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 票据生成
 */

#include "receipt.h"
#include "utils.h"

/*
 * 函数作用: 打印租车票据，显示租车编号、车辆信息、租车人、押金及日租金等详细信息
 * 入参: rentId - 租车编号
 *       vehicleId - 车辆编号
 *       brand - 车辆品牌
 *       plate - 车牌号码
 *       type - 车辆类型
 *       renterName - 租车人姓名
 *       licenseNo - 驾照号码
 *       rentDate - 租车日期
 *       expectedReturnDate - 预计归还日期
 *       deposit - 押金金额
 *       dailyRate - 日租金
 * 返回值: 无
 * 异常提示: 无
 */
void Receipt::printRentReceipt(int rentId, int vehicleId, const char* brand,
                                const char* plate, const char* type,
                                const char* renterName, const char* licenseNo,
                                const char* rentDate, const char* expectedReturnDate,
                                double deposit, double dailyRate) {
    // 票据打印: 租车票据
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

/*
 * 函数作用: 打印退车费用收据，显示租车编号、车辆信息、租用天数、总费用及退还金额等结算明细
 * 入参: rentId - 租车编号
 *       vehicleId - 车辆编号
 *       brand - 车辆品牌
 *       plate - 车牌号码
 *       renterName - 租车人姓名
 *       rentDate - 租车日期
 *       returnDate - 实际归还日期
 *       days - 租用天数
 *       dailyRate - 日租金
 *       deposit - 押金金额
 *       totalFee - 总费用
 *       refund - 退还金额（押金 - 总费用）
 * 返回值: 无
 * 异常提示: 无
 */
void Receipt::printReturnReceipt(int rentId, int vehicleId, const char* brand,
                                  const char* plate, const char* renterName,
                                  const char* rentDate, const char* returnDate,
                                  int days, double dailyRate, double deposit,
                                  double totalFee, double refund) {
    // 票据打印: 退车票据
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

#ifndef RECEIPT_H
#define RECEIPT_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 提供打印租车小票和还车小票的功能
 */

#include "common.h"

class Receipt {
public:
    /*
     * 函数作用: 打印租车小票，显示租车详细信息
     * 入参: rentId - 租赁编号；vehicleId - 车辆编号；brand - 品牌；
     *       plate - 车牌号；type - 车辆类型；renterName - 租车人姓名；
     *       licenseNo - 驾照号；rentDate - 租车日期；
     *       expectedReturnDate - 预计归还日期；deposit - 押金；dailyRate - 日租金
     * 返回值: 无
     * 异常提示: 无
     */
    static void printRentReceipt(int rentId, int vehicleId, const char* brand,
                                  const char* plate, const char* type,
                                  const char* renterName, const char* licenseNo,
                                  const char* rentDate, const char* expectedReturnDate,
                                  double deposit, double dailyRate);

    /*
     * 函数作用: 打印还车小票，显示还车结算信息
     * 入参: rentId - 租赁编号；vehicleId - 车辆编号；brand - 品牌；
     *       plate - 车牌号；renterName - 租车人姓名；rentDate - 租车日期；
     *       returnDate - 归还日期；days - 租车天数；dailyRate - 日租金；
     *       deposit - 押金；totalFee - 总费用；refund - 退款金额
     * 返回值: 无
     * 异常提示: 无
     */
    static void printReturnReceipt(int rentId, int vehicleId, const char* brand,
                                    const char* plate, const char* renterName,
                                    const char* rentDate, const char* returnDate,
                                    int days, double dailyRate, double deposit,
                                    double totalFee, double refund);
};

#endif

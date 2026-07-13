#ifndef RECEIPT_H
#define RECEIPT_H

#include "common.h"

class Receipt {
public:
    static void printRentReceipt(int rentId, int vehicleId, const char* brand,
                                  const char* plate, const char* type,
                                  const char* renterName, const char* licenseNo,
                                  const char* rentDate, const char* expectedReturnDate,
                                  double deposit, double dailyRate);
    static void printReturnReceipt(int rentId, int vehicleId, const char* brand,
                                    const char* plate, const char* renterName,
                                    const char* rentDate, const char* returnDate,
                                    int days, double dailyRate, double deposit,
                                    double totalFee, double refund);
};

#endif

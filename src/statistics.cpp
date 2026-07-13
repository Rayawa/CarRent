#include "statistics.h"
#include "vehicle_manager.h"
#include "renter_manager.h"
#include "rent_manager.h"
#include "utils.h"

void Statistics::showDashboard(VehicleManager* vm, RenterManager* rm, RentManager* rentm) {
    printSeparator('=', 60);
    printCentered("系统仪表盘", 60);
    printSeparator('=', 60);

    char now[64];
    getCurrentDateTime(now);
    printf("  当前时间: %s\n\n", now);

    printf("  ─── 车辆概况 ───\n");
    printf("    总车辆数: %d\n", vm->getTotalCount());
    printf("    可租车辆: %d\n", vm->getAvailableCount());
    printf("    已租车辆: %d\n", vm->getRentedCount());

    printf("\n  ─── 租客概况 ───\n");
    printf("    租客总数: %d\n", rm->getTotalCount());

    printf("\n  ─── 租赁概况 ───\n");
    printf("    进行中租赁: %d\n", rentm->getActiveCount());
    printf("    总营收: %.2f 元\n", rentm->getTotalRevenue());

    printSeparator('=', 60);
}

void Statistics::showVehicleBarChart(VehicleManager* vm) {
    struct BrandCount {
        char name[MAX_BRAND_LEN];
        int count;
    };
    BrandCount brands[100];
    int brandCount = 0;

    LinkedList<Vehicle>* vehicles = vm->getAllVehicles();
    ListNode<Vehicle>* node = vehicles->getHead();
    while (node != nullptr) {
        const char* brand = node->data.brand;
        bool found = false;
        for (int i = 0; i < brandCount; i++) {
            if (strcmp(brands[i].name, brand) == 0) {
                brands[i].count++;
                found = true;
                break;
            }
        }
        if (!found && brandCount < 100) {
            strncpy(brands[brandCount].name, brand, MAX_BRAND_LEN - 1);
            brands[brandCount].name[MAX_BRAND_LEN - 1] = '\0';
            brands[brandCount].count = 1;
            brandCount++;
        }
        node = node->next;
    }

    if (brandCount == 0) {
        printf("\n暂无数据\n");
        return;
    }

    int maxCount = 0;
    for (int i = 0; i < brandCount; i++) {
        if (brands[i].count > maxCount) {
            maxCount = brands[i].count;
        }
    }

    printf("\n");
    printCentered("车辆品牌分布图", 60);
    printSeparator('-', 60);

    for (int i = 0; i < brandCount; i++) {
        int barLen = (brands[i].count * 40) / maxCount;
        if (barLen == 0 && brands[i].count > 0) {
            barLen = 1;
        }
        printf("  %-12s | ", brands[i].name);
        for (int j = 0; j < barLen; j++) {
            printf("█");
        }
        printf(" %d\n", brands[i].count);
    }
    printSeparator('-', 60);
}

void Statistics::showRentTrendChart(RentManager* rentm) {
    time_t now = time(nullptr);
    int dailyCounts[7] = {0};
    char dateLabels[7][MAX_DATE_LEN];

    for (int i = 0; i < 7; i++) {
        time_t dayTime = now - (6 - i) * 86400;
        struct tm* dayTm = localtime(&dayTime);
        snprintf(dateLabels[i], MAX_DATE_LEN, "%04d-%02d-%02d",
                 dayTm->tm_year + 1900, dayTm->tm_mon + 1, dayTm->tm_mday);
    }

    LinkedList<RentRecord>* records = rentm->getAllRentRecords();
    ListNode<RentRecord>* node = records->getHead();
    while (node != nullptr) {
        for (int i = 0; i < 7; i++) {
            if (strcmp(node->data.rentDate, dateLabels[i]) == 0) {
                dailyCounts[i]++;
                break;
            }
        }
        node = node->next;
    }

    int maxCount = 0;
    for (int i = 0; i < 7; i++) {
        if (dailyCounts[i] > maxCount) {
            maxCount = dailyCounts[i];
        }
    }

    printf("\n");
    printCentered("近7日租赁趋势图", 60);
    printSeparator('-', 60);

    if (maxCount == 0) {
        printf("  暂无数据\n");
    } else {
        for (int i = 0; i < 7; i++) {
            int barLen = (dailyCounts[i] * 40) / maxCount;
            if (barLen == 0 && dailyCounts[i] > 0) {
                barLen = 1;
            }
            printf("  %s | ", dateLabels[i]);
            for (int j = 0; j < barLen; j++) {
                printf("█");
            }
            printf(" %d\n", dailyCounts[i]);
        }
    }
    printSeparator('-', 60);
}

void Statistics::showRentTypeBarChart(RentManager* rentm) {
    struct BrandCount {
        char name[MAX_BRAND_LEN];
        int count;
    };
    BrandCount brands[100];
    int brandCount = 0;

    LinkedList<RentRecord>* records = rentm->getAllRentRecords();
    ListNode<RentRecord>* node = records->getHead();
    while (node != nullptr) {
        const char* brand = node->data.vehicleBrand;
        bool found = false;
        for (int i = 0; i < brandCount; i++) {
            if (strcmp(brands[i].name, brand) == 0) {
                brands[i].count++;
                found = true;
                break;
            }
        }
        if (!found && brandCount < 100) {
            strncpy(brands[brandCount].name, brand, MAX_BRAND_LEN - 1);
            brands[brandCount].name[MAX_BRAND_LEN - 1] = '\0';
            brands[brandCount].count = 1;
            brandCount++;
        }
        node = node->next;
    }

    if (brandCount == 0) {
        printf("\n暂无数据\n");
        return;
    }

    int maxCount = 0;
    for (int i = 0; i < brandCount; i++) {
        if (brands[i].count > maxCount) {
            maxCount = brands[i].count;
        }
    }

    printf("\n");
    printCentered("租赁车型分布图", 60);
    printSeparator('-', 60);

    for (int i = 0; i < brandCount; i++) {
        int barLen = (brands[i].count * 40) / maxCount;
        if (barLen == 0 && brands[i].count > 0) {
            barLen = 1;
        }
        printf("  %-12s | ", brands[i].name);
        for (int j = 0; j < barLen; j++) {
            printf("█");
        }
        printf(" %d\n", brands[i].count);
    }
    printSeparator('-', 60);
}

void Statistics::showRevenueChart(RentManager* rentm) {
    time_t now = time(nullptr);
    double dailyRevenue[7] = {0};
    char dateLabels[7][MAX_DATE_LEN];

    for (int i = 0; i < 7; i++) {
        time_t dayTime = now - (6 - i) * 86400;
        struct tm* dayTm = localtime(&dayTime);
        snprintf(dateLabels[i], MAX_DATE_LEN, "%04d-%02d-%02d",
                 dayTm->tm_year + 1900, dayTm->tm_mon + 1, dayTm->tm_mday);
    }

    LinkedList<RentRecord>* records = rentm->getAllRentRecords();
    ListNode<RentRecord>* node = records->getHead();
    while (node != nullptr) {
        if (node->data.status == RENT_RETURNED && strlen(node->data.actualReturnDate) > 0) {
            for (int i = 0; i < 7; i++) {
                if (strcmp(node->data.actualReturnDate, dateLabels[i]) == 0) {
                    dailyRevenue[i] += node->data.totalFee;
                    break;
                }
            }
        }
        node = node->next;
    }

    double maxRevenue = 0;
    for (int i = 0; i < 7; i++) {
        if (dailyRevenue[i] > maxRevenue) {
            maxRevenue = dailyRevenue[i];
        }
    }

    printf("\n");
    printCentered("近7日营收趋势图", 60);
    printSeparator('-', 60);

    if (maxRevenue == 0) {
        printf("  暂无数据\n");
    } else {
        for (int i = 0; i < 7; i++) {
            int barLen = (int)((dailyRevenue[i] * 40) / maxRevenue);
            if (barLen == 0 && dailyRevenue[i] > 0) {
                barLen = 1;
            }
            printf("  %s | ", dateLabels[i]);
            for (int j = 0; j < barLen; j++) {
                printf("█");
            }
            printf(" %.2f\n", dailyRevenue[i]);
        }
    }
    printSeparator('-', 60);
}

/*
 * 程序功能: 汽车租赁管理系统 - 命令行交互界面
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 提供完整的命令行交互界面，管理所有菜单导航、业务操作入口、用户输入处理及结果展示
 */

#include "ui.h"
#include "utils.h"
#include "receipt.h"
#include "statistics.h"
#include "logger.h"

/*
 * 函数作用: 导出车辆信息到文件报表
 * 入参: fp - 已打开的文件指针；vehicleManager - 车辆管理器引用
 * 返回值: 无
 * 异常提示: 无
 */
static void exportVehiclesToFile(FILE* fp, VehicleManager& vehicleManager) {
    fprintf(fp, "===== 车辆信息 =====\n\n");
    LinkedList<Vehicle>* vehicles = vehicleManager.getAllVehicles();
    ListNode<Vehicle>* vNode = vehicles->getHead();
    while (vNode != nullptr) {
        fprintf(fp, "车辆编号: %d\n", vNode->data.id);
        fprintf(fp, "车牌号码: %s\n", vNode->data.plateNo);
        fprintf(fp, "车辆品牌: %s\n", vNode->data.brand);
        fprintf(fp, "车辆类型: %s\n", vNode->data.type);
        fprintf(fp, "车辆颜色: %s\n", vNode->data.color);
        fprintf(fp, "购买日期: %s\n", vNode->data.purchaseDate);
        fprintf(fp, "车辆状态: %s\n", vehicleStatusStr(vNode->data.status));
        fprintf(fp, "日租金额: %.2f\n", vNode->data.dailyRate);
        fprintf(fp, "行驶里程: %.2f\n", vNode->data.mileage);
        fprintf(fp, "保险信息: %s\n", vNode->data.insurance);
        fprintf(fp, "------------------------------\n");
        vNode = vNode->next;
    }
}

/*
 * 函数作用: 导出租车用户信息到文件报表
 * 入参: fp - 已打开的文件指针；renterManager - 租车用户管理器引用
 * 返回值: 无
 * 异常提示: 无
 */
static void exportRentersToFile(FILE* fp, RenterManager& renterManager) {
    fprintf(fp, "\n===== 租车用户信息 =====\n\n");
    LinkedList<Renter>* renters = renterManager.getAllRenters();
    ListNode<Renter>* rNode = renters->getHead();
    while (rNode != nullptr) {
        fprintf(fp, "用户编号: %d\n", rNode->data.id);
        fprintf(fp, "姓名: %s\n", rNode->data.name);
        fprintf(fp, "年龄: %d\n", rNode->data.age);
        fprintf(fp, "性别: %c\n", rNode->data.gender);
        fprintf(fp, "手机: %s\n", rNode->data.phone);
        fprintf(fp, "驾照: %s\n", rNode->data.licenseNo);
        fprintf(fp, "身份证: %s\n", rNode->data.idCard);
        fprintf(fp, "驾龄: %d年\n", rNode->data.drivingYears);
        fprintf(fp, "租车次数: %d\n", rNode->data.rentCount);
        fprintf(fp, "------------------------------\n");
        rNode = rNode->next;
    }
}

/*
 * 函数作用: 导出租车记录信息到文件报表
 * 入参: fp - 已打开的文件指针；rentManager - 租车管理器引用
 * 返回值: 无
 * 异常提示: 无
 */
static void exportRentRecordsToFile(FILE* fp, RentManager& rentManager) {
    fprintf(fp, "\n===== 租车记录 =====\n\n");
    LinkedList<RentRecord>* records = rentManager.getAllRentRecords();
    ListNode<RentRecord>* recNode = records->getHead();
    while (recNode != nullptr) {
        fprintf(fp, "租车编号: %d\n", recNode->data.id);
        fprintf(fp, "车辆编号: %d\n", recNode->data.vehicleId);
        fprintf(fp, "车辆品牌: %s\n", recNode->data.vehicleBrand);
        fprintf(fp, "车牌号: %s\n", recNode->data.vehiclePlate);
        fprintf(fp, "用户编号: %d\n", recNode->data.renterId);
        fprintf(fp, "用户姓名: %s\n", recNode->data.renterName);
        fprintf(fp, "租车日期: %s\n", recNode->data.rentDate);
        fprintf(fp, "预计归还: %s\n", recNode->data.expectedReturnDate);
        fprintf(fp, "实际归还: %s\n", recNode->data.actualReturnDate);
        fprintf(fp, "押金: %.2f\n", recNode->data.deposit);
        fprintf(fp, "日租金: %.2f\n", recNode->data.dailyRate);
        fprintf(fp, "总费用: %.2f\n", recNode->data.totalFee);
        fprintf(fp, "状态: %s\n", rentStatusStr(recNode->data.status));
        fprintf(fp, "------------------------------\n");
        recNode = recNode->next;
    }
}

/*
 * 函数作用: 导出统计汇总数据到文件报表
 * 入参: fp - 已打开的文件指针；vehicleManager - 车辆管理器引用；
 *       renterManager - 租车用户管理器引用；rentManager - 租车管理器引用
 * 返回值: 无
 * 异常提示: 无
 */
static void exportStatisticsToFile(FILE* fp, VehicleManager& vehicleManager,
                                    RenterManager& renterManager, RentManager& rentManager) {
    fprintf(fp, "\n===== 统计汇总 =====\n\n");
    fprintf(fp, "车辆总数: %d\n", vehicleManager.getTotalCount());
    fprintf(fp, "可租车辆: %d\n", vehicleManager.getAvailableCount());
    fprintf(fp, "已租车辆: %d\n", vehicleManager.getRentedCount());
    fprintf(fp, "用户总数: %d\n", renterManager.getTotalCount());
    fprintf(fp, "租车记录: %d\n", rentManager.getTotalCount());
    fprintf(fp, "进行中: %d\n", rentManager.getActiveCount());
    fprintf(fp, "总收入: %.2f 元\n", rentManager.getTotalRevenue());
}

/*
 * 函数作用: 辅助输入修改字符串字段，提示原值并接收新值
 * 入参: label - 字段标签；field - 待修改的字符串缓冲区；maxLen - 缓冲区最大长度
 * 返回值: 无
 * 异常提示: 无
 */
static void modifyStringFieldPrompt(const char* label, char* field, int maxLen) {
    char temp[256];
    printf("%s [%s]: ", label, field);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') {
            temp[len - 1] = '\0';
        }
        if (temp[0] != '\0') {
            strncpy(field, temp, maxLen - 1);
            field[maxLen - 1] = '\0';
        }
    }
}

/*
 * 函数作用: 辅助输入修改浮点数字段，提示原值并接收新值
 * 入参: label - 字段标签；field - 待修改的浮点数指针
 * 返回值: 无
 * 异常提示: 无
 */
static void modifyDoubleFieldPrompt(const char* label, double* field) {
    char temp[256];
    printf("%s [%.2f]: ", label, *field);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        double val = atof(temp);
        if (val >= 0) {
            *field = val;
        }
    }
}

/*
 * 函数作用: 辅助输入修改整数字段，提示原值并接收新值
 * 入参: label - 字段标签；field - 待修改的整数指针
 * 返回值: 无
 * 异常提示: 无
 */
static void modifyIntFieldPrompt(const char* label, int* field) {
    char temp[256];
    printf("%s [%d]: ", label, *field);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        int val = atoi(temp);
        *field = val;
    }
}

/*
 * 函数作用: 构造UI界面对象，初始化各管理器
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
UI::UI() {
    running = true;
}

/*
 * 函数作用: 显示系统Banner横幅
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::showBanner() {
    printf("\n\n");
    printf("  ╔══════════════════════════════════════════════╗\n");
    printf("  ║                                              ║\n");
    printf("  ║             汽车租赁管理系统                    ║\n");
    printf("  ║       Car Rental Management System           ║\n");
    printf("  ║                                              ║\n");
    printf("  ╚══════════════════════════════════════════════╝\n");
    printf("\n");
}

/*
 * 函数作用: 启动程序主循环，进入主菜单
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::run() {
    if (!authManager.login()) {
        printf("\n登录失败，程序退出\n");
        return;
    }

    showBanner();
    while (running) {
        mainMenu();
    }
}

/*
 * 函数作用: 显示主菜单并处理导航选择
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::mainMenu() {
    printSeparator('=', 60);
    printf("╔══════════════ 汽车租赁管理系统 ══════════════╗\n");
    printf("║  1. 车辆信息管理                            ║\n");
    printf("║  2. 租车用户信息管理                         ║\n");
    printf("║  3. 租车业务办理                            ║\n");
    printf("║  4. 退车业务办理                            ║\n");
    printf("║  5. 信息查询                                ║\n");
    printf("║  6. 统计汇总                                ║\n");
    printf("║  7. 输出全部信息                            ║\n");
    printf("║  8. 系统设置                                ║\n");
    printf("║  9. 扩展功能                                ║\n");
    printf("║  0. 退出系统                                ║\n");
    printf("╚════════════════════════════════════════════╝\n");

    int choice = getChoiceInput("请选择操作 [0-9]: ", 0, 9);

    showProgressBar("正在加载", 0, 100);
    showProgressBar("正在加载", 100, 100);

    switch (choice) {
        case 1: vehicleMenu(); break;
        case 2: renterMenu(); break;
        case 3: rentMenu(); break;
        case 4: returnMenu(); break;
        case 5: queryMenu(); break;
        case 6: statisticsMenu(); break;
        case 7:
            printf("\n");
            printCentered("===== 全部车辆信息 =====", 60);
            handleListVehicles();
            printf("\n");
            printCentered("===== 全部租车用户信息 =====", 60);
            handleListRenters();
            printf("\n");
            printCentered("===== 全部租车记录 =====", 60);
            handleListRentRecords();
            pauseScreen();
            break;
        case 8: systemMenu(); break;
        case 9: extendedMenu(); break;
        case 0:
            printf("\n感谢使用，再见！\n");
            running = false;
            break;
    }
}

/*
 * 函数作用: 显示车辆管理子菜单并处理导航选择
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::vehicleMenu() {
    while (true) {
        printSeparator('=', 60);
        printCentered("车辆信息管理", 60);
        printSeparator('=', 60);
        printf("  1. 添加车辆信息\n");
        printf("  2. 删除车辆信息\n");
        printf("  3. 修改车辆信息\n");
        printf("  4. 显示所有车辆\n");
        printf("  0. 返回主菜单\n");
        printSeparator('=', 60);

        int choice = getChoiceInput("请选择操作 [0-4]: ", 0, 4);

        showProgressBar("正在加载", 0, 100);
        showProgressBar("正在加载", 100, 100);

        switch (choice) {
            case 1: handleAddVehicle(); break;
            case 2: handleDeleteVehicle(); break;
            case 3: handleModifyVehicle(); break;
            case 4: handleListVehicles(); break;
            case 0: return;
        }
    }
}

/*
 * 函数作用: 显示租车人管理子菜单并处理导航选择
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::renterMenu() {
    while (true) {
        printSeparator('=', 60);
        printCentered("租车用户信息管理", 60);
        printSeparator('=', 60);
        printf("  1. 添加租车用户\n");
        printf("  2. 删除租车用户\n");
        printf("  3. 修改租车用户\n");
        printf("  4. 显示所有用户\n");
        printf("  0. 返回主菜单\n");
        printSeparator('=', 60);

        int choice = getChoiceInput("请选择操作 [0-4]: ", 0, 4);

        showProgressBar("正在加载", 0, 100);
        showProgressBar("正在加载", 100, 100);

        switch (choice) {
            case 1: handleAddRenter(); break;
            case 2: handleDeleteRenter(); break;
            case 3: handleModifyRenter(); break;
            case 4: handleListRenters(); break;
            case 0: return;
        }
    }
}

/*
 * 函数作用: 显示租车操作子菜单并处理导航选择
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::rentMenu() {
    while (true) {
        printSeparator('=', 60);
        printCentered("租车业务办理", 60);
        printSeparator('=', 60);
        printf("  1. 办理租车\n");
        printf("  2. 显示所有租车记录\n");
        printf("  3. 打印票据\n");
        printf("  0. 返回主菜单\n");
        printSeparator('=', 60);

        int choice = getChoiceInput("请选择操作 [0-3]: ", 0, 3);

        showProgressBar("正在加载", 0, 100);
        showProgressBar("正在加载", 100, 100);

        switch (choice) {
            case 1: handleRentVehicle(); break;
            case 2: handleListRentRecords(); break;
            case 3: handlePrintReceipt(); break;
            case 0: return;
        }
    }
}

/*
 * 函数作用: 显示还车操作子菜单并处理导航选择
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::returnMenu() {
    while (true) {
        printSeparator('=', 60);
        printCentered("退车业务办理", 60);
        printSeparator('=', 60);
        printf("  1. 办理退车\n");
        printf("  2. 显示所有租车记录\n");
        printf("  3. 打印票据\n");
        printf("  0. 返回主菜单\n");
        printSeparator('=', 60);

        int choice = getChoiceInput("请选择操作 [0-3]: ", 0, 3);

        showProgressBar("正在加载", 0, 100);
        showProgressBar("正在加载", 100, 100);

        switch (choice) {
            case 1: handleReturnVehicle(); break;
            case 2: handleListRentRecords(); break;
            case 3: handlePrintReceipt(); break;
            case 0: return;
        }
    }
}

/*
 * 函数作用: 显示查询子菜单并处理导航选择
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::queryMenu() {
    while (true) {
        printSeparator('=', 60);
        printCentered("信息查询", 60);
        printSeparator('=', 60);
        printf("  1. 车辆查询\n");
        printf("  2. 租车用户查询\n");
        printf("  3. 租车记录查询\n");
        printf("  4. 模糊搜索\n");
        printf("  0. 返回主菜单\n");
        printSeparator('=', 60);

        int choice = getChoiceInput("请选择操作 [0-4]: ", 0, 4);

        showProgressBar("正在加载", 0, 100);
        showProgressBar("正在加载", 100, 100);

        switch (choice) {
            case 1: handleQueryVehicles(); break;
            case 2: handleQueryRenters(); break;
            case 3: handleQueryRentRecords(); break;
            case 4: handleFuzzySearch(); break;
            case 0: return;
        }
    }
}

/*
 * 函数作用: 显示统计子菜单并处理导航选择
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::statisticsMenu() {
    while (true) {
        printSeparator('=', 60);
        printCentered("统计汇总", 60);
        printSeparator('=', 60);
        printf("  1. 车辆统计\n");
        printf("  2. 租车用户统计\n");
        printf("  3. 租车记录统计\n");
        printf("  4. 数据看板\n");
        printf("  5. 统计图表\n");
        printf("  0. 返回主菜单\n");
        printSeparator('=', 60);

        int choice = getChoiceInput("请选择操作 [0-5]: ", 0, 5);

        showProgressBar("正在加载", 0, 100);
        showProgressBar("正在加载", 100, 100);

        switch (choice) {
            case 1: handleVehicleStatistics(); break;
            case 2: handleRenterStatistics(); break;
            case 3: handleRentStatistics(); break;
            case 4:
                Statistics::showDashboard(&vehicleManager, &renterManager, &rentManager);
                pauseScreen();
                break;
            case 5: {
                printf("\n  1. 车辆品牌柱状图\n");
                printf("  2. 租车趋势图\n");
                printf("  3. 租车类型饼图\n");
                printf("  4. 收入走势图\n");
                int chartChoice = getChoiceInput("请选择图表 [1-4]: ", 1, 4);
                showProgressBar("正在加载", 0, 100);
                showProgressBar("正在加载", 100, 100);
                switch (chartChoice) {
                    case 1: Statistics::showVehicleBarChart(&vehicleManager); break;
                    case 2: Statistics::showRentTrendChart(&rentManager); break;
                    case 3: Statistics::showRentTypeBarChart(&rentManager); break;
                    case 4: Statistics::showRevenueChart(&rentManager); break;
                }
                pauseScreen();
                break;
            }
            case 0: return;
        }
    }
}

/*
 * 函数作用: 显示系统管理子菜单并处理导航选择
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::systemMenu() {
    while (true) {
        printSeparator('=', 60);
        printCentered("系统设置", 60);
        printSeparator('=', 60);
        printf("  1. 修改密码\n");
        printf("  2. 导出报表\n");
        printf("  3. 查看日志\n");
        printf("  4. 清空数据\n");
        printf("  0. 返回主菜单\n");
        printSeparator('=', 60);

        int choice = getChoiceInput("请选择操作 [0-4]: ", 0, 4);

        showProgressBar("正在加载", 0, 100);
        showProgressBar("正在加载", 100, 100);

        switch (choice) {
            case 1: handleChangePassword(); break;
            case 2: handleExportReport(); break;
            case 3: handleViewLog(); break;
            case 4: handleClearData(); break;
            case 0: return;
        }
    }
}

/*
 * 函数作用: 显示扩展功能子菜单并处理导航选择
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::extendedMenu() {
    while (true) {
        printSeparator('=', 60);
        printCentered("扩展功能", 60);
        printSeparator('=', 60);
        printf("  1. 数据可视化图表\n");
        printf("  2. 导出报表\n");
        printf("  3. 查看日志\n");
        printf("  4. 清空全部测试数据\n");
        printf("  5. 模糊搜索\n");
        printf("  6. 分页查询\n");
        printf("  7. 车辆动态状态图\n");
        printf("  8. 统计对比柱状图\n");
        printf("  0. 返回主菜单\n");
        printSeparator('=', 60);

        int choice = getChoiceInput("请选择操作 [0-8]: ", 0, 8);

        showProgressBar("正在加载", 0, 100);
        showProgressBar("正在加载", 100, 100);

        switch (choice) {
            case 1: {
                printf("\n  1. 车辆品牌柱状图\n");
                printf("  2. 租车趋势图\n");
                printf("  3. 租车类型饼图\n");
                printf("  4. 收入走势图\n");
                int chartChoice = getChoiceInput("请选择图表 [1-4]: ", 1, 4);
                showProgressBar("正在加载", 0, 100);
                showProgressBar("正在加载", 100, 100);
                switch (chartChoice) {
                    case 1: Statistics::showVehicleBarChart(&vehicleManager); break;
                    case 2: Statistics::showRentTrendChart(&rentManager); break;
                    case 3: Statistics::showRentTypeBarChart(&rentManager); break;
                    case 4: Statistics::showRevenueChart(&rentManager); break;
                }
                pauseScreen();
                break;
            }
            case 2: handleExportReport(); break;
            case 3: handleViewLog(); break;
            case 4: handleClearData(); break;
            case 5: handleFuzzySearch(); break;
            case 6: handlePaginatedRentRecords(); break;
            case 7: showVehicleDynamicDisplay(); break;
            case 8: showComparisonBarChart(); break;
            case 0: return;
        }
    }
}

/*
 * 函数作用: 检查车牌号是否已存在
 * 入参: plateNo - 待检查的车牌号
 * 返回值: 存在重复返回1，否则返回0
 * 异常提示: 无
 */
int UI::checkDuplicateVehicleByPlate(const char* plateNo) {
    LinkedList<Vehicle>* list = vehicleManager.getAllVehicles();
    /* 动态链表操作: 遍历车辆链表 */
    ListNode<Vehicle>* node = list->getHead();
    while (node != nullptr) {
        /* 数据校验: 比较车牌号 */
        if (strcmp(node->data.plateNo, plateNo) == 0) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

/*
 * 函数作用: 检查驾照号是否已存在
 * 入参: licenseNo - 待检查的驾照号
 * 返回值: 存在重复返回1，否则返回0
 * 异常提示: 无
 */
int UI::checkDuplicateRenterByLicense(const char* licenseNo) {
    LinkedList<Renter>* list = renterManager.getAllRenters();
    /* 动态链表操作: 遍历租车用户链表 */
    ListNode<Renter>* node = list->getHead();
    while (node != nullptr) {
        /* 数据校验: 比较驾照号 */
        if (strcmp(node->data.licenseNo, licenseNo) == 0) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

/*
 * 函数作用: 显示车辆情况动态状态图
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::showVehicleDynamicDisplay() {
    printSeparator('=', 70);
    printCentered("车辆动态状态图", 70);
    printSeparator('=', 70);

    LinkedList<Vehicle>* list = vehicleManager.getAllVehicles();
    if (list->isEmpty()) {
        printf("\n暂无车辆信息\n");
        return;
    }

    int countAvail = 0;
    int countRented = 0;
    int countMaint = 0;

    /* 动态链表操作: 遍历车辆链表统计状态 */
    ListNode<Vehicle>* node = list->getHead();
    while (node != nullptr) {
        if (node->data.status == STATUS_AVAILABLE) {
            countAvail++;
        }
        else if (node->data.status == STATUS_RENTED) {
            countRented++;
        }
        else if (node->data.status == STATUS_MAINTENANCE) {
            countMaint++;
        }
        node = node->next;
    }

    printf("\n");
    printf("  可租车辆: %d 辆  |  已租车辆: %d 辆  |  维修中: %d 辆  |  总计: %d 辆\n",
           countAvail, countRented, countMaint, list->size());
    printf("\n");

    /* 交互处理: 分组显示车辆状态 */
    printf("--- 可租车辆 (%d) ---\n", countAvail);
    node = list->getHead();
    while (node != nullptr) {
        if (node->data.status == STATUS_AVAILABLE) {
            printf("  [编号:%d 车牌:%s 状态:可租]\n",
                   node->data.id, node->data.plateNo);
        }
        node = node->next;
    }

    printf("\n--- 已租车辆 (%d) ---\n", countRented);
    node = list->getHead();
    while (node != nullptr) {
        if (node->data.status == STATUS_RENTED) {
            printf("  [编号:%d 车牌:%s 状态:已租]\n",
                   node->data.id, node->data.plateNo);
        }
        node = node->next;
    }

    printf("\n--- 维修中车辆 (%d) ---\n", countMaint);
    node = list->getHead();
    while (node != nullptr) {
        if (node->data.status == STATUS_MAINTENANCE) {
            printf("  [编号:%d 车牌:%s 状态:维修]\n",
                   node->data.id, node->data.plateNo);
        }
        node = node->next;
    }

    printSeparator('=', 70);
}

/*
 * 函数作用: 显示统计对比柱状图
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::showComparisonBarChart() {
    printSeparator('=', 70);
    printCentered("统计对比柱状图", 70);
    printSeparator('=', 70);

    printf("\n  %-20s  %-20s\n", "车辆品牌分布", "租赁品牌分布");
    printf("  %-20s  %-20s\n", "--------------------", "--------------------");

    const char* brands[] = {"丰田", "本田", "大众", "宝马", "奔驰", "奥迪", "福特", "现代", "日产", "别克"};
    int brandCount = 10;

    for (int i = 0; i < brandCount; i++) {
        int vehicleCount = vehicleManager.countByBrand(brands[i]);
        int rentCount = rentManager.countByBrand(brands[i]);

        char barV[32] = "";
        char barR[32] = "";
        int maxBarLen = 18;

        /* 业务处理: 生成车辆品牌分布柱状条 */
        for (int j = 0; j < maxBarLen; j++) {
            if (j < vehicleCount && vehicleCount > 0) {
                size_t len = strlen(barV);
                barV[len] = '=';
                barV[len + 1] = '\0';
            }
        }

        /* 业务处理: 生成租赁品牌分布柱状条 */
        for (int j = 0; j < maxBarLen; j++) {
            if (j < rentCount && rentCount > 0) {
                size_t len = strlen(barR);
                barR[len] = '=';
                barR[len + 1] = '\0';
            }
        }

        printf("  %-10s %-20s %-10s %-20s\n",
               brands[i], barV, brands[i], barR);
        printf("  %-10s %2d辆                   %2d次\n",
               "", vehicleCount, rentCount);
    }

    printSeparator('=', 70);
}

/*
 * 函数作用: 分页显示记录列表
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handlePaginatedRentRecords() {
    printSeparator('=', 60);
    printCentered("分页显示租车记录", 60);
    printSeparator('=', 60);

    LinkedList<RentRecord>* list = rentManager.getAllRentRecords();
    if (list->isEmpty()) {
        printf("\n暂无租车记录\n");
        pauseScreen();
        return;
    }

    int totalPages = (list->size() + 4) / 5;
    int currentPage = 1;
    char nav;

    do {
        printf("\n");
        printSeparator('=', 60);
        printf("  第 %d / %d 页\n", currentPage, totalPages);
        printSeparator('=', 60);
        rentRecordPrintHeader();
        printSeparator('=', 60);

        int startIdx = (currentPage - 1) * 5;
        int endIdx = startIdx + 5;
        if (endIdx > list->size()) {
            endIdx = list->size();
        }

        /* 动态链表操作: 遍历租车记录链表 */
        ListNode<RentRecord>* node = list->getHead();
        int idx = 0;
        while (node != nullptr) {
            if (idx >= startIdx && idx < endIdx) {
                rentRecordPrintRow(&node->data);
            }
            node = node->next;
            idx++;
        }

        printSeparator('=', 60);

        printf("\n");
        printf("  第%d/%d页, 按N下一页, 按P上一页, 按Q退出\n", currentPage, totalPages);
        /* 交互处理: 获取分页导航输入 */
        nav = getCharInput("请选择: ", "NnPpQq");

        if (nav == 'N' || nav == 'n') {
            if (currentPage < totalPages) {
                currentPage++;
            }
            else {
                printf("\n已经是最后一页！\n");
            }
        }
        else if (nav == 'P' || nav == 'p') {
            if (currentPage > 1) {
                currentPage--;
            }
            else {
                printf("\n已经是第一页！\n");
            }
        }
        else if (nav == 'Q' || nav == 'q') {
            break;
        }
    }
    while (true);
}

/*
 * 函数作用: 通过车辆编号自动补全输入
 * 入参: buffer - 存储输入结果的缓冲区；bufferSize - 缓冲区大小
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleAutoCompleteVehicleId(char* buffer, int bufferSize) {
    LinkedList<Vehicle>* list = vehicleManager.getAllVehicles();

    printf("\n可用的车辆列表:\n");
    vehiclePrintHeader();
    printSeparator('=', 60);
    /* 动态链表操作: 遍历车辆链表显示可用车辆 */
    ListNode<Vehicle>* node = list->getHead();
    while (node != nullptr) {
        vehiclePrintRow(&node->data);
        node = node->next;
    }
    printSeparator('=', 60);

    char input[32];
    printf("请输入车辆编号或车牌号前缀: ");
    clearInputBuffer();
    fgets(input, sizeof(input), stdin);
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    /* 数据校验: 用前缀匹配筛选车辆 */
    if (strlen(input) > 0) {
        printf("\n匹配的车辆:\n");
        int matchCount = 0;
        node = list->getHead();
        while (node != nullptr) {
            char idStr[32];
            snprintf(idStr, sizeof(idStr), "%d", node->data.id);
            if (matchPrefix(input, idStr) || matchPrefix(input, node->data.plateNo)) {
                vehiclePrintRow(&node->data);
                matchCount++;
            }
            node = node->next;
        }
        if (matchCount == 0) {
            printf("  未找到匹配的车辆\n");
        }
    }

    strncpy(buffer, input, bufferSize - 1);
    buffer[bufferSize - 1] = '\0';
}

/*
 * 函数作用: 处理添加车辆的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleAddVehicle() {
    printSeparator('=', 60);
    printCentered("添加车辆信息", 60);
    printSeparator('=', 60);

    Vehicle v;
    initVehicle(&v);

    /* 交互处理: 收集车辆信息 */
    getStringInput("车牌号码: ", v.plateNo, MAX_PLATE_LEN);

    /* 数据校验: 检查车牌号重复 */
    if (checkDuplicateVehicleByPlate(v.plateNo)) {
        printf("\n警告：该车牌号已存在！\n");
        if (!confirmAction("车牌号重复，是否继续添加？")) {
            printf("\n已取消添加车辆。\n");
            pauseScreen();
            return;
        }
    }

    getStringInput("车辆品牌: ", v.brand, MAX_BRAND_LEN);
    getStringInput("车辆类型: ", v.type, MAX_TYPE_LEN);
    getStringInput("车辆颜色: ", v.color, MAX_COLOR_LEN);
    getStringInput("购买日期 (YYYY-MM-DD): ", v.purchaseDate, MAX_DATE_LEN);
    v.dailyRate = getDoubleInput("日租金额: ", 0.01, 99999.99);
    v.mileage = getDoubleInput("行驶里程: ", 0.0, 9999999.99);
    getStringInput("保险信息: ", v.insurance, MAX_INSURANCE_LEN);

    /* 业务处理: 执行添加车辆操作 */
    if (vehicleManager.addVehicle(v)) {
        printf("\n车辆添加成功！\n");
    }
    else {
        printf("\n车辆添加失败！\n");
    }
    pauseScreen();
}

/*
 * 函数作用: 处理删除车辆的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleDeleteVehicle() {
    printSeparator('=', 60);
    printCentered("删除车辆信息", 60);
    printSeparator('=', 60);

    handleListVehicles();

    int id = getChoiceInput("请输入要删除的车辆编号: ", 1, MAX_VEHICLES);

    /* 数据校验: 查找车辆是否存在 */
    Vehicle* v = vehicleManager.findVehicleById(id);
    if (v == nullptr) {
        printf("\n未找到该车辆！\n");
        pauseScreen();
        return;
    }

    printf("\n待删除车辆信息:\n");
    vehiclePrintHeader();
    vehiclePrintRow(v);

    /* 交互处理: 确认删除操作 */
    if (confirmAction("确认删除该车辆?")) {
        /* 业务处理: 执行删除车辆操作 */
        if (vehicleManager.deleteVehicle(id)) {
            printf("\n车辆删除成功！\n");
        }
        else {
            printf("\n车辆删除失败！\n");
        }
    }
    else {
        printf("\n已取消删除操作。\n");
    }
    pauseScreen();
}

/*
 * 函数作用: 处理修改车辆信息的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleModifyVehicle() {
    printSeparator('=', 60);
    printCentered("修改车辆信息", 60);
    printSeparator('=', 60);

    int id = getChoiceInput("请输入要修改的车辆编号: ", 1, MAX_VEHICLES);

    /* 数据校验: 查找车辆是否存在 */
    Vehicle* existing = vehicleManager.findVehicleById(id);
    if (existing == nullptr) {
        printf("\n未找到该车辆！\n");
        pauseScreen();
        return;
    }

    printf("\n当前车辆信息:\n");
    vehiclePrintHeader();
    vehiclePrintRow(existing);

    Vehicle v = *existing;

    printf("\n请输入新值（直接回车保留原值）:\n");

    /* 交互处理: 逐字段修改车辆信息 */
    modifyStringFieldPrompt("车牌号码", v.plateNo, MAX_PLATE_LEN);
    modifyStringFieldPrompt("车辆品牌", v.brand, MAX_BRAND_LEN);
    modifyStringFieldPrompt("车辆类型", v.type, MAX_TYPE_LEN);
    modifyStringFieldPrompt("车辆颜色", v.color, MAX_COLOR_LEN);
    modifyStringFieldPrompt("购买日期", v.purchaseDate, MAX_DATE_LEN);
    modifyDoubleFieldPrompt("日租金额", &v.dailyRate);
    modifyDoubleFieldPrompt("行驶里程", &v.mileage);
    modifyStringFieldPrompt("保险信息", v.insurance, MAX_INSURANCE_LEN);

    /* 业务处理: 执行修改车辆操作 */
    if (vehicleManager.modifyVehicle(id, v)) {
        printf("\n车辆信息修改成功！\n");
    }
    else {
        printf("\n车辆信息修改失败！\n");
    }
    pauseScreen();
}

/*
 * 函数作用: 处理列出所有车辆的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleListVehicles() {
    LinkedList<Vehicle>* list = vehicleManager.getAllVehicles();
    if (list->isEmpty()) {
        printf("\n暂无车辆信息\n");
        pauseScreen();
        return;
    }

    printSeparator('=', 60);
    vehiclePrintHeader();
    printSeparator('=', 60);

    /* 动态链表操作: 遍历车辆链表 */
    ListNode<Vehicle>* node = list->getHead();
    while (node != nullptr) {
        vehiclePrintRow(&node->data);
        node = node->next;
    }
    printSeparator('=', 60);
    printf("共 %d 辆车\n", list->size());
    pauseScreen();
}

/*
 * 函数作用: 处理添加租车人的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleAddRenter() {
    printSeparator('=', 60);
    printCentered("添加租车用户", 60);
    printSeparator('=', 60);

    Renter r;
    initRenter(&r);

    /* 交互处理: 收集用户信息 */
    getStringInput("姓名: ", r.name, MAX_NAME_LEN);
    r.age = getIntInputWithHint("年龄: ", 18, 100);
    r.gender = getCharInput("性别 (M/F): ", "MFmf");
    if (r.gender == 'm') {
        r.gender = 'M';
    }
    if (r.gender == 'f') {
        r.gender = 'F';
    }
    getStringInput("手机号码: ", r.phone, MAX_PHONE_LEN);
    getStringInput("驾照号码: ", r.licenseNo, MAX_LICENSE_LEN);

    /* 数据校验: 检查驾照号重复 */
    if (checkDuplicateRenterByLicense(r.licenseNo)) {
        printf("\n警告：该驾照号已存在！\n");
        if (!confirmAction("驾照号重复，是否继续添加？")) {
            printf("\n已取消添加用户。\n");
            pauseScreen();
            return;
        }
    }

    getStringInput("身份证号: ", r.idCard, MAX_IDCARD_LEN);
    r.drivingYears = getIntInputWithHint("驾龄: ", 0, 60);

    /* 业务处理: 执行添加用户操作 */
    if (renterManager.addRenter(r)) {
        printf("\n用户添加成功！\n");
    }
    else {
        printf("\n用户添加失败！\n");
    }
    pauseScreen();
}

/*
 * 函数作用: 处理删除租车人的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleDeleteRenter() {
    printSeparator('=', 60);
    printCentered("删除租车用户", 60);
    printSeparator('=', 60);

    handleListRenters();

    int id = getChoiceInput("请输入要删除的用户编号: ", 1, MAX_RENTERS);

    /* 数据校验: 查找用户是否存在 */
    Renter* r = renterManager.findRenterById(id);
    if (r == nullptr) {
        printf("\n未找到该用户！\n");
        pauseScreen();
        return;
    }

    printf("\n待删除用户信息:\n");
    renterPrintHeader();
    renterPrintRow(r);

    /* 交互处理: 确认删除操作 */
    if (confirmAction("确认删除该用户?")) {
        /* 业务处理: 执行删除用户操作 */
        if (renterManager.deleteRenter(id)) {
            printf("\n用户删除成功！\n");
        }
        else {
            printf("\n用户删除失败！\n");
        }
    }
    else {
        printf("\n已取消删除操作。\n");
    }
    pauseScreen();
}

/*
 * 函数作用: 处理修改租车人信息的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleModifyRenter() {
    printSeparator('=', 60);
    printCentered("修改租车用户", 60);
    printSeparator('=', 60);

    int id = getChoiceInput("请输入要修改的用户编号: ", 1, MAX_RENTERS);

    /* 数据校验: 查找用户是否存在 */
    Renter* existing = renterManager.findRenterById(id);
    if (existing == nullptr) {
        printf("\n未找到该用户！\n");
        pauseScreen();
        return;
    }

    printf("\n当前用户信息:\n");
    renterPrintHeader();
    renterPrintRow(existing);

    Renter r = *existing;

    printf("\n请输入新值（直接回车保留原值）:\n");

    /* 交互处理: 逐字段修改用户信息 */
    modifyStringFieldPrompt("姓名", r.name, MAX_NAME_LEN);
    modifyIntFieldPrompt("年龄", &r.age);

    {
        char temp[256];
        printf("性别 [%c]: ", r.gender);
        fgets(temp, sizeof(temp), stdin);
        if (temp[0] != '\n' && temp[0] != '\0') {
            if (temp[0] == 'M' || temp[0] == 'm' || temp[0] == 'F' || temp[0] == 'f') {
                if (temp[0] == 'm') {
                    temp[0] = 'M';
                }
                if (temp[0] == 'f') {
                    temp[0] = 'F';
                }
                r.gender = temp[0];
            }
        }
    }

    modifyStringFieldPrompt("手机号码", r.phone, MAX_PHONE_LEN);
    modifyStringFieldPrompt("驾照号码", r.licenseNo, MAX_LICENSE_LEN);
    modifyStringFieldPrompt("身份证号", r.idCard, MAX_IDCARD_LEN);
    modifyIntFieldPrompt("驾龄", &r.drivingYears);

    /* 业务处理: 执行修改用户操作 */
    if (renterManager.modifyRenter(id, r)) {
        printf("\n用户信息修改成功！\n");
    }
    else {
        printf("\n用户信息修改失败！\n");
    }
    pauseScreen();
}

/*
 * 函数作用: 处理列出所有租车人的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleListRenters() {
    LinkedList<Renter>* list = renterManager.getAllRenters();
    if (list->isEmpty()) {
        printf("\n暂无租车用户信息\n");
        pauseScreen();
        return;
    }

    printSeparator('=', 60);
    renterPrintHeader();
    printSeparator('=', 60);

    /* 动态链表操作: 遍历租车用户链表 */
    ListNode<Renter>* node = list->getHead();
    while (node != nullptr) {
        renterPrintRow(&node->data);
        node = node->next;
    }
    printSeparator('=', 60);
    printf("共 %d 名用户\n", list->size());
    pauseScreen();
}

/*
 * 函数作用: 处理租车操作业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleRentVehicle() {
    printSeparator('=', 60);
    printCentered("办理租车业务", 60);
    printSeparator('=', 60);

    /* 数据校验: 检查是否有可租车辆 */
    LinkedList<Vehicle> available = vehicleManager.queryByStatus(STATUS_AVAILABLE);
    if (available.isEmpty()) {
        printf("\n当前没有可租车辆！\n");
        pauseScreen();
        return;
    }

    printf("\n可租车辆列表:\n");
    vehiclePrintHeader();
    printSeparator('=', 60);
    /* 动态链表操作: 遍历可租车辆链表 */
    ListNode<Vehicle>* node = available.getHead();
    while (node != nullptr) {
        vehiclePrintRow(&node->data);
        node = node->next;
    }
    printSeparator('=', 60);

    /* 交互处理: 显示可用车辆编号供自动补全参考 */
    printf("\n可租车辆编号: ");
    node = available.getHead();
    while (node != nullptr) {
        printf("%d ", node->data.id);
        node = node->next;
    }
    printf("\n");

    /* 交互处理: 获取车辆编号输入（带分类错误提示） */
    int vehicleId = getIntInputWithHint("请输入要租的车辆编号: ", 1, MAX_VEHICLES);

    /* 数据校验: 查找车辆 */
    Vehicle* vehicle = vehicleManager.findVehicleById(vehicleId);
    if (vehicle == nullptr) {
        printf("\n未找到该车辆！\n");
        pauseScreen();
        return;
    }
    /* 数据校验: 检查车辆是否可租 */
    if (vehicle->status != STATUS_AVAILABLE) {
        printf("\n该车辆不可租！\n");
        pauseScreen();
        return;
    }

    /* 交互处理: 获取用户编号输入（带分类错误提示） */
    int renterId = getIntInputWithHint("请输入租车用户编号: ", 1, MAX_RENTERS);

    /* 数据校验: 查找用户 */
    Renter* renter = renterManager.findRenterById(renterId);
    if (renter == nullptr) {
        printf("\n未找到该用户！\n");
        pauseScreen();
        return;
    }

    char rentDate[MAX_DATE_LEN];
    char expectedReturnDate[MAX_DATE_LEN];
    char currentDate[MAX_DATE_LEN];
    getCurrentDate(currentDate);

    printf("租车日期 [%s]: ", currentDate);
    clearInputBuffer();
    char temp[256];
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] == '\n' || temp[0] == '\0') {
        strncpy(rentDate, currentDate, MAX_DATE_LEN - 1);
        rentDate[MAX_DATE_LEN - 1] = '\0';
    }
    else {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') {
            temp[len - 1] = '\0';
        }
        strncpy(rentDate, temp, MAX_DATE_LEN - 1);
        rentDate[MAX_DATE_LEN - 1] = '\0';
    }

    getStringInput("预计归还日期 (YYYY-MM-DD): ", expectedReturnDate, MAX_DATE_LEN);

    /* 数据校验: 验证日期范围 */
    if (!isValidDateRange(rentDate, expectedReturnDate)) {
        printf("\n日期范围不合法！\n");
        pauseScreen();
        return;
    }

    int days = daysBetween(rentDate, expectedReturnDate);
    if (days < 1) {
        days = 1;
    }
    double deposit = vehicle->dailyRate * days * 2.0;

    /* 交互处理: 显示租车确认信息 */
    printf("\n租车信息确认:\n");
    printf("  车辆: [%s] %s\n", vehicle->plateNo, vehicle->brand);
    printf("  用户: %s (驾照: %s)\n", renter->name, renter->licenseNo);
    printf("  租车日期: %s\n", rentDate);
    printf("  预计归还: %s\n", expectedReturnDate);
    printf("  日租金: %.2f 元\n", vehicle->dailyRate);
    printf("  租用天数: %d 天\n", days);
    printf("  押金: %.2f 元\n", deposit);

    if (!confirmAction("确认办理租车?")) {
        printf("\n已取消租车操作。\n");
        pauseScreen();
        return;
    }

    showProgressBar("正在处理租车", 0, 100);
    showProgressBar("正在处理租车", 50, 100);

    /* 业务处理: 执行租车操作 */
    int rentId = rentManager.rentVehicle(
        vehicleId, renterId, rentDate, expectedReturnDate,
        deposit, vehicle->dailyRate, vehicle->brand, vehicle->plateNo,
        renter->name, renter->licenseNo);

    vehicle->status = STATUS_RENTED;
    vehicleManager.modifyVehicle(vehicleId, *vehicle);

    renterManager.incrementRentCount(renterId);

    showProgressBar("正在处理租车", 100, 100);

    Receipt::printRentReceipt(rentId, vehicleId, vehicle->brand,
                               vehicle->plateNo, vehicle->type,
                               renter->name, renter->licenseNo,
                               rentDate, expectedReturnDate,
                               deposit, vehicle->dailyRate);

    printf("\n租车办理成功！租车编号: %d\n", rentId);
    pauseScreen();
}

/*
 * 函数作用: 处理还车操作业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleReturnVehicle() {
    printSeparator('=', 60);
    printCentered("办理退车业务", 60);
    printSeparator('=', 60);

    /* 数据校验: 检查是否有进行中的租车记录 */
    LinkedList<RentRecord> activeRents = rentManager.getActiveRents();
    if (activeRents.isEmpty()) {
        printf("\n当前没有进行中的租车记录！\n");
        pauseScreen();
        return;
    }

    printf("\n进行中的租车记录:\n");
    rentRecordPrintHeader();
    printSeparator('=', 60);
    /* 动态链表操作: 遍历进行中租车记录链表 */
    ListNode<RentRecord>* node = activeRents.getHead();
    while (node != nullptr) {
        rentRecordPrintRow(&node->data);
        node = node->next;
    }
    printSeparator('=', 60);

    /* 交互处理: 获取租车编号输入（带分类错误提示） */
    int rentId = getIntInputWithHint("请输入要退车的租车编号: ", 1, MAX_RENTS);

    /* 数据校验: 查找租车记录 */
    RentRecord* record = rentManager.findRentById(rentId);
    if (record == nullptr) {
        printf("\n未找到该租车记录！\n");
        pauseScreen();
        return;
    }
    /* 数据校验: 检查记录是否已归还 */
    if (record->status != RENT_ACTIVE) {
        printf("\n该租车记录已归还！\n");
        pauseScreen();
        return;
    }

    char actualReturnDate[MAX_DATE_LEN];
    char currentDate[MAX_DATE_LEN];
    getCurrentDate(currentDate);

    printf("实际归还日期 [%s]: ", currentDate);
    clearInputBuffer();
    char temp[256];
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] == '\n' || temp[0] == '\0') {
        strncpy(actualReturnDate, currentDate, MAX_DATE_LEN - 1);
        actualReturnDate[MAX_DATE_LEN - 1] = '\0';
    }
    else {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') {
            temp[len - 1] = '\0';
        }
        strncpy(actualReturnDate, temp, MAX_DATE_LEN - 1);
        actualReturnDate[MAX_DATE_LEN - 1] = '\0';
    }

    int days = daysBetween(record->rentDate, actualReturnDate);
    if (days < 1) {
        days = 1;
    }
    double totalFee = record->dailyRate * days;
    double refund = record->deposit - totalFee;
    if (refund < 0) {
        refund = 0;
    }

    /* 交互处理: 显示退车费用计算 */
    printf("\n退车费用计算:\n");
    printf("  租车日期: %s\n", record->rentDate);
    printf("  归还日期: %s\n", actualReturnDate);
    printf("  租用天数: %d 天\n", days);
    printf("  日租金: %.2f 元\n", record->dailyRate);
    printf("  总费用: %.2f 元\n", totalFee);
    printf("  押金: %.2f 元\n", record->deposit);
    printf("  退款: %.2f 元\n", refund);

    if (!confirmAction("确认办理退车?")) {
        printf("\n已取消退车操作。\n");
        pauseScreen();
        return;
    }

    showProgressBar("正在处理退车", 0, 100);
    showProgressBar("正在处理退车", 50, 100);

    /* 业务处理: 执行退车操作 */
    if (rentManager.returnVehicle(rentId, actualReturnDate, totalFee)) {
        Vehicle* vehicle = vehicleManager.findVehicleById(record->vehicleId);
        if (vehicle != nullptr) {
            vehicle->status = STATUS_AVAILABLE;
            vehicleManager.modifyVehicle(record->vehicleId, *vehicle);
        }

        showProgressBar("正在处理退车", 100, 100);

        Receipt::printReturnReceipt(rentId, record->vehicleId, record->vehicleBrand,
                                     record->vehiclePlate, record->renterName,
                                     record->rentDate, actualReturnDate,
                                     days, record->dailyRate, record->deposit,
                                     totalFee, refund);

        printf("\n退车办理成功！\n");
    }
    else {
        printf("\n退车办理失败！\n");
    }
    pauseScreen();
}

/*
 * 函数作用: 处理打印小票的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handlePrintReceipt() {
    printSeparator('=', 60);
    printCentered("打印票据", 60);
    printSeparator('=', 60);

    int rentId = getChoiceInput("请输入租车编号: ", 1, MAX_RENTS);

    /* 数据校验: 查找租车记录 */
    RentRecord* record = rentManager.findRentById(rentId);
    if (record == nullptr) {
        printf("\n未找到该租车记录！\n");
        pauseScreen();
        return;
    }

    /* 业务处理: 根据记录状态打印对应票据 */
    if (record->status == RENT_ACTIVE) {
        int days = daysBetween(record->rentDate, record->expectedReturnDate);
        if (days < 1) {
            days = 1;
        }
        Receipt::printRentReceipt(record->id, record->vehicleId,
                                   record->vehicleBrand, record->vehiclePlate,
                                   record->vehicleBrand, record->renterName,
                                   record->renterLicense, record->rentDate,
                                   record->expectedReturnDate,
                                   record->deposit, record->dailyRate);
    }
    else {
        int days = daysBetween(record->rentDate, record->actualReturnDate);
        if (days < 1) {
            days = 1;
        }
        double refund = record->deposit - record->totalFee;
        if (refund < 0) {
            refund = 0;
        }
        Receipt::printReturnReceipt(record->id, record->vehicleId,
                                     record->vehicleBrand, record->vehiclePlate,
                                     record->renterName, record->rentDate,
                                     record->actualReturnDate, days,
                                     record->dailyRate, record->deposit,
                                     record->totalFee, refund);
    }
    pauseScreen();
}

/*
 * 函数作用: 处理列出所有租赁记录的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleListRentRecords() {
    LinkedList<RentRecord>* list = rentManager.getAllRentRecords();
    if (list->isEmpty()) {
        printf("\n暂无租车记录\n");
        pauseScreen();
        return;
    }

    int total = list->size();
    showProgressBar("正在加载租车记录", 0, total);

    printSeparator('=', 60);
    rentRecordPrintHeader();
    printSeparator('=', 60);

    /* 动态链表操作: 遍历租车记录链表 */
    ListNode<RentRecord>* node = list->getHead();
    int index = 0;
    while (node != nullptr) {
        rentRecordPrintRow(&node->data);
        node = node->next;
        index++;
        if (index % 10 == 0) {
            showProgressBar("正在加载租车记录", index, total);
        }
    }

    showProgressBar("正在加载租车记录", total, total);
    printSeparator('=', 60);
    printf("共 %d 条记录\n", total);
    pauseScreen();
}

/*
 * 函数作用: 处理查询车辆的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleQueryVehicles() {
    while (true) {
        printSeparator('=', 60);
        printCentered("车辆查询", 60);
        printSeparator('=', 60);
        printf("  1. 按品牌查询\n");
        printf("  2. 按类型查询\n");
        printf("  3. 按颜色查询\n");
        printf("  4. 按状态查询\n");
        printf("  0. 返回\n");
        printSeparator('=', 60);

        int choice = getChoiceInput("请选择查询方式 [0-4]: ", 0, 4);

        LinkedList<Vehicle> result;
        char keyword[MAX_BRAND_LEN];

        switch (choice) {
            case 1:
                getStringInput("请输入品牌: ", keyword, MAX_BRAND_LEN);
                result = vehicleManager.queryByBrand(keyword);
                break;
            case 2:
                getStringInput("请输入类型: ", keyword, MAX_TYPE_LEN);
                result = vehicleManager.queryByType(keyword);
                break;
            case 3:
                getStringInput("请输入颜色: ", keyword, MAX_COLOR_LEN);
                result = vehicleManager.queryByColor(keyword);
                break;
            case 4: {
                printf("状态选项: 0-可租, 1-已租, 2-维护中\n");
                int status = getChoiceInput("请选择状态: ", 0, 2);
                result = vehicleManager.queryByStatus(status);
                break;
            }
            case 0: return;
        }

        /* 数据校验: 检查查询结果 */
        if (result.isEmpty()) {
            printf("\n未找到匹配的车辆信息。\n");
            pauseScreen();
            continue;
        }

        printf("\n查询结果 (%d 条):\n", result.size());
        vehiclePrintHeader();
        printSeparator('=', 60);
        /* 动态链表操作: 遍历查询结果链表 */
        ListNode<Vehicle>* node = result.getHead();
        while (node != nullptr) {
            vehiclePrintRow(&node->data);
            node = node->next;
        }
        printSeparator('=', 60);
        pauseScreen();
    }
}

/*
 * 函数作用: 处理查询租车人的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleQueryRenters() {
    while (true) {
        printSeparator('=', 60);
        printCentered("租车用户查询", 60);
        printSeparator('=', 60);
        printf("  1. 按姓名查询\n");
        printf("  2. 按驾照号查询\n");
        printf("  0. 返回\n");
        printSeparator('=', 60);

        int choice = getChoiceInput("请选择查询方式 [0-2]: ", 0, 2);

        LinkedList<Renter> result;
        char keyword[MAX_NAME_LEN];

        switch (choice) {
            case 1:
                getStringInput("请输入姓名: ", keyword, MAX_NAME_LEN);
                result = renterManager.queryByName(keyword);
                break;
            case 2:
                getStringInput("请输入驾照号: ", keyword, MAX_LICENSE_LEN);
                result = renterManager.queryByLicense(keyword);
                break;
            case 0: return;
        }

        /* 数据校验: 检查查询结果 */
        if (result.isEmpty()) {
            printf("\n未找到匹配的用户信息。\n");
            pauseScreen();
            continue;
        }

        printf("\n查询结果 (%d 条):\n", result.size());
        renterPrintHeader();
        printSeparator('=', 60);
        /* 动态链表操作: 遍历查询结果链表 */
        ListNode<Renter>* node = result.getHead();
        while (node != nullptr) {
            renterPrintRow(&node->data);
            node = node->next;
        }
        printSeparator('=', 60);
        pauseScreen();
    }
}

/*
 * 函数作用: 处理查询租赁记录的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleQueryRentRecords() {
    while (true) {
        printSeparator('=', 60);
        printCentered("租车记录查询", 60);
        printSeparator('=', 60);
        printf("  1. 按车辆编号查询\n");
        printf("  2. 按用户编号查询\n");
        printf("  3. 按日期查询\n");
        printf("  4. 按状态查询\n");
        printf("  0. 返回\n");
        printSeparator('=', 60);

        int choice = getChoiceInput("请选择查询方式 [0-4]: ", 0, 4);

        LinkedList<RentRecord> result;

        switch (choice) {
            case 1: {
                int vehicleId = getChoiceInput("请输入车辆编号: ", 1, MAX_VEHICLES);
                result = rentManager.queryByVehicleId(vehicleId);
                break;
            }
            case 2: {
                int renterId = getChoiceInput("请输入用户编号: ", 1, MAX_RENTERS);
                result = rentManager.queryByRenterId(renterId);
                break;
            }
            case 3: {
                char date[MAX_DATE_LEN];
                getStringInput("请输入日期 (YYYY-MM-DD): ", date, MAX_DATE_LEN);
                result = rentManager.queryByDate(date);
                break;
            }
            case 4: {
                printf("状态选项: 0-租用中, 1-已归还\n");
                int status = getChoiceInput("请选择状态: ", 0, 1);
                result = rentManager.queryByStatus(status);
                break;
            }
            case 0: return;
        }

        /* 数据校验: 检查查询结果 */
        if (result.isEmpty()) {
            printf("\n未找到匹配的租车记录。\n");
            pauseScreen();
            continue;
        }

        printf("\n查询结果 (%d 条):\n", result.size());
        rentRecordPrintHeader();
        printSeparator('=', 60);
        /* 动态链表操作: 遍历查询结果链表 */
        ListNode<RentRecord>* node = result.getHead();
        while (node != nullptr) {
            rentRecordPrintRow(&node->data);
            node = node->next;
        }
        printSeparator('=', 60);
        pauseScreen();
    }
}

/*
 * 函数作用: 处理车辆统计的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleVehicleStatistics() {
    printSeparator('=', 60);
    printCentered("车辆统计", 60);
    printSeparator('=', 60);

    vehicleManager.printStatistics();

    printf("\n详细统计:\n");
    printf("  1. 按品牌统计\n");
    printf("  2. 按类型统计\n");
    printf("  3. 按颜色统计\n");
    char choice = getCharInput("请选择统计方式 [1-3，其他键跳过]: ", "123");

    if (choice == '1') {
        char brand[MAX_BRAND_LEN];
        getStringInput("请输入品牌: ", brand, MAX_BRAND_LEN);
        int count = vehicleManager.countByBrand(brand);
        printf("\n品牌 [%s] 的车辆数: %d\n", brand, count);
    }
    else if (choice == '2') {
        char type[MAX_TYPE_LEN];
        getStringInput("请输入类型: ", type, MAX_TYPE_LEN);
        int count = vehicleManager.countByType(type);
        printf("\n类型 [%s] 的车辆数: %d\n", type, count);
    }
    else if (choice == '3') {
        char color[MAX_COLOR_LEN];
        getStringInput("请输入颜色: ", color, MAX_COLOR_LEN);
        int count = vehicleManager.countByColor(color);
        printf("\n颜色 [%s] 的车辆数: %d\n", color, count);
    }

    pauseScreen();
}

/*
 * 函数作用: 处理租车人统计的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleRenterStatistics() {
    printSeparator('=', 60);
    printCentered("租车用户统计", 60);
    printSeparator('=', 60);
    renterManager.printStatistics();
    pauseScreen();
}

/*
 * 函数作用: 处理租赁统计的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleRentStatistics() {
    printSeparator('=', 60);
    printCentered("租车记录统计", 60);
    printSeparator('=', 60);
    rentManager.printStatistics();
    pauseScreen();
}

/*
 * 函数作用: 处理修改密码的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleChangePassword() {
    printSeparator('=', 60);
    printCentered("修改密码", 60);
    printSeparator('=', 60);

    char oldPassword[64];
    char newPassword[64];
    char confirmPassword[64];

    /* 交互处理: 获取旧密码 */
    printf("请输入旧密码: ");
    clearInputBuffer();
    fgets(oldPassword, sizeof(oldPassword), stdin);
    size_t len = strlen(oldPassword);
    if (len > 0 && oldPassword[len - 1] == '\n') {
        oldPassword[len - 1] = '\0';
    }

    /* 交互处理: 获取新密码并确认 */
    printf("请输入新密码: ");
    fgets(newPassword, sizeof(newPassword), stdin);
    len = strlen(newPassword);
    if (len > 0 && newPassword[len - 1] == '\n') {
        newPassword[len - 1] = '\0';
    }

    printf("请确认新密码: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    len = strlen(confirmPassword);
    if (len > 0 && confirmPassword[len - 1] == '\n') {
        confirmPassword[len - 1] = '\0';
    }

    /* 数据校验: 验证两次密码一致 */
    if (strcmp(newPassword, confirmPassword) != 0) {
        printf("\n两次输入的密码不一致！\n");
        pauseScreen();
        return;
    }

    /* 业务处理: 执行密码修改 */
    if (authManager.setPassword(oldPassword, newPassword)) {
        printf("\n密码修改成功！\n");
    }
    else {
        printf("\n密码修改失败，请检查旧密码是否正确。\n");
    }
    pauseScreen();
}

/*
 * 函数作用: 处理导出报表的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleExportReport() {
    printSeparator('=', 60);
    printCentered("导出报表", 60);
    printSeparator('=', 60);

    char currentDateTime[64];
    getCurrentDateTime(currentDateTime);

    char filename[128];
    snprintf(filename, sizeof(filename), "report_%s.txt", currentDateTime);

    for (int i = 0; filename[i] != '\0'; i++) {
        if (filename[i] == ' ' || filename[i] == ':' || filename[i] == '/') {
            filename[i] = '_';
        }
    }

    /* 文件操作: 打开报表文件 */
    FILE* fp = fopen(filename, "w");
    if (fp == nullptr) {
        printf("\n无法创建报表文件！\n");
        pauseScreen();
        return;
    }

    showProgressBar("正在导出报表", 0, 100);

    fprintf(fp, "═══════════════════════════════════════════\n");
    fprintf(fp, "      汽车租赁管理系统 - 数据报表\n");
    fprintf(fp, "      导出时间: %s\n", currentDateTime);
    fprintf(fp, "═══════════════════════════════════════════\n\n");

    showProgressBar("正在导出报表", 20, 100);

    /* 业务处理: 导出车辆信息 */
    exportVehiclesToFile(fp, vehicleManager);

    showProgressBar("正在导出报表", 40, 100);

    /* 业务处理: 导出租车用户信息 */
    exportRentersToFile(fp, renterManager);

    showProgressBar("正在导出报表", 60, 100);

    /* 业务处理: 导出租车记录 */
    exportRentRecordsToFile(fp, rentManager);

    showProgressBar("正在导出报表", 80, 100);

    /* 业务处理: 导出统计汇总 */
    exportStatisticsToFile(fp, vehicleManager, renterManager, rentManager);

    showProgressBar("正在导出报表", 100, 100);

    /* 文件操作: 关闭报表文件 */
    fclose(fp);
    printf("\n报表已导出到文件: %s\n", filename);
    pauseScreen();
}

/*
 * 函数作用: 处理查看操作日志的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleViewLog() {
    printSeparator('=', 60);
    printCentered("系统日志", 60);
    printSeparator('=', 60);
    Logger::showLog();
    pauseScreen();
}

/*
 * 函数作用: 处理清空数据的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleClearData() {
    printSeparator('=', 60);
    printCentered("清空全部数据", 60);
    printSeparator('=', 60);

    printf("\n警告：此操作将清空所有车辆、用户和租车记录数据！\n");
    printf("此操作不可恢复！\n\n");

    /* 交互处理: 确认清空操作 */
    if (!confirmAction("确认清空全部数据?")) {
        printf("\n已取消操作。\n");
        pauseScreen();
        return;
    }

    /* 业务处理: 清空车辆链表 */
    LinkedList<Vehicle>* vehicles = vehicleManager.getAllVehicles();
    while (vehicles->getHead() != nullptr) {
        vehicleManager.deleteVehicle(vehicles->getHead()->data.id);
    }

    /* 业务处理: 清空用户链表 */
    LinkedList<Renter>* renters = renterManager.getAllRenters();
    while (renters->getHead() != nullptr) {
        renterManager.deleteRenter(renters->getHead()->data.id);
    }

    /* 业务处理: 清空租车记录链表 */
    LinkedList<RentRecord>* records = rentManager.getAllRentRecords();
    ListNode<RentRecord>* node = records->getHead();
    while (node != nullptr) {
        ListNode<RentRecord>* next = node->next;
        records->removeNode(node);
        node = next;
    }

    /* 文件操作: 清空数据文件 */
    FILE* fp = fopen(FILE_VEHICLE, "wb");
    if (fp != nullptr) {
        fclose(fp);
    }
    fp = fopen(FILE_RENTER, "wb");
    if (fp != nullptr) {
        fclose(fp);
    }
    fp = fopen(FILE_RENT, "wb");
    if (fp != nullptr) {
        fclose(fp);
    }

    Logger::logOperation("清空全部数据");

    printf("\n全部数据已清空！\n");
    pauseScreen();
}

/*
 * 函数作用: 处理模糊搜索的业务流程
 * 入参: 无
 * 返回值: 无
 * 异常提示: 无
 */
void UI::handleFuzzySearch() {
    printSeparator('=', 60);
    printCentered("模糊搜索", 60);
    printSeparator('=', 60);

    char keyword[MAX_BRAND_LEN];
    getStringInput("请输入搜索关键词: ", keyword, MAX_BRAND_LEN);

    printf("\n正在搜索...\n");

    /* 业务处理: 执行模糊搜索 */
    LinkedList<Vehicle> vehicleResults = vehicleManager.queryFuzzy(keyword);
    LinkedList<Renter> renterResults = renterManager.queryFuzzy(keyword);
    LinkedList<RentRecord> rentResults = rentManager.queryFuzzy(keyword);

    int totalResults = vehicleResults.size() + renterResults.size() + rentResults.size();

    /* 数据校验: 检查搜索结果 */
    if (totalResults == 0) {
        printf("\n未找到匹配的结果。\n");
        pauseScreen();
        return;
    }

    printf("\n搜索 \"%s\" 的结果 (共 %d 条):\n", keyword, totalResults);

    /* 动态链表操作: 遍历车辆搜索结果 */
    if (!vehicleResults.isEmpty()) {
        printf("\n--- 车辆匹配 (%d 条) ---\n", vehicleResults.size());
        vehiclePrintHeader();
        ListNode<Vehicle>* vNode = vehicleResults.getHead();
        while (vNode != nullptr) {
            vehiclePrintRow(&vNode->data);
            vNode = vNode->next;
        }
    }

    /* 动态链表操作: 遍历用户搜索结果 */
    if (!renterResults.isEmpty()) {
        printf("\n--- 用户匹配 (%d 条) ---\n", renterResults.size());
        renterPrintHeader();
        ListNode<Renter>* rNode = renterResults.getHead();
        while (rNode != nullptr) {
            renterPrintRow(&rNode->data);
            rNode = rNode->next;
        }
    }

    /* 动态链表操作: 遍历租车记录搜索结果 */
    if (!rentResults.isEmpty()) {
        printf("\n--- 租车记录匹配 (%d 条) ---\n", rentResults.size());
        rentRecordPrintHeader();
        ListNode<RentRecord>* recNode = rentResults.getHead();
        while (recNode != nullptr) {
            rentRecordPrintRow(&recNode->data);
            recNode = recNode->next;
        }
    }

    pauseScreen();
}
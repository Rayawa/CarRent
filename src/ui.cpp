#include "ui.h"
#include "utils.h"
#include "receipt.h"
#include "statistics.h"
#include "logger.h"

UI::UI() {
    running = true;
}

void UI::showBanner() {
    printf("\n\n");
    printf("  ╔══════════════════════════════════════════════╗\n");
    printf("  ║                                              ║\n");
    printf("  ║         汽车租赁管理系统                     ║\n");
    printf("  ║       Car Rental Management System           ║\n");
    printf("  ║                                              ║\n");
    printf("  ╚══════════════════════════════════════════════╝\n");
    printf("\n");
}

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

void UI::mainMenu() {
    printSeparator('=', 60);
    printf("╔══════════════ 汽车租赁管理系统 ══════════════╗\n");
    printf("║  1. 车辆信息管理                             ║\n");
    printf("║  2. 租车用户信息管理                         ║\n");
    printf("║  3. 租车业务办理                             ║\n");
    printf("║  4. 退车业务办理                             ║\n");
    printf("║  5. 信息查询                                 ║\n");
    printf("║  6. 统计汇总                                 ║\n");
    printf("║  7. 输出全部信息                             ║\n");
    printf("║  8. 系统设置                                 ║\n");
    printf("║  9. 扩展功能                                 ║\n");
    printf("║  0. 退出系统                                 ║\n");
    printf("╚══════════════════════════════════════════════╝\n");

    int choice = getIntInput("请选择操作 [0-9]: ", 0, 9);

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

        int choice = getIntInput("请选择操作 [0-4]: ", 0, 4);

        switch (choice) {
            case 1: handleAddVehicle(); break;
            case 2: handleDeleteVehicle(); break;
            case 3: handleModifyVehicle(); break;
            case 4: handleListVehicles(); break;
            case 0: return;
        }
    }
}

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

        int choice = getIntInput("请选择操作 [0-4]: ", 0, 4);

        switch (choice) {
            case 1: handleAddRenter(); break;
            case 2: handleDeleteRenter(); break;
            case 3: handleModifyRenter(); break;
            case 4: handleListRenters(); break;
            case 0: return;
        }
    }
}

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

        int choice = getIntInput("请选择操作 [0-3]: ", 0, 3);

        switch (choice) {
            case 1: handleRentVehicle(); break;
            case 2: handleListRentRecords(); break;
            case 3: handlePrintReceipt(); break;
            case 0: return;
        }
    }
}

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

        int choice = getIntInput("请选择操作 [0-3]: ", 0, 3);

        switch (choice) {
            case 1: handleReturnVehicle(); break;
            case 2: handleListRentRecords(); break;
            case 3: handlePrintReceipt(); break;
            case 0: return;
        }
    }
}

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

        int choice = getIntInput("请选择操作 [0-4]: ", 0, 4);

        switch (choice) {
            case 1: handleQueryVehicles(); break;
            case 2: handleQueryRenters(); break;
            case 3: handleQueryRentRecords(); break;
            case 4: handleFuzzySearch(); break;
            case 0: return;
        }
    }
}

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

        int choice = getIntInput("请选择操作 [0-5]: ", 0, 5);

        switch (choice) {
            case 1: handleVehicleStatistics(); break;
            case 2: handleRenterStatistics(); break;
            case 3: handleRentStatistics(); break;
            case 4: Statistics::showDashboard(&vehicleManager, &renterManager, &rentManager); pauseScreen(); break;
            case 5: {
                printf("\n  1. 车辆品牌柱状图\n");
                printf("  2. 租车趋势图\n");
                printf("  3. 租车类型饼图\n");
                printf("  4. 收入走势图\n");
                int chartChoice = getIntInput("请选择图表 [1-4]: ", 1, 4);
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

        int choice = getIntInput("请选择操作 [0-4]: ", 0, 4);

        switch (choice) {
            case 1: handleChangePassword(); break;
            case 2: handleExportReport(); break;
            case 3: handleViewLog(); break;
            case 4: handleClearData(); break;
            case 0: return;
        }
    }
}

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
        printf("  0. 返回主菜单\n");
        printSeparator('=', 60);

        int choice = getIntInput("请选择操作 [0-5]: ", 0, 5);

        switch (choice) {
            case 1: {
                printf("\n  1. 车辆品牌柱状图\n");
                printf("  2. 租车趋势图\n");
                printf("  3. 租车类型饼图\n");
                printf("  4. 收入走势图\n");
                int chartChoice = getIntInput("请选择图表 [1-4]: ", 1, 4);
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
            case 0: return;
        }
    }
}

void UI::handleAddVehicle() {
    printSeparator('=', 60);
    printCentered("添加车辆信息", 60);
    printSeparator('=', 60);

    Vehicle v;
    vehicleInit(&v);

    getStringInput("车牌号码: ", v.plateNo, MAX_PLATE_LEN);
    getStringInput("车辆品牌: ", v.brand, MAX_BRAND_LEN);
    getStringInput("车辆类型: ", v.type, MAX_TYPE_LEN);
    getStringInput("车辆颜色: ", v.color, MAX_COLOR_LEN);
    getStringInput("购买日期 (YYYY-MM-DD): ", v.purchaseDate, MAX_DATE_LEN);
    v.dailyRate = getDoubleInput("日租金额: ", 0.01, 99999.99);
    v.mileage = getDoubleInput("行驶里程: ", 0.0, 9999999.99);
    getStringInput("保险信息: ", v.insurance, MAX_INSURANCE_LEN);

    if (vehicleManager.addVehicle(v)) {
        printf("\n车辆添加成功！\n");
    } else {
        printf("\n车辆添加失败！\n");
    }
    pauseScreen();
}

void UI::handleDeleteVehicle() {
    printSeparator('=', 60);
    printCentered("删除车辆信息", 60);
    printSeparator('=', 60);

    handleListVehicles();

    int id = getIntInput("请输入要删除的车辆编号: ", 1, MAX_VEHICLES);

    Vehicle* v = vehicleManager.findVehicleById(id);
    if (v == nullptr) {
        printf("\n未找到该车辆！\n");
        pauseScreen();
        return;
    }

    printf("\n待删除车辆信息:\n");
    vehiclePrintHeader();
    vehiclePrintRow(v);

    if (confirmAction("确认删除该车辆?")) {
        if (vehicleManager.deleteVehicle(id)) {
            printf("\n车辆删除成功！\n");
        } else {
            printf("\n车辆删除失败！\n");
        }
    } else {
        printf("\n已取消删除操作。\n");
    }
    pauseScreen();
}

void UI::handleModifyVehicle() {
    printSeparator('=', 60);
    printCentered("修改车辆信息", 60);
    printSeparator('=', 60);

    int id = getIntInput("请输入要修改的车辆编号: ", 1, MAX_VEHICLES);

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
    char temp[256];

    printf("\n请输入新值（直接回车保留原值）:\n");

    printf("车牌号码 [%s]: ", v.plateNo);
    clearInputBuffer();
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';
        if (temp[0] != '\0') {
            strncpy(v.plateNo, temp, MAX_PLATE_LEN - 1);
            v.plateNo[MAX_PLATE_LEN - 1] = '\0';
        }
    }

    printf("车辆品牌 [%s]: ", v.brand);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';
        if (temp[0] != '\0') {
            strncpy(v.brand, temp, MAX_BRAND_LEN - 1);
            v.brand[MAX_BRAND_LEN - 1] = '\0';
        }
    }

    printf("车辆类型 [%s]: ", v.type);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';
        if (temp[0] != '\0') {
            strncpy(v.type, temp, MAX_TYPE_LEN - 1);
            v.type[MAX_TYPE_LEN - 1] = '\0';
        }
    }

    printf("车辆颜色 [%s]: ", v.color);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';
        if (temp[0] != '\0') {
            strncpy(v.color, temp, MAX_COLOR_LEN - 1);
            v.color[MAX_COLOR_LEN - 1] = '\0';
        }
    }

    printf("购买日期 [%s]: ", v.purchaseDate);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';
        if (temp[0] != '\0') {
            strncpy(v.purchaseDate, temp, MAX_DATE_LEN - 1);
            v.purchaseDate[MAX_DATE_LEN - 1] = '\0';
        }
    }

    printf("日租金额 [%.2f]: ", v.dailyRate);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        double val = atof(temp);
        if (val > 0) v.dailyRate = val;
    }

    printf("行驶里程 [%.2f]: ", v.mileage);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        double val = atof(temp);
        if (val >= 0) v.mileage = val;
    }

    printf("保险信息 [%s]: ", v.insurance);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';
        if (temp[0] != '\0') {
            strncpy(v.insurance, temp, MAX_INSURANCE_LEN - 1);
            v.insurance[MAX_INSURANCE_LEN - 1] = '\0';
        }
    }

    if (vehicleManager.modifyVehicle(id, v)) {
        printf("\n车辆信息修改成功！\n");
    } else {
        printf("\n车辆信息修改失败！\n");
    }
    pauseScreen();
}

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

    ListNode<Vehicle>* node = list->getHead();
    while (node != nullptr) {
        vehiclePrintRow(&node->data);
        node = node->next;
    }
    printSeparator('=', 60);
    printf("共 %d 辆车\n", list->size());
    pauseScreen();
}

void UI::handleAddRenter() {
    printSeparator('=', 60);
    printCentered("添加租车用户", 60);
    printSeparator('=', 60);

    Renter r;
    renterInit(&r);

    getStringInput("姓名: ", r.name, MAX_NAME_LEN);
    r.age = getIntInput("年龄: ", 18, 100);
    r.gender = getCharInput("性别 (M/F): ", "MFmf");
    if (r.gender == 'm') r.gender = 'M';
    if (r.gender == 'f') r.gender = 'F';
    getStringInput("手机号码: ", r.phone, MAX_PHONE_LEN);
    getStringInput("驾照号码: ", r.licenseNo, MAX_LICENSE_LEN);
    getStringInput("身份证号: ", r.idCard, MAX_IDCARD_LEN);
    r.drivingYears = getIntInput("驾龄: ", 0, 60);

    if (renterManager.addRenter(r)) {
        printf("\n用户添加成功！\n");
    } else {
        printf("\n用户添加失败！\n");
    }
    pauseScreen();
}

void UI::handleDeleteRenter() {
    printSeparator('=', 60);
    printCentered("删除租车用户", 60);
    printSeparator('=', 60);

    handleListRenters();

    int id = getIntInput("请输入要删除的用户编号: ", 1, MAX_RENTERS);

    Renter* r = renterManager.findRenterById(id);
    if (r == nullptr) {
        printf("\n未找到该用户！\n");
        pauseScreen();
        return;
    }

    printf("\n待删除用户信息:\n");
    renterPrintHeader();
    renterPrintRow(r);

    if (confirmAction("确认删除该用户?")) {
        if (renterManager.deleteRenter(id)) {
            printf("\n用户删除成功！\n");
        } else {
            printf("\n用户删除失败！\n");
        }
    } else {
        printf("\n已取消删除操作。\n");
    }
    pauseScreen();
}

void UI::handleModifyRenter() {
    printSeparator('=', 60);
    printCentered("修改租车用户", 60);
    printSeparator('=', 60);

    int id = getIntInput("请输入要修改的用户编号: ", 1, MAX_RENTERS);

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
    char temp[256];

    printf("\n请输入新值（直接回车保留原值）:\n");

    printf("姓名 [%s]: ", r.name);
    clearInputBuffer();
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';
        if (temp[0] != '\0') {
            strncpy(r.name, temp, MAX_NAME_LEN - 1);
            r.name[MAX_NAME_LEN - 1] = '\0';
        }
    }

    printf("年龄 [%d]: ", r.age);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        int val = atoi(temp);
        if (val >= 18 && val <= 100) r.age = val;
    }

    printf("性别 [%c]: ", r.gender);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        if (temp[0] == 'M' || temp[0] == 'm' || temp[0] == 'F' || temp[0] == 'f') {
            if (temp[0] == 'm') temp[0] = 'M';
            if (temp[0] == 'f') temp[0] = 'F';
            r.gender = temp[0];
        }
    }

    printf("手机号码 [%s]: ", r.phone);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';
        if (temp[0] != '\0') {
            strncpy(r.phone, temp, MAX_PHONE_LEN - 1);
            r.phone[MAX_PHONE_LEN - 1] = '\0';
        }
    }

    printf("驾照号码 [%s]: ", r.licenseNo);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';
        if (temp[0] != '\0') {
            strncpy(r.licenseNo, temp, MAX_LICENSE_LEN - 1);
            r.licenseNo[MAX_LICENSE_LEN - 1] = '\0';
        }
    }

    printf("身份证号 [%s]: ", r.idCard);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';
        if (temp[0] != '\0') {
            strncpy(r.idCard, temp, MAX_IDCARD_LEN - 1);
            r.idCard[MAX_IDCARD_LEN - 1] = '\0';
        }
    }

    printf("驾龄 [%d]: ", r.drivingYears);
    fgets(temp, sizeof(temp), stdin);
    if (temp[0] != '\n' && temp[0] != '\0') {
        int val = atoi(temp);
        if (val >= 0 && val <= 60) r.drivingYears = val;
    }

    if (renterManager.modifyRenter(id, r)) {
        printf("\n用户信息修改成功！\n");
    } else {
        printf("\n用户信息修改失败！\n");
    }
    pauseScreen();
}

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

    ListNode<Renter>* node = list->getHead();
    while (node != nullptr) {
        renterPrintRow(&node->data);
        node = node->next;
    }
    printSeparator('=', 60);
    printf("共 %d 名用户\n", list->size());
    pauseScreen();
}

void UI::handleRentVehicle() {
    printSeparator('=', 60);
    printCentered("办理租车业务", 60);
    printSeparator('=', 60);

    LinkedList<Vehicle> available = vehicleManager.queryByStatus(STATUS_AVAILABLE);
    if (available.isEmpty()) {
        printf("\n当前没有可租车辆！\n");
        pauseScreen();
        return;
    }

    printf("\n可租车辆列表:\n");
    vehiclePrintHeader();
    printSeparator('=', 60);
    ListNode<Vehicle>* node = available.getHead();
    while (node != nullptr) {
        vehiclePrintRow(&node->data);
        node = node->next;
    }
    printSeparator('=', 60);

    int vehicleId = getIntInput("请输入要租的车辆编号: ", 1, MAX_VEHICLES);
    Vehicle* vehicle = vehicleManager.findVehicleById(vehicleId);
    if (vehicle == nullptr) {
        printf("\n未找到该车辆！\n");
        pauseScreen();
        return;
    }
    if (vehicle->status != STATUS_AVAILABLE) {
        printf("\n该车辆不可租！\n");
        pauseScreen();
        return;
    }

    int renterId = getIntInput("请输入租车用户编号: ", 1, MAX_RENTERS);
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
    } else {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';
        strncpy(rentDate, temp, MAX_DATE_LEN - 1);
        rentDate[MAX_DATE_LEN - 1] = '\0';
    }

    getStringInput("预计归还日期 (YYYY-MM-DD): ", expectedReturnDate, MAX_DATE_LEN);

    if (!isValidDateRange(rentDate, expectedReturnDate)) {
        printf("\n日期范围不合法！\n");
        pauseScreen();
        return;
    }

    int days = daysBetween(rentDate, expectedReturnDate);
    if (days < 1) days = 1;
    double deposit = vehicle->dailyRate * days * 2.0;

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

void UI::handleReturnVehicle() {
    printSeparator('=', 60);
    printCentered("办理退车业务", 60);
    printSeparator('=', 60);

    LinkedList<RentRecord> activeRents = rentManager.getActiveRents();
    if (activeRents.isEmpty()) {
        printf("\n当前没有进行中的租车记录！\n");
        pauseScreen();
        return;
    }

    printf("\n进行中的租车记录:\n");
    rentRecordPrintHeader();
    printSeparator('=', 60);
    ListNode<RentRecord>* node = activeRents.getHead();
    while (node != nullptr) {
        rentRecordPrintRow(&node->data);
        node = node->next;
    }
    printSeparator('=', 60);

    int rentId = getIntInput("请输入要退车的租车编号: ", 1, MAX_RENTS);
    RentRecord* record = rentManager.findRentById(rentId);
    if (record == nullptr) {
        printf("\n未找到该租车记录！\n");
        pauseScreen();
        return;
    }
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
    } else {
        size_t len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n') temp[len - 1] = '\0';
        strncpy(actualReturnDate, temp, MAX_DATE_LEN - 1);
        actualReturnDate[MAX_DATE_LEN - 1] = '\0';
    }

    int days = daysBetween(record->rentDate, actualReturnDate);
    if (days < 1) days = 1;
    double totalFee = record->dailyRate * days;
    double refund = record->deposit - totalFee;
    if (refund < 0) refund = 0;

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
    } else {
        printf("\n退车办理失败！\n");
    }
    pauseScreen();
}

void UI::handlePrintReceipt() {
    printSeparator('=', 60);
    printCentered("打印票据", 60);
    printSeparator('=', 60);

    int rentId = getIntInput("请输入租车编号: ", 1, MAX_RENTS);
    RentRecord* record = rentManager.findRentById(rentId);
    if (record == nullptr) {
        printf("\n未找到该租车记录！\n");
        pauseScreen();
        return;
    }

    if (record->status == RENT_ACTIVE) {
        int days = daysBetween(record->rentDate, record->expectedReturnDate);
        if (days < 1) days = 1;
        Receipt::printRentReceipt(record->id, record->vehicleId,
                                   record->vehicleBrand, record->vehiclePlate,
                                   record->vehicleBrand, record->renterName,
                                   record->renterLicense, record->rentDate,
                                   record->expectedReturnDate,
                                   record->deposit, record->dailyRate);
    } else {
        int days = daysBetween(record->rentDate, record->actualReturnDate);
        if (days < 1) days = 1;
        double refund = record->deposit - record->totalFee;
        if (refund < 0) refund = 0;
        Receipt::printReturnReceipt(record->id, record->vehicleId,
                                     record->vehicleBrand, record->vehiclePlate,
                                     record->renterName, record->rentDate,
                                     record->actualReturnDate, days,
                                     record->dailyRate, record->deposit,
                                     record->totalFee, refund);
    }
    pauseScreen();
}

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

        int choice = getIntInput("请选择查询方式 [0-4]: ", 0, 4);

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
                int status = getIntInput("请选择状态: ", 0, 2);
                result = vehicleManager.queryByStatus(status);
                break;
            }
            case 0: return;
        }

        if (result.isEmpty()) {
            printf("\n未找到匹配的车辆信息。\n");
            pauseScreen();
            continue;
        }

        printf("\n查询结果 (%d 条):\n", result.size());
        vehiclePrintHeader();
        printSeparator('=', 60);
        ListNode<Vehicle>* node = result.getHead();
        while (node != nullptr) {
            vehiclePrintRow(&node->data);
            node = node->next;
        }
        printSeparator('=', 60);
        pauseScreen();
    }
}

void UI::handleQueryRenters() {
    while (true) {
        printSeparator('=', 60);
        printCentered("租车用户查询", 60);
        printSeparator('=', 60);
        printf("  1. 按姓名查询\n");
        printf("  2. 按驾照号查询\n");
        printf("  0. 返回\n");
        printSeparator('=', 60);

        int choice = getIntInput("请选择查询方式 [0-2]: ", 0, 2);

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

        if (result.isEmpty()) {
            printf("\n未找到匹配的用户信息。\n");
            pauseScreen();
            continue;
        }

        printf("\n查询结果 (%d 条):\n", result.size());
        renterPrintHeader();
        printSeparator('=', 60);
        ListNode<Renter>* node = result.getHead();
        while (node != nullptr) {
            renterPrintRow(&node->data);
            node = node->next;
        }
        printSeparator('=', 60);
        pauseScreen();
    }
}

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

        int choice = getIntInput("请选择查询方式 [0-4]: ", 0, 4);

        LinkedList<RentRecord> result;

        switch (choice) {
            case 1: {
                int vehicleId = getIntInput("请输入车辆编号: ", 1, MAX_VEHICLES);
                result = rentManager.queryByVehicleId(vehicleId);
                break;
            }
            case 2: {
                int renterId = getIntInput("请输入用户编号: ", 1, MAX_RENTERS);
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
                int status = getIntInput("请选择状态: ", 0, 1);
                result = rentManager.queryByStatus(status);
                break;
            }
            case 0: return;
        }

        if (result.isEmpty()) {
            printf("\n未找到匹配的租车记录。\n");
            pauseScreen();
            continue;
        }

        printf("\n查询结果 (%d 条):\n", result.size());
        rentRecordPrintHeader();
        printSeparator('=', 60);
        ListNode<RentRecord>* node = result.getHead();
        while (node != nullptr) {
            rentRecordPrintRow(&node->data);
            node = node->next;
        }
        printSeparator('=', 60);
        pauseScreen();
    }
}

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
    } else if (choice == '2') {
        char type[MAX_TYPE_LEN];
        getStringInput("请输入类型: ", type, MAX_TYPE_LEN);
        int count = vehicleManager.countByType(type);
        printf("\n类型 [%s] 的车辆数: %d\n", type, count);
    } else if (choice == '3') {
        char color[MAX_COLOR_LEN];
        getStringInput("请输入颜色: ", color, MAX_COLOR_LEN);
        int count = vehicleManager.countByColor(color);
        printf("\n颜色 [%s] 的车辆数: %d\n", color, count);
    }

    pauseScreen();
}

void UI::handleRenterStatistics() {
    printSeparator('=', 60);
    printCentered("租车用户统计", 60);
    printSeparator('=', 60);
    renterManager.printStatistics();
    pauseScreen();
}

void UI::handleRentStatistics() {
    printSeparator('=', 60);
    printCentered("租车记录统计", 60);
    printSeparator('=', 60);
    rentManager.printStatistics();
    pauseScreen();
}

void UI::handleChangePassword() {
    printSeparator('=', 60);
    printCentered("修改密码", 60);
    printSeparator('=', 60);

    char oldPassword[64];
    char newPassword[64];
    char confirmPassword[64];

    printf("请输入旧密码: ");
    clearInputBuffer();
    fgets(oldPassword, sizeof(oldPassword), stdin);
    size_t len = strlen(oldPassword);
    if (len > 0 && oldPassword[len - 1] == '\n') oldPassword[len - 1] = '\0';

    printf("请输入新密码: ");
    fgets(newPassword, sizeof(newPassword), stdin);
    len = strlen(newPassword);
    if (len > 0 && newPassword[len - 1] == '\n') newPassword[len - 1] = '\0';

    printf("请确认新密码: ");
    fgets(confirmPassword, sizeof(confirmPassword), stdin);
    len = strlen(confirmPassword);
    if (len > 0 && confirmPassword[len - 1] == '\n') confirmPassword[len - 1] = '\0';

    if (strcmp(newPassword, confirmPassword) != 0) {
        printf("\n两次输入的密码不一致！\n");
        pauseScreen();
        return;
    }

    if (authManager.setPassword(oldPassword, newPassword)) {
        printf("\n密码修改成功！\n");
    } else {
        printf("\n密码修改失败，请检查旧密码是否正确。\n");
    }
    pauseScreen();
}

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

    showProgressBar("正在导出报表", 40, 100);

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

    showProgressBar("正在导出报表", 60, 100);

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

    showProgressBar("正在导出报表", 80, 100);

    fprintf(fp, "\n===== 统计汇总 =====\n\n");
    fprintf(fp, "车辆总数: %d\n", vehicleManager.getTotalCount());
    fprintf(fp, "可租车辆: %d\n", vehicleManager.getAvailableCount());
    fprintf(fp, "已租车辆: %d\n", vehicleManager.getRentedCount());
    fprintf(fp, "用户总数: %d\n", renterManager.getTotalCount());
    fprintf(fp, "租车记录: %d\n", rentManager.getTotalCount());
    fprintf(fp, "进行中: %d\n", rentManager.getActiveCount());
    fprintf(fp, "总收入: %.2f 元\n", rentManager.getTotalRevenue());

    showProgressBar("正在导出报表", 100, 100);

    fclose(fp);
    printf("\n报表已导出到文件: %s\n", filename);
    pauseScreen();
}

void UI::handleViewLog() {
    printSeparator('=', 60);
    printCentered("系统日志", 60);
    printSeparator('=', 60);
    Logger::showLog();
    pauseScreen();
}

void UI::handleClearData() {
    printSeparator('=', 60);
    printCentered("清空全部数据", 60);
    printSeparator('=', 60);

    printf("\n警告：此操作将清空所有车辆、用户和租车记录数据！\n");
    printf("此操作不可恢复！\n\n");

    if (!confirmAction("确认清空全部数据?")) {
        printf("\n已取消操作。\n");
        pauseScreen();
        return;
    }

    LinkedList<Vehicle>* vehicles = vehicleManager.getAllVehicles();
    while (vehicles->getHead() != nullptr) {
        vehicleManager.deleteVehicle(vehicles->getHead()->data.id);
    }

    LinkedList<Renter>* renters = renterManager.getAllRenters();
    while (renters->getHead() != nullptr) {
        renterManager.deleteRenter(renters->getHead()->data.id);
    }

    LinkedList<RentRecord>* records = rentManager.getAllRentRecords();
    ListNode<RentRecord>* node = records->getHead();
    while (node != nullptr) {
        ListNode<RentRecord>* next = node->next;
        records->removeNode(node);
        node = next;
    }

    FILE* fp = fopen(FILE_VEHICLE, "wb");
    if (fp != nullptr) fclose(fp);
    fp = fopen(FILE_RENTER, "wb");
    if (fp != nullptr) fclose(fp);
    fp = fopen(FILE_RENT, "wb");
    if (fp != nullptr) fclose(fp);

    Logger::logOperation("清空全部数据");

    printf("\n全部数据已清空！\n");
    pauseScreen();
}

void UI::handleFuzzySearch() {
    printSeparator('=', 60);
    printCentered("模糊搜索", 60);
    printSeparator('=', 60);

    char keyword[MAX_BRAND_LEN];
    getStringInput("请输入搜索关键词: ", keyword, MAX_BRAND_LEN);

    printf("\n正在搜索...\n");

    LinkedList<Vehicle> vehicleResults = vehicleManager.queryFuzzy(keyword);
    LinkedList<Renter> renterResults = renterManager.queryFuzzy(keyword);
    LinkedList<RentRecord> rentResults = rentManager.queryFuzzy(keyword);

    int totalResults = vehicleResults.size() + renterResults.size() + rentResults.size();

    if (totalResults == 0) {
        printf("\n未找到匹配的结果。\n");
        pauseScreen();
        return;
    }

    printf("\n搜索 \"%s\" 的结果 (共 %d 条):\n", keyword, totalResults);

    if (!vehicleResults.isEmpty()) {
        printf("\n--- 车辆匹配 (%d 条) ---\n", vehicleResults.size());
        vehiclePrintHeader();
        ListNode<Vehicle>* vNode = vehicleResults.getHead();
        while (vNode != nullptr) {
            vehiclePrintRow(&vNode->data);
            vNode = vNode->next;
        }
    }

    if (!renterResults.isEmpty()) {
        printf("\n--- 用户匹配 (%d 条) ---\n", renterResults.size());
        renterPrintHeader();
        ListNode<Renter>* rNode = renterResults.getHead();
        while (rNode != nullptr) {
            renterPrintRow(&rNode->data);
            rNode = rNode->next;
        }
    }

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

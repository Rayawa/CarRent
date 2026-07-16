/*
 * 汽车租赁管理系统
 * 文件: menu3_rent.cpp
 * 功能: 租车业务办理子菜单
 * 日期: 2026-07
 */
void menu3Rent() {
    while (true) {
        printf("\n1.办理租车 2.显示租车记录 0.返回\n");
        int c = inputInt("请选择: ", 0, 2);
        if (c == 0) return;
        if (c == 2) { printAllRents(); pauseScreen(); continue; }
        // 先遍历链表列出所有可租车辆，若无则提示
        printf("\n可用车辆:\n");
        int avail = countAvailableVehicles();   // 遍历vehicleHead统计status==可租的数量
        if (avail == 0) { printf("没有剩余车辆。\n"); pauseScreen(); continue; }
        VehicleNode* cur = vehicleHead;
        while (cur) {
            if (cur->data.status == STATUS_AVAILABLE) printVehicleRow(cur->data);
            cur = cur->next;
        }
        // 办理租车：输入车辆ID+用户ID→校验日期格式→关联创建租车记录→打印票据
        int vehicleId = inputInt("车辆ID: ", 1, 9999);
        int renterId = inputInt("用户ID: ", 1, 9999);
        char rentDate[MAX_DATE_LEN], expectedDate[MAX_DATE_LEN];
        inputLine("租车日期(YYYY-MM-DD): ", rentDate, MAX_DATE_LEN);
        inputLine("预计归还日期(YYYY-MM-DD): ", expectedDate, MAX_DATE_LEN);
        if (!isValidDate(rentDate) || !isValidDate(expectedDate)) {   // 含闰年+每月天数校验
            printf("日期格式错误(需YYYY-MM-DD)\n"); pauseScreen(); continue;
        }
        if (!addRentRecord(vehicleId, renterId, rentDate, expectedDate)) {
            printf("办理失败(车辆不可租或不存在)\n"); pauseScreen(); continue;
        }
        printf("已办理租车\n");
        // 找到刚创建的租车记录，打印租车票据
        RentNode* rn = rentHead;
        while (rn) { if (rn->data.vehicleId == vehicleId && rn->data.renterId == renterId) break; rn = rn->next; }
        if (rn) printRentTicket(rn->data);   // 格式化输出"汽车租赁公司租车票据"
        pauseScreen();
    }
}

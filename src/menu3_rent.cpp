/*
 * 汽车租赁管理系统
 * 文件: menu3_rent.cpp
 * 功能: 租车业务办理子菜单
 * 日期: 2026-07-16
 */
void menu3Rent() {
    while (true) {
        printf("\n1.办理租车 2.显示租车记录 0.返回\n");
        int c = inputInt("请选择: ", 0, 2);
        if (c == 0) return;
        if (c == 2) { printAllRents(); pauseScreen(); continue; } // 直接打印
        printf("\n可用车辆:\n");
        int avail = countAvailableVehicles();   // 可用车数量存在avail
        if (avail == 0) { printf("没有剩余车辆。\n"); pauseScreen(); continue; } // 若无可用跳出
        VehicleNode* cur = vehicleHead;
        while (cur) { // 遍历打印所有车信息，链表下一个
            if (cur->data.status == STATUS_AVAILABLE) printVehicleRow(cur->data);
            cur = cur->next;
        }
        int vehicleId = inputInt("车辆ID: ", 1, 9999);
        int renterId = inputInt("用户ID: ", 1, 9999);
        char rentDate[MAX_DATE_LEN], expectedDate[MAX_DATE_LEN]; // 定义两个日期并输入
        inputLine("租车日期(YYYY-MM-DD): ", rentDate, MAX_DATE_LEN);
        inputLine("预计归还日期(YYYY-MM-DD): ", expectedDate, MAX_DATE_LEN);
        if (!isValidDate(rentDate) || !isValidDate(expectedDate)) { // 校验日期格式
            printf("日期格式错误(需YYYY-MM-DD)\n"); pauseScreen(); continue;
        }
        if (!addRentRecord(vehicleId, renterId, rentDate, expectedDate)) { // 校验的同时进入函数办理租车，错误则跳出
            printf("办理失败(车辆不可租或不存在)\n"); pauseScreen(); continue;
        }
        printf("已办理租车\n");
        RentNode* rn = rentHead;
        while (rn) { if (rn->data.vehicleId == vehicleId && rn->data.renterId == renterId) break; rn = rn->next; } // 找到刚刚的车
        if (rn) printRentTicket(rn->data); // 打印租车票据
        pauseScreen();
    }
}

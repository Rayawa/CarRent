/*
 * 汽车租赁管理系统
 * 文件: menu4_return.cpp
 * 功能: 退车业务办理子菜单
 * 日期: 2026-07-16
 */
void menu4Return() {
    while (true) {
        printf("\n1.办理退车 2.显示租车记录 3.打印票据 0.返回\n");
        int c = inputInt("请选择: ", 0, 3);
        if (c == 0) return;
        if (c == 2) { printAllRents(); pauseScreen(); continue; } // 直接打印
        int rentId = inputInt("租车记录ID: ", 1, 9999); // 2与3均需要租车记录，提前输入存在rentId
        RentRecord* r = findRent(rentId);
        if (!r) { printf("没找到\n"); pauseScreen(); continue; } // 没有就没找到，提前判断
        if (c == 3) {
            printf("租车ID:%d 车辆:%d 用户:%d\n", r->id, r->vehicleId, r->renterId);
            printf("日期:%s -> %s\n", r->rentDate, r->expectedReturnDate);
            printRentTicket(*r); // 格式化输出
            pauseScreen(); continue;
        }
        char returnDate[MAX_DATE_LEN];
        inputLine("实际归还日期(YYYY-MM-DD): ", returnDate, MAX_DATE_LEN); // 输入归还日期
        double totalFee = 0, refund = 0;
        if (!returnRent(rentId, returnDate, totalFee, refund)) { // 进入函数计算出结果，如果false则跳出
            printf("办理失败(已归还或不存在)\n"); pauseScreen(); continue;
        }
        RentRecord* rec = findRent(rentId);
        int days = calcDateDiff(rec->rentDate, returnDate); // 计算天数
        if (days < 1) days = 1; // 错误处理
        printReturnReceipt(*rec, days, totalFee, refund); // 打印退车票据
        printf("已退车\n");
        pauseScreen();
    }
}

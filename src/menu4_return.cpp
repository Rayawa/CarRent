/*
 * 汽车租赁管理系统
 * 文件: menu4_return.cpp  功能: 退车业务办理子菜单
 * 作者: 孙老师组     日期: 2026-07
 */
//==========================菜单4：退车业务办理====================
// 按天数×日租金计算总费用→退还押金差额→打印退车收据
void menu4Return() {
    while (true) {
        printf("\n1.办理退车 2.显示租车记录 3.打印票据 0.返回\n");
        int c = inputInt("请选择: ", 0, 3);
        if (c == 0) return;
        if (c == 2) { printAllRents(); pauseScreen(); continue; }
        int rentId = inputInt("租车记录ID: ", 1, 9999);
        RentRecord* r = findRent(rentId);
        if (!r) { printf("没找到\n"); pauseScreen(); continue; }
        // 打印票据：输出该租车记录的基本信息
        if (c == 3) {
            printf("租车ID:%d 车辆:%d 用户:%d\n", r->id, r->vehicleId, r->renterId);
            printf("日期:%s -> %s\n", r->rentDate, r->expectedReturnDate);
            printRentTicket(*r);
            pauseScreen(); continue;
        }
        // 办理退车：输入归还日期→计算费用→打印收据
        char returnDate[MAX_DATE_LEN];
        inputLine("实际归还日期(YYYY-MM-DD): ", returnDate, MAX_DATE_LEN);
        double totalFee = 0, refund = 0;
        if (!returnRent(rentId, returnDate, totalFee, refund)) {
            printf("办理失败(已归还或不存在)\n"); pauseScreen(); continue;
        }
        RentRecord* rec = findRent(rentId);
        int days = calcDateDiff(rec->rentDate, returnDate);
        if (days < 1) days = 1;
        printReturnReceipt(*rec, days, totalFee, refund);
        printf("已退车\n");
        pauseScreen();
    }
}

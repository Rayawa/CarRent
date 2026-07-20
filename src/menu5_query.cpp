/*
 * 汽车租赁管理系统
 * 文件: menu5_query.cpp
 * 功能: 信息查询子菜单
 * 日期: 2026-07-16
 */
void menu5Query() {
    while (true) {
        printf("\n1.分类查询 2.模糊搜索 0.返回\n");
        int c = inputInt("请选择: ", 0, 2);
        if (c == 0) return;
        if (c == 2) {
            char key[64]; // 定义并输入模糊搜索关键字
            inputLine("关键词: ", key, sizeof(key));
            printf("\n车辆匹配:\n"); printVehicleHeader();
            VehicleNode* vc = vehicleHead;
            while (vc) { // 遍历所有车辆，strstr对比搜索关键字又没有出现在brand和plateNo里面，有就输出，链表下一个
                if (strstr(vc->data.brand, key) || strstr(vc->data.plateNo, key)) printVehicleRow(vc->data);
                vc = vc->next;
            }
            printf("\n用户匹配:\n"); printRenterHeader();
            RenterNode* rc = renterHead;
            while (rc) {// 遍历所有用户，strstr对比搜索关键字又没有出现在name和licenseNo里面，有就输出，链表下一个
                if (strstr(rc->data.name, key) || strstr(rc->data.licenseNo, key)) printRenterRow(rc->data);
                rc = rc->next;
            }
            pauseScreen();
            continue;
        }
        printf("\n1.车辆查询 2.用户查询 3.租车记录查询 0.返回\n");
        int qc = inputInt("请选择: ", 0, 3);
        if (qc == 0) continue;
        if (qc == 1) {
            printf("\n1.按品牌 2.按类型 3.按颜色 4.按状态 0.返回\n");
            int sc = inputInt("请选择: ", 0, 4);
            if (sc == 0) continue;
            char key[32];
            if (sc <= 3) inputLine("输入关键词: ", key, sizeof(key)); // 如果是1-3则输入搜索关键字
            int st = sc == 4 ? inputInt("状态(0可租/1已租/2维修): ", 0, 2) : -1; // 如果是4就保存在st里面，否则-1
            printVehicleHeader();
            VehicleNode* cur = vehicleHead;
            while (cur) {
                bool match = false;
                if (sc == 1) match = strstr(cur->data.brand, key);
                else if (sc == 2) match = strstr(cur->data.type, key);
                else if (sc == 3) match = strstr(cur->data.color, key);
                else if (sc == 4) match = (cur->data.status == st); // 1-3通过strstr对比搜索关键字，出现了就标记match为true然后输出整个data，4对比status
                if (match) printVehicleRow(cur->data);
                cur = cur->next; // 链表下一个
            }
            pauseScreen();
        } else if (qc == 2) {
            printf("\n1.按姓名 2.按驾照号 3.按性别 0.返回\n");
            int sc = inputInt("请选择: ", 0, 3);
            if (sc == 0) continue;
            char key[32];
            if (sc <= 2) inputLine("输入关键词: ", key, sizeof(key));
            printRenterHeader();
            RenterNode* cur = renterHead;
            while (cur) {
                bool match = false;
                if (sc == 1) match = strstr(cur->data.name, key);
                else if (sc == 2) match = strstr(cur->data.licenseNo, key); // 和上面同理
                else if (sc == 3) match = (cur->data.gender == key[0] || cur->data.gender == (key[0] - 32)); // 同理但是增加大小写处理
                if (match) printRenterRow(cur->data);
                cur = cur->next; // 链表下一个
            }
            pauseScreen();
        } else if (qc == 3) {
            printf("\n1.按状态 2.按日期范围 0.返回\n");
            int sc = inputInt("请选择: ", 0, 2);
            if (sc == 0) continue;
            printRentHeader();
            if (sc == 1) {
                int st = inputInt("状态(0租用中/1已归还): ", 0, 1);
                RentNode* cur = rentHead;
                while (cur) { if (cur->data.status == st) printRentRow(cur->data); cur = cur->next; } // 与上同理
            } else {
                char d1[MAX_DATE_LEN], d2[MAX_DATE_LEN]; // 定义并输入两个日期
                inputLine("起始日期(YYYY-MM-DD): ", d1, MAX_DATE_LEN);
                inputLine("结束日期(YYYY-MM-DD): ", d2, MAX_DATE_LEN);
                if (!isValidDate(d1) || !isValidDate(d2)) { printf("日期格式错误\n"); pauseScreen(); continue; } // 判断日期格式
                int start = dateToDays(d1), end = dateToDays(d2);// 转换天数
                RentNode* cur = rentHead;
                while (cur) {
                    int rd = dateToDays(cur->data.rentDate); // rd为租用日期
                    if (rd >= start && rd <= end) printRentRow(cur->data); // 从起始日期到结束日期搜索
                    cur = cur->next;
                }
            }
            pauseScreen();
        }
    }
}

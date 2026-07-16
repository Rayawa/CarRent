/*
 * 汽车租赁管理系统
 * 文件: menu5_query.cpp  功能: 信息查询子菜单
 * 作者: 孙老师组     日期: 2026-07
 */
//==========================菜单5：信息查询====================
// 按类型/品牌/颜色/状态/姓名/驾照号/日期分类筛选查询
void menu5Query() {
    while (true) {
        printf("\n1.车辆查询 2.用户查询 3.租车记录查询 0.返回\n");
        int c = inputInt("请选择: ", 0, 3);
        if (c == 0) return;
        // 车辆查询：按品牌/类型/颜色/状态筛选
        if (c == 1) {
            printf("\n1.按品牌 2.按类型 3.按颜色 4.按状态 0.返回\n");
            int sc = inputInt("请选择: ", 0, 4);
            if (sc == 0) continue;
            char key[32];
            if (sc <= 3) inputLine("输入关键词: ", key, sizeof(key));
            int st = sc == 4 ? inputInt("状态(0可租/1已租/2维修): ", 0, 2) : -1;
            printVehicleHeader();
            VehicleNode* cur = vehicleHead;
            while (cur) {
                bool match = false;
                if (sc == 1) match = strstr(cur->data.brand, key);
                else if (sc == 2) match = strstr(cur->data.type, key);
                else if (sc == 3) match = strstr(cur->data.color, key);
                else if (sc == 4) match = (cur->data.status == st);
                if (match) printVehicleRow(cur->data);
                cur = cur->next;
            }
            pauseScreen();
        // 用户查询：按姓名/驾照号/性别筛选
        } else if (c == 2) {
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
                else if (sc == 2) match = strstr(cur->data.licenseNo, key);
                else if (sc == 3) match = (cur->data.gender == key[0] || cur->data.gender == (key[0] - 32));
                if (match) printRenterRow(cur->data);
                cur = cur->next;
            }
            pauseScreen();
        // 租车记录查询：按状态/日期筛选
        } else if (c == 3) {
            printf("\n1.按状态 2.按日期范围 0.返回\n");
            int sc = inputInt("请选择: ", 0, 2);
            if (sc == 0) continue;
            printRentHeader();
            if (sc == 1) {
                int st = inputInt("状态(0租用中/1已归还): ", 0, 1);
                RentNode* cur = rentHead;
                while (cur) { if (cur->data.status == st) printRentRow(cur->data); cur = cur->next; }
            } else {
                char d1[MAX_DATE_LEN], d2[MAX_DATE_LEN];
                inputLine("起始日期(YYYY-MM-DD): ", d1, MAX_DATE_LEN);
                inputLine("结束日期(YYYY-MM-DD): ", d2, MAX_DATE_LEN);
                if (!isValidDate(d1) || !isValidDate(d2)) { printf("日期格式错误\n"); pauseScreen(); continue; }
                int start = dateToDays(d1), end = dateToDays(d2);
                RentNode* cur = rentHead;
                while (cur) {
                    int rd = dateToDays(cur->data.rentDate);
                    if (rd >= start && rd <= end) printRentRow(cur->data);
                    cur = cur->next;
                }
            }
            pauseScreen();
        }
    }
}

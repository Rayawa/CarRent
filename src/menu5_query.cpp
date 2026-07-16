/*
 * 汽车租赁管理系统
 * 文件: menu5_query.cpp
 * 功能: 信息查询子菜单
 * 日期: 2026-07
 */
void menu5Query() {
    while (true) {
        printf("\n1.分类查询 2.模糊搜索 0.返回\n");
        int c = inputInt("请选择: ", 0, 2);
        if (c == 0) return;
        // 模糊搜索：strstr在品牌/车牌/姓名/驾照号中做跨实体子串匹配
        if (c == 2) {
            char key[64];
            inputLine("关键词: ", key, sizeof(key));
            printf("\n车辆匹配:\n"); printVehicleHeader();
            VehicleNode* vc = vehicleHead;
            while (vc) {
                if (strstr(vc->data.brand, key) || strstr(vc->data.plateNo, key)) printVehicleRow(vc->data);
                vc = vc->next;
            }
            printf("\n用户匹配:\n"); printRenterHeader();
            RenterNode* rc = renterHead;
            while (rc) {
                if (strstr(rc->data.name, key) || strstr(rc->data.licenseNo, key)) printRenterRow(rc->data);
                rc = rc->next;
            }
            pauseScreen();
            continue;
        }
        // 分类查询：车辆(品牌/类型/颜色/状态)、用户(姓名/驾照/性别)、租车(状态/日期范围)
        printf("\n1.车辆查询 2.用户查询 3.租车记录查询 0.返回\n");
        int qc = inputInt("请选择: ", 0, 3);
        if (qc == 0) continue;
        if (qc == 1) {
            printf("\n1.按品牌 2.按类型 3.按颜色 4.按状态 0.返回\n");
            int sc = inputInt("请选择: ", 0, 4);
            if (sc == 0) continue;
            char key[32];
            if (sc <= 3) inputLine("输入关键词: ", key, sizeof(key));
            int st = sc == 4 ? inputInt("状态(0可租/1已租/2维修): ", 0, 2) : -1;
            printVehicleHeader();
            VehicleNode* cur = vehicleHead;
            while (cur) {
                // 遍历链表→strstr子串匹配or状态相等→命中则输出
                bool match = false;
                if (sc == 1) match = strstr(cur->data.brand, key);
                else if (sc == 2) match = strstr(cur->data.type, key);
                else if (sc == 3) match = strstr(cur->data.color, key);
                else if (sc == 4) match = (cur->data.status == st);
                if (match) printVehicleRow(cur->data);
                cur = cur->next;
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
                else if (sc == 2) match = strstr(cur->data.licenseNo, key);
                // 性别匹配：大小写不敏感(M/m、F/f都可以)
                else if (sc == 3) match = (cur->data.gender == key[0] || cur->data.gender == (key[0] - 32));
                if (match) printRenterRow(cur->data);
                cur = cur->next;
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
                while (cur) { if (cur->data.status == st) printRentRow(cur->data); cur = cur->next; }
            } else {
                // 日期范围查询：将起止日期转为天数→遍历链表比较数值范围
                char d1[MAX_DATE_LEN], d2[MAX_DATE_LEN];
                inputLine("起始日期(YYYY-MM-DD): ", d1, MAX_DATE_LEN);
                inputLine("结束日期(YYYY-MM-DD): ", d2, MAX_DATE_LEN);
                if (!isValidDate(d1) || !isValidDate(d2)) { printf("日期格式错误\n"); pauseScreen(); continue; }
                int start = dateToDays(d1), end = dateToDays(d2);    // 转为自2000-01-01起的天数
                RentNode* cur = rentHead;
                while (cur) {
                    int rd = dateToDays(cur->data.rentDate);         // 将租车日期也转为天数
                    if (rd >= start && rd <= end) printRentRow(cur->data);   // 在范围内则输出
                    cur = cur->next;
                }
            }
            pauseScreen();
        }
    }
}

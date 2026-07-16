/*
 * 汽车租赁管理系统
 * 文件: menu6_statistics.cpp  功能: 统计汇总子菜单
 * 作者: 孙老师组     日期: 2026-07
 */
//==========================菜单6：统计汇总====================
// 按车型/品牌/颜色/性别/驾龄/月份分组统计,ASCII柱状图展示
void menu6Statistics() {
    printf("\n===== 系统概览 =====\n");
    printStatistics();
    while (true) {
        printf("\n1.车辆统计 2.用户统计 3.租车统计 0.返回\n");
        int c = inputInt("请选择: ", 0, 3);
        if (c == 0) return;
        if (c == 1) {
            printf("\n1.按品牌 2.按类型 3.按颜色 0.返回\n");
            int sc = inputInt("请选择: ", 0, 3);
            if (sc == 0) continue;
            char labels[50][32]; int values[50]; int n = 0;
            if (sc == 1) n = countVehiclesByBrand(labels, values, 50);
            else if (sc == 2) n = countVehiclesByType(labels, values, 50);
            else n = countVehiclesByColor(labels, values, 50);
            printf("\n");
            const char* labelPtrs[50];
            for (int i = 0; i < n; i++) labelPtrs[i] = labels[i];
            drawBarChart(labelPtrs, values, n);
            pauseScreen();
        } else if (c == 2) {
            printf("\n1.按性别 2.按驾龄分段 0.返回\n");
            int sc = inputInt("请选择: ", 0, 2);
            if (sc == 0) continue;
            if (sc == 1) {
                int vals[2]; countRentersByGender(vals);
                printf("\n  男性      [%3d] ", vals[0]);
                int bar = (vals[0] + vals[1]) > 0 ? vals[0] * 30 / (vals[0] + vals[1]) : 0;
                for (int j = 0; j < bar; j++) printf("#");
                printf("\n  女性      [%3d] ", vals[1]);
                bar = (vals[0] + vals[1]) > 0 ? vals[1] * 30 / (vals[0] + vals[1]) : 0;
                for (int j = 0; j < bar; j++) printf("#");
                printf("\n");
            } else {
                int vals[3]; countRentersByDrivingYears(vals);
                const char* lb[] = {"0-3年", "4-10年", "10年+"};
                int mx = 0; for (int i = 0; i < 3; i++) if (vals[i] > mx) mx = vals[i];
                for (int i = 0; i < 3; i++) {
                    printf("  %-6s [%3d] ", lb[i], vals[i]);
                    int bar = mx > 0 ? vals[i] * 30 / mx : 0;
                    for (int j = 0; j < bar; j++) printf("#");
                    printf("\n");
                }
            }
            pauseScreen();
        } else if (c == 3) {
            int vals[12]; countRentsByMonth(vals);
            const char* mb[] = {"1月","2月","3月","4月","5月","6月","7月","8月","9月","10月","11月","12月"};
            int mx = 0; for (int i = 0; i < 12; i++) if (vals[i] > mx) mx = vals[i];
            printf("\n月度租车量:\n");
            for (int i = 0; i < 12; i++) {
                printf("  %-4s [%3d] ", mb[i], vals[i]);
                int bar = mx > 0 ? vals[i] * 30 / mx : 0;
                for (int j = 0; j < bar; j++) printf("#");
                printf("\n");
            }
            pauseScreen();
        }
    }
}

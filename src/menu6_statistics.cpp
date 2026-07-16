/*
 * 汽车租赁管理系统
 * 文件: menu6_statistics.cpp  功能: 统计汇总子菜单
 * 作者: 孙老师组     日期: 2026-07
 */
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
            drawBarChart(labels, values, n);
            pauseScreen();
        } else if (c == 2) {
            printf("\n1.按性别 2.按驾龄分段 0.返回\n");
            int sc = inputInt("请选择: ", 0, 2);
            if (sc == 0) continue;
            if (sc == 1) {
                int vals[2]; countRentersByGender(vals);
                char gl[2][32]; strncpy(gl[0], "男性", 31); strncpy(gl[1], "女性", 31);
                drawBarChart(gl, vals, 2);
            } else {
                int vals[3]; countRentersByDrivingYears(vals);
                char dl[3][32]; strncpy(dl[0], "0-3年", 31); strncpy(dl[1], "4-10年", 31); strncpy(dl[2], "10年+", 31);
                drawBarChart(dl, vals, 3);
            }
            pauseScreen();
        } else if (c == 3) {
            int vals[12]; countRentsByMonth(vals);
            char ml[12][32];
            for (int i = 0; i < 12; i++) snprintf(ml[i], 32, "%d月", i + 1);
            drawBarChart(ml, vals, 12);
            pauseScreen();
        }
    }
}

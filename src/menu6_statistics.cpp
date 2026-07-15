//==========================菜单6：统计汇总====================
// 展示系统数据统计概览，包括车辆、用户、租车记录的汇总信息
void menu6Statistics() {
    printf("\n===== 统计 =====\n");
    printStatistics();
    // 按品牌分组展示：遍历车辆数组依次输出品牌名
    printf("\n按品牌简单统计车辆:\n");
    for (int i = 0; i < vehicleCount; i++) {
        printf("%s\n", vehicles[i].brand);
    }
    pauseScreen();
}

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

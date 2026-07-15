void menu6Statistics() {
    printf("\n===== 统计 =====\n");
    printStatistics();
    printf("\n按品牌简单统计车辆:\n");
    for (int i = 0; i < vehicleCount; i++) {
        printf("%s\n", vehicles[i].brand);
    }
    pauseScreen();
}

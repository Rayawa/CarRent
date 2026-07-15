void menu8System() {
    while (true) {
        printf("\n1. 修改密码 2. 导出报表 3. 查看日志 4. 清空数据 0. 返回\n");
        int c = inputInt("请选择: ", 0, 4);
        if (c == 0) return;
        if (c == 1) {
            char oldPwd[64], newPwd[64], confirmPwd[64];
            inputLine("旧密码: ", oldPwd, sizeof(oldPwd));
            inputLine("新密码: ", newPwd, sizeof(newPwd));
            inputLine("确认密码: ", confirmPwd, sizeof(confirmPwd));
            if (strcmp(newPwd, confirmPwd) != 0 || !checkPassword(oldPwd)) {
                printf("失败\n");
            } else {
                setNewPassword(newPwd);
                printf("已修改\n");
            }
            pauseScreen();
        } else if (c == 2) {
            exportReport();
            printf("已导出\n");
            pauseScreen();
        } else if (c == 3) {
            FILE* fp = fopen(FILE_LOG, "r");
            if (!fp) {
                printf("暂无日志\n");
                pauseScreen();
                continue;
            }
            char line[256];
            while (fgets(line, sizeof(line), fp)) printf("%s", line);
            fclose(fp);
            pauseScreen();
        } else if (c == 4) {
            if (confirm("确认清空数据?")) {
                vehicleCount = renterCount = rentCount = 0;
                saveAllData();
                printf("已清空\n");
            }
            pauseScreen();
        }
    }
}

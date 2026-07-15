void menu2Renter() {
    while (true) {
        printf("\n1. 添加用户 2. 删除用户 3. 修改用户 4. 显示所有 0. 返回\n");
        int c = inputInt("请选择: ", 0, 4);
        if (c == 0) return;
        if (c == 4) {
            printAllRenters();
            pauseScreen();
            continue;
        }
        // 添加用户：逐字段录入，性别统一大写后追加到数组末尾
        if (c == 1) {
            Renter r;
            initRenter(r);
            inputLine("姓名: ", r.name, MAX_NAME_LEN);
            r.age = inputInt("年龄: ", 1, 120);
            r.gender = inputChar("性别(M/F): ", "MmFf");
            if (r.gender == 'm') r.gender = 'M';
            if (r.gender == 'f') r.gender = 'F';
            inputLine("电话: ", r.phone, MAX_PHONE_LEN);
            inputLine("驾照号: ", r.licenseNo, MAX_LICENSE_LEN);
            inputLine("身份证号: ", r.idCard, MAX_IDCARD_LEN);
            r.drivingYears = inputInt("驾龄: ", 0, 60);
            addRenter(r);
            printf("已添加\n");
            pauseScreen();
        // 删除用户：先展示全部用户，通过ID定位后从数组中移除（后续元素前移覆盖）
        } else if (c == 2) {
            printAllRenters();
            int id = inputInt("输入用户ID: ", 1, 9999);
            printf(deleteRenter(id) ? "已删除\n" : "没找到\n");
            pauseScreen();
        // 修改用户：通过ID查找用户，展示当前值后覆盖更新
        } else if (c == 3) {
            int id = inputInt("输入用户ID: ", 1, 9999);
            Renter* p = findRenter(id);
            if (!p) { printf("没找到\n"); pauseScreen(); continue; }
            Renter r = *p;
            inputLine("姓名: ", r.name, MAX_NAME_LEN);
            r.age = inputInt("年龄: ", 1, 120);
            r.gender = inputChar("性别(M/F): ", "MmFf");
            if (r.gender == 'm') r.gender = 'M';
            if (r.gender == 'f') r.gender = 'F';
            inputLine("电话: ", r.phone, MAX_PHONE_LEN);
            inputLine("驾照号: ", r.licenseNo, MAX_LICENSE_LEN);
            inputLine("身份证号: ", r.idCard, MAX_IDCARD_LEN);
            r.drivingYears = inputInt("驾龄: ", 0, 60);
            printf(modifyRenter(id, r) ? "已修改\n" : "失败\n");
            pauseScreen();
        }
    }
}

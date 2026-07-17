/*
 * 汽车租赁管理系统
 * 文件: car_rent.cpp
 * 功能: 公共定义、链表结构、工具函数、数据持久化、业务逻辑、主菜单
 * 日期: 2026-07
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

//==========================第一部分：常量与类型定义====================
// 定义数量上下限
constexpr int MAX_NAME_LEN = 32;
constexpr int MAX_BRAND_LEN = 32;
constexpr int MAX_TYPE_LEN = 32;
constexpr int MAX_COLOR_LEN = 16;
constexpr int MAX_PLATE_LEN = 16;
constexpr int MAX_PHONE_LEN = 20;
constexpr int MAX_IDCARD_LEN = 20;
constexpr int MAX_LICENSE_LEN = 20;
constexpr int MAX_INSURANCE_LEN = 64;
constexpr int MAX_DATE_LEN = 16;
constexpr int MAX_LOG_LEN = 256;
constexpr int MAX_VEHICLES = 100;
constexpr int MAX_RENTERS = 100;
constexpr int MAX_RENTS = 300;
constexpr int PASSWORD_MIN_LEN = 6;
constexpr int PASSWORD_MAX_LEN = 16;
// 文件保存位置
constexpr char FILE_VEHICLE[] = "vehicle.dat";
constexpr char FILE_RENTER[] = "renter.dat";
constexpr char FILE_RENT[] = "rent.dat";
constexpr char FILE_PASSWORD[] = "pwd.dat";
constexpr char FILE_LOG[] = "log.txt";
enum VehicleStatus { STATUS_AVAILABLE = 0, STATUS_RENTED = 1, STATUS_MAINTENANCE = 2 }; // 车状态：可用0、租出去1、维修2
enum RentStatus { RENT_ACTIVE = 0, RENT_RETURNED = 1 }; // 租状态： 租0回1
// 三种类型结构体以及各自的数据都有哪些
struct Vehicle {
    int id;
    char plateNo[MAX_PLATE_LEN];
    char brand[MAX_BRAND_LEN];
    char type[MAX_TYPE_LEN];
    char color[MAX_COLOR_LEN];
    char purchaseDate[MAX_DATE_LEN];
    int status;
    double dailyRate;
    double mileage;
    char insurance[MAX_INSURANCE_LEN];
};
struct Renter {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char gender;
    char phone[MAX_PHONE_LEN];
    char licenseNo[MAX_LICENSE_LEN];
    char idCard[MAX_IDCARD_LEN];
    int drivingYears;
    int rentCount;
};
struct RentRecord {
    int id;
    int vehicleId;
    int renterId;
    char rentDate[MAX_DATE_LEN];
    char expectedReturnDate[MAX_DATE_LEN];
    char actualReturnDate[MAX_DATE_LEN];
    double deposit; // 押金
    double dailyRate; // 每日租金
    double totalFee; // 总费用
    int status; // 订单状态
    char vehicleBrand[MAX_BRAND_LEN];
    char vehiclePlate[MAX_PLATE_LEN];
    char renterName[MAX_NAME_LEN];
    char renterLicense[MAX_LICENSE_LEN];
};
// 链表节点与头指针
struct VehicleNode { Vehicle data; VehicleNode* next; };
struct RenterNode   { Renter data;   RenterNode* next; };
struct RentNode     { RentRecord data; RentNode* next; };
VehicleNode* vehicleHead = nullptr;
RenterNode*   renterHead = nullptr;
RentNode*     rentHead = nullptr;
// 计数器
int vehicleCount = 0;
int renterCount = 0;
int rentCount = 0;
// 密码初始化
char passwordStore[64] = {0};
char usernameStore[32] = {0};
bool passwordReady = false;

//==========================第二部分：系统工具====================
// 去除字符串末尾换行符
void trimNewLine(char* s) {
    if (!s) return;                    // 1. 空指针检查
    size_t n = strlen(s);              // 2. 获取字符串长度
    if (n > 0 && s[n - 1] == '\n')     // 3. 检查最后一个字符是否是换行符
        s[n - 1] = '\0';               // 4. 将换行符替换为字符串结束符
}
// 暂停屏幕
void pauseScreen() {
    printf("按回车继续...");          // 1. 显示提示信息
    char buf[8];                     // 2. 创建输入缓冲区
    fgets(buf, sizeof(buf), stdin);  // 3. 等待用户输入
}

//==========================第三部分：输入方法====================
// 读取一行字符串
void inputLine(const char* prompt, char* buf, int size) {
    printf("%s", prompt);              // 1. 显示提示信息
    fgets(buf, size, stdin);           // 2. 读取用户输入
    trimNewLine(buf);                  // 3. 去掉换行符
}
int inputInt(const char* prompt, int minValue, int maxValue) {
    char line[64];
    while (true) {
        printf("%s", prompt);
        fgets(line, sizeof(line), stdin);
        trimNewLine(line); // 删掉换行
        if (line[0] == '\0') { printf("输入不能为空\n"); continue; } // 判断直接换行
        char* end;
        long v = strtol(line, &end, 10); // 对比十进制情况下end指针指到了那里，如果是换行就对了
        if (*end != '\0') { printf("请输入有效的整数\n"); continue; }
        if (v < minValue || v > maxValue) { printf("请输入%d到%d之间的整数\n", minValue, maxValue); continue; } // 检查范围是否合法
        return static_cast<int>(v); // long强制转换int
    }
}
double inputDouble(const char* prompt, double minValue, double maxValue) {
    char line[64];
    while (true) {
        printf("%s", prompt);
        fgets(line, sizeof(line), stdin);
        trimNewLine(line);
        if (line[0] == '\0') { printf("输入不能为空\n"); continue; }
        char* end;
        double v = strtod(line, &end); // 同理遍历到换行
        if (*end != '\0') { printf("请输入有效的数值\n"); continue; }
        if (v < minValue || v > maxValue) { printf("请输入%.2f到%.2f之间的数值\n", minValue, maxValue); continue; }
        return v;
    }
}
char inputChar(const char* prompt, const char* valid) {
    char line[64];
    while (true) {
        printf("%s", prompt);
        fgets(line, sizeof(line), stdin);
        trimNewLine(line);
        if (line[0] == '\0') continue; // 直接换行则continue
        char c = line[0];
        for (int i = 0; valid[i]; i++) { if (valid[i] == c) return c; } // 判断是否合法字符
        printf("请输入有效字符[%s]\n", valid);
    }
}
bool confirm(const char* prompt) {
    char c = inputChar(prompt, "yYnN");
    return c == 'y' || c == 'Y'; // 只有yYnN是合法字符
}

//==========================第四部分：时间日期工具====================
// 获取当前日期(YYYY-MM-DD)
void getNowDate(char* buf, int size) {
    time_t t = time(nullptr);
    tm* tmv = localtime(&t); // time结构体
    snprintf(buf, size, "%04d-%02d-%02d", tmv->tm_year + 1900, tmv->tm_mon + 1, tmv->tm_mday); // 格式化输出
}
void getNowDateTime(char* buf, int size) {
    time_t t = time(nullptr);
    tm* tmv = localtime(&t);
    snprintf(buf, size, "%04d-%02d-%02d %02d:%02d:%02d",
             tmv->tm_year + 1900, tmv->tm_mon + 1, tmv->tm_mday, // 日期一样，月份+1，年份从1900开始
             tmv->tm_hour, tmv->tm_min, tmv->tm_sec);
}
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0; // 判断润年
}
bool isValidDate(const char* date) {
    if (!date || strlen(date) != 10) return false; // 判断长度对不对
    if (date[4] != '-' || date[7] != '-') return false; // 判断5和8是否是-
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    } // 跳过-到时候判断是否全是数字
    int y = static_cast<int>(strtol(date, nullptr, 10)); // 年份，解析到-就停止
    int m = static_cast<int>(strtol(date + 5, nullptr, 10)); // 月份+5位，解析到-就停止
    int d = static_cast<int>(strtol(date + 8, nullptr, 10)); // 日+5位，解析到\0就停止
    if (y < 2000 || y > 2100 || m < 1 || m > 12 || d < 1) return false; // 判断是否在日期范围内
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 判断月中有多少天
    if (isLeapYear(y)) days[1] = 29; // 闰年2月29天
    return d <= days[m - 1]; // 如果输入天数比当月要多就false，否则true
}
int dateToDays(const char* date) {
    int y = static_cast<int>(strtol(date, nullptr, 10));
    int m = static_cast<int>(strtol(date + 5, nullptr, 10));
    int d = static_cast<int>(strtol(date + 8, nullptr, 10));
    int days = 0;
    for (int i = 2000; i < y; i++) days += isLeapYear(i) ? 366 : 365; // 从2000年到输入日期有多少天
    int mdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(y)) mdays[1] = 29;
    for (int i = 1; i < m; i++) days += mdays[i - 1]; // 计算多余的月
    return days + d; // 年+月
}
int calcDateDiff(const char* a, const char* b) {
    int x = dateToDays(a), y = dateToDays(b);
    return x > y ? x - y : y - x; // 计算两个日期的时间差，先转换为对2000年有多少天，然后相减返回绝对值
}

//==========================第五部分：状态文案映射====================
const char* vehicleStatusStr(int s) { return s == STATUS_AVAILABLE ? "可租" : s == STATUS_RENTED ? "已租" : "维修"; }
const char* rentStatusStr(int s) { return s == RENT_ACTIVE ? "租用中" : "已归还"; }

//==========================第六部分：结构体初始化====================
void initVehicle(Vehicle& v) { memset(&v, 0, sizeof(v)); v.status = STATUS_AVAILABLE; }
void initRenter(Renter& r) { memset(&r, 0, sizeof(r)); r.gender = 'M'; }
void initRent(RentRecord& r) { memset(&r, 0, sizeof(r)); r.status = RENT_ACTIVE; }

//==========================第七部分：链表查找与ID分配====================
Vehicle* findVehicle(int id) {
    VehicleNode* cur = vehicleHead;
    while (cur) { if (cur->data.id == id) return &cur->data; cur = cur->next; }
    return nullptr;
}
Renter* findRenter(int id) {
    RenterNode* cur = renterHead;
    while (cur) { if (cur->data.id == id) return &cur->data; cur = cur->next; }
    return nullptr;
}
RentRecord* findRent(int id) {
    RentNode* cur = rentHead;
    while (cur) { if (cur->data.id == id) return &cur->data; cur = cur->next; }
    return nullptr;
}
int nextVehicleId() {
    int mx = 0;
    VehicleNode* cur = vehicleHead;
    while (cur) { if (cur->data.id > mx) mx = cur->data.id; cur = cur->next; }
    return mx + 1;
}
int nextRenterId() {
    int mx = 0;
    RenterNode* cur = renterHead;
    while (cur) { if (cur->data.id > mx) mx = cur->data.id; cur = cur->next; }
    return mx + 1;
}
int nextRentId() {
    int mx = 0;
    RentNode* cur = rentHead;
    while (cur) { if (cur->data.id > mx) mx = cur->data.id; cur = cur->next; }
    return mx + 1;
}

//==========================第八部分：重复数据检查====================
bool isPlateNoDuplicate(const char* plateNo) {
    VehicleNode* cur = vehicleHead; // 从头遍历
    while (cur) { if (strcmp(cur->data.plateNo, plateNo) == 0) return true; cur = cur->next; }
    return false; // 找到匹配立刻返回true，否则跑完了就是没找到false
}
bool isLicenseNoDuplicate(const char* licenseNo) {
    RenterNode* cur = renterHead;
    while (cur) { if (strcmp(cur->data.licenseNo, licenseNo) == 0) return true; cur = cur->next; }
    return false; // 同上
}
bool isIdCardDuplicate(const char* idCard) {
    RenterNode* cur = renterHead;
    while (cur) { if (strcmp(cur->data.idCard, idCard) == 0) return true; cur = cur->next; }
    return false; // 同上
}

//==========================第九部分：数据持久化====================
// 操作日志
void logAction(const char* action) {
    FILE* fp = fopen(FILE_LOG, "a");
    if (!fp) return;
    char buf[32];
    getNowDateTime(buf, sizeof(buf));
    fprintf(fp, "%s %s\n", buf, action);
    fclose(fp);
}
// 保存车辆链表
void saveVehicles() {
    FILE* fp = fopen(FILE_VEHICLE, "wb");
    if (!fp) return;
    fwrite(&vehicleCount, sizeof(int), 1, fp);
    VehicleNode* cur = vehicleHead;
    while (cur) { fwrite(&cur->data, sizeof(Vehicle), 1, fp); cur = cur->next; }
    fclose(fp);
}
void saveRenters() {
    FILE* fp = fopen(FILE_RENTER, "wb");
    if (!fp) return;
    fwrite(&renterCount, sizeof(int), 1, fp);
    RenterNode* cur = renterHead;
    while (cur) { fwrite(&cur->data, sizeof(Renter), 1, fp); cur = cur->next; }
    fclose(fp);
}
void saveRents() {
    FILE* fp = fopen(FILE_RENT, "wb");
    if (!fp) return;
    fwrite(&rentCount, sizeof(int), 1, fp);
    RentNode* cur = rentHead;
    while (cur) { fwrite(&cur->data, sizeof(RentRecord), 1, fp); cur = cur->next; }
    fclose(fp);
}
void savePassword() {
    FILE* fp = fopen(FILE_PASSWORD, "wb");
    if (!fp) return;
    fwrite(usernameStore, sizeof(usernameStore), 1, fp);
    fwrite(passwordStore, sizeof(passwordStore), 1, fp);
    fclose(fp);
}
// 加载并构建链表
void loadVehicles() {
    FILE* fp = fopen(FILE_VEHICLE, "rb");
    if (!fp) return;
    fread(&vehicleCount, sizeof(int), 1, fp);
    if (vehicleCount < 0 || vehicleCount > MAX_VEHICLES) { vehicleCount = 0; fclose(fp); return; }
    VehicleNode* tail = nullptr;
    vehicleHead = nullptr;
    for (int i = 0; i < vehicleCount; i++) {
        VehicleNode* node = new VehicleNode;
        fread(&node->data, sizeof(Vehicle), 1, fp);
        node->next = nullptr;
        if (!vehicleHead) vehicleHead = node;
        else tail->next = node;
        tail = node;
    }
    fclose(fp);
}
void loadRenters() {
    FILE* fp = fopen(FILE_RENTER, "rb");
    if (!fp) return;
    fread(&renterCount, sizeof(int), 1, fp);
    if (renterCount < 0 || renterCount > MAX_RENTERS) { renterCount = 0; fclose(fp); return; }
    RenterNode* tail = nullptr;
    renterHead = nullptr;
    for (int i = 0; i < renterCount; i++) {
        RenterNode* node = new RenterNode;
        fread(&node->data, sizeof(Renter), 1, fp);
        node->next = nullptr;
        if (!renterHead) renterHead = node;
        else tail->next = node;
        tail = node;
    }
    fclose(fp);
}
void loadRents() {
    FILE* fp = fopen(FILE_RENT, "rb");
    if (!fp) return;
    fread(&rentCount, sizeof(int), 1, fp);
    if (rentCount < 0 || rentCount > MAX_RENTS) { rentCount = 0; fclose(fp); return; }
    RentNode* tail = nullptr;
    rentHead = nullptr;
    for (int i = 0; i < rentCount; i++) {
        RentNode* node = new RentNode;
        fread(&node->data, sizeof(RentRecord), 1, fp);
        node->next = nullptr;
        if (!rentHead) rentHead = node;
        else tail->next = node;
        tail = node;
    }
    fclose(fp);
}
void loadPassword() {
    FILE* fp = fopen(FILE_PASSWORD, "rb");
    if (!fp) return;
    fread(usernameStore, sizeof(usernameStore), 1, fp);
    fread(passwordStore, sizeof(passwordStore), 1, fp);
    fclose(fp);
    passwordReady = passwordStore[0] != '\0';
}
void loadAllData() { loadVehicles(); loadRenters(); loadRents(); loadPassword(); }
void saveAllData() { saveVehicles(); saveRenters(); saveRents(); savePassword(); }

//==========================第十部分：密码与登录====================
// 密码相关
void xorPassword(const char* plain, char* out) {
    int len = static_cast<int>(strlen(plain));
    for (int i = 0; i < 64; i++) out[i] = i < len ? static_cast<char>(plain[i] ^ 0x5A) : '\0';
}
bool checkPassword(const char* plain) {
    char enc[64];
    xorPassword(plain, enc);
    return memcmp(enc, passwordStore, sizeof(passwordStore)) == 0;
}
bool setNewPassword(const char* plain) {
    int len = static_cast<int>(strlen(plain));
    if (len < PASSWORD_MIN_LEN || len > PASSWORD_MAX_LEN) return false;
    xorPassword(plain, passwordStore);
    passwordReady = true;
    savePassword();
    return true;
}
// 用户登录
bool login() {
    if (!passwordReady) {
        printf("首次使用，请设置登录信息\n");
        inputLine("设置用户名: ", usernameStore, sizeof(usernameStore));
        char p1[64], p2[64];
        while (true) {
            inputLine("设置密码: ", p1, sizeof(p1));
            inputLine("确认密码: ", p2, sizeof(p2));
            if (strcmp(p1, p2) == 0 && setNewPassword(p1)) break;
            printf("密码不符合要求或不一致\n");
        }
        savePassword();
        logAction("首次设置用户名密码");
        return true;
    }
    for (int i = 0; i < 3; i++) {
        char u[64], p[64];
        inputLine("用户名: ", u, sizeof(u));
        inputLine("密码: ", p, sizeof(p));
        if (strcmp(u, usernameStore) == 0 && checkPassword(p)) {
            logAction("登录成功");
            return true;
        }
        printf("用户名或密码错误\n");
        logAction("登录失败");
    }
    return false;
}

//==========================第十一部分：数据增删改====================
// 车辆增删改
bool addVehicle(const Vehicle& v) {
    if (vehicleCount >= MAX_VEHICLES) return false;
    VehicleNode* node = new VehicleNode;
    node->data = v;
    node->data.id = nextVehicleId();
    node->data.status = STATUS_AVAILABLE;
    node->next = nullptr;
    if (!vehicleHead) { vehicleHead = node; }
    else { VehicleNode* cur = vehicleHead; while (cur->next) cur = cur->next; cur->next = node; }
    vehicleCount++;
    saveVehicles();
    logAction("添加车辆");
    return true;
}
bool deleteVehicle(int id) {
    VehicleNode* prev = nullptr;
    VehicleNode* cur = vehicleHead;
    while (cur) {
        if (cur->data.id == id) {
            if (prev) prev->next = cur->next; else vehicleHead = cur->next;
            delete cur;
            vehicleCount--;
            saveVehicles();
            logAction("删除车辆");
            return true;
        }
        prev = cur; cur = cur->next;
    }
    return false;
}
bool modifyVehicle(int id, const Vehicle& v) {
    Vehicle* p = findVehicle(id);
    if (!p) return false;
    Vehicle tmp = v; tmp.id = id; *p = tmp;
    saveVehicles();
    logAction("修改车辆");
    return true;
}
// 用户增删改
bool addRenter(const Renter& r) {
    if (renterCount >= MAX_RENTERS) return false;
    RenterNode* node = new RenterNode;
    node->data = r;
    node->data.id = nextRenterId();
    node->data.rentCount = 0;
    node->next = nullptr;
    if (!renterHead) { renterHead = node; }
    else { RenterNode* cur = renterHead; while (cur->next) cur = cur->next; cur->next = node; }
    renterCount++;
    saveRenters();
    logAction("添加用户");
    return true;
}
bool deleteRenter(int id) {
    RenterNode* prev = nullptr;
    RenterNode* cur = renterHead;
    while (cur) {
        if (cur->data.id == id) {
            if (prev) prev->next = cur->next; else renterHead = cur->next;
            delete cur;
            renterCount--;
            saveRenters();
            logAction("删除用户");
            return true;
        }
        prev = cur; cur = cur->next;
    }
    return false;
}
bool modifyRenter(int id, const Renter& r) {
    Renter* p = findRenter(id);
    if (!p) return false;
    Renter tmp = r; tmp.id = id; *p = tmp;
    saveRenters();
    logAction("修改用户");
    return true;
}
// 租车退车
bool addRentRecord(int vehicleId, int renterId, const char* rentDate, const char* expectDate) {
    if (rentCount >= MAX_RENTS) return false;
    Vehicle* v = findVehicle(vehicleId);
    Renter* r = findRenter(renterId);
    if (!v || !r || v->status != STATUS_AVAILABLE) return false;
    RentRecord rec = {};
    initRent(rec);
    rec.id = nextRentId();
    rec.vehicleId = vehicleId;
    rec.renterId = renterId;
    strncpy(rec.rentDate, rentDate, MAX_DATE_LEN - 1);
    strncpy(rec.expectedReturnDate, expectDate, MAX_DATE_LEN - 1);
    rec.deposit = v->dailyRate * 3;
    rec.dailyRate = v->dailyRate;
    strncpy(rec.vehicleBrand, v->brand, MAX_BRAND_LEN - 1);
    strncpy(rec.vehiclePlate, v->plateNo, MAX_PLATE_LEN - 1);
    strncpy(rec.renterName, r->name, MAX_NAME_LEN - 1);
    strncpy(rec.renterLicense, r->licenseNo, MAX_LICENSE_LEN - 1);
    RentNode* node = new RentNode;
    node->data = rec;
    node->next = nullptr;
    if (!rentHead) { rentHead = node; }
    else { RentNode* cur = rentHead; while (cur->next) cur = cur->next; cur->next = node; }
    rentCount++;
    v->status = STATUS_RENTED;
    r->rentCount++;
    saveAllData();
    logAction("办理租车");
    return true;
}
bool returnRent(int rentId, const char* returnDate, double& totalFee, double& refund) {
    RentRecord* rec = findRent(rentId);
    if (!rec || rec->status == RENT_RETURNED) return false;
    int days = calcDateDiff(rec->rentDate, returnDate);
    if (days < 1) days = 1;
    totalFee = days * rec->dailyRate;
    refund = rec->deposit - totalFee;
    if (refund < 0) refund = 0;
    strncpy(rec->actualReturnDate, returnDate, MAX_DATE_LEN - 1);
    rec->totalFee = totalFee;
    rec->status = RENT_RETURNED;
    Vehicle* v = findVehicle(rec->vehicleId);
    if (v) v->status = STATUS_AVAILABLE;
    saveAllData();
    logAction("办理退车");
    return true;
}

//==========================第十二部分：输出打印====================
// 票据：格式化输出
void printRentTicket(const RentRecord& r) {
    printf("\n========================================\n");
    printf("       汽车租赁公司租车票据\n");
    printf("========================================\n");
    printf(" 票据编号: %-6d    日期: %s\n", r.id, r.rentDate);
    printf("----------------------------------------\n");
    printf(" 车辆品牌: %-10s  车牌号: %s\n", r.vehicleBrand, r.vehiclePlate);
    printf(" 日 租 金: %-10.2f  押  金: %.2f\n", r.dailyRate, r.deposit);
    printf("----------------------------------------\n");
    printf(" 用户姓名: %-10s  驾照号: %s\n", r.renterName, r.renterLicense);
    printf(" 租车日期: %-10s  预计归还: %s\n", r.rentDate, r.expectedReturnDate);
    printf("========================================\n");
}
void printReturnReceipt(const RentRecord& r, int days, double total, double refund) {
    printf("\n========================================\n");
    printf("     汽车租赁公司租车费用收据\n");
    printf("========================================\n");
    printf(" 票据编号: %-6d  归还日期: %s\n", r.id, r.actualReturnDate);
    printf("----------------------------------------\n");
    printf(" 车辆品牌: %-10s  车牌号: %s\n", r.vehicleBrand, r.vehiclePlate);
    printf(" 用户姓名: %s\n", r.renterName);
    printf("----------------------------------------\n");
    printf(" 租用天数: %-4d天    日租金: %.2f\n", days, r.dailyRate);
    printf(" 总 费 用: %-10.2f  押  金: %.2f\n", total, r.deposit);
    printf(" 实际退款: %.2f\n", refund);
    printf("========================================\n");
}
// 数据：格式化输出
void printVehicleHeader() {
    printf("%-4s %-10s %-10s %-10s %-8s %-12s %-6s %-8s %-10s\n",
           "ID", "车牌", "品牌", "类型", "颜色", "购车日期", "状态", "日租金", "里程");
}
void printVehicleRow(const Vehicle& v) {
    printf("%-4d %-10s %-10s %-10s %-8s %-12s %-6s %-8.2f %-10.1f\n",
           v.id, v.plateNo, v.brand, v.type, v.color, v.purchaseDate,
           vehicleStatusStr(v.status), v.dailyRate, v.mileage);
}
void printRenterHeader() {
    printf("%-4s %-10s %-4s %-2s %-12s %-16s %-16s %-4s %-4s\n",
           "ID", "姓名", "年龄", "性", "电话", "驾照", "身份证", "驾龄", "次数");
}
void printRenterRow(const Renter& r) {
    printf("%-4d %-10s %-4d %-2c %-12s %-16s %-16s %-4d %-4d\n",
           r.id, r.name, r.age, r.gender, r.phone, r.licenseNo, r.idCard, r.drivingYears, r.rentCount);
}
void printRentHeader() {
    printf("%-4s %-4s %-4s %-12s %-12s %-12s %-8s %-8s %-8s %-6s\n",
           "ID", "车", "人", "租车日期", "预计归还", "实际归还", "押金", "日租金", "总费用", "状态");
}
void printRentRow(const RentRecord& r) {
    printf("%-4d %-4d %-4d %-12s %-12s %-12s %-8.2f %-8.2f %-8.2f %-6s\n",
           r.id, r.vehicleId, r.renterId, r.rentDate, r.expectedReturnDate,
           r.actualReturnDate[0] ? r.actualReturnDate : "-",
           r.deposit, r.dailyRate, r.totalFee, rentStatusStr(r.status));
}
// 打印全部：链表遍历
void printAllVehicles() {
    printVehicleHeader();
    VehicleNode* cur = vehicleHead;
    while (cur) {
        printVehicleRow(cur->data);
        cur = cur->next;
    }
}
void printAllRenters() {
    printRenterHeader();
    RenterNode* cur = renterHead;
    while (cur) {
        printRenterRow(cur->data);
        cur = cur->next;
    }
}
void printAllRents() {
    printRentHeader();
    RentNode* cur = rentHead;
    while (cur) {
        printRentRow(cur->data);
        cur = cur->next;
    }
}

//==========================第十三部分：统计与ASCII柱状图====================
// 计算数量：链表遍历与计数器
int countAvailableVehicles() {
    int c = 0; VehicleNode* cur = vehicleHead;
    while (cur) { if (cur->data.status == STATUS_AVAILABLE) c++; cur = cur->next; }
    return c;
}
int countRentedVehicles() {
    int c = 0; VehicleNode* cur = vehicleHead;
    while (cur) { if (cur->data.status == STATUS_RENTED) c++; cur = cur->next; }
    return c;
}
int countActiveRents() {
    int c = 0; RentNode* cur = rentHead;
    while (cur) { if (cur->data.status == RENT_ACTIVE) c++; cur = cur->next; }
    return c;
}
// *？？？？
double totalRevenue() {
    double sum = 0; RentNode* cur = rentHead;
    while (cur) { if (cur->data.status == RENT_RETURNED) sum += cur->data.totalFee; cur = cur->next; }
    return sum;
}
// *按品牌/类型/颜色分组计数
int countVehiclesByBrand(char labels[][32], int values[], int max) {
    int n = 0;
    VehicleNode* cur = vehicleHead;
    while (cur) {
        int found = -1;
        for (int i = 0; i < n; i++) { if (strcmp(labels[i], cur->data.brand) == 0) { found = i; break; } }
        if (found >= 0) values[found]++;
        else if (n < max) { strncpy(labels[n], cur->data.brand, 31); values[n] = 1; n++; }
        cur = cur->next;
    }
    return n;
}
int countVehiclesByType(char labels[][32], int values[], int max) {
    int n = 0;
    VehicleNode* cur = vehicleHead;
    while (cur) {
        int found = -1;
        for (int i = 0; i < n; i++) { if (strcmp(labels[i], cur->data.type) == 0) { found = i; break; } }
        if (found >= 0) values[found]++;
        else if (n < max) { strncpy(labels[n], cur->data.type, 31); values[n] = 1; n++; }
        cur = cur->next;
    }
    return n;
}
int countVehiclesByColor(char labels[][32], int values[], int max) {
    int n = 0;
    VehicleNode* cur = vehicleHead;
    while (cur) {
        int found = -1;
        for (int i = 0; i < n; i++) { if (strcmp(labels[i], cur->data.color) == 0) { found = i; break; } }
        if (found >= 0) values[found]++;
        else if (n < max) { strncpy(labels[n], cur->data.color, 31); values[n] = 1; n++; }
        cur = cur->next;
    }
    return n;
}
int countRentersByGender(int values[2]) {
    values[0] = values[1] = 0;
    RenterNode* cur = renterHead;
    while (cur) { if (cur->data.gender == 'M') values[0]++; else values[1]++; cur = cur->next; }
    return 2;
}
// *统计用户按驾龄分段
void countRentersByDrivingYears(int values[3]) {
    values[0] = values[1] = values[2] = 0;
    RenterNode* cur = renterHead;
    while (cur) {
        int y = cur->data.drivingYears;
        if (y <= 3) values[0]++; else if (y <= 10) values[1]++; else values[2]++;
        cur = cur->next;
    }
}
// *按月统计租车记录数
void countRentsByMonth(int values[12]) {
    for (int i = 0; i < 12; i++) values[i] = 0;
    RentNode* cur = rentHead;
    while (cur) {
        int m = static_cast<int>(strtol(cur->data.rentDate + 5, nullptr, 10));
        if (m >= 1 && m <= 12) values[m - 1]++;
        cur = cur->next;
    }
}
// *柱状图
void drawBarChart(char labels[][32], int values[], int n) {
    int mx = 0;
    for (int i = 0; i < n; i++) if (values[i] > mx) mx = values[i];
    for (int i = 0; i < n; i++) {
        printf("  %-10s [%3d] ", labels[i], values[i]);
        int bar = mx > 0 ? values[i] * 30 / mx : 0;
        for (int j = 0; j < bar; j++) printf("#");
        printf("\n");
    }
}
void printStatistics() {
    printf("车辆总数: %d  可租: %d  已租: %d\n", vehicleCount, countAvailableVehicles(), countRentedVehicles());
    printf("用户总数: %d  租车记录: %d  进行中: %d  总收入: %.2f\n", renterCount, rentCount, countActiveRents(), totalRevenue());
}
// *导出报表
void exportReport() {
    char name[64];
    getNowDateTime(name, sizeof(name));
    for (int i = 0; name[i]; i++) if (name[i] == ' ' || name[i] == ':') name[i] = '_';
    char fileName[96];
    snprintf(fileName, sizeof(fileName), "report_%s.txt", name);
    FILE* fp = fopen(fileName, "w");
    if (!fp) return;
    fprintf(fp, "车辆信息\n");
    VehicleNode* vc = vehicleHead;
    while (vc) {
        fprintf(fp, "%d %s %s %s %s %.2f %s\n", vc->data.id, vc->data.plateNo, vc->data.brand,
                vc->data.type, vc->data.color, vc->data.dailyRate, vehicleStatusStr(vc->data.status));
        vc = vc->next;
    }
    fprintf(fp, "\n用户信息\n");
    RenterNode* rc = renterHead;
    while (rc) {
        fprintf(fp, "%d %s %s %s\n", rc->data.id, rc->data.name, rc->data.licenseNo, rc->data.phone);
        rc = rc->next;
    }
    fprintf(fp, "\n租车记录\n");
    RentNode* rtc = rentHead;
    while (rtc) {
        fprintf(fp, "%d %d %d %s %s %.2f %s\n", rtc->data.id, rtc->data.vehicleId, rtc->data.renterId,
                rtc->data.rentDate, rtc->data.expectedReturnDate, rtc->data.totalFee, rentStatusStr(rtc->data.status));
        rtc = rtc->next;
    }
    fclose(fp);
}
// 显示全部信息：直接调用三个打印全部
void showAllInfo() {
    printf("\n===== 车辆 =====\n"); printAllVehicles();
    printf("\n===== 用户 =====\n"); printAllRenters();
    printf("\n===== 租车记录 =====\n"); printAllRents();
}

//==========================第十四部分：子模块引用====================
#include "menu1_vehicle.cpp"
#include "menu2_renter.cpp"
#include "menu3_rent.cpp"
#include "menu4_return.cpp"
#include "menu5_query.cpp"
#include "menu6_statistics.cpp"
#include "menu7_system.cpp"

//==========================第十五部分：界面与入口====================
// 获得时间信息并打印
void showBanner() {
    char now[32];
    getNowDateTime(now, sizeof(now));
    printf("\n汽车租赁管理系统  %s\n", now);
}
// 主界面，打印选项之后switch
bool mainMenu() {
    printf("\n1.车辆管理 2.用户管理 3.租车办理 4.退车办理\n");
    printf("5.信息查询 6.统计汇总 7.系统设置 0.退出系统\n");
    int choice = inputInt("请选择: ", 0, 7);
    switch (choice) {
        case 1: menu1Vehicle(); break;
        case 2: menu2Renter(); break;
        case 3: menu3Rent(); break;
        case 4: menu4Return(); break;
        case 5: menu5Query(); break;
        case 6: menu6Statistics(); break;
        case 7: menu7System(); break;
        case 0: return false;
        default: break;
    }
    return true;
}
// 程序入口
void runApp() {
    loadAllData(); // 加载所有数据
    if (!login()) { printf("登录失败\n"); return; } // 登陆判断
    showBanner(); // 打印标题时间信息
    while (mainMenu()) {} // 主程序
    saveAllData(); // 退出之前报错所有数据
}

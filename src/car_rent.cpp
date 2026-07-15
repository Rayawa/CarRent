#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

//==========================第一部分：定义、规范类型====================
// 系统相关常量定义
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
// 文件位置定义
constexpr char FILE_VEHICLE[] = "vehicle.dat";
constexpr char FILE_RENTER[] = "renter.dat";
constexpr char FILE_RENT[] = "rent.dat";
constexpr char FILE_PASSWORD[] = "pwd.dat";
constexpr char FILE_LOG[] = "log.txt";
// 系统状态定义
enum VehicleStatus {
    STATUS_AVAILABLE = 0,
    STATUS_RENTED = 1,
    STATUS_MAINTENANCE = 2
};
enum RentStatus {
    RENT_ACTIVE = 0,
    RENT_RETURNED = 1
};
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
    double deposit;
    double dailyRate;
    double totalFee;
    int status;
    char vehicleBrand[MAX_BRAND_LEN];
    char vehiclePlate[MAX_PLATE_LEN];
    char renterName[MAX_NAME_LEN];
    char renterLicense[MAX_LICENSE_LEN];
};
Vehicle vehicles[MAX_VEHICLES];
Renter renters[MAX_RENTERS];
RentRecord rents[MAX_RENTS];
int vehicleCount = 0;
int renterCount = 0;
int rentCount = 0;
char passwordStore[64] = {0};
bool passwordReady = false;

//==========================第二部分：系统工具方法====================
// 去除字符串末尾换行符
void trimNewline(char* s) {
    if (!s) return;
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') s[n - 1] = '\0';
}
// 暂停屏幕等待用户按键
void pauseScreen() {
    printf("按回车继续...");
    char buf[8];
    fgets(buf, sizeof(buf), stdin);
}

//==========================第三部分：输入方法====================
// 读取一行字符串
void inputLine(const char* prompt, char* buf, int size) {
    printf("%s", prompt);
    fgets(buf, size, stdin);
    trimNewline(buf);
}
// 读取整数（含范围校验）
int inputInt(const char* prompt, int minValue, int maxValue) {
    char line[64];
    while (true) {
        printf("%s", prompt);
        fgets(line, sizeof(line), stdin);
        trimNewline(line);
        if (line[0] == '\0') continue;
        int v = static_cast<int>(strtol(line, nullptr, 10));
        if (v >= minValue && v <= maxValue) return v;
        printf("请输入 %d 到 %d 之间的整数\n", minValue, maxValue);
    }
}
// 读取浮点数（含范围校验）
double inputDouble(const char* prompt, double minValue, double maxValue) {
    char line[64];
    while (true) {
        printf("%s", prompt);
        fgets(line, sizeof(line), stdin);
        trimNewline(line);
        if (line[0] == '\0') continue;
        double v = strtod(line, nullptr);
        if (v >= minValue && v <= maxValue) return v;
        printf("请输入 %.2f 到 %.2f 之间的数值\n", minValue, maxValue);
    }
}
// 读取字符（含合法字符集合校验）
char inputChar(const char* prompt, const char* valid) {
    char line[64];
    while (true) {
        printf("%s", prompt);
        fgets(line, sizeof(line), stdin);
        trimNewline(line);
        if (line[0] == '\0') continue;
        char c = line[0];
        for (int i = 0; valid[i]; i++) {
            if (valid[i] == c) return c;
        }
        printf("请输入有效字符 [%s]\n", valid);
    }
}
// 用户确认（Y/N）
bool confirm(const char* prompt) {
    char c = inputChar(prompt, "yYnN");
    return c == 'y' || c == 'Y';
}

//==========================第四部分：时间日期工具====================
// 获取当前日期字符串（YYYY-MM-DD）
void nowDate(char* buf, int size) {
    time_t t = time(nullptr);
    tm* tmv = localtime(&t);
    snprintf(buf, size, "%04d-%02d-%02d",
             tmv->tm_year + 1900, tmv->tm_mon + 1, tmv->tm_mday);
}
// 获取当前日期时间字符串（YYYY-MM-DD HH:MM:SS）
void nowDateTime(char* buf, int size) {
    time_t t = time(nullptr);
    tm* tmv = localtime(&t);
    snprintf(buf, size, "%04d-%02d-%02d %02d:%02d:%02d",
             tmv->tm_year + 1900, tmv->tm_mon + 1, tmv->tm_mday,
             tmv->tm_hour, tmv->tm_min, tmv->tm_sec);
}
// 判断是否为闰年
int isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
// 校验日期字符串格式合法性（YYYY-MM-DD）
bool validDate(const char* date) {
    if (!date || strlen(date) != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    }
    int y = static_cast<int>(strtol(date, nullptr, 10));
    int m = static_cast<int>(strtol(date + 5, nullptr, 10));
    int d = static_cast<int>(strtol(date + 8, nullptr, 10));
    if (y < 2000 || y > 2100 || m < 1 || m > 12 || d < 1) return false;
    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (isLeap(y)) days[1] = 29;
    return d <= days[m - 1];
}
// 将日期字符串转换为从2000-01-01起的天数（用于日期差计算）
int dateToDays(const char* date) {
    int y = static_cast<int>(strtol(date, nullptr, 10));
    int m = static_cast<int>(strtol(date + 5, nullptr, 10));
    int d = static_cast<int>(strtol(date + 8, nullptr, 10));
    int days = 0;
    for (int i = 2000; i < y; i++) days += isLeap(i) ? 366 : 365;
    int mdays[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (isLeap(y)) mdays[1] = 29;
    for (int i = 1; i < m; i++) days += mdays[i - 1];
    return days + d;
}
// 计算两个日期之间的天数差（绝对值）
int diffDays(const char* a, const char* b) {
    int x = dateToDays(a);
    int y = dateToDays(b);
    return x > y ? x - y : y - x;
}

//==========================第五部分：状态文案映射====================
// 车辆状态 → 中文文案
const char* vehicleStatusStr(int s) {
    return s == STATUS_AVAILABLE ? "可租" : s == STATUS_RENTED ? "已租" : "维修";
}
// 租车状态 → 中文文案
const char* rentStatusStr(int s) {
    return s == RENT_ACTIVE ? "租用中" : "已归还";
}

//==========================第六部分：结构体初始化方法====================
// 初始化车辆结构体（清零后设为可租状态）
void initVehicle(Vehicle& v) {
    memset(&v, 0, sizeof(v));
    v.status = STATUS_AVAILABLE;
}
// 初始化用户结构体（清零后性别默认男）
void initRenter(Renter& r) {
    memset(&r, 0, sizeof(r));
    r.gender = 'M';
}
// 初始化租车记录结构体（清零后状态设为租用中）
void initRent(RentRecord& r) {
    memset(&r, 0, sizeof(r));
    r.status = RENT_ACTIVE;
}

//==========================第七部分：ID分配与查找方法====================
// 分配新的车辆ID —— 遍历现有数据取最大ID+1
int nextVehicleId() {
    int mx = 0;
    for (int i = 0; i < vehicleCount; i++) if (vehicles[i].id > mx) mx = vehicles[i].id;
    return mx + 1;
}
// 分配新的用户ID —— 遍历现有数据取最大ID+1
int nextRenterId() {
    int mx = 0;
    for (int i = 0; i < renterCount; i++) if (renters[i].id > mx) mx = renters[i].id;
    return mx + 1;
}
// 分配新的租车记录ID —— 遍历现有数据取最大ID+1
int nextRentId() {
    int mx = 0;
    for (int i = 0; i < rentCount; i++) if (rents[i].id > mx) mx = rents[i].id;
    return mx + 1;
}
// 按ID查找车辆 —— 线性遍历匹配
Vehicle* findVehicle(int id) {
    for (int i = 0; i < vehicleCount; i++) if (vehicles[i].id == id) return &vehicles[i];
    return nullptr;
}
// 按ID查找用户 —— 线性遍历匹配
Renter* findRenter(int id) {
    for (int i = 0; i < renterCount; i++) if (renters[i].id == id) return &renters[i];
    return nullptr;
}
// 按ID查找租车记录 —— 线性遍历匹配
RentRecord* findRent(int id) {
    for (int i = 0; i < rentCount; i++) if (rents[i].id == id) return &rents[i];
    return nullptr;
}

//==========================第八部分：日志与数据持久化====================
// 追加操作日志到文件
void logAction(const char* action) {
    FILE* fp = fopen(FILE_LOG, "a");
    if (!fp) return;
    char buf[32];
    nowDateTime(buf, sizeof(buf));
    fprintf(fp, "%s %s\n", buf, action);
    fclose(fp);
}
// 保存车辆数据到二进制文件（文件头写入数量，后续为数据块）
void saveVehicles() {
    FILE* fp = fopen(FILE_VEHICLE, "wb");
    if (!fp) return;
    fwrite(&vehicleCount, sizeof(int), 1, fp);
    fwrite(vehicles, sizeof(Vehicle), vehicleCount, fp);
    fclose(fp);
}
// 保存用户数据到二进制文件
void saveRenters() {
    FILE* fp = fopen(FILE_RENTER, "wb");
    if (!fp) return;
    fwrite(&renterCount, sizeof(int), 1, fp);
    fwrite(renters, sizeof(Renter), renterCount, fp);
    fclose(fp);
}
// 保存租车记录数据到二进制文件
void saveRents() {
    FILE* fp = fopen(FILE_RENT, "wb");
    if (!fp) return;
    fwrite(&rentCount, sizeof(int), 1, fp);
    fwrite(rents, sizeof(RentRecord), rentCount, fp);
    fclose(fp);
}
// 保存密码到二进制文件
void savePassword() {
    FILE* fp = fopen(FILE_PASSWORD, "wb");
    if (!fp) return;
    fwrite(passwordStore, sizeof(passwordStore), 1, fp);
    fclose(fp);
}
// 从二进制文件加载车辆数据（含数量合法性校验）
void loadVehicles() {
    FILE* fp = fopen(FILE_VEHICLE, "rb");
    if (!fp) return;
    fread(&vehicleCount, sizeof(int), 1, fp);
    if (vehicleCount < 0 || vehicleCount > MAX_VEHICLES) vehicleCount = 0;
    fread(vehicles, sizeof(Vehicle), vehicleCount, fp);
    fclose(fp);
}
// 从二进制文件加载用户数据（含数量合法性校验）
void loadRenters() {
    FILE* fp = fopen(FILE_RENTER, "rb");
    if (!fp) return;
    fread(&renterCount, sizeof(int), 1, fp);
    if (renterCount < 0 || renterCount > MAX_RENTERS) renterCount = 0;
    fread(renters, sizeof(Renter), renterCount, fp);
    fclose(fp);
}
// 从二进制文件加载租车记录数据（含数量合法性校验）
void loadRents() {
    FILE* fp = fopen(FILE_RENT, "rb");
    if (!fp) return;
    fread(&rentCount, sizeof(int), 1, fp);
    if (rentCount < 0 || rentCount > MAX_RENTS) rentCount = 0;
    fread(rents, sizeof(RentRecord), rentCount, fp);
    fclose(fp);
}
// 从二进制文件加载密码
void loadPassword() {
    FILE* fp = fopen(FILE_PASSWORD, "rb");
    if (!fp) return;
    fread(passwordStore, sizeof(passwordStore), 1, fp);
    fclose(fp);
    passwordReady = passwordStore[0] != '\0';
}
// 批量加载全部数据
void loadAllData() {
    loadVehicles();
    loadRenters();
    loadRents();
    loadPassword();
}
// 批量保存全部数据
void saveAllData() {
    saveVehicles();
    saveRenters();
    saveRents();
    savePassword();
}

//==========================第九部分：密码管理====================
// 异或加密密码（与0x5A做异或混淆后存入密码存储区）
void xorPassword(const char* plain, char* out) {
    int len = static_cast<int>(strlen(plain));
    for (int i = 0; i < 64; i++) {
        out[i] = i < len ? static_cast<char>(plain[i] ^ 0x5A) : '\0';
    }
}
// 校验明文密码是否与存储的加密密码一致
bool checkPassword(const char* plain) {
    char enc[64];
    xorPassword(plain, enc);
    return memcmp(enc, passwordStore, sizeof(passwordStore)) == 0;
}
// 设置新密码（明文加密后持久化存储）
bool setNewPassword(const char* plain) {
    int len = static_cast<int>(strlen(plain));
    if (len < PASSWORD_MIN_LEN || len > PASSWORD_MAX_LEN) return false;
    xorPassword(plain, passwordStore);
    passwordReady = true;
    savePassword();
    return true;
}
// 用户登录（首次使用时引导设密，已有密码时最多尝试3次）
bool login() {
    if (!passwordReady) {
        char p1[64];
        char p2[64];
        printf("首次使用，请设置密码\n");
        while (true) {
            inputLine("新密码: ", p1, sizeof(p1));
            inputLine("确认密码: ", p2, sizeof(p2));
            if (strcmp(p1, p2) == 0 && setNewPassword(p1)) break;
            printf("密码不符合要求或不一致\n");
        }
        logAction("首次设置密码");
        return true;
    }
    for (int i = 0; i < 3; i++) {
        char p[64];
        inputLine("请输入密码: ", p, sizeof(p));
        if (checkPassword(p)) {
            logAction("登录成功");
            return true;
        }
        printf("密码错误\n");
        logAction("登录失败");
    }
    return false;
}

//==========================第十部分：数据增删改操作====================
// 添加车辆 —— 追加到数组末尾，自动分配ID，保存并记录日志
bool addVehicle(const Vehicle& v) {
    if (vehicleCount >= MAX_VEHICLES) return false;
    vehicles[vehicleCount] = v;
    vehicles[vehicleCount].id = nextVehicleId();
    vehicles[vehicleCount].status = STATUS_AVAILABLE;
    vehicleCount++;
    saveVehicles();
    logAction("添加车辆");
    return true;
}
// 删除车辆 —— 按ID线性查找，找到后将后续元素前移覆盖
bool deleteVehicle(int id) {
    for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i].id == id) {
            for (int j = i; j < vehicleCount - 1; j++) vehicles[j] = vehicles[j + 1];
            vehicleCount--;
            saveVehicles();
            logAction("删除车辆");
            return true;
        }
    }
    return false;
}
// 修改车辆 —— 按ID查找后覆盖更新字段
bool modifyVehicle(int id, const Vehicle& v) {
    Vehicle* p = findVehicle(id);
    if (!p) return false;
    Vehicle tmp = v;
    tmp.id = id;
    *p = tmp;
    saveVehicles();
    logAction("修改车辆");
    return true;
}
// 添加用户 —— 追加到数组末尾，自动分配ID，保存并记录日志
bool addRenter(const Renter& r) {
    if (renterCount >= MAX_RENTERS) return false;
    renters[renterCount] = r;
    renters[renterCount].id = nextRenterId();
    renters[renterCount].rentCount = 0;
    renterCount++;
    saveRenters();
    logAction("添加用户");
    return true;
}
// 删除用户 —— 按ID线性查找，找到后将后续元素前移覆盖
bool deleteRenter(int id) {
    for (int i = 0; i < renterCount; i++) {
        if (renters[i].id == id) {
            for (int j = i; j < renterCount - 1; j++) renters[j] = renters[j + 1];
            renterCount--;
            saveRenters();
            logAction("删除用户");
            return true;
        }
    }
    return false;
}
// 修改用户 —— 按ID查找后覆盖更新字段
bool modifyRenter(int id, const Renter& r) {
    Renter* p = findRenter(id);
    if (!p) return false;
    Renter tmp = r;
    tmp.id = id;
    *p = tmp;
    saveRenters();
    logAction("修改用户");
    return true;
}
// 办理租车 —— 校验车辆可租状态后创建租车记录，更新车辆状态和用户租车次数
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
    rents[rentCount++] = rec;
    v->status = STATUS_RENTED;
    r->rentCount++;
    saveAllData();
    logAction("办理租车");
    return true;
}
// 办理退车 —— 按租车天数 × 日租金计算总费用，退还押金差额，恢复车辆为可租状态
bool returnRent(int rentId, const char* returnDate, double& totalFee, double& refund) {
    RentRecord* rec = findRent(rentId);
    if (!rec || rec->status == RENT_RETURNED) return false;
    int days = diffDays(rec->rentDate, returnDate);
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

//==========================第十一部分：打印信息方法====================
// 打印车辆表头
void printVehicleHeader() {
    printf("%-4s %-10s %-10s %-10s %-8s %-12s %-6s %-8s %-10s\n",
           "ID", "车牌", "品牌", "类型", "颜色", "购车日期", "状态", "日租金", "里程");
}
// 打印车辆单行
void printVehicleRow(const Vehicle& v) {
    printf("%-4d %-10s %-10s %-10s %-8s %-12s %-6s %-8.2f %-10.1f\n",
           v.id, v.plateNo, v.brand, v.type, v.color, v.purchaseDate,
           vehicleStatusStr(v.status), v.dailyRate, v.mileage);
}
// 打印用户表头
void printRenterHeader() {
    printf("%-4s %-10s %-4s %-2s %-12s %-16s %-16s %-4s %-4s\n",
           "ID", "姓名", "年龄", "性", "电话", "驾照", "身份证", "驾龄", "次数");
}
// 打印用户单行
void printRenterRow(const Renter& r) {
    printf("%-4d %-10s %-4d %-2c %-12s %-16s %-16s %-4d %-4d\n",
           r.id, r.name, r.age, r.gender, r.phone, r.licenseNo, r.idCard, r.drivingYears, r.rentCount);
}
// 打印租车记录表头
void printRentHeader() {
    printf("%-4s %-4s %-4s %-12s %-12s %-12s %-8s %-8s %-8s %-6s\n",
           "ID", "车", "人", "租车日期", "预计归还", "实际归还", "押金", "日租金", "总费用", "状态");
}
// 打印租车记录单行
void printRentRow(const RentRecord& r) {
    printf("%-4d %-4d %-4d %-12s %-12s %-12s %-8.2f %-8.2f %-8.2f %-6s\n",
           r.id, r.vehicleId, r.renterId, r.rentDate, r.expectedReturnDate,
           r.actualReturnDate[0] ? r.actualReturnDate : "-",
           r.deposit, r.dailyRate, r.totalFee, rentStatusStr(r.status));
}
// 打印全部车辆列表
void printAllVehicles() {
    printVehicleHeader();
    for (int i = 0; i < vehicleCount; i++) printVehicleRow(vehicles[i]);
}
// 打印全部用户列表
void printAllRenters() {
    printRenterHeader();
    for (int i = 0; i < renterCount; i++) printRenterRow(renters[i]);
}
// 打印全部租车记录列表
void printAllRents() {
    printRentHeader();
    for (int i = 0; i < rentCount; i++) printRentRow(rents[i]);
}

//==========================第十二部分：统计汇总方法====================
// 统计可租车辆数量
int countAvailableVehicles() {
    int c = 0;
    for (int i = 0; i < vehicleCount; i++) if (vehicles[i].status == STATUS_AVAILABLE) c++;
    return c;
}
// 统计已租车辆数量
int countRentedVehicles() {
    int c = 0;
    for (int i = 0; i < vehicleCount; i++) if (vehicles[i].status == STATUS_RENTED) c++;
    return c;
}
// 统计进行中的租车记录数量
int countActiveRents() {
    int c = 0;
    for (int i = 0; i < rentCount; i++) if (rents[i].status == RENT_ACTIVE) c++;
    return c;
}
// 统计总收入（已归还记录的总费用之和）
double totalRevenue() {
    double sum = 0;
    for (int i = 0; i < rentCount; i++) if (rents[i].status == RENT_RETURNED) sum += rents[i].totalFee;
    return sum;
}
// 打印统计汇总信息
void printStatistics() {
    printf("车辆总数: %d\n", vehicleCount);
    printf("可租车辆: %d\n", countAvailableVehicles());
    printf("已租车辆: %d\n", countRentedVehicles());
    printf("用户总数: %d\n", renterCount);
    printf("租车记录: %d\n", rentCount);
    printf("进行中: %d\n", countActiveRents());
    printf("总收入: %.2f\n", totalRevenue());
}
// 导出报表到带时间戳的文本文件
void exportReport() {
    char name[64];
    nowDateTime(name, sizeof(name));
    for (int i = 0; name[i]; i++) if (name[i] == ' ' || name[i] == ':') name[i] = '_';
    char fileName[96];
    snprintf(fileName, sizeof(fileName), "report_%s.txt", name);
    FILE* fp = fopen(fileName, "w");
    if (!fp) return;
    fprintf(fp, "车辆信息\n");
    for (int i = 0; i < vehicleCount; i++) {
        fprintf(fp, "%d %s %s %s %s %.2f %s\n", vehicles[i].id, vehicles[i].plateNo, vehicles[i].brand,
                vehicles[i].type, vehicles[i].color, vehicles[i].dailyRate, vehicleStatusStr(vehicles[i].status));
    }
    fprintf(fp, "\n用户信息\n");
    for (int i = 0; i < renterCount; i++) {
        fprintf(fp, "%d %s %s %s\n", renters[i].id, renters[i].name, renters[i].licenseNo, renters[i].phone);
    }
    fprintf(fp, "\n租车记录\n");
    for (int i = 0; i < rentCount; i++) {
        fprintf(fp, "%d %d %d %s %s %.2f %s\n", rents[i].id, rents[i].vehicleId, rents[i].renterId,
                rents[i].rentDate, rents[i].expectedReturnDate, rents[i].totalFee, rentStatusStr(rents[i].status));
    }
    fclose(fp);
}

//==========================第十三部分：综合输出====================
// 一次性输出全部信息（车辆、用户、租车记录）
void showAllInfo() {
    printf("\n===== 车辆 =====\n");
    printAllVehicles();
    printf("\n===== 用户 =====\n");
    printAllRenters();
    printf("\n===== 租车记录 =====\n");
    printAllRents();
}

//==========================第十五部分：子菜单模块引用====================
#include "menu1_vehicle.cpp"
#include "menu2_renter.cpp"
#include "menu3_rent.cpp"
#include "menu4_return.cpp"
#include "menu5_query.cpp"
#include "menu6_statistics.cpp"
#include "menu7_output.cpp"
#include "menu8_system.cpp"
#include "menu9_extended.cpp"

//==========================第十六部分：界面渲染与程序入口====================
// 打印系统标题横幅
void showBanner() {
    printf("\n汽车租赁管理系统\n");
}
// 主菜单 —— 显示9个功能模块选项，用户选择后进入对应子菜单，返回false表示退出
bool mainMenu() {
    printf("\n1. 车辆信息管理\n");
    printf("2. 租车用户信息管理\n");
    printf("3. 租车业务办理\n");
    printf("4. 退车业务办理\n");
    printf("5. 信息查询\n");
    printf("6. 统计汇总\n");
    printf("7. 输出全部信息\n");
    printf("8. 系统设置\n");
    printf("9. 扩展功能\n");
    printf("0. 退出系统\n");
    int choice = inputInt("请选择: ", 0, 9);
    switch (choice) {
        case 1: menu1Vehicle(); break;
        case 2: menu2Renter(); break;
        case 3: menu3Rent(); break;
        case 4: menu4Return(); break;
        case 5: menu5Query(); break;
        case 6: menu6Statistics(); break;
        case 7: menu7Output(); break;
        case 8: menu8System(); break;
        case 9: menu9Extended(); break;
        case 0: return false;
        default: break;
    }
    return true;
}
// 程序启动入口 —— 加载数据 → 登录校验 → 主循环 → 保存数据
void runApp() {
    loadAllData();
    if (!login()) {
        printf("登录失败\n");
        return;
    }
    showBanner();
    while (mainMenu()) {}
    saveAllData();
}

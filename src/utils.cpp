#include "utils.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>

void getCurrentDate(char* buffer) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    snprintf(buffer, MAX_DATE_LEN, "%04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
}

void getCurrentDateTime(char* buffer) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    snprintf(buffer, MAX_DATE_LEN + 12, "%04d-%02d-%02d %02d:%02d:%02d",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
}

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int isValidDate(const char* date) {
    if (date == NULL) return 0;
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit((unsigned char)date[i])) return 0;
    }
    int year = atoi(date);
    int month = atoi(date + 5);
    int day = atoi(date + 8);
    if (year < 2000 || year > 2100) return 0;
    if (month < 1 || month > 12) return 0;
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year)) daysInMonth[1] = 29;
    if (day < 1 || day > daysInMonth[month - 1]) return 0;
    return 1;
}

int compareDate(const char* date1, const char* date2) {
    return strcmp(date1, date2);
}

static int dateToDays(const char* date) {
    int y = atoi(date);
    int m = atoi(date + 5);
    int d = atoi(date + 8);
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = 0;
    for (int i = 0; i < y; i++) {
        days += isLeapYear(i) ? 366 : 365;
    }
    for (int i = 1; i < m; i++) {
        days += daysInMonth[i - 1];
        if (i == 2 && isLeapYear(y)) days++;
    }
    days += d - 1;
    return days;
}

int daysBetween(const char* date1, const char* date2) {
    int d1 = dateToDays(date1);
    int d2 = dateToDays(date2);
    return d1 > d2 ? d1 - d2 : d2 - d1;
}

int isValidDateRange(const char* startDate, const char* endDate) {
    return compareDate(startDate, endDate) <= 0;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getIntInput(const char* prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
            clearInputBuffer();
            return value;
        }
        printf("输入无效，请输入 %d 到 %d 之间的整数\n", min, max);
        clearInputBuffer();
    }
}

double getDoubleInput(const char* prompt, double min, double max) {
    double value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &value) == 1 && value >= min && value <= max) {
            clearInputBuffer();
            return value;
        }
        printf("输入无效，请输入 %.2f 到 %.2f 之间的数值\n", min, max);
        clearInputBuffer();
    }
}

void getStringInput(const char* prompt, char* buffer, int maxLen) {
    printf("%s", prompt);
    fgets(buffer, maxLen, stdin);
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

char getCharInput(const char* prompt, const char* validChars) {
    char ch;
    while (1) {
        printf("%s", prompt);
        scanf(" %c", &ch);
        clearInputBuffer();
        if (strchr(validChars, ch) != NULL) {
            return ch;
        }
        printf("输入无效，请输入 [%s] 中的一个字符\n", validChars);
    }
}

int confirmAction(const char* prompt) {
    char ch;
    printf("%s 确认? (y/n): ", prompt);
    scanf(" %c", &ch);
    clearInputBuffer();
    return (ch == 'y' || ch == 'Y') ? 1 : 0;
}

void showProgressBar(const char* label, int current, int total) {
    if (total == 0) return;
    int percent = current * 100 / total;
    int barLen = 20;
    int filled = current * barLen / total;
    printf("%s [", label);
    for (int i = 0; i < filled; i++) printf("=");
    if (filled < barLen) printf(">");
    for (int i = filled + 1; i < barLen; i++) printf(" ");
    printf("] %d%%\n", percent);
}

void printSeparator(char ch, int count) {
    for (int i = 0; i < count; i++) {
        putchar(ch);
    }
    putchar('\n');
}

void printCentered(const char* text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    if (padding < 0) padding = 0;
    for (int i = 0; i < padding; i++) putchar(' ');
    printf("%s\n", text);
}

void pauseScreen() {
    printf("按回车键继续...");
    getchar();
}

int fuzzyMatch(const char* text, const char* pattern) {
    if (text == NULL || pattern == NULL) return 0;
    if (strlen(pattern) == 0) return 1;
    int textLen = strlen(text);
    int patLen = strlen(pattern);
    for (int i = 0; i <= textLen - patLen; i++) {
        int match = 1;
        for (int j = 0; j < patLen; j++) {
            if (tolower((unsigned char)text[i + j]) != tolower((unsigned char)pattern[j])) {
                match = 0;
                break;
            }
        }
        if (match) return 1;
    }
    return 0;
}

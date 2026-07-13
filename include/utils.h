#ifndef UTILS_H
#define UTILS_H

#include "common.h"

void getCurrentDate(char* buffer);
void getCurrentDateTime(char* buffer);
int compareDate(const char* date1, const char* date2);
int daysBetween(const char* date1, const char* date2);
int isValidDate(const char* date);
int isLeapYear(int year);
int isValidDateRange(const char* startDate, const char* endDate);
void clearInputBuffer();
int getIntInput(const char* prompt, int min, int max);
double getDoubleInput(const char* prompt, double min, double max);
void getStringInput(const char* prompt, char* buffer, int maxLen);
char getCharInput(const char* prompt, const char* validChars);
int confirmAction(const char* prompt);
void showProgressBar(const char* label, int current, int total);
void printSeparator(char ch, int count);
void printCentered(const char* text, int width);
void pauseScreen();
int fuzzyMatch(const char* text, const char* pattern);

#endif

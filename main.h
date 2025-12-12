/* ========================================
   FILE: main.h (Header File)
   ======================================== */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <time.h>

enum Status { ACTIVE, BLOCKED };

struct Student {
    int id;
    char name[30];
    int warnings;
    int loginCount;
    enum Status status;
    char lastLogin[40];
};

extern struct Student students[];
extern char allowed[10][30];
extern char blocked[10][30];
extern int allowedCount, blockedCount;

extern const char adminUser[];
extern const char adminPass[];

extern const char *STUDENT_FILE;
extern const char *HISTORY_FILE;
extern const char *ALLOWED_FILE;
extern const char *BLOCKED_FILE;

void clearInputBuffer();
void updateLoginTime(int index);

void saveStudents();
void loadStudents();
void saveSites();
void loadSites();
void logToHistory(const char *action);

void studentLogin();

void adminLogin();
void viewStudents();
void addStudent();
void updateStudent();
void deleteStudent();
void resetWarnings();
void addAllowedSite();
void addBlockedSite();
void viewSites();
void viewHistory();

#endif


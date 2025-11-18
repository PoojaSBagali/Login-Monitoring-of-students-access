#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 3
#define MAX_SITES 10

enum Status { ACTIVE, BLOCKED };

struct Student {
    int id;
    char name[30];
    int warnings;
    enum Status status;
};

extern struct Student students[MAX_STUDENTS];
extern char allowed[MAX_SITES][30];
extern char blocked[MAX_SITES][30];
extern int allowedCount, blockedCount;
extern const char adminUser[];
extern const char adminPass[];

void studentLogin();
void adminLogin();
void viewStudents();
void resetWarnings();
void addAllowedSite();
void addBlockedSite();
void viewSites();

#endif

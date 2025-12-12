/* ========================================
   FILE: student.c (Student Functions)
   ======================================== */

#include "main.h"

void studentLogin() {
    int id;
    char name[30], site[64];
    int idx = -1;

    printf("\n");
    printf("========================================\n");
    printf("          STUDENT LOGIN\n");
    printf("========================================\n");

    printf("Enter Student ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    printf("Enter Name: ");
    scanf("%29s", name);
    clearInputBuffer();

    for (int i = 0; i < 3; i++) {
        if (students[i].id == id && students[i].id != 0 && strcmp(students[i].name, name) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("\n*** ERROR: Invalid Student login!\n");
        char logMsg[128];
        sprintf(logMsg, "STUDENT: Failed login attempt (ID:%d, Name:%s)", id, name);
        logToHistory(logMsg);
        return;
    }

    if (students[idx].status == BLOCKED) {
        printf("\n*** BLOCKED: You are BLOCKED!\n");
        char logMsg[128];
        sprintf(logMsg, "STUDENT: %s (ID:%d) attempted login while BLOCKED", name, id);
        logToHistory(logMsg);
        return;
    }

    students[idx].loginCount++;
    updateLoginTime(idx);
    saveStudents();

    char loginMsg[128];
    sprintf(loginMsg, "STUDENT: %s (ID:%d) logged in successfully", students[idx].name, students[idx].id);
    logToHistory(loginMsg);

    FILE *hf = fopen(HISTORY_FILE, "a");

    printf("\nWelcome %s!\n", students[idx].name);
    printf("\n--- ALLOWED SITES ---\n");
    for (int j = 0; j < allowedCount; j++) {
        printf("  %d. %s\n", j+1, allowed[j]);
    }

    printf("\n--- BLOCKED SITES ---\n");
    for (int j = 0; j < blockedCount; j++) {
        printf("  %d. %s\n", j+1, blocked[j]);
    }
    printf("-------------------------------------------\n");

    while (1) {
        printf("\nEnter website (type 'exit' to logout): ");
        scanf("%63s", site);

        if (strcmp(site, "exit") == 0) break;

        int allow = 0, block = 0;

        for (int j = 0; j < allowedCount; j++) {
            if (strcmp(site, allowed[j]) == 0) {
                allow = 1;
            }
        }

        for (int j = 0; j < blockedCount; j++) {
            if (strcmp(site, blocked[j]) == 0) {
                block = 1;
            }
        }

        char result[64];

        if (allow) {
            strcpy(result, "ALLOWED");
            printf("OK: Access granted.\n");

        } else if (block) {
            students[idx].warnings++;
            saveStudents();

            if (students[idx].warnings >= 2) {
                students[idx].status = BLOCKED;
                saveStudents();
                strcpy(result, "BLOCKED (User Blocked)");
                printf("\n*** BLOCKED: You are now BLOCKED!\n");
                
                char blockMsg[128];
                sprintf(blockMsg, "STUDENT: %s (ID:%d) BLOCKED after 2 warnings", students[idx].name, students[idx].id);
                logToHistory(blockMsg);
                break;
            } else {
                sprintf(result, "BLOCKED (Warning %d)", students[idx].warnings);
                printf("WARNING: Warning %d!\n", students[idx].warnings);
            }

        } else {
            strcpy(result, "UNKNOWN SITE");
            printf("UNKNOWN: Unknown site.\n");
        }

        if (hf) {
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            char timestr[40];
            strftime(timestr, 40, "%d-%m-%Y %H:%M:%S", t);

            static int loginCounter = 1;

            fprintf(hf,
                "STUDENT: %s (ID:%d)\n"
                "Access #%d | Time: %s | Site: %s | Result: %s\n\n",
                students[idx].name,
                students[idx].id,
                loginCounter++,
                timestr,
                site,
                result
            );
        }
        
        char webLogMsg[200];
        sprintf(webLogMsg, "STUDENT: %s (ID:%d) - Site: %s | Result: %s", 
                students[idx].name, students[idx].id, site, result);
        logToHistory(webLogMsg);
    }

    if (hf) {
        fclose(hf);
    }
    
    char logoutMsg[128];
    sprintf(logoutMsg, "STUDENT: %s (ID:%d) logged out", students[idx].name, students[idx].id);
    logToHistory(logoutMsg);
    
    printf("\nLogged out successfully.\n");
}


#include "main.h"

/* ---------------- BUFFER CLEAN ---------------- */
void clearInputBuffer() {
    while (getchar() != '\n');
}

void updateLoginTime(int index) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    if (t) {
        strftime(students[index].lastLogin, sizeof(students[index].lastLogin),
                 "%d-%m-%Y %H:%M:%S", t);
    }
}

/* ---------------- SAVE / LOAD ---------------- */
void saveStudents() {
    FILE *fp = fopen(STUDENT_FILE, "w");
    if (!fp) return;

    for (int i = 0; i < 3; i++) {
        fprintf(fp, "%d %s %d %d %d %s\n",
                students[i].id,
                students[i].name,
                students[i].warnings,
                students[i].loginCount,
                students[i].status,
                students[i].lastLogin);
    }
    fclose(fp);
}

void loadStudents() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) return;

    for (int i = 0; i < 3; i++) {
        int st;
        if (fscanf(fp, "%d %29s %d %d %d %[^\n]",
               &students[i].id,
               students[i].name,
               &students[i].warnings,
               &students[i].loginCount,
               &st,
               students[i].lastLogin) != 6) break;

        students[i].status = st;
    }
    fclose(fp);
}

/* ---------------- STUDENT LOGIN ---------------- */
void studentLogin() {
    int id;
    char name[30], site[64];
    int idx = -1;

    printf("Enter Student ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    printf("Enter Name: ");
    scanf("%29s", name);
    clearInputBuffer();

    for (int i = 0; i < 3; i++) {
        if (students[i].id == id && strcmp(students[i].name, name) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Invalid Student login!\n");
        return;
    }

    if (students[idx].status == BLOCKED) {
        printf("You are BLOCKED!\n");
        return;
    }

    students[idx].loginCount++;
    updateLoginTime(idx);
    saveStudents();

    FILE *hf = fopen(HISTORY_FILE, "a");

    printf("\nWelcome %s!\n", students[idx].name);


    printf("\nAllowed Sites:\n");
    for (int j = 0; j < allowedCount; j++) printf("- %s\n", allowed[j]);

    printf("\nBlocked Sites:\n");
    for (int j = 0; j < blockedCount; j++) printf("- %s\n", blocked[j]);

    printf("---------------------------------------------------\n");



    while (1) {
        printf("\nEnter website (type 'exit'): ");
        scanf("%63s", site);

        if (strcmp(site, "exit") == 0) break;

        int allow = 0, block = 0;

        for (int j = 0; j < allowedCount; j++)
            if (strcmp(site, allowed[j]) == 0) allow = 1;

        for (int j = 0; j < blockedCount; j++)
            if (strcmp(site, blocked[j]) == 0) block = 1;

        char result[64];

        if (allow) {
            strcpy(result, "ALLOWED");
            printf("Access granted.\n");

        } else if (block) {
            students[idx].warnings++;
            saveStudents();

            if (students[idx].warnings >= 2) {
                students[idx].status = BLOCKED;
                saveStudents();
                strcpy(result, "BLOCKED (User Blocked)");
                printf("You are now BLOCKED!\n");
                break;
            } else {
                sprintf(result, "BLOCKED (Warning %d)", students[idx].warnings);
                printf("Warning %d!\n", students[idx].warnings);
            }

        } else {
            strcpy(result, "UNKNOWN SITE");
            printf("Unknown site.\n");
        }

       if (hf) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestr[40];
    strftime(timestr, 40, "%d-%m-%Y %H:%M:%S", t);

    static int loginCounter = 1;  // increments for each entry

    fprintf(hf,
        "Student: %s (ID:%d)\n"
        "Login #%d | Time: %s | Site: %s | Result: %s\n\n",
        students[idx].name,
        students[idx].id,
        loginCounter++,
        timestr,
        site,
        result
    );
}
    }

    if (hf) fclose(hf);
}

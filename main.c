/* ========================================
   FILE: main.c (Main Program & Utilities)
   ======================================== */

#include "main.h"
#include "student.c"
#include "admin.c"

struct Student students[5] = {
    {101, "A", 0, 0, ACTIVE, "No login yet"},
    {102, "B", 0, 0, ACTIVE, "No login yet"},
    {103, "C", 0, 0, ACTIVE, "No login yet"}
};

char allowed[10][30] = {"eduportal.com", "library.com", "assignments.edu"};
char blocked[10][30] = {"facebook.com", "youtube.com", "gaming.com", "chatapp.com"};
int allowedCount = 3, blockedCount = 4;

const char adminUser[] = "admin";
const char adminPass[] = "1234";

const char *STUDENT_FILE = "students.txt";
const char *HISTORY_FILE = "student_history.txt";
const char *ALLOWED_FILE = "allowed_sites.txt";
const char *BLOCKED_FILE = "blocked_sites.txt";

/* ============ UTILITY FUNCTIONS ============ */
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

void logToHistory(const char *action) {
    FILE *fp = fopen(HISTORY_FILE, "a");
    if (!fp) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestr[40];
    strftime(timestr, 40, "%d-%m-%Y %H:%M:%S", t);

    fprintf(fp, "[%s] %s\n", timestr, action);
    fclose(fp);
}

/* ============ FILE OPERATIONS ============ */
void saveStudents() {
    FILE *fp = fopen(STUDENT_FILE, "w");
    if (!fp) return;

    for (int i = 0; i < 5; i++) {
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

    for (int i = 0; i < 5; i++) {
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

void saveSites() {
    FILE *fp = fopen(ALLOWED_FILE, "w");
    if (fp) {
        for (int i = 0; i < allowedCount; i++) {
            fprintf(fp, "%s\n", allowed[i]);
        }
        fclose(fp);
    }

    fp = fopen(BLOCKED_FILE, "w");
    if (fp) {
        for (int i = 0; i < blockedCount; i++) {
            fprintf(fp, "%s\n", blocked[i]);
        }
        fclose(fp);
    }
}

void loadSites() {
    FILE *fp = fopen(ALLOWED_FILE, "r");
    if (fp) {
        allowedCount = 0;
        while (fgets(allowed[allowedCount], 30, fp) && allowedCount < 10) {
            size_t len = strlen(allowed[allowedCount]);
            if (len > 0 && allowed[allowedCount][len-1] == '\n') {
                allowed[allowedCount][len-1] = '\0';
            }
            allowedCount++;
        }
        fclose(fp);
    }

    fp = fopen(BLOCKED_FILE, "r");
    if (fp) {
        blockedCount = 0;
        while (fgets(blocked[blockedCount], 30, fp) && blockedCount < 10) {
            size_t len = strlen(blocked[blockedCount]);
            if (len > 0 && blocked[blockedCount][len-1] == '\n') {
                blocked[blockedCount][len-1] = '\0';
            }
            blockedCount++;
        }
        fclose(fp);
    }
}

/* ============ MAIN MENU ============ */
int main() {
    int mainChoice;
    loadStudents();
    loadSites();

    while (1) {
	printf("\n");
        printf("====================================================================\n");
        printf("         	STUDENT PORTAL MONITORING PORTAL\n");
        printf("====================================================================\n");

        printf("\n");
        printf("========================================\n");
        printf("          MAIN MENU\n");
        printf("========================================\n");
        printf("1. Student Login\n");
        printf("2. Admin Login\n");
        printf("3. Exit\n");
        printf("========================================\n");
        printf("Enter choice: ");
        
        while (scanf("%d", &mainChoice) != 1) {
            clearInputBuffer();
            printf("Invalid! Enter again: ");
        }
        clearInputBuffer();

        switch (mainChoice) {
            case 1: studentLogin(); break;
            case 2: adminLogin(); break;
            case 3:
                saveStudents();
                saveSites();
                logToHistory("=== SYSTEM: Program exited ===");
                printf("\nExiting system...\n");
                return 0;
            default:
                printf("Invalid option!\n");
        }
    }
}

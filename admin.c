#include "main.h"

/* ---------------- ADMIN LOGIN (FIXED) ---------------- */
void adminLogin() {
    char user[30], pass[30];

    printf("Admin Username: ");
    scanf("%29s", user);
    clearInputBuffer();

    printf("Password: ");
    scanf("%29s", pass);
    clearInputBuffer();

    if (strcmp(user, adminUser) != 0 || strcmp(pass, adminPass) != 0) {
        printf("Invalid Admin Login!\n");
        return;   // <-- FIX: return to main menu
    }

    int choice;
    while (1) {
        printf("\n----- ADMIN MENU -----\n");
        printf("1. View Students\n2. View History\n3. Reset Warnings\n4. Add Allowed Site\n5. Add Blocked Site\n6. View Sites\n7. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: viewStudents(); break;
            case 2: viewHistory(); break;
            case 3: resetWarnings(); break;
            case 4: addAllowedSite(); break;
            case 5: addBlockedSite(); break;
            case 6: viewSites(); break;
            case 7: return;        // logout
            default: printf("Invalid choice!\n");
        }
    }
}

/* ---------------- ADMIN FUNCTIONS ---------------- */
void viewStudents() {
    printf("\nID   Name   Warn  Logins  Status  Last Login\n");
    for (int i = 0; i < 3; i++) {
        printf("%d  %s  %d  %d  %s  %s\n",
               students[i].id,
               students[i].name,
               students[i].warnings,
               students[i].loginCount,
               students[i].status == BLOCKED ? "Blocked" : "Active",
               students[i].lastLogin);
    }
}

void viewHistory() {
    FILE *fp = fopen(HISTORY_FILE, "r");
    if (!fp) {
        printf("History not found.\n");
        return;
    }

    char line[256];
    while (fgets(line, 256, fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

void resetWarnings() {
    int sid;
    printf("Enter student ID: ");
    scanf("%d", &sid);

    for (int i = 0; i < 3; i++) {
        if (students[i].id == sid) {
            students[i].warnings = 0;
            students[i].status = ACTIVE;
            saveStudents();
            printf("Student unblocked.\n");
            return;
        }
    }
    printf("Invalid ID!\n");
}

void addAllowedSite() {
    char site[30];
    if (allowedCount >= 10) return;

    printf("Enter site: ");
    scanf("%29s", site);
    strcpy(allowed[allowedCount++], site);

    printf("Added to allowed list.\n");
}

void addBlockedSite() {
    char site[30];
    if (blockedCount >= 10) return;

    printf("Enter site: ");
    scanf("%29s", site);
    strcpy(blocked[blockedCount++], site);

    printf("Added to blocked list.\n");
}

void viewSites() {
    printf("\nAllowed Sites:\n");
    for (int i = 0; i < allowedCount; i++)
        printf("%d. %s\n", i + 1, allowed[i]);

    printf("\nBlocked Sites:\n");
    for (int i = 0; i < blockedCount; i++)
        printf("%d. %s\n", i + 1, blocked[i]);
}

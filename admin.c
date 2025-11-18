#include "main.h"

void adminLogin() {
    char user[20], pass[20];
    printf("Enter admin username: ");
    scanf("%s", user);
    printf("Enter password: ");
    scanf("%s", pass);

    if (strcmp(user, adminUser) != 0 || strcmp(pass, adminPass) != 0) {
        printf("Invalid admin credentials!\n");
        return;
    }

    int choice;
    while (1) {
        printf("\n--- Admin Menu ---\n");
        printf("1. View Students\n2. Reset Warnings\n3. Add Allowed Site\n4. Add Blocked Site\n5. View Sites\n6. Logout\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewStudents(); break;
            case 2: resetWarnings(); break;
            case 3: addAllowedSite(); break;
            case 4: addBlockedSite(); break;
            case 5: viewSites(); break;
            case 6: printf("Admin logged out.\n"); return;
            default: printf("Invalid choice!\n");
        }
    }
}

void viewStudents() {
    for (register int i = 0; i < MAX_STUDENTS; i++)
        printf("ID: %d   Name: %s   Warnings: %d   Status: %s\n",
               students[i].id, students[i].name,
               students[i].warnings,
               students[i].status == BLOCKED ? "Blocked" : "Active");
}

void resetWarnings() {
    auto int sid, found = 0;
    printf("Enter Student ID to reset: ");
    scanf("%d", &sid);
    for (register int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].id == sid) {
            students[i].warnings = 0;
            students[i].status = ACTIVE;
            printf("%s reset successfully.\n", students[i].name);
            found = 1;
            break;
        }
    }
    if (!found) printf("Invalid ID!\n");
}

void addAllowedSite() {
    if (allowedCount < MAX_SITES) {
        printf("Enter new allowed website: ");
        scanf("%s", allowed[allowedCount]);
        allowedCount++;
        printf("Website added to allowed list.\n");
    } else
        printf("Allowed list is full.\n");
}

void addBlockedSite() {
    if (blockedCount < MAX_SITES) {
        printf("Enter new blocked website: ");
        scanf("%s", blocked[blockedCount]);
        blockedCount++;
        printf("Website added to blocked list.\n");
    } else
        printf("Blocked list is full.\n");
}

void viewSites() {
    printf("\n--- Allowed Websites ---\n");
    for (register int j = 0; j < allowedCount; j++)
        printf("%d. %s\n", j + 1, allowed[j]);

    printf("\n--- Blocked Websites ---\n");
    for (register int j = 0; j < blockedCount; j++)
        printf("%d. %s\n", j + 1, blocked[j]);
}

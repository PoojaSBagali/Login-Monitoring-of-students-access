/* ========================================
   FILE: admin.c (Admin Functions)
   ======================================== */

#include "main.h"

void viewStudents() {
    printf("\n");
    printf("===========================================================================\n");
    printf("                  		STUDENT LIST\n");
    printf("===========================================================================\n");
    printf("ID   Name            Warn   Login       Status         Last Login\n");
    printf("===========================================================================\n");
    
    int count = 0;
    for (int i = 0; i < 3; i++) {
        if (students[i].id != 0) {
            printf("%-3d  %-16s  %-5d  %-7d  %-10s  %s\n",
                   students[i].id,
                   students[i].name,
                   students[i].warnings,
                   students[i].loginCount,
                   students[i].status == BLOCKED ? "BLOCKED" : "ACTIVE",
                   students[i].lastLogin);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No students registered yet.\n");
    }
    printf("===========================================================================\n");
    printf("Total Active Students: %d/3\n", count);
    printf("===========================================================================\n");
    logToHistory("ADMIN: Viewed student list");
}

void addStudent() {
    int id;
    char name[30];
    int idx = -1;

    printf("\n");
    printf("========================================\n");
    printf("           ADD NEW STUDENT\n");
    printf("========================================\n");

    for (int i = 0; i < 3; i++) {
        if (students[i].id == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("ERROR: All student slots are full!\n");
        logToHistory("ADMIN: Failed to add student - All slots full");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    for (int i = 0; i < 3; i++) {
        if (students[i].id == id) {
            printf("ERROR: Student ID already exists!\n");
            logToHistory("ADMIN: Failed to add student - Duplicate ID");
            return;
        }
    }

    printf("Enter Student Name: ");
    scanf("%29s", name);
    clearInputBuffer();

    students[idx].id = id;
    strcpy(students[idx].name, name);
    students[idx].warnings = 0;
    students[idx].loginCount = 0;
    students[idx].status = ACTIVE;
    strcpy(students[idx].lastLogin, "No login yet");

    saveStudents();

    printf("SUCCESS: Student %s (ID:%d) added successfully!\n", name, id);
    
    char logMsg[128];
    sprintf(logMsg, "ADMIN: Added new student - %s (ID:%d)", name, id);
    logToHistory(logMsg);
}

void deleteStudent() {
    int sid;
    printf("\n");
    printf("========================================\n");
    printf("           DELETE STUDENT\n");
    printf("========================================\n");

    printf("Enter student ID to delete: ");
    scanf("%d", &sid);
    clearInputBuffer();

    for (int i = 0; i < 3; i++) {
        if (students[i].id == sid) {
            char logMsg[128];
            sprintf(logMsg, "ADMIN: Deleted student - %s (ID:%d)", students[i].name, sid);
            
            students[i].id = 0;
            strcpy(students[i].name, "");
            students[i].warnings = 0;
            students[i].loginCount = 0;
            students[i].status = ACTIVE;
            strcpy(students[i].lastLogin, "");

            saveStudents();

            printf("SUCCESS: Student deleted successfully!\n");
            logToHistory(logMsg);
            return;
        }
    }
    printf("ERROR: Student ID not found!\n");
    logToHistory("ADMIN: Failed to delete - Student ID not found");
}

void updateStudent() {
    int sid;
    printf("\n");
    printf("========================================\n");
    printf("           UPDATE STUDENT\n");
    printf("========================================\n");

    printf("Enter student ID to update: ");
    scanf("%d", &sid);
    clearInputBuffer();

    int idx = -1;
    for (int i = 0; i < 3; i++) {
        if (students[i].id == sid) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("ERROR: Student ID not found!\n");
        logToHistory("ADMIN: Failed to update - Student ID not found");
        return;
    }

    printf("\nUpdate Options for Student %s (ID:%d):\n", students[idx].name, sid);
    printf("1. Update Name\n");
    printf("2. Reset Warnings\n");
    printf("3. Change Status\n");
    printf("4. Back to Admin Menu\n");
    printf("Enter choice: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
        case 1: {
            printf("Enter new name: ");
            scanf("%29s", students[idx].name);
            clearInputBuffer();
            saveStudents();
            printf("SUCCESS: Name updated!\n");
            char logMsg[128];
            sprintf(logMsg, "ADMIN: Updated student name - ID:%d to %s", sid, students[idx].name);
            logToHistory(logMsg);
            break;
        }
        case 2: {
            students[idx].warnings = 0;
            students[idx].status = ACTIVE;
            saveStudents();
            printf("SUCCESS: Warnings reset!\n");
            char logMsg[128];
            sprintf(logMsg, "ADMIN: Updated student %s (ID:%d) - Warnings reset", students[idx].name, sid);
            logToHistory(logMsg);
            break;
        }
        case 3: {
            printf("Current Status: %s\n", students[idx].status == ACTIVE ? "ACTIVE" : "BLOCKED");
            printf("Change to: 1.ACTIVE  2.BLOCKED: ");
            int status;
            scanf("%d", &status);
            clearInputBuffer();
            students[idx].status = (status == 1) ? ACTIVE : BLOCKED;
            saveStudents();
            printf("SUCCESS: Status updated!\n");
            char logMsg[128];
            sprintf(logMsg, "ADMIN: Updated student %s (ID:%d) - Status: %s", 
                    students[idx].name, sid, students[idx].status == ACTIVE ? "ACTIVE" : "BLOCKED");
            logToHistory(logMsg);
            break;
        }
        case 4:
            return;
        default:
            printf("ERROR: Invalid choice!\n");
    }
}

void viewHistory() {
    FILE *fp = fopen(HISTORY_FILE, "r");
    if (!fp) {
        printf("\nWARNING: History file not found.\n");
        return;
    }

    printf("\n");
    printf("=========================================================\n");
    printf("                    SYSTEM HISTORY LOG\n");
    printf("=========================================================\n\n");
    
    char line[256];
    while (fgets(line, 256, fp)) {
        printf("%s", line);
    }
    fclose(fp);
    printf("\n=========================================================\n");
    
    logToHistory("ADMIN: Viewed system history");
}

void resetWarnings() {
    int sid;
    printf("Enter student ID: ");
    scanf("%d", &sid);
    clearInputBuffer();

    for (int i = 0; i < 3; i++) {
        if (students[i].id == sid) {
            students[i].warnings = 0;
            students[i].status = ACTIVE;
            saveStudents();
            printf("SUCCESS: Student %s unblocked and warnings reset.\n", students[i].name);
            
            char logMsg[128];
            sprintf(logMsg, "ADMIN: Reset warnings for Student %s (ID:%d)", students[i].name, sid);
            logToHistory(logMsg);
            return;
        }
    }
    printf("ERROR: Invalid ID!\n");
    logToHistory("ADMIN: Failed to reset - Invalid student ID");
}

void addAllowedSite() {
    char site[30];
    if (allowedCount >= 10) {
        printf("ERROR: Maximum allowed sites reached!\n");
        logToHistory("ADMIN: Failed to add allowed site - Maximum limit reached");
        return;
    }

    printf("Enter site: ");
    scanf("%29s", site);
    clearInputBuffer();
    
    strcpy(allowed[allowedCount++], site);
    saveSites();

    printf("SUCCESS: Added '%s' to allowed list.\n", site);
    
    char logMsg[128];
    sprintf(logMsg, "ADMIN: Added allowed site - %s", site);
    logToHistory(logMsg);
}

void addBlockedSite() {
    char site[30];
    if (blockedCount >= 10) {
        printf("ERROR: Maximum blocked sites reached!\n");
        logToHistory("ADMIN: Failed to add blocked site - Maximum limit reached");
        return;
    }

    printf("Enter site: ");
    scanf("%29s", site);
    clearInputBuffer();
    
    strcpy(blocked[blockedCount++], site);
    saveSites();

    printf("SUCCESS: Added '%s' to blocked list.\n", site);
    
    char logMsg[128];
    sprintf(logMsg, "ADMIN: Added blocked site - %s", site);
    logToHistory(logMsg);
}

void viewSites() {
    printf("\n");
    printf("=========================================================\n");
    printf("              SITE MANAGEMENT\n");
    printf("=========================================================\n");
    
    printf("\nALLOWED SITES (%d):\n", allowedCount);
    printf("-----------\n");
    for (int i = 0; i < allowedCount; i++) {
        printf("%d. %s\n", i + 1, allowed[i]);
    }

    printf("\nBLOCKED SITES (%d):\n", blockedCount);
    printf("-----------\n");
    for (int i = 0; i < blockedCount; i++) {
        printf("%d. %s\n", i + 1, blocked[i]);
    }
    printf("\n=========================================================\n");
    
    logToHistory("ADMIN: Viewed site lists");
}

void adminLogin() {
    char user[30], pass[30];

    printf("\n");
    printf("========================================\n");
    printf("          ADMIN LOGIN\n");
    printf("========================================\n");

    printf("Admin Username: ");
    scanf("%29s", user);
    clearInputBuffer();

    printf("Password: ");
    scanf("%29s", pass);
    clearInputBuffer();

    if (strcmp(user, adminUser) != 0 || strcmp(pass, adminPass) != 0) {
        printf("\n*** ERROR: Invalid Admin Login!\n");
        logToHistory("ADMIN: Failed login attempt");
        return;
    }

    printf("\nAdmin Login Successful!\n");
    logToHistory("ADMIN: Logged in successfully");

    int choice;
    while (1) {
        printf("\n");
        printf("========================================\n");
        printf("           ADMIN MENU\n");
        printf("========================================\n");
        printf("1. View Students\n");
        printf("2. Add Student\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. View History\n");
        printf("6. Reset Warnings\n");
        printf("7. Add Allowed Site\n");
        printf("8. Add Blocked Site\n");
        printf("9. View Sites\n");
        printf("10. Logout\n");
        printf("========================================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: viewStudents(); break;
            case 2: addStudent(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: viewHistory(); break;
            case 6: resetWarnings(); break;
            case 7: addAllowedSite(); break;
            case 8: addBlockedSite(); break;
            case 9: viewSites(); break;
            case 10:{
                logToHistory("ADMIN: Logged out");
               printf("\nstudents.txt			-	To view the student database");
			printf("\nstudent_history.txt		-	To view the audit log of all activities");	
			printf("\nallowed_sites.txt		-	To view Allowed websites");
			printf("\nblocked_sites.txt		-	To view Blocked websites");
		printf("\nLogged out successfully.\n");
                return;}
            default: printf("ERROR: Invalid choice!\n");
        }
    }
}

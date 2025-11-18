#include <stdio.h>
#include <string.h>

int main() {
    int i, mainChoice;

    struct Student {
        int id;
        char name[30];
        int warnings;
        int isBlocked;
    } students[3] = {
        {101, "A", 0, 0},
        {102, "B", 0, 0},
        {103, "C", 0, 0}
    };

    char adminUser[20] = "admin";
    char adminPass[20] = "1234";

    char allowed[10][30] = {"eduportal.com", "library.com", "assignments.edu"};
    char blocked[10][30] = {"facebook.com", "youtube.com", "gaming.com", "chatapp.com"};
    int allowedCount = 3, blockedCount = 4;

    while (1) {
        printf("\n------------------ Main Menu ----------------------\n");
        printf("1. Student Login\n2. Admin Login\n3. Exit\nEnter choice: ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {

            // -------- STUDENT LOGIN --------
            case 1: {
                int id, found = 0;
                char name[30], site[30];

                printf("Enter Student ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf("%s", name);

                for (i = 0; i < 3; i++) {
                    if (id == students[i].id && strcmp(name, students[i].name) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("Invalid Student login!\n");
                    break;
                }

                if (students[i].isBlocked) {
                    printf("You are BLOCKED! Contact admin.\n");
                    break;
                }

                printf("\nWelcome %s!\n", students[i].name);

                // Show only allowed websites
                printf("\n-------------------- Allowed Websites -----------------------\n");
                for (int j = 0; j < allowedCount; j++)
                    printf("%d. %s ", j + 1, allowed[j]);

                // Browsing loop
                while (1) {
                    printf("\nEnter website to visit (type 'exit' to logout): ");
                    scanf("%s", site);

                    if (strcmp(site, "exit") == 0)
                        break;

                    int allow = 0, block = 0;

                    for (int j = 0; j < allowedCount; j++)
                        if (strcmp(site, allowed[j]) == 0)
                            allow = 1;

                    for (int j = 0; j < blockedCount; j++)
                        if (strcmp(site, blocked[j]) == 0)
                            block = 1;

                    if (allow)
                        printf("Access granted to %s\n", site);
                    else if (block) {
                        students[i].warnings++;
                        printf("Warning %d! %s is blocked!\n", students[i].warnings, site);
                        if (students[i].warnings >= 2) {
                            students[i].isBlocked = 1;
                            printf("You are now BLOCKED due to repeated misuse!\n");
                            break;
                        }
                    } else
                        printf("Unknown site. Not in allowed list.\n");
                }
                break;
            }

            // -------- ADMIN LOGIN --------
            case 2: {
                char user[20], pass[20];
                printf("Enter admin username: ");
                scanf("%s", user);
                printf("Enter password: ");
                scanf("%s", pass);

                if (strcmp(user, adminUser) != 0 || strcmp(pass, adminPass) != 0) {
                    printf("Invalid admin credentials!\n");
                    break;
                }

                int choice;
                while (1) {
                    printf("\n--- Admin Menu ---\n");
                    printf("1. View Students\n2. Reset Warnings\n3. Add Allowed Site\n4. View Allowed Sites\n5. Logout\nEnter choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            for (i = 0; i < 3; i++)
                                printf("ID: %d   Name: %s   Warnings: %d   Status: %s\n",
                                       students[i].id, students[i].name,
                                       students[i].warnings,
                                       students[i].isBlocked ? "Blocked" : "Active");
                            break;

                        case 2: {
                            int sid, found = 0;
                            printf("Enter Student ID to reset: ");
                            scanf("%d", &sid);
                            for (i = 0; i < 3; i++) {
                                if (students[i].id == sid) {
                                    students[i].warnings = 0;
                                    students[i].isBlocked = 0;
                                    printf("%s reset successfully.\n", students[i].name);
                                    found = 1;
                                    break;
                                }
                            }
                            if (!found) printf("Invalid ID!\n");
                            break;
                        }

                        case 3:
                            if (allowedCount < 10) {
                                printf("Enter new allowed website: ");
                                scanf("%s", allowed[allowedCount]);
                                allowedCount++;
                                printf("Website added to allowed list.\n");
                            } else
                                printf("Allowed list is full.\n");
                            break;

                        case 4:
                            printf("\n--- Allowed Websites ---\n");
                            for (int j = 0; j < allowedCount; j++)
                                printf("%d. %s\n", j + 1, allowed[j]);
                            break;

                        case 5:
                            printf("Admin logged out.\n");
                            goto admin_out;

                        default:
                            printf("Invalid choice!\n");
                    }
                }
                admin_out: ;
                break;
            }

            // -------- EXIT --------
            case 3:
                printf("Exiting system...\nThank you for visiting!\n");
                return 0;

            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
}

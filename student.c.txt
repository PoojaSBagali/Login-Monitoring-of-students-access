#include "main.h"

struct Student students[MAX_STUDENTS] = {
    {101, "A", 0, ACTIVE},
    {102, "B", 0, ACTIVE},
    {103, "C", 0, ACTIVE}
};

char allowed[MAX_SITES][30] = {"eduportal.com", "library.com", "assignments.edu"};
char blocked[MAX_SITES][30] = {"facebook.com", "youtube.com", "gaming.com", "chatapp.com"};
int allowedCount = 3, blockedCount = 4;

const char adminUser[] = "admin";
const char adminPass[] = "1234";

void studentLogin() {
    auto int id, found = 0;
    char name[30], site[30];
    int i;

    printf("Enter Student ID: ");
    scanf("%d", &id);
    printf("Enter Name: ");
    scanf("%s", name);

    for (i = 0; i < MAX_STUDENTS; i++) {
        if (id == students[i].id && strcmp(name, students[i].name) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Invalid Student login!\n");
        return;
    }

    if (students[i].status == BLOCKED) {
        printf("You are BLOCKED! Contact admin.\n");
        return;
    }

    printf("\nWelcome %s!\n", students[i].name);
    printf("\n--- Allowed Websites ---\n");
    for (register int j = 0; j < allowedCount; j++)
        printf("%d. %s ", j + 1, allowed[j]);

    while (1) {
        printf("\nEnter website to visit (type 'exit' to logout): ");
        scanf("%s", site);

        if (strcmp(site, "exit") == 0)
            break;

        register int allow = 0, block = 0;

        for (register int j = 0; j < allowedCount; j++)
            if (strcmp(site, allowed[j]) == 0)
                allow = 1;

        for (register int j = 0; j < blockedCount; j++)
            if (strcmp(site, blocked[j]) == 0)
                block = 1;

        if (allow)
            printf("Access granted to %s\n", site);
        else if (block) {
            students[i].warnings++;
            printf("Warning %d! %s is blocked!\n", students[i].warnings, site);
            if (students[i].warnings >= 2) {
                students[i].status = BLOCKED;
                printf("You are now BLOCKED due to repeated misuse!\n");
                break;
            }
        } else
            printf("Unknown site. Not in allowed list.\n");
    }
}

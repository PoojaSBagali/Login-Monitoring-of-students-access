#include "main.h"
#include "student.c"
#include "admin.c"

/* INITIAL DATA */
struct Student students[3] = {
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

/* ---------------- MAIN ---------------- */
int main() {
    int mainChoice;
    loadStudents();

    while (1) {
        printf("\n------------------ MAIN MENU ----------------------\n");
        printf("1. Student Login\n2. Admin Login\n3. Exit\nEnter choice: ");
        
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
                printf("Exiting system...\n");
                return 0;
            default:
                printf("Invalid option!\n");
        }
    }
}

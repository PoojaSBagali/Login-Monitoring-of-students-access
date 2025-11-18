#include "main.h"

int main() {
    auto int mainChoice;

    while (1) {
        printf("\n------------------ Main Menu ----------------------\n");
        printf("1. Student Login\n2. Admin Login\n3. Exit\nEnter choice: ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1: studentLogin(); break;
            case 2: adminLogin(); break;
            case 3:
                printf("Exiting system...\nThank you for visiting!\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
}

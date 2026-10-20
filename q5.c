#include <stdio.h>
#include <string.h>

void displayMenu() {
    printf("\n===== LIBRARY MENU =====\n");
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter choice: ");
}

void registerMember(char name[], int *studentID, int *memberType) {
    printf("Enter name: ");
    scanf(" %[^\n]", name);

    printf("Enter student ID: ");
    scanf("%d", studentID);

    do {
        printf("Membership type (1 = Student, 2 = Faculty): ");
        scanf("%d", memberType);
        if (*memberType != 1 && *memberType != 2) {
            printf("Invalid membership type. Try again.\n");
        }
    } while (*memberType != 1 && *memberType != 2);
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks) {
    int i;

    printf("\n%-6s %-25s %s\n", "ID", "Title", "Copies");
    for (i = 0; i < totalBooks; i++) {
        printf("%-6d %-25s %d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks,
                int borrowedBookIDs[], int *borrowedCount, int memberType) {
    int id, days, i, index = -1;

    if (*borrowedCount >= 3) {
        printf("Borrowing limit reached (max 3 books).\n");
        return;
    }

    printf("Enter book ID: ");
    scanf("%d", &id);

    do {
        printf("Enter number of days: ");
        scanf("%d", &days);
        if (days <= 0) {
            printf("Days must be positive.\n");
        }
    } while (days <= 0);

    for (i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id) {
            index = i;
        }
    }

    if (index == -1) {
        printf("Invalid book ID.\n");
    } else if (availableCopies[index] == 0) {
        printf("No copies available.\n");
    } else {
        borrowedBookIDs[*borrowedCount] = id;
        (*borrowedCount)++;
        availableCopies[index]--;
        printf("Borrowed: %s\n", bookTitles[index]);
    }
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[],
                 int *borrowedCount, int memberType, float *totalFine) {
    int id, days, i, k, pos = -1, index = -1;
    int allowed, rate, extraDays;
    float fine = 0, payable = 0;
    char code[20];

    printf("Enter book ID to return: ");
    scanf("%d", &id);

    do {
        printf("Enter actual days kept: ");
        scanf("%d", &days);
        if (days <= 0) {
            printf("Days must be positive.\n");
        }
    } while (days <= 0);

    /* check karo ke member ne ye book borrow ki thi */
    for (i = 0; i < *borrowedCount; i++) {
        if (borrowedBookIDs[i] == id) {
            pos = i;
        }
    }

    if (pos == -1) {
        printf("You have not borrowed this book.\n");
        return 0;
    }

    /* inventory mein book ka index dhoondo aur copy wapas jodo */
    for (i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id) {
            index = i;
        }
    }
    availableCopies[index]++;

    /* borrowed list se book hatao: baaki books ek jagah aage khiskao */
    for (k = pos; k < *borrowedCount - 1; k++) {
        borrowedBookIDs[k] = borrowedBookIDs[k + 1];
    }
    (*borrowedCount)--;

    /* allowed days aur fine rate */
    if (memberType == 1) {
        allowed = 14;
        rate = 20;
    } else {
        allowed = 30;
        rate = 10;
    }

    if (days > allowed) {
        extraDays = days - allowed;
        fine = extraDays * rate;
        *totalFine = *totalFine + fine;

        printf("Late return. Fine: Rs. %.2f\n", fine);
        printf("Enter membership code: ");
        scanf("%s", code);

        if (strcmp(code, "LIB2026") == 0) {
            payable = fine / 2;
            printf("Waiver applied. Payable: Rs. %.2f\n", payable);
        } else {
            payable = fine;
            printf("No waiver. Payable: Rs. %.2f\n", payable);
        }
    } else {
        printf("Returned on time. No fine.\n");
    }

    return payable;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[],
                         int borrowedCount, float totalFine, float fineAfterWaiver) {
    int i;

    printf("\n===== MEMBER RECORD =====\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);

    if (memberType == 1) {
        printf("Membership: Student\n");
    } else {
        printf("Membership: Faculty\n");
    }

    printf("Currently borrowed books: ");
    if (borrowedCount == 0) {
        printf("None");
    } else {
        for (i = 0; i < borrowedCount; i++) {
            printf("%d ", borrowedBookIDs[i]);
        }
    }
    printf("\n");

    printf("Total fine (before waiver): Rs. %.2f\n", totalFine);
    printf("Fine payable (after waiver): Rs. %.2f\n", fineAfterWaiver);
}

int main() {
    int bookIDs[4] = {101, 102, 103, 104};
    char bookTitles[4][50] = {"Programming in C", "Data Structures",
                              "Database Systems", "Computer Networks"};
    int availableCopies[4] = {5, 3, 0, 4};
    int totalBooks = 4;

    char name[50];
    int studentID, memberType;
    int registered = 0;

    int borrowedBookIDs[3];
    int borrowedCount = 0;
    float totalFine = 0, fineAfterWaiver = 0;

    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerMember(name, &studentID, &memberType);
                registered = 1;
                printf("Registration successful.\n");
                break;

            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
                break;

            case 3:
                if (registered == 0) {
                    printf("Please register first.\n");
                    break;
                }
                borrowBook(bookIDs, bookTitles, availableCopies, totalBooks,
                           borrowedBookIDs, &borrowedCount, memberType);
                break;

            case 4:
                if (registered == 0) {
                    printf("Please register first.\n");
                    break;
                }
                fineAfterWaiver = fineAfterWaiver + returnBook(bookIDs, availableCopies, totalBooks,
                                      borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                break;

            case 5:
                if (registered == 0) {
                    printf("Please register first.\n");
                    break;
                }
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs,
                                    borrowedCount, totalFine, fineAfterWaiver);
                break;

            case 6:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 6);

    return 0;
}

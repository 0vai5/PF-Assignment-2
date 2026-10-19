#include <stdio.h>

int main() {
    int seating[50][50];
    int order[50];
    int rows, cols, k;
    int i, j, d, idx, r;
    int mid, n = 0;
    int rowFree, totalFree = 0;
    int count, found = 0;
    int bookedRow = -1, startSeat = -1;

    do {
        printf("Enter number of rows (1-50): ");
        scanf("%d", &rows);
    } while (rows < 1 || rows > 50);

    do {
        printf("Enter number of seats per row (1-50): ");
        scanf("%d", &cols);
    } while (cols < 1 || cols > 50);

    mid = rows / 2;

    for (i = 0; i < rows; i++) {
        printf("Row %d - enter %d values (0 = free, 1 = booked): ", i, cols);
        for (j = 0; j < cols; j++) {
            scanf("%d", &seating[i][j]);
        }
    }

    printf("\nSeating plan:\n");
    printf("    ");
    for (j = 0; j < cols; j++) {
        printf("%-3d", j);
    }
    printf("\n");

    for (i = 0; i < rows; i++) {
        printf("R%-2d ", i);
        for (j = 0; j < cols; j++) {
            printf("%c  ", seating[i][j] == 0 ? '_' : 'X');
        }
        printf("\n");
    }

    printf("\nFree seats per row: ");
    for (i = 0; i < rows; i++) {
        rowFree = 0;
        for (j = 0; j < cols; j++) {
            if (seating[i][j] == 0) {
                rowFree++;
            }
        }
        printf("%d ", rowFree);
        totalFree += rowFree;
    }
    printf("  Total free: %d\n", totalFree);

    do {
        printf("\nEnter group size (1-%d): ", cols);
        scanf("%d", &k);
    } while (k <= 0 || k > cols);

    /* Build row search order: middle first, then by distance, smaller row first */
    for (d = 0; d < rows; d++) {
        if (mid - d >= 0) {
            order[n] = mid - d;
            n++;
        }
        if (d > 0 && mid + d < rows) {
            order[n] = mid + d;
            n++;
        }
    }

    /* Find first block of k consecutive free seats */
    for (idx = 0; idx < n && !found; idx++) {
        r = order[idx];
        count = 0;

        for (j = 0; j < cols && !found; j++) {
            if (seating[r][j] == 0) {
                count++;
            } else {
                count = 0;
            }

            if (count == k) {
                found = 1;
                bookedRow = r;
                startSeat = j - k + 1;
            }
        }
    }

    if (found) {
        for (j = startSeat; j < startSeat + k; j++) {
            seating[bookedRow][j] = 1;
        }

        printf("\nGroup of %d seated in Row %d, Seats %d to %d\n",
               k, bookedRow, startSeat, startSeat + k - 1);

        printf("\nUpdated seating plan:\n");
        printf("    ");
        for (j = 0; j < cols; j++) {
            printf("%-3d", j);
        }
        printf("\n");

        for (i = 0; i < rows; i++) {
            printf("R%-2d ", i);
            for (j = 0; j < cols; j++) {
                printf("%c  ", seating[i][j] == 0 ? '_' : 'X');
            }
            printf("\n");
        }

        printf("\nRemaining free seats: %d\n", totalFree - k);
    } else {
        printf("\nNo row has %d consecutive free seats. Seating plan unchanged.\n", k);
    }

    return 0;
}

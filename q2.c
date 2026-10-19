#include <stdio.h>

int sumDivisors(int x) {
    int sum = 0;
    int i;

    for (i = 1; i <= x / 2; i++) {
        if (x % i == 0) {
            sum = sum + i;
        }
    }

    return sum;
}

int main() {
    int n, a, b, count = 0;

    do {
        printf("Enter a positive number n: ");
        scanf("%d", &n);
    } while (n <= 0);

    printf("Amicable pairs up to %d:\n", n);

    for (a = 1; a <= n; a++) {
        b = sumDivisors(a);

        if (b > a && b <= n && sumDivisors(b) == a) {
            printf("(%d, %d)\n", a, b);
            count++;
        }
    }

    if (count > 0) {
        printf("Total pairs: %d\n", count);
    } else {
        printf("No amicable pairs found up to %d.\n", n);
    }

    return 0;
}

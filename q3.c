#include <stdio.h>

#define MAX_SENSORS 20
#define MAX_HOURS 50

void inputReadings(int readings[][MAX_HOURS], int sensors, int hours) {
    int i, j;

    for (i = 0; i < sensors; i++) {
        for (j = 0; j < hours; j++) {
            printf("Sensor %d, Hour %d: ", i + 1, j + 1);
            scanf("%d", &readings[i][j]);
        }
    }
}

float analyzeSensor(int row[], int hours, int sensorNo) {
    int i;
    int total = 0, max, min;
    int critical = 0, warning = 0;
    int streak = 0, longest = 0;
    float avg;

    max = row[0];
    min = row[0];

    for (i = 0; i < hours; i++) {
        total = total + row[i];

        if (row[i] > max) {
            max = row[i];
        }
        if (row[i] < min) {
            min = row[i];
        }

        if (row[i] >= 40) {
            critical++;
        }
        if (row[i] >= 35 && row[i] <= 39) {
            warning++;
        }

        if (row[i] >= 35) {
            streak++;
            if (streak > longest) {
                longest = streak;
            }
        } else {
            streak = 0;
        }
    }

    avg = (float) total / hours;

    printf("Sensor %d: Total=%d Avg=%.2f Max=%d Min=%d\n", sensorNo, total, avg, max, min);
    printf("          Critical=%d Warning=%d Longest hot streak=%d\n", critical, warning, longest);

    return avg;
}

int highestAverage(float averages[], int sensors) {
    int i, best = 0;

    for (i = 1; i < sensors; i++) {
        if (averages[i] > averages[best]) {
            best = i;
        }
    }

    return best;
}

int main() {
    int readings[MAX_SENSORS][MAX_HOURS];
    float averages[MAX_SENSORS];
    int sensors, hours, i, best;

    do {
        printf("Enter number of sensors (1-%d): ", MAX_SENSORS);
        scanf("%d", &sensors);
    } while (sensors < 1 || sensors > MAX_SENSORS);

    do {
        printf("Enter number of hourly readings (1-%d): ", MAX_HOURS);
        scanf("%d", &hours);
    } while (hours < 1 || hours > MAX_HOURS);

    inputReadings(readings, sensors, hours);

    printf("\n");
    for (i = 0; i < sensors; i++) {
        averages[i] = analyzeSensor(readings[i], hours, i + 1);
    }

    best = highestAverage(averages, sensors);

    printf("\nHighest average: Sensor %d (%.2f)\n", best + 1, averages[best]);

    return 0;
}

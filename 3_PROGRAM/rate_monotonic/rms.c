#include <stdio.h>

#define MAX 10

struct Task {
    int id;
    int execution;
    int period;
    int deadline;
    int remaining;
};

void RM(struct Task t[], int n, int h) {

    printf("\nRate Monotonic Scheduling\n");
    printf("\nTime\tTask\n");

    for (int i = 0; i < n; i++) {
        t[i].remaining = 0;
    }

    for (int time = 0; time < h; time++) {

        for (int i = 0; i < n; i++) {
            if (time % t[i].period == 0) {
                t[i].remaining = t[i].execution;
            }
        }

        int current = -1;

        for (int i = 0; i < n; i++) {

            if (t[i].remaining > 0 &&
               (current == -1 ||
                t[i].period < t[current].period)) {

                current = i;
            }
        }

        if (current != -1) {
            printf("%d\tT%d\n", time, t[current].id);
            t[current].remaining--;
        }
        else {
            printf("%d\tIDLE\n", time);
        }
    }
}

int main() {

    int n, h;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task t[MAX];

    for (int i = 0; i < n; i++) {

        t[i].id = i + 1;

        printf("\nTask T%d\n", t[i].id);

        printf("Execution Time: ");
        scanf("%d", &t[i].execution);

        printf("Period: ");
        scanf("%d", &t[i].period);

        printf("Deadline: ");
        scanf("%d", &t[i].deadline);
    }

    printf("\nEnter hyperperiod: ");
    scanf("%d", &h);

    RM(t, n, h);

    return 0;
}
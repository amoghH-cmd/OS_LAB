#include <stdio.h>

#define MAX 10

struct Task {
    int id;
    int execution;
    int period;
    int deadline;
    int remaining;
};

void PROPORTIONAL(struct Task t[], int n, int h) {

    printf("\nProportional Sharing Scheduling\n");
    printf("\nTime\tTask\n");

    for (int i = 0; i < n; i++) {
        t[i].remaining = 0;
    }

    int turn = 0;

    for (int time = 0; time < h; time++) {

        for (int i = 0; i < n; i++) {
            if (time % t[i].period == 0) {
                t[i].remaining = t[i].execution;
            }
        }

        int checked = 0;

        while (checked < n && t[turn].remaining == 0) {
            turn = (turn + 1) % n;
            checked++;
        }

        if (checked < n) {
            printf("%d\tT%d\n", time, t[turn].id);

            t[turn].remaining--;

            turn = (turn + 1) % n;
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

    PROPORTIONAL(t, n, h);

    return 0;
}
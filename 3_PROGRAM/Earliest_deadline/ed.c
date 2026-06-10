#include <stdio.h>

#define MAX 10

struct Task {
    int id;
    int execution;
    int period;
    int deadline;
    int remaining;
};


int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}


int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}


int calculateHyperperiod(struct Task t[], int n) {

    int h = t[0].period;

    for (int i = 1; i < n; i++) {
        h = lcm(h, t[i].period);
    }

    return h;
}


void inputTasks(struct Task t[], int n) {

    printf("\n===== Enter Task Details =====\n");

    for (int i = 0; i < n; i++) {

        t[i].id = i + 1;

        printf("\nTask T%d\n", t[i].id);

        printf("Enter Execution Time : ");
        scanf("%d", &t[i].execution);

        printf("Enter Period Time    : ");
        scanf("%d", &t[i].period);

        printf("Enter Deadline Time  : ");
        scanf("%d", &t[i].deadline);

        t[i].remaining = 0;
    }
}


void EDF(struct Task t[], int n, int h) {

    int dynamicDeadline[MAX];

    printf("\n\n========== EARLIEST DEADLINE FIRST ==========\n");

    printf("\nTime\tRunning Task\n");
    printf("---------------------------\n");

    // Initialize
    for (int i = 0; i < n; i++) {
        dynamicDeadline[i] = t[i].deadline;
        t[i].remaining = 0;
    }

    for (int time = 0; time < h; time++) {

        
        for (int i = 0; i < n; i++) {

            if (time % t[i].period == 0) {

                t[i].remaining = t[i].execution;

                
                dynamicDeadline[i] = time + t[i].deadline;
            }
        }

        int selected = -1;

        
        for (int i = 0; i < n; i++) {

            if (t[i].remaining > 0 &&
                (selected == -1 ||
                 dynamicDeadline[i] < dynamicDeadline[selected])) {

                selected = i;
            }
        }

        if (selected != -1) {

            printf("%d\tT%d\n", time, t[selected].id);

            t[selected].remaining--;
        }
        else {

            printf("%d\tIDLE\n", time);
        }
    }
}


int main() {

    int n;

    printf("Enter Number of Tasks: ");
    scanf("%d", &n);

    struct Task t[MAX];

    inputTasks(t, n);

    int h = calculateHyperperiod(t, n);

    printf("\nCalculated Hyperperiod = %d\n", h);

    EDF(t, n, h);

    return 0;
}
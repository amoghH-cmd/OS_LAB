#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

// States of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];

pthread_mutex_t mutex;
sem_t S[N];

// Function declarations
void think(int ph_num);
void eat(int ph_num);
void test(int ph_num);
void take_fork(int ph_num);
void put_fork(int ph_num);
void* philosopher(void* num);

// Left and right philosopher
int left(int ph_num) {
    return (ph_num + 4) % N;
}

int right(int ph_num) {
    return (ph_num + 1) % N;
}

// Philosopher is thinking
void think(int ph_num) {
    printf("Philosopher %d is Thinking\n", ph_num);
    sleep(1);
}

// Philosopher is eating
void eat(int ph_num) {
    printf("Philosopher %d is Eating\n", ph_num);
    sleep(2);
}

// Check if philosopher can eat
void test(int ph_num) {

    if (state[ph_num] == HUNGRY &&
        state[left(ph_num)] != EATING &&
        state[right(ph_num)] != EATING) {

        state[ph_num] = EATING;

        printf("Philosopher %d takes fork %d and %d\n",
               ph_num,
               left(ph_num),
               ph_num);

        printf("Philosopher %d starts Eating\n", ph_num);

        sem_post(&S[ph_num]);
    }
}

// Pick up forks
void take_fork(int ph_num) {

    pthread_mutex_lock(&mutex);

    state[ph_num] = HUNGRY;

    printf("Philosopher %d is Hungry\n", ph_num);

    test(ph_num);

    pthread_mutex_unlock(&mutex);

    sem_wait(&S[ph_num]);

    sleep(1);
}

// Put down forks
void put_fork(int ph_num) {

    pthread_mutex_lock(&mutex);

    state[ph_num] = THINKING;

    printf("Philosopher %d putting fork %d and %d down\n",
           ph_num,
           left(ph_num),
           ph_num);

    printf("Philosopher %d starts Thinking\n", ph_num);

    // Check if neighbors can now eat
    test(left(ph_num));
    test(right(ph_num));

    pthread_mutex_unlock(&mutex);
}

// Philosopher lifecycle
void* philosopher(void* num) {

    int ph_num = *(int*)num;

    while (1) {

        think(ph_num);

        take_fork(ph_num);

        eat(ph_num);

        put_fork(ph_num);
    }
}

int main() {

    int i;
    pthread_t thread_id[N];

    pthread_mutex_init(&mutex, NULL);

    // Initialize semaphores
    for (i = 0; i < N; i++) {
        sem_init(&S[i], 0, 0);
    }

    int phil_num[N];

    // Create philosopher threads
    for (i = 0; i < N; i++) {

        phil_num[i] = i;

        pthread_create(&thread_id[i],
                       NULL,
                       philosopher,
                       &phil_num[i]);

        printf("Philosopher %d is created\n", i);
    }

    // Join threads
    for (i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }

    return 0;
}

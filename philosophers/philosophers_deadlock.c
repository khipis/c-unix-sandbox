#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 

pthread_t philosopher[5];
pthread_mutex_t chopstick[5] = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
                                PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};
struct philosopher_t {
    int nr;
    int left;
    int right;
};

int threadError(char *msg, int nr);


void *philosopher_deadlock(void *p) {
    struct philosopher_t philosopher = *((struct philosopher_t *) (p));
    printf("%d pick up's left chopstick \n", philosopher.nr);
    while (1) {
        if (pthread_mutex_lock(&chopstick[philosopher.left])) {
            printf("%d pick up's left chopstick \n", philosopher.nr);
            while (1)
                if (pthread_mutex_lock(&chopstick[philosopher.right])) {
                    printf("%d pick up's right chopstick, happy bastard, EAT \n", philosopher.nr);
                    pthread_mutex_unlock(&chopstick[philosopher.left]);
                    pthread_mutex_unlock(&chopstick[philosopher.right]);
                    break;
                }
        }
    }

}

int main() {

    struct philosopher_t *p0_t, *p1_t, *p2_t, *p3_t, *p4_t;
    p0_t = malloc(sizeof(struct philosopher_t));
    p1_t = malloc(sizeof(struct philosopher_t));
    p2_t = malloc(sizeof(struct philosopher_t));
    p3_t = malloc(sizeof(struct philosopher_t));
    p4_t = malloc(sizeof(struct philosopher_t));

    (*p0_t).nr = 0;
    (*p0_t).left = 0;
    (*p0_t).right = 1;

    (*p1_t).nr = 1;
    (*p1_t).left = 1;
    (*p1_t).right = 2;

    (*p2_t).nr = 2;
    (*p2_t).left = 2;
    (*p2_t).right = 3;

    (*p3_t).nr = 3;
    (*p3_t).left = 3;
    (*p3_t).right = 4;

    (*p4_t).nr = 4;
    (*p4_t).left = 4;
    (*p4_t).right = 0;

    if (pthread_create(&philosopher[0], NULL, philosopher_deadlock, p0_t)) {
        threadError("Error while creating philosopher %d\n", p0_t->nr);
    }
    if (pthread_create(&philosopher[1], NULL, philosopher_deadlock, p1_t)) {
        threadError("Error while creating philosopher %d\n", p1_t->nr);
    }
    if (pthread_create(&philosopher[2], NULL, philosopher_deadlock, p2_t)) {
        threadError("Error while creating philosopher %d\n", p2_t->nr);
    }
    if (pthread_create(&philosopher[3], NULL, philosopher_deadlock, p3_t)) {
        threadError("Error while creating philosopher %d\n", p4_t->nr);
    }
    if (pthread_create(&philosopher[4], NULL, philosopher_deadlock, p4_t)) {
        threadError("Error while creating philosopher %d\n", p4_t->nr);
    }

    if (pthread_join(philosopher[0], NULL)) {
        threadError("Error while ending philosopher %d\n", p0_t->nr);
    }
    if (pthread_join(philosopher[1], NULL)) {
        threadError("Error while ending philosopher %d\n", p1_t->nr);
    }
    if (pthread_join(philosopher[2], NULL)) {
        threadError("Error while ending philosopher %d\n", p2_t->nr);
    }
    if (pthread_join(philosopher[3], NULL)) {
        threadError("Error while ending philosopher %d\n", p3_t->nr);
    }
    if (pthread_join(philosopher[4], NULL)) {
        threadError("Error while ending philosopher %d\n", p4_t->nr);
    }

    return 0;
}

int threadError(char *msg, int nr) {
    printf(msg, nr);
    exit(1);
}




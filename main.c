#include "LinkedList.h"
#include <stdio.h>
#include <pthread.h>

#define ADD         1
#define DELETE      2
#define PRINT       3
#define SORT        4
#define NUM_THREADS 3

struct my_barrier_t {
    pthread_mutex_t lock;
    pthread_cond_t  cond;
    int nr_still_to_come;
};

struct my_argumemts_t {
    unsigned int  *instructions;
    int           *values;
    unsigned int  thd_id;
};
 
struct my_barrier_t bar;

void my_barrier_init(struct my_barrier_t *bar, int nr_still_to_come) {
    pthread_mutex_init(&bar->lock, NULL);
    pthread_cond_init(&bar->cond, NULL);
    bar->nr_still_to_come = nr_still_to_come;
}
 
void my_barrier_destroy(struct my_barrier_t *bar) {
    pthread_cond_destroy(&bar->cond);
    pthread_mutex_destroy(&bar->lock);  
}

void *thread_routine(void *arg) {
    int thd_id = ((my_argumemts_t) arg).thd_id;
 
    pthread_mutex_lock(&bar.lock);

    int is_last_to_arrive = (bar.nr_still_to_come == 1);
    bar.nr_still_to_come --;
 
    while (bar.nr_still_to_come != 0)
        pthread_cond_wait(&bar.cond, &bar.lock); 
 
    if (is_last_to_arrive) {
        pthread_cond_broadcast(&bar.cond);
    }

    pthread_mutex_unlock(&bar.lock);
 
    return NULL;
}

int main() {
  Node *head = NULL;
  int i;
  pthread_t tids[NUM_THREADS];
  struct my_argumemts_t arguments[3];

  arguments[0].instructions = {1, 1, 2, 4, 2, 2};
  arguments[1].instructions = {1, 2, 1, 3};
  arguments[2].instructions = {1, 1, 1, 4, 3, 2};

  arguments[0].values = {2, 4,, 10, 2, 10, 5};
  arguments[1].values = {1, 11, 8};
  arguments[2].values = {30, 25, 100, 100};

  my_barrier_init(&bar, NUM_THREADS);

  for (i = 0; i < NUM_THREADS; i++) {
    arguments[i].thd_id = i;
    pthread_create(&tids[i], NULL, thread_routine, (void *) arguments + i);  
  }

  for (i = 0; i < NUM_THREADS; i++)
    pthread_join(tids[i], NULL);
  
  my_barrier_destroy(&bar);

  return 0;
}

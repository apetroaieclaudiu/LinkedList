#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

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
Node *head = NULL;
pthread_mutex_t lockList;

void my_barrier_init(struct my_barrier_t *bar, int nr_still_to_come) {
    pthread_mutex_init(&bar->lock, NULL);
    pthread_cond_init(&bar->cond, NULL);
    pthread_mutex_init(&lockList, NULL);
    bar->nr_still_to_come = nr_still_to_come;
}
 
void my_barrier_destroy(struct my_barrier_t *bar) {
    pthread_cond_destroy(&bar->cond);
    pthread_mutex_destroy(&bar->lock);  
}

void execute_instruction(struct my_argumemts_t *argument) {
    int i,j;
    j = 0;
    for (i = 0; (argument->instructions[i]) != 0; i++) {
        pthread_mutex_lock(&lockList);
        switch (argument->instructions[i]) {
            case ADD:
                printf("Thread with id: %d is adding the value: %d\n", argument->thd_id, argument->values[j]);
                add_node(&head, argument->values[j]);
                j++;
                break;
            case DELETE:
                printf("Thread with id: %d is deleting the node with value: %d\n", argument->thd_id, argument->values[j]);
                delete_node(&head, argument->values[j]);
                j++;
                break;
            case SORT:
                printf("Thread with id: %d is sorting the list\n", argument->thd_id);
                sort_list(&head);
                break;
            case PRINT:
                printf("Thread with id: %d is printing the list\n", argument->thd_id);
                print_list(&head);
                break;
            default:
                printf("Thread with id: %d dont know what he is doing\n", argument->thd_id);
                break;
        }
        pthread_mutex_unlock(&lockList);
    }
}

void *thread_routine(void *arg) {
    struct my_argumemts_t *argument = (struct my_argumemts_t*) arg;
    pthread_mutex_lock(&bar.lock);

    int is_last_to_arrive = (bar.nr_still_to_come == 1);
    bar.nr_still_to_come --;
 
    while (bar.nr_still_to_come != 0)
        pthread_cond_wait(&bar.cond, &bar.lock); 
 
    if (is_last_to_arrive) {
        pthread_cond_broadcast(&bar.cond);
    }

    execute_instruction(argument);

    pthread_mutex_unlock(&bar.lock);
 
    return NULL;
}

int main() {
    int i;
    pthread_t tids[NUM_THREADS];
    struct my_argumemts_t arguments[3];

    arguments[0].instructions = (unsigned int*) calloc(8, sizeof(unsigned int));
    memcpy(arguments[0].instructions, (unsigned int[7]){ADD, ADD, ADD, DELETE, SORT, DELETE, DELETE}, 7 * sizeof(unsigned int));
    arguments[1].instructions = (unsigned int*) calloc(6, sizeof(unsigned int));
    memcpy(arguments[1].instructions, (unsigned int[5]){ADD, ADD, DELETE, ADD, PRINT}, 5 * sizeof(unsigned int));
    arguments[2].instructions = (unsigned int*) calloc(7, sizeof(unsigned int));
    memcpy(arguments[2].instructions, (unsigned int[6]){ADD, ADD, ADD, SORT, PRINT, DELETE}, 6 * sizeof(unsigned int));

    arguments[0].values = (int*) malloc(sizeof (int) * 6);
    memcpy(arguments[0].values, (unsigned int[6]){2, 4, 10, 2, 10, 5}, 6 * sizeof(int));
    arguments[1].values = (int*) malloc(sizeof (int) * 4);
    memcpy(arguments[1].values, (int[4]){11, 1, 11, 8}, 4 * sizeof(int));
    arguments[2].values = (int*) malloc(sizeof (int) * 4);
    memcpy(arguments[2].values, (int[4]){30, 25, 100, 100}, 4 * sizeof(int));
    
    my_barrier_init(&bar, NUM_THREADS);

    for (i = 0; i < NUM_THREADS; i++) {
        arguments[i].thd_id = i;
        pthread_create(&tids[i], NULL, &thread_routine, &arguments[i]);  
    }

    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(tids[i], NULL);

    my_barrier_destroy(&bar);
    free(arguments[0].instructions);
    free(arguments[1].instructions);
    free(arguments[2].instructions);
    free(arguments[0].values);
    free(arguments[1].values);
    free(arguments[2].values);
    print_list(&head);
    flush_list(&head);

    return 0;
}

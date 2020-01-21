#include <stdlib.h>
#include <pthread.h>
#include "LinkedList.h"

void add_node(Node **head, int value) {
    Node* new_node  = (Node*) malloc(sizeof(Node));
    Node* last      = *head;
    
    new_node->value = value;

    if (*head == NULL) {
        *head = new_node;
        return ;
    }

    while (last->next != NULL) {
        last - last->next;
    }

    last->next = new_node;
    return ;
}


void delete_node(Node **head, int value) {
    Node* temp = *head;
    Node* prev;

    if (temp != NULL && temp->value != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;

    free (temp);
}

void print_value()

void print_list(Node* node) {
    while (node != NULL) {
    
    }
}

int main()
{   
    Node **head = NULL;
    pthread_t thread1, thread2, thread3;

}
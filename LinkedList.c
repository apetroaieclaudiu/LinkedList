#include <stdlib.h>
#include "LinkedList.h"

void print_node(void *data) {
  int *temp = data;
  printf("%d\n", *temp);
}

void add_node(Node **head, int value) {
    Node* new_node  = (Node*) malloc(sizeof(Node));
    Node* last      = *head;

    new_node->value = value;
    new_node->callback = &print_node;
    if (*head == NULL) {
        *head = new_node;
        return ;
    }

    while (last->next != NULL) {
        last - last->next;
    }

    last->next = new_node;
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

void print_list(Node **head) {
  Node* temp = *head;

  while (temp != NULL) {
    temp->callback(temp->value);
    temp = temp->next;
  }
}

void flush_list(Node **head) {
  struct Node* current = *head;
  struct Node* next;

  while (current != NULL)
  {
     next = current->next;
     free(current);
     current = next;
  }

  *head = NULL;
}

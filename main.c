#include "LinkedList.h"
#include <stdio.h>

int main() {
  Node *head = NULL;

  add_node(&head, 10);
  add_node(&head, 20);
  add_node(&head, 100);
  add_node(&head, 1);
  add_node(&head, 142);
  add_node(&head, 42);
  add_node(&head, 240);
  add_node(&head, 30);
  add_node(&head, 500);
  add_node(&head, 200);
  sort_list(&head);
  print_list(&head);
  flush_list(&head);
  print_list(&head);

  return 0;
}

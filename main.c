#include "LinkedList.h"
#include <stdio.h>

int main() {
  Node **head = NULL;

  add_node(head, 10);
  add_ndoe(head, 20);
  add_node(head, 100);
  print_list(head);
  return 0;
}

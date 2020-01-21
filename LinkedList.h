

typedef struct Node {
    int value;
    struct Node *next;
} Node;

//This function will add a new node at the end of the list with the value equal to "value"
void add_node(Node** head, int value);

//This function will delete the node with the specified value
void delete_node(Node** head, int value);

//A function which will print all the elements of the current list 
void print_list(Node head**);

//A functin that will sort the current list in an ascending order
void sort_list(Node head**);
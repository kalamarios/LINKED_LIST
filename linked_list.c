#include <stdio.h>
#include <stdlib.h>

//consists of the data and the next part. Data stores the integer and next is a pointer to a node that points to the next element of the linked list
struct node {
    int data;
    struct node *next;
};
typedef struct node linked_list_node;
typedef struct node *linked_list_ptr; //renamed for easier use

void insert_start(linked_list_ptr *head, int num); //insert element in the start of the list
void insert_after(linked_list_ptr ptr, int num); //insert element after an existing one in the list, with the function having the pointer to the previous element from the one we want to insert as an argument
void destroy_list(linked_list_ptr *head); //destroys list and frees memory
void print_list(linked_list_ptr head); //prints the list with its head being the argument
linked_list_ptr recursive_search(linked_list_ptr head, int num); //searches recursively to see if the number is in the list and returns a pointer to the node that the number is stored into, otherwise null

int main() {
    linked_list_ptr list; //the head of the list
    int value;

    insert_start(&list, 5 ); //insert 5 in the start of the list
    insert_start(&list, 6 );
    insert_start(&list, 7 );
    insert_after(list, 13); //insert 13 in the following position of the one that list points to (after the number 7)
    insert_after(list, 15);
    insert_after(list, 62);

    print_list(list);
    printf("\n");
    printf("Type which number to search in the list:");
    scanf("%d", &value);

    if (recursive_search(list, value) != NULL)
        printf("Number was found!\n");
    else
        printf("Number wasn't found!\n");

    destroy_list(&list);

    return 0;
}

void insert_start(linked_list_ptr *head, int num) {
    linked_list_ptr new_node = (linked_list_node *)malloc(sizeof(linked_list_node));
    if (new_node == NULL) {
        printf("Memory allocation error");
    }
    else {
        new_node -> data = num; //if the memory allocation is successful, updates the data that new_node points to
        new_node -> next = *head;
        *head = new_node; //now the head of the list points to wherever new_node was
    }

}

void insert_after(linked_list_ptr ptr, int num) {
    linked_list_ptr new_node = malloc(sizeof(linked_list_node));
    if (new_node == NULL) {
        printf("Memory allocation error");
    }
    else {
        new_node -> data = num;
        new_node -> next = ptr -> next;
        ptr -> next = new_node; //the 'next' of the previous element of the list will point to the temporary variable new_node
    }
}

void destroy_list(linked_list_ptr *head) {
    linked_list_ptr ptr;
    while (*head != NULL) {
        ptr = *head;
        *head = (*head) -> next;
        free(ptr); //frees the memory for every element of the list
    }
}

void print_list(linked_list_ptr head) {
    linked_list_ptr current;
    current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current -> next;
    }
}

linked_list_ptr recursive_search(linked_list_ptr head, int num) {
    if (head == NULL)
        return NULL;
    if (head -> data == num)
        return head;
    return recursive_search(head -> next, num); //every time the function is being called and doesn't find the number we want, it's then being called recursively, beginning the search from the following element of the list until the number is found, otherwise returns null
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node* prev; // pointer to previous node
    struct Node* next; // pointer to next node
    char* string; // data contained in node
} Node;

// method to insert method at the head or after prev node
// "Node**" because sometimes we change the head pointer itself
void insertNode (Node** list, Node* prev, const char* string) {
    Node* node = malloc(sizeof(Node)); //fixed size, use sizeof
    node->string = malloc(strlen(string) + 1); // runtime size, use strlen
    strcpy(node->string, string);

    // insert at head
    if (prev == NULL) {
        if (*list != NULL) {
            // assign the previous to the node
            (*list)->prev = node;
        }

        node->prev = NULL;
        node->next = *list;
        // the head pointer now points to the head of the list
        *list = node;
    } else {
        // assign the node after the new node with the original next node
        node->next = prev->next;
        // check if original next node was the end of list
        if (node->next != NULL) {
            // assign the original next node pointing to the newly inserted node
            node->next->prev = node;
        }
        // insert the new node after the previous
        prev->next = node;
        node->prev = prev;
    }
}

Node* search (Node* list, const char* string)  {
    while (list != NULL) {
        if (strcmp(string, list->string) == 0) {
            return list;
        }
        list = list->next;
    }
}

void delete (Node** list, Node* node) {
    // connecting the deleted node's next to the deleted node's previous node
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    // connecting the deleted node's previous to the deleted node's next node
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    //update the head if it is deleted
    if (*list == node) {
        *list = node->next;
    }

    // free memory after deletion
    free(node->string);
    free(node);
}

void printList (Node* list) {
    while (list != NULL) {
        printf("%s\n", list->string);
        list = list->next;
    }
}

int main (int argc, const char* argv[]) {
    printf("Doubly Linked List\n\n");

    Node* list = NULL;
    // pushing at the head
    insertNode(&list, NULL, "Four");
    insertNode(&list, NULL, "One");

    // pushing after a node
    insertNode(&list, search(list, "One"), "Two");
    insertNode(&list, search(list, "Two"), "Three");
    insertNode(&list, search(list, "Four"), "Five");

    printList(list);
    printf("\n");

    printf("Removing Four:\n\n");
    delete(&list, search(list, "Four"));

    printList(list);

    return 0;
}
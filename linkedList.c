
// This is a C-file that creates a simple Linked List that is sorted in ascending order.
// The list will initially contain integers 1-5.
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// This is a node structure that the list comprises of.
typedef struct Node {
    struct Node *next;
    struct Node *prev;
    int data;
} node_t;

// This is a structure that represents a Linked List.
typedef struct LinkedList {
    node_t *head;
    node_t *tail;
    int size;
} list_t;

// This is the function that creates a new list. A new list contains integers 1-5 in ascending order.
list_t *newList();

// These are the desired add/remove functions for the list.
bool removeNode(list_t *list, int x);
bool addNode(list_t *list, int x);

// This is a helper function that initializes an empty list.
list_t *initializeList();

// These are helper functions for special add/remove cases.
bool addTail(list_t *list, node_t *n);
bool addHead(list_t *list, node_t *n);
bool addInPlace(list_t *list, node_t *n);
bool addEmpty(list_t *list, node_t *n);
bool checkInRange(list_t *list, int x);
bool removeHead(list_t *list);
bool removeBasic(list_t *list, int x);
bool removeSingle(list_t *list);

// This is a helper function to check if the additions are correctly made.
void printList(list_t *list);
void printBackwards(list_t *list);

// This is a main function used to create a Linked List that contains integers 1 through 5.
int main() {
    list_t *testList = newList(); 

    // If space for the list could be allocated, the integers are added to it in sorted order.
    if (testList != NULL) {

        // These are basic print statements that help the user visually see if the list works correctly.
        // The user can add more tests here if they'd like to.
        printList(testList);
        printBackwards(testList);
        //addNode(testList, 0);
        //printList(testList);
        //printBackwards(testList);
        //removeNode(testList, 1);
        //removeNode(testList, 5);
        //removeNode(testList, 2);
        //removeNode(testList, 3);
        //removeNode(testList, 4);
        //removeNode(testList, 0);
        //removeNode(testList, 6);
        //printList(testList);
        //printBackwards(testList);
        //addNode(testList, 3);
        //addNode(testList, -1);
        //addNode(testList, 0);
        //printList(testList);
        //printBackwards(testList);
    }

    return 0;
}

// This prints the linked list. This is for debugging purposes.
void printList(list_t *list) {
    node_t *cur = list->head;
    int curVal;

    if (list != NULL && list->size > 0) {
        printf("\n");
        printf("HEAD IS %d\n", (list->head)->data);
        printf("TAIL IS %d\n", (list->tail)->data);
        printf("SIZE IS %d\n", (list->size));
        printf("\n");
    }

    printf("THIS IS THE LIST IN ORDER: ");

    // This loops through the list and prints each element.
    while (cur != NULL) {
        curVal = cur->data;
        printf(" %d -> ", curVal);
        cur = cur->next;
    }

    printf("NULL\n");
    printf("\n");
}

// This is a print method for debugging purposes. It prints a list backwards
// to correctly check the 'prev' pointers.
void printBackwards(list_t *list) {
    node_t *cur = list->tail;
    int curVal;

    if (list != NULL && list->size > 0) {
        printf("\n");
        printf("HEAD IS %d\n", (list->head)->data);
        printf("TAIL IS %d\n", (list->tail)->data);
        printf("SIZE IS %d\n", (list->size));
        printf("\n");
    }

    printf("THE LIST BACKWARDS: ");

    // This loops through the list and prints each element.
    while (cur != NULL) {
        curVal = cur->data;
        printf(" %d -> ", curVal);
        cur = cur->prev;
    }

    printf("NULL\n");
    printf("\n");
}



// This functions creates a new Linked List that contains integer 1-5.
// It returns a pointer to the new list.
list_t *newList() {
    list_t *list = initializeList();

    // If the list cannot be created, NULL is returned.
    if (list == NULL) {
        return NULL;
    }

    // Otherwise, the integers are added to the list and the list is returned.
    addNode(list, 1);
    addNode(list, 2);
    addNode(list, 3);
    addNode(list, 4);
    addNode(list, 5);
    return list;
}

// This function initializes a linked list and returns a pointer to that list.
list_t *initializeList() {
    list_t *list = malloc(sizeof(list_t));

    // If space can be allocated, the fields of the list are intitialized.
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0; 
    }

    // The pointer to the new list is returned.
    return list;
}

// This is a function that removes a node from the linked list.
bool removeNode(list_t *list, int x) {
    int SINGLE = 1;
    int headVal;
    int tailVal;

    // If the list is not NULL and the node is in the possible range, 
    // the Linked List is accessed appropriately.
    if (list != NULL && list->size > 0 && checkInRange(list, x)) {
        headVal = (list->head)->data;
        tailVal = (list->tail)->data;

        // If the list is a single element, the list is updated appropriately.
        if (list->size == SINGLE) {
            return removeSingle(list);
        }

        // If the node to be removed is equivalent to the head, the head is removed.
        if (x == headVal) {
            return removeHead(list);
        }

        // Otherwise, the first instance of the node is searched for and removed.
        return removeBasic(list, x);
    }

    // If this point is reached, a removal cannot take place.
    return false;
}

// This removes a node that is not the head of the list.
bool removeBasic(list_t *list, int x) {
    node_t *cur = list->head;
    node_t *prev = NULL;
    int oldSize = list->size;

    // This loops through the list until it finds the desired value to remove.
    while (cur != NULL && x != cur->data) {
        prev = cur;
        cur = cur->next;
    }

    // If the value has been found, a removal will take place.
    if (cur != NULL && x == cur->data) {

        // If the current node is the tail of the list, the pointer is updated appropriately.
        if (cur->next == NULL) {
            list->tail = prev;
        }

        // Otherwise, the portions of the non-NULL pointer are updated.
        else {
            (cur->next)->prev = prev;
        }

        // The removal takes place.
        prev->next = cur->next;
        cur->next = NULL;
        cur->prev = NULL;
        free(cur);
        list->size = oldSize - 1;
    }

    // Whether or not a removal took place is returned.
    return (oldSize != list->size);
}

// This removes the head of the list.
bool removeHead(list_t *list) {

    // The current head and the new head are obtained.
    int oldSize = list->size;
    node_t *n = list->head;
    node_t *newHead = n->next;

    // The pointers for the lists and nodes are altered appropriately.
    list->head = newHead;
    list->size = oldSize - 1;
    newHead->prev = NULL;
    n->next = NULL;
    n->prev = NULL;
    free(n);
    return (oldSize != list->size);
}

// This removes an element from a single list.
bool removeSingle(list_t *list) {
    int oldSize = list->size;
    node_t *n = list->head;
    n->next = NULL;
    n->prev = NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    free(n);
    return (oldSize != list->size);
}

// This checks whether or not the value is in range.
bool checkInRange(list_t *list, int x) {
    int headVal = (list->head)->data;
    int tailVal = (list->tail)->data;
    return (x >= headVal && x <= tailVal);
}

// This is a function that adds to the linked list. It assumes that the sent in list is not NULL.
// Whether or not the addition took place is returned as a boolean.
bool addNode(list_t *list, int x) {

    // A new node is created so that it can be added to the list.
    node_t *n = malloc(sizeof(node_t));
    int headVal;
    int tailVal;

    // If space cannot be allocated for the node, then FALSE is returned.
    if (n == NULL) {
        return false;
    }

    // The fields of the new node are updated.
    n->data = x;
    n->next = NULL;
    n->prev = NULL;

    // If the list is empty, a new node is added to it.
    if (list->size == 0) {
        return addEmpty(list, n);
    }

    // The values of the head and tail of the list are obtained.
    headVal = (list->head)->data;
    tailVal = (list->tail)->data;

    // If the node is smaller than the head of the list, it is the new head.
    if (x <= headVal) {
        return addHead(list, n);
    }

    // If the node is larger than the tail of the list, it is the new tail.
    if (x >= tailVal) {
        return addTail(list, n);
    }

    // Otherwise, the node is added to the appropriate place in the list.
    return addInPlace(list, n);
}

// This is a special case where a node is added to an empty list.
bool addEmpty(list_t *list, node_t *n) {
    int oldSize = list->size;
    list->head = n;
    list->tail = n;
    list->size = 1;
    return (oldSize != list->size);
}

// This adds a new head to the list.
bool addHead(list_t *list, node_t *n) {

    // The old head is obtained, and then the new node is added.
    node_t *oldHead = list->head;
    int oldSize = list->size;
    list->head = n;
    n->next = oldHead;
    n->prev = NULL;
    oldHead->prev = n;
    list->size = oldSize + 1;
    return (oldSize != list->size);
}

// This adds a new tail to the list.
bool addTail(list_t *list, node_t *n) {

    // The old tail is obtained, and then the new tail is added.
    node_t *oldTail = list->tail;
    int oldSize = list->size;
    oldTail->next = n;
    list->tail = n;
    list->size = oldSize + 1;
    n->prev = oldTail;
    return (oldSize != list->size);
}

// This adds a node to the middle of the list in sorted order.
bool addInPlace(list_t *list, node_t *n) {
    node_t *cur = list->head;
    node_t *prev = NULL;
    int oldSize = list->size;
    int addData = n->data;

    // This iterates through the linked list until it finds a node that it is smaller than.
    while (cur != NULL && addData >= cur->data) {
        prev = cur;
        cur = cur->next;
    }

    // If the 'cur' node is not NULL, the new node is appropriately added.
    if (cur != NULL) {
        n->next = cur;
        n->prev = prev;
        prev->next = n;
        cur->prev = n;
        list->size = oldSize + 1;
    }

    return (oldSize != list->size);
}

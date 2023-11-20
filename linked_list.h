#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *previous;
} Node;

typedef struct LinkedList
{
    Node *head;
    int size;
} LinkedList;


LinkedList *createLinkedList();
void showAllItems(LinkedList);
void insertBefore(LinkedList *, Node *, int);
void insertAfter(LinkedList *, Node *, int);
void shift(LinkedList *, int);
void append(LinkedList *, int);
int isEmpty(LinkedList);
int search(LinkedList, int);
void insertAllBefore(LinkedList *, Node *, int, int, ...);
void insertAllAfter(LinkedList *, Node *, int, int, ...);
void appendAll(LinkedList *, int, ...);
void shiftAll(LinkedList *, int, ...);
int popFirst(LinkedList *);
int popLast(LinkedList *);
int pop(LinkedList *, int);
int getSize(LinkedList, Node *);
int getFirst(LinkedList);
int getLast(LinkedList);
int getItemByIndex(LinkedList, int);
void sort(LinkedList *, int);
Node *getNode(LinkedList, int);
void reverse(LinkedList *);
void update(LinkedList *, int, int);
void concatenate(LinkedList *, LinkedList);
void splitByPosition(LinkedList, int, LinkedList *, LinkedList *);
LinkedList *mergeSorted(LinkedList, LinkedList, int);
bool FloydTurtoisHareCycle(LinkedList);
Node *findIntersectionNode(LinkedList, LinkedList);
void removeDuplicates(LinkedList *);
bool isSortedAsc(LinkedList);
bool isSortedDesc(LinkedList);
Node *searchWithCriteria(LinkedList, CriteriaFunction);
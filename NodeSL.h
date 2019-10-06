#ifndef NODESL_H
#define NODESL_H

typedef struct Node
{
    unsigned long id;
    struct Node *next;

} Node;

void printList(Node **head);
void freeList(Node **head);
void push(Node **head, Node **tail, unsigned long newID);
void pop(Node **head, Node **tail, unsigned long delID);

#endif /* NODESL_H */

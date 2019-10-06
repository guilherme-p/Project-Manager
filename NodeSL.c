#include "NodeSL.h"
#include "main.h"

/**
* Imprime lista ligada do tipo Node.
* 
* @param Ponteiro para a head da lista ligada.
*/
void printList(Node **head)
{
    Node *cur = NULL;
    for (cur = *head; cur != NULL; cur = cur->next)
        printf(" %lu", cur->id);
}

/**
* Liberta lista ligada do tipo Node.
* 
* @param Ponteiro para a head da lista ligada.
*/
void freeList(Node **head)
{
    Node *temp = NULL;
    while (*head != NULL) {
        temp = *head;
        (*head) = (*head)->next;
        free(temp);
    }
}

/**
* Acrescenta elemento a uma lista ligada do tipo Node.
* 
* @param Ponteiro para a head da lista ligada.
* @param Ponteiro para a tail da lista ligada.
* @param ID a acrescentar.
*/
void push(Node **head, Node **tail, unsigned long newID)
{
    Node *new = (Node *) malloc(sizeof(Node));
    new->id = newID;
    new->next = NULL;

    if ( (*head) == NULL && (*tail) == NULL ) {
        (*head) = new;
        (*tail) = new;
        return;
    }

    (*tail)->next = new;
    (*tail) = new;

}

/**
* Remove elemento de uma lista ligada do tipo Node.
* 
* @param Ponteiro para a head da lista ligada.
* @param Ponteiro para a tail da lista ligada.
* @param ID a remover.
*/
void pop(Node **head, Node **tail, unsigned long delID)
{
    Node *cur = *head, *prev = NULL;
    
    if ( (*head) == NULL && (*tail) == NULL)
        return;
    
    if ( (*head)->id == delID && (*tail)->id == delID) {
        (*head) = NULL;
        (*tail) = NULL;
        free(cur);
        return;
    }

    if ( (*head)->id == delID ) {
        (*head) = cur->next;
        free(cur);
        return;
    }
    
    for (; cur != NULL && cur->id != delID; cur = cur->next)
        prev = cur;
    
    if (cur == NULL)
        return;

    if (cur == (*tail))
        (*tail) = prev;
    
    prev->next = cur->next;
    free(cur);

}
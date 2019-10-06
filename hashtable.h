#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "NodeSL.h"

typedef struct HTarefa
{
    unsigned long id;
    char *descricao;
    unsigned long duration;
    unsigned long earlyStart;
    unsigned long lateStart;
    
    struct HTarefa *prev;           /* Para remover em O(1) e */
    struct HTarefa *next;           /* ter uma lista duplamente ligada */
    
    struct Node *dependenciasHead;  /* Lista ligada de dependencias */
    struct Node *dependenciasTail;  /* Tail para insercao ser O(1) */
    
    struct Node *dependentesHead;   /* Lista ligada de dependentes */
    struct Node *dependentesTail;   /* Tail para insercao ser O(1) */

} HTarefa;

typedef struct HNode
{
    struct HTarefa HTask;
    struct HNode *next;

} HNode;

void init(int m);
void freeTable();
HTarefa *HTSearch(unsigned long id);
HTarefa *HNSearch(HNode *head, unsigned long id);
void HTInsert(HTarefa h);
void HTDelete(unsigned long id);
void HNInsert(HNode **head, HTarefa h);
void HNRemove(HNode **head, unsigned long delID);
void addDependencia(unsigned long id, unsigned long depID);
void removeDependencia(unsigned long id, unsigned long delID);

#endif /* HASHTABLE_H */
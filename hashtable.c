#include "main.h"
#include "hashtable.h"
#define hash(A, B) (A % B)

static int M;
static HNode **heads;

/**
* Inicializa a hash table.
*
* @param Numero que queremos usar para a funcao de hash.
*/
void init(int m)
{
    int i;
    M = m;
    heads = (HNode **) malloc(M * sizeof(HNode));
    for (i = 0; i < M; i++) heads[i] = NULL;
}

/**
* Liberta uma linha da hash table ao libertar a 
* lista ligada de HNodes (encadeamento externo).
*
* @param Ponteiro para a head da lista ligada de HNodes
* para a (head) podermos modificar.
*/
void freeHNodes(HNode **head)
{
    HNode *temp = NULL;
    while (*head != NULL) {
        temp = *head;
        (*head) = (*head)->next;
        free((temp->HTask).descricao);
        freeList( &((temp->HTask).dependenciasHead) );
        freeList( &((temp->HTask).dependentesHead) );
        free(temp);
    }
}

/**
* Liberta a hash table toda.
*/
void freeTable()
{
    int i;

    for (i = 0; i < M; i++) {
        if (heads[i] != NULL)
            freeHNodes(&(heads[i]));
        
        free(heads[i]);
    }

    free(heads);
}

/**
* Procura uma tarefa dentro da hash table.
* Calcula a hash do ID e chama a funcao HNSearch.
*
* @param ID da tarefa a procurar.
*
* @return Ponteiro para a tarefa cujo ID e o desejado.
*/
HTarefa *HTSearch(unsigned long id)
{
    int i = hash(id, M);
    return HNSearch(heads[i], id);
}

/**
* Procura uma tarefa dentro de uma lista ligada de HNodes.
*
* @param Head da lista ligada de HNodes.
*
* @return Ponteiro para a tarefa cujo ID e o desejado.
*/
HTarefa *HNSearch(HNode *head, unsigned long id)
{
    HNode *cur = NULL;
    for (cur = head; cur != NULL; cur = cur->next)
        if ( (cur->HTask).id == id)
            return &(cur->HTask);
    return NULL;
}

/**
* Insere uma tarefa na hash table.
* Calcula a hash do ID da Tarefa e chama a funcao HNInsert.
*
* @param Tarefa a inserir.
*/
void HTInsert(HTarefa h)
{
    int i = hash(h.id, M);
    HNInsert(&heads[i], h);
}

/**
* Insere uma tarefa numa lista ligada de HNodes.
*
* @param Ponteiro para a head de uma lista ligada de HNodes para a (head) podermos modificar.
* @param Tarefa a inserir.
*/
void HNInsert(HNode **head, HTarefa h)
{
    HNode *cur = *head;
    HNode *new = (HNode *) malloc(sizeof(HNode));
    new->HTask = h;
    new->next = NULL;

    if ((*head) == NULL) {
        (*head) = new;
        return;
    }

    while (cur->next != NULL)                               /* Encontrar o ponto de insercao */
        cur = cur->next;
    
    cur->next = new;
}

/**
* Remove uma tarefa da hash table.
* Calcula a hash do ID da Tarefa e chama a funcao HNRemove.
*
* @param ID da tarefa a remover.
*/
void HTDelete(unsigned long id)
{
    int i = hash(id, M);
    HNRemove(&heads[i], id);
}

/**
* Remove uma tarefa de uma lista ligada de HNodes.
*
* @param Ponteiro para a head de uma lista ligada de HNodes para a (head) podermos modificar.
* @param Tarefa a inserir.
*/
void HNRemove(HNode **head, unsigned long delID)
{
    HNode *cur = (*head), *prev = NULL;
    if ( cur != NULL && ((*head)->HTask).id == delID ) {
        (*head) = cur->next;                                        /* Ajustar head caso aponte para a tarefa a apagar */
        free((cur->HTask).descricao);                               /* Libertar descricao */
        freeList(&(cur->HTask.dependenciasHead));                   /* Libertar lista de dependencias */
        freeList(&(cur->HTask.dependentesHead));                    /* Libertar lista de dependentes */
        free(cur);                                                  /* Libertar o no em si */
        return;
    }
    
    while (cur != NULL && (cur->HTask).id != delID) {               /* Encontrar a tarefa */
        prev = cur;
        cur = cur->next;
    }
        
    if (cur == NULL) return;                                        /* Nao foi encontrada */
    
    prev->next = cur->next;                                         /* Ajustar next da posicao anterior */
    free((cur->HTask).descricao);
    freeList(&(cur->HTask.dependenciasHead));
    freeList(&(cur->HTask.dependentesHead));
    free(cur);

}

/**
* Adiciona depID a lista de dependentes de id.
*
* @param ID da tarefa que depID depende.
* @param ID da tarefa que depende de id.
*/
void addDependencia(unsigned long id, unsigned long depID)
{
    HTarefa *alvo = HTSearch(id);
    Node **head = &(alvo->dependentesHead), **tail = &(alvo->dependentesTail);

    push(head, tail, depID);

}

/**
* Remove depID da lista de dependentes de id.
*
* @param ID da tarefa que depID depende.
* @param ID da tarefa que depende de id.
*/
void removeDependencia(unsigned long id, unsigned long delID)
{
    HTarefa *alvo = HTSearch(id);
    Node **head = &(alvo->dependentesHead), **tail = &(alvo->dependentesTail);

    pop(head, tail, delID);

}


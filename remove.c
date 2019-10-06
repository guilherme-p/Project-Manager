#include "main.h"
#include "remove.h"
#include "hashtable.h"

/**
* Valida o input e remove elemento da hash table e da lista duplamente ligada de
* tarefas ao chamar a funcao HPop.
* 
* @param Input do utilizador.
* @param Ponteiro para a head da lista duplamente ligada de tarefas.
* @param Ponteiro para a tail da lista duplamente ligada de tarefas.
* @param Ponteiro para caminhoCalculado, para o depois atualizar caso o input seja valido.
*/
void removeT(char input[], HTarefa **head, HTarefa **tail, int *caminhoCalculado)
{
    unsigned long removeID;
    HTarefa *alvo = NULL;

    if (sscanf(input, "%*s %lu", &removeID) != 1 || removeID < 1) {         /* Se houver algum problema com a atribuicao do sscanf */
        illegal();                                                          /* ou o valor for menor que 1, o argumento e ilegal */
        return;
    }
    
    alvo = HTSearch(removeID);
    
    if (alvo == NULL) {
        printf("no such task\n");
        return;
    }

    if (alvo->dependentesHead != NULL) {
        printf("task with dependencies\n");
        return;
    }

    HPop(head, tail, alvo);
    *caminhoCalculado = 0;

}

/**
* Apaga a tarefa especificado da hash table e
* ajusta head e tail da lista ligada de tarefas.
*
* Ajusta tambem o next da tarefa anterior, e o prev
* do elemento a seguir.
*
* @param Head da lista ligada de tarefas.
* @param Tail da lista ligada de tarefas.
* @param Ponteiro para a tarefa a apagar.
*/
void HPop(HTarefa **head, HTarefa **tail, HTarefa *delAlvo)
{
    if ( (*head) == delAlvo && (*tail) == delAlvo ) {
        (*head) = NULL;
        (*tail) = NULL;
        HTDelete(delAlvo->id);
        return;
    }

    if ( (*head) == delAlvo ) {
        (*head) = delAlvo->next;
        delAlvo->next->prev = NULL;
        removeDependencias(delAlvo);
        HTDelete(delAlvo->id);
        return;
    }

    if ( (*tail) == delAlvo ) {
        (*tail) = delAlvo->prev;
        delAlvo->prev->next = NULL;
        removeDependencias(delAlvo);   
        HTDelete(delAlvo->id);
        return;
    }


    delAlvo->next->prev = delAlvo->prev;
    delAlvo->prev->next = delAlvo->next;
    removeDependencias(delAlvo);        
    HTDelete(delAlvo->id);

}

/**
* Elimina o elemento especificado da lista de dependentes
* das suas dependencias.
* 
* @param Ponteiro para a tarefa que queremos remover.
*/
void removeDependencias(HTarefa *delAlvo)
{
    Node *cur = NULL;
    for (cur = delAlvo->dependenciasHead; cur != NULL; cur = cur->next)
        removeDependencia(cur->id, delAlvo->id);

}
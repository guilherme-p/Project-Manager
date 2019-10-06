#include "main.h"
#include "NodeSL.h"
#include "hashtable.h"
#include "depend.h"
#include "path.h"

/**
* Valida o input e verifica a lista de dependentes do ID providenciado.
* 
* @param Input do utilizador.
* @param Ponteiro para a head da lista duplamente ligada de tarefas.
*/
void depend(char input[], HTarefa **head)
{
    unsigned long dependID;
    Node *cur = NULL;
    HTarefa *alvo = NULL;

    if (sscanf(input, "%*s %lu", &dependID) != 1 || dependID < 1) {             /* Se houver algum problema com a atribuicao do sscanf */
        illegal();                                                              /* ou o valor for menor que 1, o argumento e ilegal */
        return;
    }

    alvo = HTSearch(dependID);
    
    if (alvo == NULL) {
        printf("no such task\n");
        return;
    }
    
    printf("%lu:", dependID);


    if (eFinal(alvo)) {
        printf(" no dependencies\n");
        return;
    }

    for (cur = alvo->dependentesHead; cur != NULL; cur = cur->next)
        printf(" %lu", cur->id);

    printf("\n");
}

#include "main.h"
#include "hashtable.h"
#include "NodeSL.h"
#include "duration.h"
#include "path.h"

/**
* Valida o input e imprime as tarefas do projeto de acordo.
* com a maneira especificada.
*
* @param Input do utilizador.
* @param Indice de input a partir da qual devemos comecar a ler.
* @param Valor de caminhoCalculado, para imprimirmos de acordo.
*/
void duration(char input[], int start, HTarefa **head, int caminhoCalculado)
{
    unsigned long value;

    if (input[start] == '\0') {
        if (!caminhoCalculado) {
            TPrintList(head, 0);
            return;
        }
        
        else {
            PPrintList((*head), 1, 0);
            return;
        }
    }
    
    else {
        
        if (sscanf(input, "%*s %lu", &value) != 1 || value < 1) {           /* Se houver algum problema com a atribuicao do sscanf */
            illegal();                                                      /* ou o valor for menor que 1, o argumento e ilegal */
            return;
        }

        if (!caminhoCalculado)
            TPrintList(head, value);
        else
            PPrintList((*head), 1, value);
        
    }

}

/**
* Imprime a lista ligada de tarefas de acordo com o 
* formato especificado sem o caminho critico estar calculado.
* 
* @param Head da lista ligada de tarefas.
* @param Duracao a usar para filtrar a lista (quando um valor nao
* e especificado, 0 e usado).
*/
void TPrintList(HTarefa **head, unsigned long durationThreshold)
{
    HTarefa *cur = NULL;
    for (cur = *head; cur != NULL; cur = cur->next) {
        if (cur->duration >= durationThreshold) {
            printf("%lu ", cur->id);
            printf("%s ", cur->descricao);
            printf("%lu", cur->duration);
            printList( &( cur->dependenciasHead ) );
            printf("\n");
        }
    }
    
}

/**
* Imprime a lista ligada de tarefas de acordo com o 
* formato especificado quando o caminho critico esta calculado.
* 
* @param Head da lista ligada de tarefas.
* @param Modo para imprimir.
* @param Duracao a usar para filtrar a lista (quando um valor nao
* e especificado, 0 e usado).
*
* Quando modo = 1, imprime todas as tarefas.
* Quando modo = 2, imprime todas as tarefas criticas.
*/
void PPrintList(HTarefa *head, int modo, unsigned long durationThreshold)
{
    HTarefa *cur = NULL;
    if (modo == 1) {
        for (cur = head; cur != NULL; cur = cur->next) {
            if (cur->duration >= durationThreshold) {
                printf("%lu ", cur->id);
                printf("%s ", cur->descricao);
                printf("%lu ", cur->duration);
                
                if ( earlyIgualALate(*cur) )
                    printf("[%lu CRITICAL]", cur->earlyStart);
                else
                    printf("[%lu %lu]", cur->earlyStart, cur->lateStart);
                
                printList( &( cur->dependenciasHead ) );
                printf("\n");
            }
        }
    }

    if (modo == 2) {
        for (cur = head; cur != NULL; cur = cur->next) {
            if (earlyIgualALate(*cur)) {
                printf("%lu ", cur->id);
                printf("%s ", cur->descricao);
                printf("%lu ", cur->duration);
                printf("[%lu CRITICAL]", cur->earlyStart);
                printList( &( cur->dependenciasHead ) );
                printf("\n");
            }
        }
    }
}
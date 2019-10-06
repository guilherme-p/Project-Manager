#include "main.h"
#include "path.h"
#include "hashtable.h"
#include "NodeSL.h"
#include "duration.h"

/**
* Calcula e imprime o caminho critico do projeto.
* 
* @param Ponteiro para a head da lista duplamente ligada de tarefas.
* @param Ponteiro para a tail da lista duplamente ligada de tarefas.
* @param Ponteiro para caminhoCalculado, para o depois atualizar.
*/
void path(HTarefa *head, HTarefa *tail, int *caminhoCalculado)
{
    unsigned long projectDur = projectDuration(head);

    if (*caminhoCalculado == 0) {
        atualizaLateStart(head);
        lateStart(projectDur, tail);
    }
        
    PPrintList(head, 2, 0);

    printf("project duration = %lu\n", projectDur);

    *caminhoCalculado = 1;
}

/**
* Calcula o early start de uma determinada tarefa.
* Isto e feito mal a tarefa e adicionada, por isso
* e garantido que ao percorrer as suas dependencias
* o early start delas ja esteja calculado.
*
* @param Tarefa cujo early start queremos calcular.
*
* @return Early start da tarefa.
*/
unsigned long earlyStart(HTarefa tarefa)
{
    Node *cur = NULL;
    HTarefa *alvo = NULL;
    unsigned long maxES = 0, curES;
    
    if (tarefa.dependenciasHead == NULL)                                    /* E Tarefa Origem */
        return 0;
    
    for (cur = tarefa.dependenciasHead; cur != NULL; cur = cur->next) {
        alvo = HTSearch(cur->id);
        curES = alvo->duration + alvo->earlyStart;
        maxES = max(maxES, curES);                                          /* "maior valor (duraçãoi + early-starti) entre todas as dependências i da tarefa." */
    }

    return maxES;

}

/**
* Calcula o early finish de uma determinada tarefa.
*
* @param Tarefa cujo early finish queremos calcular.
*
* @return Early finish da tarefa.
*/
unsigned long earlyFinish(HTarefa tarefaFinal)
{
    return tarefaFinal.duration + earlyStart(tarefaFinal);
}

/**
* Determina se uma tarefa e final.
*
* @param Ponteiro para a tarefa que queremos verificar.
*
* @return True (1) ou False (0).
*/
int eFinal(HTarefa *tarefaF)
{
    return tarefaF->dependentesHead == NULL;                                /* E final se a lista de dependentes estiver vazia */
}

/**
* Calcula a duracao do projeto.
*
* @param Head da lista ligada de tarefas que representam o projeto.
*
* @return Duracao do projeto.
*/
unsigned long projectDuration(HTarefa *head)
{
    HTarefa *cur = head;
    unsigned long maxDuration = 0;
    for (; cur != NULL; cur = cur->next)
        maxDuration = max( maxDuration, earlyFinish(*cur) );            /* "A duração do projecto é o maior valor entre os early finish das tarefas finais, onde o */
                                                                        /* early finish é a soma da duração da tarefa com o seu early start." */

    return maxDuration;
}

/**
* Calcula o late start de todas as tarefas do projeto.
* Traverso a lista duplamente ligada de tarefas do fim para
* o inicio, de maneira a comecar numa tarefa final e construir
* a solucao para a frente.
*
* @param Duracao do projeto
* @param Tail da lista duplamente ligada de tarefas.
*/
void lateStart(unsigned long projectDur, HTarefa *tail)
{
    HTarefa *cur = NULL, *alvo = NULL;
    Node *cur2 = NULL;
    unsigned long minLS;

    for (cur = tail; cur != NULL; cur = cur->prev) {
        if (eFinal(cur))
            cur->lateStart = projectDur - cur->duration;
        
        else {
            minLS = ULONG_MAX;
            for (cur2 = (cur->dependentesHead); cur2 != NULL; cur2 = cur2->next) {
                alvo = HTSearch(cur2->id);
                minLS = min(minLS, alvo->lateStart - cur->duration);
            }
            cur->lateStart = minLS;
        }

    }

}

/**
* Atualiza o late start de todas as tarefas para ULONG_MAX.
* Esta funcao e executada quando o caminho calculado esta invalido.
*
* @param Head da lista ligada de tarefas que representam o projeto.
*/
void atualizaLateStart(HTarefa *head)
{
    HTarefa *cur = head;
    for (; cur != NULL; cur = cur->next) 
        cur->lateStart = ULONG_MAX;

}

/**
* Determina se uma tarefa e do caminho critico do projeto.
*
* @param Ponteiro para a tarefa que queremos verificar.
*
* @return True (1) ou False (0).
*/
int earlyIgualALate(HTarefa task)
{
    return task.earlyStart == task.lateStart;
}
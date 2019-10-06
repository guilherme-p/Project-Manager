#ifndef PATH_H
#define PATH_H

#include "hashtable.h"

void path(HTarefa *head, HTarefa *tail, int *caminhoCalculado);
unsigned long earlyStart(HTarefa tarefa);
unsigned long earlyFinish(HTarefa tarefaFinal);
int eFinal(HTarefa *tarefaF);
unsigned long projectDuration(HTarefa *head);
void lateStart(unsigned long projectDur, HTarefa *tail);
void atualizaLateStart(HTarefa *head);
int earlyIgualALate(HTarefa task);

#endif /* PATH_H */
#ifndef REMOVE_H
#define REMOVE_H

#include "hashtable.h"

void removeT(char input[], HTarefa **head, HTarefa **tail, int *caminhoCalculado);
void HPop(HTarefa **head, HTarefa **tail, HTarefa *delAlvo);
void removeDependencias(HTarefa *delAlvo);

#endif /* REMOVE_H */
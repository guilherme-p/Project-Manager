#ifndef DURATION_H
#define DURATION_H

#include "hashtable.h"
void duration(char input[], int start, HTarefa **head, int caminhoCalculado);
void TPrintList(HTarefa **head, unsigned long durationThreshold);
void PPrintList(HTarefa *head, int modo, unsigned long durationThreshold);

#endif /* DURATION_H */

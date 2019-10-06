#ifndef ADD_H
#define ADD_H

#include "hashtable.h"
#include "NodeSL.h"

void add(char input[], int start, HTarefa **thead, HTarefa **ttail, int *caminhoCalculado);
int validaAdd(char input[], int start, HTarefa **head, HTarefa **tail);
void HPush(HTarefa **head, HTarefa **tail, HTarefa novaTarefa);
int eInteiro(char str[]);
int eDescricao(char str[]);
int leInteiro(char input[], unsigned long i, char ctemp[]);
int leDescricao(char input[], unsigned long i, char ctemp[]);
void adicionaDependencias(unsigned long nID, Node *nhead);

#endif /* ADD_H */

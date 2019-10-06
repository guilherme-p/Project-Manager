#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_DESCRICAO 8001
#define MAX_COMANDO 9
#define HASH_TABLE_SIZE 211     /* primo */

#define eq(A, B) (!strcmp(A, B))
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

int main();
void illegal();

#endif /* MAIN_H */
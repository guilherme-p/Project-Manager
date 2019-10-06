#include "NodeSL.h"
#include "hashtable.h"
#include "readStdin.h"

#include "main.h"
#include "add.h"
#include "duration.h"
#include "depend.h"
#include "remove.h"
#include "path.h"


int main()
{
    int caminhoCalculado = 0;                           /* Caminho critico ainda nao calculado */
    char *input, comando[MAX_COMANDO];
    HTarefa *head = NULL; HTarefa *tail = NULL;         /* Head e tail da lista duplamente ligada de tarefas, guardadas numa hash table */

    init(HASH_TABLE_SIZE);                              /* Inicializar hash table */

    input = readStdin();
    sscanf(input, "%s", comando);
    
    while( !eq(input, "exit") ) {
        if (input[0] == ' ')
            illegal();
        else if (eq(comando, "add"))
            add(input, strlen(comando) + 1, &head, &tail, &caminhoCalculado);
        else if (eq(comando, "duration"))
            duration(input, strlen(comando), &head, caminhoCalculado);
        else if (eq(comando, "depend"))
            depend(input, &head);
        else if (eq(comando, "remove"))
            removeT(input, &head, &tail, &caminhoCalculado);
        else if (eq(comando, "path")) 
            path(head, tail, &caminhoCalculado);
        else
            illegal();
        

        free(input);                                   /* Libertar input anterior */
        input = readStdin();
        sscanf(input, "%s", comando);
    }

    freeTable();                                       /* Libertar hash table */
    free(input);                                       /* Libertar input final */
    
    return 0;
}

void illegal()
{
    printf("illegal arguments\n");
}
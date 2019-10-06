#include "add.h"
#include "hashtable.h"
#include "NodeSL.h"
#include "main.h"
#include "path.h"

/**
* Valida o input e acrescenta elemento a hash table e a lista duplamente ligada
* de tarefas ao chamar a funcao valida_add (que o faz ao chamar a funcao HPush).
* 
* @param Input do utilizador.
* @param Primeira posicao no input que nao inclui o comando 'add'.
* @param Ponteiro para a head da lista duplamente ligada de tarefas.
* @param Ponteiro para a tail da lista duplamente ligada de tarefas.
* @param Ponteiro para caminhoCalculado, para o depois atualizar caso o input seja valido.
*/
void add(char input[], int start, HTarefa **thead, HTarefa **ttail, int *caminhoCalculado)
{  
    int ret = validaAdd(input, start, thead, ttail);
    if (ret == 0)
        illegal();
    else if (ret == 2)
        printf("no such task\n");
    else if (ret == 3)
        printf("id already exists\n");
    else
        *caminhoCalculado = 0;
    
}

/**
* Valida o input e acrescenta elemento a hash table e a lista ligada do tipo HTarefa.
* O input e validado ao ler e validar cada expressao no input separado por um espaco. 
*
* @param Input do utilizador.
* @param Primeira posicao no input que nao inclui o comando 'add'.
* @param Ponteiro para a head da lista ligada do tipo HTarefa.
* @param Ponteiro para a tail da lista ligada do tipo HTarefa.
* 
* @return Status da validacao. 1 = Successo, 2 = no such task, 3 = id already exists.
*/
int validaAdd(char input[], int start, HTarefa **head, HTarefa **tail)
{
    unsigned long nID, duration, tID = 0, i = start;
    char *descricao, ctemp[MAX_DESCRICAO], *ptr;
    Node *nhead = NULL, *ntail = NULL;
    HTarefa novaTarefa;


    i = leInteiro(input, i, ctemp);
    i++; /* espaco entre comandos */


    if (eInteiro(ctemp)) {
        nID = strtol(ctemp, &ptr, 10);  /* Converter representacao em string de inteiro para inteiro */
        if (nID < 1)
            return 0;
        if ( HTSearch(nID) != NULL )
            return 3;                   /* id already exists */
    }
    
    else
        return 0;


    i = leDescricao(input, i, ctemp);
    i++; /* espaco entre comandos */

    if (eDescricao(ctemp)) {
        descricao = (char *) malloc(sizeof(char) * (strlen(ctemp) + 1));
        strcpy(descricao, ctemp);
    }

    else
        return 0;

    i = leInteiro(input, i, ctemp);

    if (eInteiro(ctemp)) {
        duration = strtol(ctemp, &ptr, 10);
        if (duration < 1) {
            free(descricao);                    /* Se houver um erro, precisamos de dar free a duration que alocamos */
            return 0;
        }
    }
    
    else {
        free(descricao);
        return 0;
    }
    
    while (input[i] != '\0') {
        
        i++; /* espaco entre comandos */
        i = leInteiro(input, i, ctemp);

        if (eInteiro(ctemp)) {
            tID = strtol(ctemp, &ptr, 10);
            if (tID < 1) {
                free(descricao);
                freeList(&nhead);               
                return 0;
            }
            
            if ( HTSearch(tID) != NULL )
                push(&nhead, &ntail, tID);      /* Acrescento as dependencias a uma lista ligada local, a qual depois
                                                dou free se houver um erro, ou associo a novaTarefa */
            
            else {
                freeList(&nhead);               /* Se houver um erro, precisamos de dar free a lista ligada que criamos */
                free(descricao);
                return 2;                       /* no such task */
            }

        }
        
        else {
            free(descricao);
            freeList(&nhead);
            return 0;
        }
        
    }


    novaTarefa.id = nID;
    novaTarefa.descricao = descricao;
    novaTarefa.duration = duration;
    novaTarefa.dependenciasHead = nhead;
    novaTarefa.dependenciasTail = ntail;
    novaTarefa.earlyStart = earlyStart(novaTarefa);     /* Calculo o earlyStart imediatamente */
    novaTarefa.lateStart = ULONG_MAX;
    novaTarefa.prev = NULL;
    novaTarefa.next = NULL;
    novaTarefa.dependentesHead = NULL;
    novaTarefa.dependentesTail = NULL;


    HPush(head, tail, novaTarefa);          /* Insiro nova tarefa na hash table e lista ligada */
    adicionaDependencias(nID, nhead);       /* Acrescento a nova tarefa a lista de dependentes das suas dependencias */
    
    return 1;
}

/**
* Acrescenta elemento a hash table e adiciona-o a lista ligada do tipo
* HTarefa. Insiro primeiro na hash table pois a lista ligada so contem
* ponteiros para a tarefa na hash table.
*
* @param Input do utilizador.
* @param Primeira posicao no input que nao inclui o comando 'add'.
* @param Ponteiro para a head da lista ligada do tipo HTarefa.
* @param Ponteiro para a tail da lista ligada do tipo HTarefa.
* @param Ponteiro para caminhoCalculado, para o depois atualizar caso o input seja valido.
*/
void HPush(HTarefa **head, HTarefa **tail, HTarefa novaTarefa)
{
    
    HTarefa *new = NULL;

    if ( (*head) == NULL && (*tail) == NULL ) {
        HTInsert(novaTarefa);
        new = HTSearch(novaTarefa.id);
        (*head) = new;
        (*tail) = new;
        return;
    }


    novaTarefa.prev = (*tail);
    HTInsert(novaTarefa);    
    new = HTSearch(novaTarefa.id);
    (*tail)->next = new;
    (*tail) = new;
    
}

/**
* Verifica se uma cadeia de caracteres e um inteiro em formato de cadeia de caracteres.
* 
* @param Cadeia de caracteres em questao.
* 
* @return Status da verificacao (True ou False).
*/
int eInteiro(char str[])
{
    unsigned short i = -1, len = strlen(str);
    while (++i < len)
        if (!isdigit(str[i]))                       /* Verifica se todos os caracteres de str sao digitos */
            return 0;
    return 1;
}

/**
* Verifica se uma cadeia de caracteres e uma descricao.
* 
* @param Cadeia de caracteres em questao.
* 
* @return Status da verificacao (True ou False).
*/
int eDescricao(char str[])
{
    unsigned short len = strlen(str);                                           /* Associei a length de str a uma variavel para reutilizar o valor de forma eficiente */
    return (str[0] == '"' && str[len - 1] == '"' && len < MAX_DESCRICAO);       /* Verifica se e contido por aspas e se tem menos caracteres que 8000 */
}

/**
* Le um potencial inteiro do input e coloca-o numa cadeia de caracteres temporaria.
* 
* @param Input do utilizador.
* @param Indice de input a partir da qual devemos comecar a ler.
* @param Cadeia de caracteres temporaria.
*
* @return Indice de input imediatamente a seguir ao inteiro.
*/
int leInteiro(char input[], unsigned long i, char ctemp[])
{
    unsigned long offset = i;                               /* Offset necessario para colocar inteiro no inicio de ctemp */
    while (input[i] != ' ' && input[i] != '\0') {
        ctemp[i-offset] = input[i];
        i++;
    }
    ctemp[i-offset] = '\0';                                 /* Terminar a cadeia de caracteres */
    return i;
}

/**
* Le uma potencial descricao do input e coloca-o numa cadeia de caracteres temporaria.
* 
* @param Input do utilizador.
* @param Indice de input a partir da qual devemos comecar a ler.
* @param Cadeia de caracteres temporaria.
*
* @return Indice de input imediatamente a seguir ao inteiro.
*/
int leDescricao(char input[], unsigned long i, char ctemp[])
{
    unsigned long offset = i, aspas = 0;
    while (input[i] != ' ' || aspas) {
        if (input[i] == '"')
            aspas = !aspas;

        ctemp[i-offset] = input[i];
        i++;
    }
    
    ctemp[i-offset] = '\0';
    return i;
}

/**
* Acrescento uma nova tarefa a lista de dependentes das suas dependencias.
* 
* @param ID da nova tarefa.
* @param Head da lista ligada que contem as dependencias da nova tarefa.
*/
void adicionaDependencias(unsigned long nID, Node *nhead)
{
    Node *cur = nhead;
    for (; cur != NULL; cur = cur->next) 
        addDependencia(cur->id, nID);

}

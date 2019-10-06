#include "main.h"

/**
* Recolhe o input caracter a caracter, realocando sempre
* que chega ao limite. Quando chega ao fim, coloca '\0'.
* 
* 
* @return Array de caracteres
*/
char *readStdin()
{
  int cap = 4096, /* Capacidade inicial para o buffer de chars */
      len =    0; /* Comprimento atual do buffer */
  
  char *buffer = malloc(cap * sizeof (char));
  int c;

  /* Ler input caracter a caracter, parar quando chegarmos a EOF ou newline */
  while ((c = fgetc(stdin)) != '\n' && !feof(stdin))
    {
      buffer[len] = c;

      /* Quando cap == len, precisamos de aumentar */
      /* o tamanho do buffer */
       
      if (++len == cap)
        /* Duplica o tamanho do buffer */
        buffer = realloc(buffer, (cap *= 2) * sizeof (char));
    }

  /* Aparar o buffer para nao haverem bytes nao utilizados */
  buffer = realloc(buffer, (len + 1) * sizeof (char));

  /* Terminar a cadeia de caracteres */
  buffer[len] = '\0';

  return buffer;
}
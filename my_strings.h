#ifndef my_strings
#define my_strings

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*------------------------------------------------------------------------------------------------------------
   Nome()
        Descricao
        - Parametros
          tipo : descricao
        - Retorno
          tipo : descricao
*/
void copy_sized_string_input(FILE *input, void *location, int size);
/*------------------------------------------------------------------------------------------------------------
   Nome()
        Descricao
        - Parametros
          tipo : descricao
        - Retorno
          tipo : descricao
*/
char **get_string_list(FILE *stream, int *tam, int mode);

/*------------------------------------------------------------------------------------------------------------
   Nome()
        Descricao
        - Parametros
          tipo : descricao
        - Retorno
          tipo : descricao
*/
char *read_sized_string(FILE *stream, int size);

/*------------------------------------------------------------------------------------------------------------
   Nome()
        Descricao
        - Parametros
          tipo : descricao
        - Retorno
          tipo : descricao
*/
char *my_get_line_valid(FILE *stream, int *ending);

/*------------------------------------------------------------------------------------------------------------
   Nome()
        Descricao
        - Parametros
          tipo : descricao
        - Retorno
          tipo : descricao
*/
char *my_gets(FILE *stream, int str_size);

/*------------------------------------------------------------------------------------------------------------
   Nome()
        Descricao
        - Parametros
          tipo : descricao
        - Retorno
          tipo : descricao
*/
void free_string_list(char **string_list, int size);

/*------------------------------------------------------------------------------------------------------------
   Nome()
        Descricao
        - Parametros
          tipo : descricao
        - Retorno
          tipo : descricao
*/
char *my_get_line(FILE *stream);

/*------------------------------------------------------------------------------------------------------------
   Nome()
        Descricao
        - Parametros
          tipo : descricao
        - Retorno
          tipo : descricao
*/
void print_string_list(char **string_list, int size);

#endif

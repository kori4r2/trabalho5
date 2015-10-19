#ifndef my_strings
#define my_strings

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*------------------------------------------------------------------------------------------------------------
   copy_sized_string_input()
        Funcao que le uma string de tamanho pre-definido da stream de dados passada e a armazena no local apontado
	pelo ponteiro passado
        - Parametros
          FILE* : stream de dados a ser lida
	  void* : ponteiro da regiao de memoria onde a string sera escrita
	  int : tamanho da string
        - Retorno
          void
*/
void copy_sized_string_input(FILE*, void*, int);
/*------------------------------------------------------------------------------------------------------------
   get_string_list()
        Funcao que le varias strings da stream de dados passada, tendo dois modos de leitura: um modo le linhas
	de tamanho indefinidos usando a funcao my_get_line(), equanto o outro modo le qual o tamanho maximo dessas
	linhas e utiliza esse tamanho para a leitura, usando a funcao read_sized_string(). Nao importando qual
	o modo escolhido, a funcao lera, antes das strings, o numero de linhas que serao passadas
        - Parametros
          FILE* : stream de dados a ser lida
	  int* : endereco da variavel que armazenara o numero de linhas lidas
	  int : modo de execucao; 0 - tamaho limitado; 1 - tamanho ilimitado;
        - Retorno
          char** : lista de strings lidas; NULL caso erro de alocacao ou de leitura;
*/
char **get_string_list(FILE *stream, int *tam, int mode);

/*------------------------------------------------------------------------------------------------------------
   read_sized_string()
        Funcao que le uma string da stream de dados passada. As condicoes de paradas sao uma quebra de linha ou
	o fim de arquivo, mas um numero limitado de caracteres sera armazenado
        - Parametros
          FILE* : stream de dados a ser lida
	  int : tamanho maximo da string a ser lida
        - Retorno
          char* : string lida
*/
char *read_sized_string(FILE *stream, int size);

/*------------------------------------------------------------------------------------------------------------
   my_get_line_valid()
        Funcao que le uma linha da stream de dados passada, mas antes de realizar a leitura analisa a posicao
	atual na stream para ver se e possivel ser lida uma string nao vazia. A variavel pasada como parametro
	armazena a condicao de parada da funcao, e se ela for chamada em um local invalido o retorno sera NULL
        - Parametros
          FILE* : stream de dados a ser lida
	  int* : condicao de parada; -2 - EOF antes da leitura; -1 - EOF apos leitura; 0 - quebra de linha;
        - Retorno
          char* : string lida da stream de dados; NULL caso chamada em local invalido;
*/
char *my_get_line_valid(FILE *stream, int *ending);

/*------------------------------------------------------------------------------------------------------------
   my_gets()
        Funcao que le uma string do tamanho desejado da stream de dados passada, analisando o local onde foi
	chamada e retornando NULL caso seja um local invalido
        - Parametros
          FILE* : stream de dados a ser lida
	  int : tamanho da string a ser alocada(contando com '\0')
        - Retorno
          char* : string lida da stream de dados; NULL caso chamada em local invalido
*/
char *my_gets(FILE *stream, int str_size);

/*------------------------------------------------------------------------------------------------------------
   free_string_list()
        Funcao que libera a memoria alocada pela lista de string do tamanho passado
        - Parametros
          char** : lista de strings alocada em memoria
	  int : numero de strings alocadas
        - Retorno
          void
*/
void free_string_list(char **string_list, int size);

/*------------------------------------------------------------------------------------------------------------
   my_get_line()
        Funcao que le uma linha da stream de dados passada. As unicas condicoes de paradas sao quebra de linha
	e fim de arquivo. Armazenara todo caracter lido, seja ele valido ou nao e se chamada em local invalido
	retornara uma string vazia
        - Parametros
          FILE* : stream de dados a ser lida
        - Retorno
          char* : string lida da stream de dados
*/
char *my_get_line(FILE *stream);

/*------------------------------------------------------------------------------------------------------------
   print_string_list()
        Funcao que imprime na stdout todas as strings armazenada numa lista de strings
        - Parametros
          char** : lista de strings a ser impressa
	  int : numero de strings armazenadas
        - Retorno
          void
*/
void print_string_list(char **string_list, int size);

#endif

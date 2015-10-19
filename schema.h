/*
		Trabalho 4: K-Nearest Neighbors (KNN)
		Trabalho 5: Optical Character Recognition (OCR)

			Italo Tobler Silva - nUSP 8551910		18/10/2015

	OBS1: Recomendável para a leitura do codigo manter aberto uma copia dos defines e dos conteudos das structs
	para facilitar consulta
	OBS2: As funcoes referentes ao trabalho 5 encontram-se no final do codigo. As funcoes anteriores de criacao
	e leitura do schema (get_schema() e read_schema()) tiveram que ser alteradas para acomodar a possibilidade
	de ser passado 'none' no lugar do nome do arquivo. As funcoes de leitura de itens e impressao de itens tambem
	precisaram ser modificadas (terminam com _item).

*/
#ifndef _SCHEMA
#define _SCHEMA

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "my_strings.h"

// Length items é o numero maximo de digitos dos numeros lidos
#define LENGTH_ITEMS 50
// Esses sao os identificadores usados para cada tipo de dado manipulado
#define INT_T 0
#define STRING_T 1
#define DOUBLE_T 2
#define BYTE_T 3

/*
	Essas strings sao definidas para o caso do usuario desejar mudar o identificador dos tipos de dado ou do nome dos arquivos
   ou do indicador de ordenacao. A string DELIMITERS é foi criada para o uso da função strtok na leitura do .schema
*/
#define STR_TABLE "table"
#define STR_ORDER "order"
#define STR_CHAR "char"
#define STR_INT "int"
#define STR_DOUBLE "double"
#define STR_BYTE "byte"
#define DELIMITERS " []\t"

/*
	As informações do arquivo .schema são armazenadas como se fizessem parte de uma lista duplamente ligada onde cada nó contém
   as informações necessárias para serem feitas operações de comparação, impressão e análise de tamanho
*/
typedef struct schema SCHEMA;

/*------------------------------------------------------------------------------------------------------------
   create_schema()
        Funcao que cria o schema, apenas alocando a memoria necessaria
        - Parametros
          void
        - Retorno
          SCHEMA* : NULL - erro na alocacao de memoria; Caso contrario - endereco do schema criado
*/
SCHEMA *create_schema(void);

/*------------------------------------------------------------------------------------------------------------
   get_schema()
        Funcao que le o nome do arquivo .schema da stdin, abre-o para leitura e interpreta seu conteudo para
	preencher o schema. Caso seja lido o "none" no lugar do nome do arquivo, o schema passado e apagado e
	setado para NULL
        - Parametros
          SCHEMA* : schema a ser preenchido
        - Retorno
          SCHEMA* : o mesmo schema apos leitura; NULL caso erro ou caso "none" inserido na leitura;
*/
SCHEMA* get_schema(SCHEMA*);

/*------------------------------------------------------------------------------------------------------------
   dump_schema()
        Funcao que imprime as informacoes do schema salvo
        - Parametros
          SCHEMA* : schema salvo
        - Retorno
          void
*/
void dump_schema(SCHEMA*);

/*------------------------------------------------------------------------------------------------------------
   delete_schema()
        Funcao que deleta o esquema, liberando toda a memoria alocada e setando NULL
        - Parametros
          SCHEMA** : endereco do schema a ser deletado
        - Retorno
          void
*/
void delete_schema(SCHEMA**);

/*------------------------------------------------------------------------------------------------------------
   get_data()        
	Funcao que recebe as informacoes do arquivo .data da stdin com excecao do campo dist e escreve o arquivo
	de acordo com o que for passado
        - Parametros
          SCHEMA* : schema dos dados
        - Retorno
          void
*/
void get_data(SCHEMA *schema);

/*------------------------------------------------------------------------------------------------------------
   dump_data()
        Funcao que imprime as informacoes salvas no arquivo .data
        - Parametros
          SCHEMA* : schema dos dados
        - Retorno
          void
*/
void dump_data(SCHEMA*);

/*------------------------------------------------------------------------------------------------------------
   get_index()
        Funcao que analisa todos os campos do schema para ver quais precisam de um indice e cria os indices
	correspondentes com as informacoes dos campos e o offset do item dentro do .data
        - Parametros
          SCHEMA* : schema dos dados
        - Retorno
          void
*/
void get_index(SCHEMA*);

/*------------------------------------------------------------------------------------------------------------
   print_index()
        Funcao que imprime os conteudos de todos os arquivos index criados
        - Parametros
          SCHEMA* : schema dos dados
        - Retorno
          void
*/
void print_index(SCHEMA*);

/*------------------------------------------------------------------------------------------------------------
   sort_index()
        Funcao que ordena todos os arquivos index criados usando um algoritmo de insertion sort adaptado
        - Parametros
          SCHEMA* : schema dos dados
        - Retorno
          void
*/
void sort_index(SCHEMA*);

/*------------------------------------------------------------------------------------------------------------
   insert_data()
        Funcao que le todas as informacoes de um elemento da stdin e adiciona esse elemento no fim do arquivo
	.data
        - Parametros
          SCHEMA* : schema dos dados
        - Retorno
          void
*/
void insert_data(SCHEMA*);

/*------------------------------------------------------------------------------------------------------------
   search_index_data()
        Funcao que le o nome de um campo e o conteudo desse campo da stdin, e a seguir executa uma busca binaria
	dentro do arquivo index do campo correspondente e uma busca sequencial nos elementos adicionados ao .data
	que n haviam sido indexados ainda, imprimindo o resultado da busca
        - Parametros
          SCHEMA* : schema dos dados
        - Retorno
          void
*/
void search_index_data(SCHEMA*);

/*------------------------------------------------------------------------------------------------------------
   save_temporary_input()
        Funcao que le da stdin todas as informacoes de um elemento menos a classe e a distancia (os dois ultimos)
	e salva o que foi lido dentro de um arquivo .temp
        - Parametros
          SCHEMA* : schema dos dados
        - Retorno
          void
*/
void save_temporary_input(SCHEMA*);

/*------------------------------------------------------------------------------------------------------------
   update_distances()
	Essa funcao atualiza o valor de todas as distancias do .data de acordo com as informacoes do elemento
	salvo no arquivo .temp
        - Parametros
          SCHEMA* : schema dos dados
        - Retorno
          void
*/
void update_distances(SCHEMA*);

/*------------------------------------------------------------------------------------------------------------
   dump_nn()
        Funcao que analisa o index da distancia e imprime os n elementos com menor distancia
        - Parametros
          SCHEMA* : schema dos dados
	  int : numero de elementos a serem impressos
        - Retorno
          void
*/
void dump_nn(SCHEMA*, int);

/*------------------------------------------------------------------------------------------------------------
   get_class()
        Funcao que analisa o k vizinhos mais proximos do elemento salvo no arquivo .temp para obter sua classe,
	e o coloca no fim do arquivo .data com essa nova classe e distancia 0
        - Parametros
          SCHEMA* : schema dos dados
	  int : numero de elementos a serem lidos
	  int : tipo de distancia calculada
        - Retorno
          void
*/
void get_class(SCHEMA*, int, int);

void ocr_update_distances(SCHEMA*);

void ocr_save_temporary_input(SCHEMA*, unsigned char*, int, int);

unsigned char *read_image(int, int);

int print_byte(unsigned char*, int, int, char*);

int hamming_distance(unsigned char*, unsigned char*, int, int);

unsigned char **bits_to_matrix(unsigned char*, int, int);

unsigned char *matrix_to_bits(unsigned char**, int, int);

int print_matrix(unsigned char**, int, int);

int free_matrix(unsigned char ***, int);

unsigned char **erode(unsigned char**, int, int, unsigned char**, int, int);

unsigned char **dilate(unsigned char**, int, int, unsigned char**, int, int);

#endif

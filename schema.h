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
	Funcao que atualiza o valor de todas as distancias do .data de acordo com as informacoes do elemento
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

/*------------------------------------------------------------------------------------------------------------
   ocr_update_distances()
        Funcao que faz o mesmo que a funcao update_distances() mas utiliza a distancia de hamming do campo bit
	para o calculo de distancias
        - Parametros
          SCHEMA* : schema dos dados
        - Retorno
          void
*/
void ocr_update_distances(SCHEMA*);

/*------------------------------------------------------------------------------------------------------------
   ocr_save_temporary_input()
        Funcao que salva as informacoes de uma imagem passada num arquivo .temp, seguindo as ocupações de memoria
	definidas pelo schema de dados passado
        - Parametros
          SCHEMA* : schema dos dados
	  unsigned char* : vetor de unsigned char* contendo a versao convertida para bits da imagem
	  int : numero de linhas da matriz
	  int : numero de colunas da matriz
        - Retorno
          void
*/
void ocr_save_temporary_input(SCHEMA*, unsigned char*, int, int);

/*------------------------------------------------------------------------------------------------------------
   read_image()
        Funcao que le os numeros de uma matriz de unsigned char da stdin de acordo com o numero de linhas e
	colunas passadas como parametro e os armazenas nos bits de um vetor unsigned char*
        - Parametros
          int : numero de linhas da matriz
          int : numero de colunas da matriz
        - Retorno
          unsigned char* : vetor de unsigned char com os elementos da matriz armazenados nos bits
*/
unsigned char *read_image(int, int);

/*------------------------------------------------------------------------------------------------------------
   print_byte()
        Funcao que imprime a matriz salva nos bits de  um vetor unsigned char* para uma string passada
        - Parametros
          unsigned char* : vetor que armazena a matriz de imagem nos seus bits
	  int : numero de linhas da matriz
	  int : numero de colunas da matriz
	  char* : string para a qual o resultado deve ser escrito
        - Retorno
          int : 1- parametro invalido passado; 0 - sucesso; 
*/
int print_byte(unsigned char*, int, int, char*);

/*------------------------------------------------------------------------------------------------------------
   hamming_distance()
        Funcao que analisa dois vetores de unsigned char com matrizes em seus bits e calculam a distancia de
	hamming entre elas
        - Parametros
          unsigned char* : vetor 1
          unsigned char* : vetor 2
	  int : numero de linhas das matrizes
	  int : numero de colunas das matrizes
        - Retorno
          int : distancia calculada; -1, caso parametro invalido passado;
*/
int hamming_distance(unsigned char*, unsigned char*, int, int);

/*------------------------------------------------------------------------------------------------------------
   bits_to_matrix()
        Funcao que interpreta os bits de um vetor de unsigned char para obter a matriz salva neles e retorna
	essa matriz alocada em memoria
        - Parametros
          unsigned char* : vetor contendo a matriz armazenada em bits
	  int : numero de linhas da matriz
	  int : numero de colunas da matriz
        - Retorno
          unsigned char* : matriz alocada na memoria; NULL, caso parametro invalido passado ou erro de alocacao
*/
unsigned char **bits_to_matrix(unsigned char*, int, int);

/*------------------------------------------------------------------------------------------------------------
   matrix_to_bits()
        Funcao que analisa uma matriz de unsigned char e armazena seu conteudo nos bits de um vetor de unsigned
	char alocado em memoria
        - Parametros
          unsigned char** : matriz a ser convertida
	  int : numero de linhas da matriz
	  int : numero de colunas da matriz
        - Retorno
          unsigned char* : vetor contendo a matriz armazenada em bits; NULL, caso parametro invalido passado ou erro
*/
unsigned char *matrix_to_bits(unsigned char**, int, int);

/*------------------------------------------------------------------------------------------------------------
   print_matrix()
        Funcao que imprime o conteudo de uma matriz de unsigned char uma linha por vez
        - Parametros
          unsigned char** : matriz a ser impressa
	  int : numero de linhas da matriz
	  int : numero de colunas da matriz
        - Retorno
          int : 1 - parametro invalido passado; 0 - sucesso;
*/
int print_matrix(unsigned char**, int, int);

/*------------------------------------------------------------------------------------------------------------
   free_matrix()
        Funcao que verifica se uma matriz de unsigned char esta diferente de NULL, e se estiver, libera a toda
	memoria alocada e seta NULL na variavel
        - Parametros
          unsigned char*** : endereco da matriz
	  int : numero de linhas da matriz
        - Retorno
          int : 1 - parametro invalido passado; 0 - sucesso;
*/
int free_matrix(unsigned char ***, int);

/*------------------------------------------------------------------------------------------------------------
   erode()
        Funcao que recebe uma matriz armazenando a imagem, uma matriz armazenando a mascara para realizar a
	operacao de erosao e as dimensoes de ambas
        - Parametros
          unsigned char** : imagem armazenada em uma matriz
	  int : numero de linhas da matriz da imagem
	  int : numero de colunas da matriz da imagem
          unsigned char** : mascara armazenada em uma matriz
	  int : numero de linhas da matriz da mascara
	  int : numero de colunas da matriz da mascara
        - Retorno
          unsigned char** : matriz contendo o resultado da operação; NULL caso parametro invalido passado;
*/
unsigned char **erode(unsigned char**, int, int, unsigned char**, int, int);

/*------------------------------------------------------------------------------------------------------------
   dilate()
        Funcao que recebe uma matriz armazenando a imagem, uma matriz armazenando a mascara para realizar a
	operacao de dilatacao e as dimensoes de ambas
        - Parametros
          unsigned char** : imagem armazenada em uma matriz
	  int : numero de linhas da matriz da imagem
	  int : numero de colunas da matriz da imagem
          unsigned char** : mascara armazenada em uma matriz
	  int : numero de linhas da matriz da mascara
	  int : numero de colunas da matriz da mascara
        - Retorno
          unsigned char** : matriz contendo o resultado da operação; NULL caso parametro invalido passado;
*/
unsigned char **dilate(unsigned char**, int, int, unsigned char**, int, int);

#endif

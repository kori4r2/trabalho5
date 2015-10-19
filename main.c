#include <stdio.h>
#include <stdlib.h>
#include "schema.h"

// Funcao que le uma imagem, uma mascara e o nome de uma operacao da stdin e realiza a operacao desejada, imprimindo o resultado se assim se desejar
// e retornando a matriz resultante;
unsigned char **mem_op(int *repeat, int print, int *n_rows, int *n_cols){
	int ending, n_rowsA, n_colsA, n_rowsB, n_colsB;
	char *input = NULL;
	unsigned char *imageA, *imageB, **matrixA, **matrixB, **matrixC;
	
	// Le as duas imagens da stdin e as armazena em bits de um vetor unsigned char
	scanf("%d %d", &n_rowsA, &n_colsA);
	(*n_rows) = n_rowsA;
	(*n_cols) = n_colsA;
	imageA = read_image(n_rowsA, n_colsA);
	scanf("%d %d", &n_rowsB, &n_colsB);
	imageB = read_image(n_rowsB, n_colsB);

	// Converte os vetores para matrizes e os libera apos a conversao
	matrixA = bits_to_matrix(imageA, n_rowsA, n_colsA);
	free(imageA);
	matrixB = bits_to_matrix(imageB, n_rowsB, n_colsB);
	free(imageB);

	// Se for o desejado, imprime as matrizes lidas, identificando cada uma
	if(print){
		printf("im:\n");
		print_matrix(matrixA, n_rowsA, n_colsA);
		printf("el:\n");
		print_matrix(matrixB, n_rowsB, n_colsB);
	}

	// Le qual a operacao a ser feita com as duas imagens passadas
	input = my_get_line_valid(stdin, &ending);
	if(input != NULL){
		if(strcmp(input, "erode") == 0){
			// Caso seja pedida a erosao, armazena o resultado na matriz C e libera a memoria alocada pelas outras duas
			matrixC = erode(matrixA, n_rowsA, n_colsA, matrixB, n_rowsB, n_colsB);
			free_matrix(&matrixA, n_rowsA);
			free_matrix(&matrixB, n_rowsB);
		}else if(strcmp(input, "dilate") == 0){
			// Caso seja pedida dilatacao, faz o mesmo que erosao, mas chama a funcao de dilatacao ao inves de erosao
			matrixC = dilate(matrixA, n_rowsA, n_colsA, matrixB, n_rowsB, n_colsB);
			free_matrix(&matrixA, n_rowsA);
			free_matrix(&matrixB, n_rowsB);
		}else if(strcmp(input, "open") == 0){
			// Caso seja pedida a abertura, e feita a erosao e a dilatacao uma apos a outra
			matrixC = erode(matrixA, n_rowsA, n_colsA, matrixB, n_rowsB, n_colsB);
			free_matrix(&matrixA, n_rowsA);
			matrixA = dilate(matrixC, n_rowsA, n_colsA, matrixB, n_rowsB, n_colsB);
			free_matrix(&matrixC, n_rowsA);
			free_matrix(&matrixB, n_rowsB);
			// E o resultado e armazenado na matriz C
			matrixC = matrixA;
			matrixA = NULL;
		}else if(strcmp(input, "close") == 0){
			// O mesmo da abertura, apenas inverte a ordem
			matrixC = dilate(matrixA, n_rowsA, n_colsA, matrixB, n_rowsB, n_colsB);
			free_matrix(&matrixA, n_rowsA);
			matrixA = erode(matrixC, n_rowsA, n_colsA, matrixB, n_rowsB, n_colsB);
			free_matrix(&matrixC, n_rowsA);
			free_matrix(&matrixB, n_rowsB);
			matrixC = matrixA;
			matrixA = NULL;
		}else{
			fprintf(stderr, "invalid operation\n");
			(*repeat) = 0;
			return NULL;
		}

		// Libera a memoria alocada e retorna a matriz com o resultado
		free(input);
		free_matrix(&matrixA, n_rowsA);
		free_matrix(&matrixB, n_rowsB);
		return(matrixC);
	}else{
		// Caso haja erro, imprime a mensagem de erro, garante que o programa saira do loop e retorna NULL
		fprintf(stderr, "error reading operation\n");
		(*repeat) = 0;
		return NULL;
	}
}

int main(int argc, char *argv[]){

	int repeat, n, n_rowsA, n_colsA;
	char *input = NULL;
	unsigned char *imageA, *imageB, **matrix;

	// A lista schema é criada e lida da stdin
	SCHEMA *schema = create_schema();
	schema = get_schema(schema);
	// Os dados sao lidos da stdin e armazenados no arquivo .data
	if(schema != NULL) get_data(schema);

	do{
		// A cada repeticao le um comando da stdin
		repeat = 1;
		while(input == NULL){
			input = my_get_line_valid(stdin, &n);
			if(n == -2){
				fprintf(stderr, "End of file reached\n");
				input = strdup("exit");
			}
		}

		// Analisa qual o comando desejado e chama a(s) funcao(oes) responsavel(is) por realiza-lo
		if(strcmp(input, "dump_schema") == 0){
			dump_schema(schema);
		}else if(strcmp(input, "dump_data") == 0){
			dump_data(schema);
		}else if(strcmp(input, "dump_nn") == 0){
			scanf("%d", &n);
			save_temporary_input(schema);
			update_distances(schema);
			get_index(schema);
			sort_index(schema);
			dump_nn(schema, n);
		}else if(strcmp(input, "knn") == 0){
			scanf("%d", &n);
			save_temporary_input(schema);
			get_class(schema, n, 1);
		}else if(strcmp(input, "mem_dist") == 0){
			scanf("%d %d", &n_rowsA, &n_colsA);
			imageA = read_image(n_rowsA, n_colsA);
			imageB = read_image(n_rowsA, n_colsA);
			printf("dist = %d\n", hamming_distance(imageA, imageB, n_rowsA, n_colsA));

			free(imageA);
			free(imageB);
			imageA = imageB = NULL;
		}else if(strcmp(input, "mem_op") == 0){
			matrix = mem_op(&repeat, 1, &n_rowsA, &n_colsA);
			printf("out:\n");
			print_matrix(matrix, n_rowsA, n_colsA);

			free_matrix(&matrix, n_rowsA);
		}else if(strcmp(input, "ocr_dump_nn") == 0){
			matrix = mem_op(&repeat, 1, &n_rowsA, &n_colsA);
			printf("out:\n");
			print_matrix(matrix, n_rowsA, n_colsA);
			imageA = matrix_to_bits(matrix, n_rowsA, n_colsA);
			ocr_save_temporary_input(schema, imageA, n_rowsA, n_colsA);
			ocr_update_distances(schema);
			get_index(schema);
			sort_index(schema);
			scanf("%d", &n);
			dump_nn(schema, n);

			free_matrix(&matrix, n_rowsA);
			free(imageA);
		}else if(strcmp(input, "ocr_knn") == 0){
			matrix = mem_op(&repeat, 0, &n_rowsA, &n_colsA);
			imageA = matrix_to_bits(matrix, n_rowsA, n_colsA);
			ocr_save_temporary_input(schema, imageA, n_rowsA, n_colsA);

			scanf("%d", &n);
			get_class(schema, n, 2);

			free_matrix(&matrix, n_rowsA);
			free(imageA);
		}else if(strcmp(input, "exit") == 0){
			// Caso seja digitado "exit", repeat recebe 0, saindo do loop
			repeat = 0;
		}

		// A cada repeticao input eh liberado caso tenha sido alocado adequadamente
		if(input != NULL){
			free(input);
			input = NULL;
		}
	}while(repeat);

	// Libera a memoria alocada
	delete_schema(&schema);

	return 0;
}

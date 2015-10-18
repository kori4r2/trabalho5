#include <stdio.h>
#include <stdlib.h>
#include "schema.h"

int main(int argc, char *argv[]){

	int repeat, n, n_rowsA, n_colsA;// n_rowsB, n_colsB;
	char *input = NULL;
	unsigned char *imageA, *imageB;

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
				repeat = 0;
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
			get_class(schema, n);
		}else if(strcmp(input, "mem_dist") == 0){
			scanf("%d %d", &n_rowsA, &n_colsA);
			imageA = read_image(n_rowsA, n_colsA);
			imageB = read_image(n_rowsA, n_colsA);
			printf("dist = %d\n", hamming_distance(imageA, imageB, n_rowsA, n_colsA));
			free(imageA);
			free(imageB);
			imageA = imageB = NULL;
		}else if(strcmp(input, "mem_op")){
			
		}else if(strcmp(input, "ocr_dump_nn")){
			
		}else if(strcmp(input, "ocr_knn")){
			
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

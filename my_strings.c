#include "my_strings.h"

void copy_sized_string_input(FILE *stream, void *location, int size){
	int input, pos = 0;
	char *string = NULL;

	do{
		input = fgetc(stream);
	}while((char)input != '\n' && input != EOF && !isprint(input));

	while(input == '\n') input = fgetc(stream);
	if(input == EOF){   // Chamada da função em local invalido do arquivo:
		fprintf(stderr, "EOF reached\n");
		return;
	}

	do{
		if(pos < size-1){
			string = realloc(string, (pos+1)*sizeof(char));
			string[pos++] = (char)input;
			input = fgetc(stream);
		}
	}while(input != '\n' && input != EOF && input != '\0');
	string = realloc(string, (pos+1)*sizeof(char));
	string[pos++] = '\0';
	memcpy(location, string, pos);
	free(string);
}

char *read_sized_string(FILE *stream, int size){

	char *string = NULL;
        int i = 0, input;

	// Aloca a maxima memoria necessaria
	string = (char*)malloc((size+1) * sizeof(char));
	memset(string, 0, size+1);

        while(1){
		// Le um char
                input = fgetc(stream);
		// Analisa se eh um char indicado de fim de string/arquivo
                if( ((char)input != '\n') && (input != EOF)){
			// Caso nao seja e ainda esteja dentro do tamanho permitido, salva o char
			if(i < size) string[i++] = (char)input;
		// Caso encontre o fim antes de haver escrito algo, sai da repeticao
                }else if(i > 0) break;
		// Caso a funcao tenha sido chamado no fim de arquivo, retorna NULL
		else if(input == EOF && i == 0){
			free(string);
			return NULL;
		}
        }

	// Coloca o indicado de fim de string e retorna o que foi lido
        string[i] = '\0';
        return string;
}

char *my_get_line_valid(FILE *stream, int *ending){
	char *string = NULL;
	int input, size = 0;

	// Procura o primeiro caracter valido para comecar a leitura da string
	do{
		input = fgetc(stream);
	}while(!isprint(input) && (char)input != '\n' && input != EOF);

	if(input == EOF){   // Chamada da função em local invalido do arquivo:
//		if(input == '\n') (*ending) = 1;       // -linha vazia  OBS: Essa checagem precisou ser removida para evitar erros
		(*ending) = -2;             	       // -final do arquivo
		return NULL;
	}
	// Assim como a remocao da linha acima, essa repeticao evita que ocorra erro por ler uma quebra de linha, mas pode gerar outros
	// Para esse caso especifico, ela cumpre a funcao desejada
	while(input == '\n') input = fgetc(stream);

	// Le um caracter por vez alocando a memoria necessaria ate encontrar quebra de linha ou fim de arquivo
	do{
		string = (char*)realloc(string, (size+1) * sizeof(char));
		string[size++] = (char)input;
		input = fgetc(stream);
	}while(input != '\n' && input != EOF);
	// Adicao o indicado de fim de string
	string = (char*)realloc(string, (size+1) * sizeof(char));
	string[size] = '\0';

	// Registra se foi encontrada quebra de linha ou fim de arquivo
	if(input == '\n') (*ending) = 0;
	else (*ending) = -1;

	// Retorna a string lida
	return string;
}

char *my_gets(FILE *stream, int str_size){
	// Aloca a memoria de acordo com o tamanho passado
	char *string = (char*)malloc(str_size);
	memset(string, 0, str_size);
	int input, cur_size = 0;

	// Ignora todos os caracteres invalidos ate encontrar um valido ou o fim do arquivo
	do{
		input = fgetc(stream);
	}while( ((char)input == ' ' || (char)input == '\n') && input != EOF);
	// Caso atinja o fim do arquivo nessa busca, encerra o programa com mensagem de erro
	if(input == EOF){
		fprintf(stderr, "error reading string\n");
		free(string);
		return NULL;
	}

	// Le no maximo str_size caracteres da stream, parando caso encontre uma quebra de linha ou fim de arquivo
	do{
		string[cur_size++] = (char)input;
		input = fgetc(stream);
	}while((char)input != '\n' && input != EOF && cur_size < str_size-1);

	// Adicao do indicador de fim de string e retorno
	string[cur_size] = '\0';
	return string;
}

char **get_string_list(FILE *stream, int *tam, int mode){
	int size, length, i = 0, j = 0, error_count = 0;
	char **list = NULL, *string = NULL;

	// Le o tamanho maximo e o numero de strings a serem lidas
	if(scanf("%d", &size) < 1){
		size = 1;
	}

	if(mode == 0) scanf("%d", &length);
	// Aloca a memoria necessaria
	list = (char**)malloc(size * sizeof(char*));
	// Percorre o vetor char**
	fgetc(stream);
	for(i = 0; i < size; i++){
		// Le uma string
		if(mode == 0) string = read_sized_string(stdin, length);
		else if(mode == 1) string = my_get_line(stdin);
		// Caso seja lida uma string valida, armazena o endereco na lista
		if(string != NULL) list[i] = string;
		else{
			free(string);
			i--;
			error_count++;
			if(error_count > 2){
				for(j = i; j>= 0; j--){
					if(list[j] != NULL) free(list[j]);
				}
				exit(2);
			}
		}
	}

	(*tam) = size;
	return list;

}

void free_string_list(char **string_list, int size){
	int i;

	if(string_list != NULL){
		for(i = 0; i < size; i++){
			if(string_list[i] != NULL) free(string_list[i]);
		}
		free(string_list);
	}
}

char *my_get_line(FILE *stream){
	int input, size = 0;
	char *string = NULL;

	do{
		input = fgetc(stream);
		if(input != EOF){
			string = (char*)realloc(string, (size+1) * sizeof(char));
			string[size++] = (char)input;
		}
	}while(input != '\n' && input != EOF);

	if(string == NULL){
		string = (char*)malloc(sizeof(char));
		string[size++] = '\n';
	}
	if(string[size-1] == '\n') string[size-1] = '\0';
	else{
		string = (char*)realloc(string, (size+1) * sizeof(char));
		string[size] = '\0';
	}

	return string;
}

void print_string_list(char **string_list, int size){
	int i;
	for(i = 0; i < size; i++){
		printf("%s\n", string_list[i]);
	}
}

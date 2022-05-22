#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

#include "iterative_binary_tree.h"
#include "optarg.h"

#define MAX_MESSAGE_SIZE 1024
#define MAX_LETTER_SIZE  6

Arguments args;

void init_char_array(char* array, int size) {
	for (int i = i; i < size; i++) {
		array[i] = '\0';
		array++;
	}
}

char* translate_text(FILE* file) {
	char* result       = malloc(MAX_MESSAGE_SIZE);
	char* letter       = malloc(MAX_LETTER_SIZE);
	char* first_symbol = letter;

	init_char_array(result, MAX_MESSAGE_SIZE);
	init_char_array(letter, MAX_LETTER_SIZE);

	int letter_index = 0;
	int result_index = 0;
	char symbol;
	while ((symbol = fgetc(file)) != EOF) {
		printf("%c", symbol);
		if (symbol == ' ') {
			result[result_index] = morse_to_text(letter);
			result_index++;
			letter_index = 0;
			init_char_array(letter, MAX_LETTER_SIZE);
		} else {
			letter[letter_index] = symbol;
			letter_index++;
		}
	}

	result[result_index] = morse_to_text(letter);

	free(letter);
	printf("\n");
	return result;
}

int main( int argc, char** argv ) {
	arg_parser(argc, argv, &args);
	char* translation = translate_text(args.file_pointer);
	printf("TEXT: %s\n", translation);

	free(translation);
}

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

#include "bintree.h"
#include "iterative_binary_tree.h"
#include "optarg.h"

m2targs args;

char morse_to_text(char* text) {
	if (args.use_iterative, ITERATIVE)
		return iterative_morse_to_text(text);
	return recursive_morse_to_text(text);
}

char * translate_file(char * filename) {
    char * file_buf       = malloc (8* 1024);
    char * file_buf_null  = file_buf;
    char * morse_buf      = malloc(8 * 8);
    char * morse_buf_null = morse_buf;
    FILE * fp             = fopen(filename, "r");
    if (!fp) {
        printf("File Error\n");
        exit(-1);
    }

    char character;
    bool state = false;
    while ((character = fgetc(fp)) != EOF) {
        if (character == '.' || character == '-') {
           state = true;
           *morse_buf = character;
           morse_buf++;

        } else {
            if (state) {
                state = false;
                *morse_buf = '\0';
                morse_buf = morse_buf_null;
                *file_buf = morse_to_text(morse_buf);
                file_buf++;
                *file_buf = '\0';
            }
        }
    }

    if (state) {
        state = false;
        *morse_buf = '\0';
        morse_buf = morse_buf_null;
        *file_buf = morse_to_text(morse_buf);
        file_buf++;
        *file_buf = '\0';
    }

    free(morse_buf_null);
    return file_buf_null;
}

char * translate_text(char* text) {
	//TODO continue here
}

int main( int argc, char ** argv ) {
    arg_parser(argc, argv, &args);
    char * text = (args.use_file)
                ? translate_file(args.filepath)
	        : translate_text(args.text);
    printf("TEXT: %s\n", text);
}

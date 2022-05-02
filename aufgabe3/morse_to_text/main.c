#include <stdio.h>
//#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>

#include "bintree.h"

char * read_file(char * filename) {
    char * file_buf = malloc (8* 1024);
    char * file_buf_null = file_buf;
    char * morse_buf = malloc(8 * 8);
    char * morse_buf_null = morse_buf; 
    FILE * fp = fopen(filename, "r");
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
           //printf("Character: %c\n", character);
           morse_buf++;

        } else {
            if (state) {
                state = false;
                *morse_buf = '\0';
                morse_buf = morse_buf_null;
                *file_buf = morse_to_text(morse_buf);
                //printf("CHARCATER:  %c\n", *file_buf);
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
        //printf("CHARCATER:  %c\n", *file_buf);
        file_buf++;
        *file_buf = '\0';
    }
    free(morse_buf_null);
    return file_buf_null;
}


int main( int argc, char ** argv ) {
    //printf("Char: %c\n", morse_to_text("."));
    char * text = read_file("morseCode.txt");
    printf("TEXT: %s\n", text);
}

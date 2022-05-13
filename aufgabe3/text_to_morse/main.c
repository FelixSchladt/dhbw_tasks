#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#include "optarg.h"

void std_fprintf(FILE *stream, bool quiet, const char *format, ...) {
    va_list args;

    //prints to file
    va_start(args, format);
    vfprintf(stream, format, args);
    va_end(args);

    //if boolean is not set print to stdout
    if (!quiet) {
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}

void text_morse(char ** morse_arr) {
    for (int i = 0; i < 128; i++) {
        morse_arr[i] = (char*)malloc(8 * 8);
        strcpy(morse_arr[i], " ");
    }

    int i = 48;
    strcpy(morse_arr[0+i], "-----"); //0
    strcpy(morse_arr[1+i], ".----"); //1
    strcpy(morse_arr[2+i], "..---"); //2
    strcpy(morse_arr[3+i], "...--"); //3
    strcpy(morse_arr[4+i], "....-"); //4
    strcpy(morse_arr[5+i], "....."); //5
    strcpy(morse_arr[6+i], "-...."); //6
    strcpy(morse_arr[7+i], "--..."); //7
    strcpy(morse_arr[8+i], "---.."); //8
    strcpy(morse_arr[9+i], "----."); //9


    for(; i < 90; i  = i + 32) {
    strcpy(morse_arr[17+i], ".-"); //A
    strcpy(morse_arr[18+i], "-..."); //B
    strcpy(morse_arr[19+i], "-.-."); //c
    strcpy(morse_arr[20+i], "-.."); //d
    strcpy(morse_arr[21+i], "."); //e
    strcpy(morse_arr[22+i], "..-."); //f
    strcpy(morse_arr[23+i], "--."); //g
    strcpy(morse_arr[24+i], "...."); //h
    strcpy(morse_arr[25+i], ".."); //i
    strcpy(morse_arr[26+i], ".---"); //j
    strcpy(morse_arr[27+i], "-.-"); //k
    strcpy(morse_arr[28+i], ".-.."); //l
    strcpy(morse_arr[29+i], "--"); //m
    strcpy(morse_arr[30+i], "-."); //n
    strcpy(morse_arr[31+i], "---"); //o
    strcpy(morse_arr[34+i], ".-."); //r
    strcpy(morse_arr[35+i], "..."); //s
    strcpy(morse_arr[36+i], "-"); //t
    strcpy(morse_arr[37+i], "..-"); //u
    strcpy(morse_arr[38+i], "...-"); //v
    strcpy(morse_arr[39+i], ".--"); //w
    strcpy(morse_arr[40+i], "-..-"); //x
    strcpy(morse_arr[41+i], "-.--"); //y
    strcpy(morse_arr[42+i], "--.."); //z
    }

}

char * char_to_morse(char ** morse_arr,  char input) {
    return morse_arr[input];
}

void text_to_morse(char * dest, char * input) {
    char ** morse_arr = malloc(sizeof(char *) * 64);
    text_morse(morse_arr);
    char buf[8];
    char character; 
    memset(dest, '\0', sizeof(&dest));
    int counter = 0;

    while ((character = input[counter]) != '\0') {
        strcpy(buf, char_to_morse(morse_arr, character));
        sprintf(dest, "%s %s", dest, buf);
        counter++;
    }
}

void read_file(Arguments * args) {
    char * line = NULL;
    size_t len = 0;
    size_t read;

    if (args->file_pointer == NULL) { exit(EXIT_FAILURE); }
        
    while ((read = getline(&line, &len, args->file_pointer)) != -1) {
        char dest[128];
        text_to_morse(dest, line);
        std_fprintf( args->output_file, args->quiet, "%s\n", dest );
    }
    
    if (line) { free(line); }
}

int main(int argc, char ** argv) {
    Arguments args; 
    if (arg_parser(argc, argv, &args) != 0 ) { exit(-1); }
    read_file(&args);
}

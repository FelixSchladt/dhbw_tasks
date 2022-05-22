//Copyright 2022 Felix Schladt (https://github.com/FelixSchladt)

#include <stdbool.h>
#include <stdio.h>

#define LINE_LENGHT 256
#define DEFAULT_OUTPUT_PATH "out.morse"


typedef struct arguments {
    bool quiet;
    bool output_to_file;
    FILE * file_pointer;
    FILE * output_file;
} Arguments;

int arg_parser(int, char **, Arguments *);


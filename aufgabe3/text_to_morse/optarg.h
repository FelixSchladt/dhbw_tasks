#include <stdbool.h>
#include <stdio.h>

#define LINE_LENGHT 256
#define DEFAULT_OUTPUT_PATH "out.morse"


typedef struct arguments {
    //char output_path[128];
    unsigned short group_size;
    bool quiet;
    bool output_to_file;
    FILE * file_pointer;
    FILE * output_file;
} Arguments;

int arg_parser(int, char **, Arguments *);


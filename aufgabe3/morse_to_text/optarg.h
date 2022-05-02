#include <stdbool.h>

#define DEFAULT_OUTPUT_PATH "morse_output.txt"
#define DEFAULT_GROUP_SIZE 4

#define LINE_LENGHT 256


typedef struct arguments {
    char input_path[128];
    char output_path[128];
    unsigned short group_size;
    bool quiet;
} Arguments;

int arg_parser(int, char **, Arguments *);


#ifndef OPTARG
#define OPTARG

#include <stdbool.h>

#define DEFAULT_OUTPUT_PATH "morse_output.txt"
#define DEFAULT_GROUP_SIZE 4

#define LINE_LENGHT 256
#define ITERATIVE   "i"

typedef struct MorseToTextArgs {
	char filepath[128];
	char text[1024];
	bool use_iterative;
	bool use_file;
} m2targs;

int arg_parser(int, char **, m2targs *);

#endif

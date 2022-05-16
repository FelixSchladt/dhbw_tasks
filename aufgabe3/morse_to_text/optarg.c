#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#include "optarg.h"

void print_missing_input_file() {
    printf("group_parser: missing input file\n");
    printf("Try 'group_parser -h' for more information.\n");
}

void print_invalid_file() {
    printf("morse2text: input file not found\n");
    printf("Try 'group_parser -h' for more information.\n");
}

void print_help() {
    puts("Usage: morse2text [INPUTFILE] [OPTION...]\n\n"\
    "morse2text -- translate morse code to readable text\n\n"\
    "-t    TEXT    morse code is read from provided string\n"\
    "-m    r/i     Choose the translation method: recursiv [r] / iterative [i]\n"\
    "-h            Show this help message");
}

//uses getopt to read cmd line options
int arg_parser(int argc, char **argv, m2targs * args) {
    if (argc < 2) {
        print_missing_input_file();
        return -1;
    }

    int option = 0;
    strcpy(args -> filepath, DEFAULT_OUTPUT_PATH);

    if (!access(argv[1], F_OK)) {
        strncpy(args -> filepath, argv[1], 50);
        strcpy(argv[1], argv[0]);
	args->use_file = true;
        argc--;
        argv++;
    } else if (strcmp(argv[1], "-h") != 0
	       && strcmp(argv[1], "-t") != 0) {
        print_invalid_file();
	return -1;
    }

    while ((option = getopt(argc, argv, "t:m:h")) != -1) {
	switch(option) {
	    case 't':
		//get message as string instead as file
		strcpy(args->text, optarg);
		args->use_file = false;
		break;
	    case 'm':
		//choose between iterative and recursive mode
		args->use_iterative = strcmp(optarg, ITERATIVE) == 0;
		break;
	    case 'h':
                print_help();
                return 0;
	    case '?':
	    default:
		print_help();
		return -1;
	}
    }

    return 0;
}


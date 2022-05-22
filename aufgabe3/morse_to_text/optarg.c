//Copyright 2022 Felix Schladt (https://github.com/FelixSchladt)

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

#include "optarg.h"

void print_missing_input_file() {
        printf("morse2text: missing input file\n");
        printf("Try 'morse2text -h' for more information.\n");
}

void print_invalid_file() {
        printf("morse2text: input file not found\n");
        printf("Try 'morse2text -h' for more information.\n");
}

void print_help() {
        puts("Usage: morse2text INPUTFILE [OPTION...]\n"\
        "morse2text -- convert text into morse code\n"\
        "-o    FILE    Provide name of output file\n"\
        "-h            Show this help message");
}

int arg_parser(int argc, char **argv, Arguments * args) {
    bool piped_content = !isatty(fileno(stdin));
    if (argc < 2 && !piped_content) {
        print_missing_input_file();
        exit(-1);
    }

    int option = 0;
    bool output_to_file = false;
    
    if ( access(argv[1], F_OK ) == 0 ) {
        args->file_pointer = fopen(argv[1], "r");
        strncpy(argv[1], argv[0], strlen(argv[1]));
        argc--;
        argv++;
    } else if (piped_content) { //give stdin as file replacement
         args->file_pointer = stdin;
    } else if ( strcmp(argv[1], "-h" ) == 0) {
        print_help();
        exit(0);
    } else {
        print_invalid_file();
        exit(-1);
    }

    while ((option = getopt(argc, argv, "o:O:h:")) != -1) {
	switch(option) {
		case 'o':
            	case 'O':
   	                args->output_file = fopen(optarg, "w");
        	        output_to_file = true;
                	break;

		case 'h':
                	print_help();
                	exit(0);
		case '?':	
		default:
                	printf("Invalid parameter!\nTry 'morse2text -h' for more information.\n");
			exit(-1);
	}
    }

    if (!output_to_file) {
    	args->output_file = fopen("/dev/null", "w");
    }

    return 0;
}


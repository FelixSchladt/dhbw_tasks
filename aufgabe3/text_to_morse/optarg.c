#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

#include "optarg.h"

void print_missing_input_file() {
        printf("group_parser: missing input file\n");
        printf("Try 'group_parser -h' for more information.\n");
}

void print_invalid_file() {
        printf("group_parser: input file not found\n");
        printf("Try 'group_parser -h' for more information.\n");
}

void print_help() {
        puts("Usage: text_to_morse INPUTFILE [OPTION...]\n"\
        "text_to_morse -- convert text into morse code\n"\
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
        strcpy(argv[1], argv[0]);
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

    while ((option = getopt(argc, argv, "o:O:h:q")) != -1) {
		switch(option) {
			case 'o':
            case 'O':
                args->output_file = fopen(optarg, "w");
                output_to_file = true;
                break;
            case 'q':
                args->quiet = true;
                break;
			case 'h':
                print_help();
                exit(0);
			case '?':	
			default:
                printf("Try 'group_parser -h' for more information.\n");
				exit(-1);
		}
	}
    if (!output_to_file) {
        args->output_file = fopen("/dev/null", "w");
    }
    return 0;
}


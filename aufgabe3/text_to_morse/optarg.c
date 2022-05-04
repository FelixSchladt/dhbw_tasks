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
        "text_to_morse -- convert text into morse code"\
        "-o    FILE    Provide name of output file"\
        "-h            Show this help message");
}

//uses getopt to read cmd line options
int arg_parser(int argc, char **argv, Arguments * args) {
    bool piped_content = !isatty(fileno(stdin));
    if (argc < 2 || piped_content) {
        print_missing_input_file();
        return -1;
    }

    int option = 0;
	strcpy(args -> output_path, DEFAULT_OUTPUT_PATH);
    
    if ( access(argv[1], F_OK ) == 0 ) {
        //strncpy(args -> input_path, argv[1], 50);
        args->file_pointer = fopen(argv[1], "r");
        strcpy(argv[1], argv[0]);
        argc--;
        argv++;
    } else if (piped_content) { //give stdin as file replacement
         args->file_pointer = stdin;
    } else if ( strcmp(argv[1], "-h" ) == 0) {
        print_help();
        return 0;
    } else {
        print_invalid_file();
        return -1;
    }

    while ((option = getopt(argc, argv, "o:O:hQ")) != -1) {
		switch(option) {
			case 'o':
            case 'O':
				strcpy(args -> output_path, optarg);
                break;
			case 'h':
                print_help();
                return 0;
			case '?':	
			default:
                printf("Try 'group_parser -h' for more information.\n");
				return -1;
		}
	}
    return 0;
}


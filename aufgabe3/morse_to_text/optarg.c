#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#ifndef OPTARG_H
#define OPTARG_H
#include "optarg.h"
#endif

void print_missing_input_file() {
        printf("group_parser: missing input file\n");
        printf("Try 'group_parser -h' for more information.\n");
}

void print_invalid_file() {
        printf("group_parser: input file not found\n");
        printf("Try 'group_parser -h' for more information.\n");
}

void print_invalid_outfile() {
        printf("group_parser: output file not found\n");
        printf("Try 'group_parser -h' for more information.\n");
}

void print_help() {
        puts("Usage: aufgabe1 INPUTFILE [OPTION...]\n"\
        "Group parser -- sort students into random groups"\
        "o    FILE    Provide name of output file"\
        "-s    SIZE    Group size"\
        "-q            no output to stdout"\
        "-h            Show this help message");
}

//uses getopt to read cmd line options
int arg_parser(int argc, char **argv, Arguments * args) {
    if (argc < 2) {
        print_missing_input_file();
        return -1;
    }

    int option = 0;
    args->group_size = 4;
	strcpy(args -> output_path, DEFAULT_OUTPUT_PATH);
    args->quiet = false;

    if ( access(argv[1], F_OK) == 0 ) {
        strncpy(args -> input_path, argv[1], 50);
        strcpy(argv[1], argv[0]);
        argc--;
        argv++;
    } else if (strcmp(argv[1], "-h") == 0) {
       print_help();
       return 0;
    } else {
        print_invalid_file();
        return -1;
    }

    while ((option = getopt(argc, argv, "s:S:o:O:hqQ")) != -1) {
		switch(option) {
			case 's':
            case 'S':
				args -> group_size = atoi(optarg);
				break;
			case 'o':
            case 'O':
				strcpy(args -> output_path, optarg);
				break;
            case 'q':
            case 'Q':
                args -> quiet = true;
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


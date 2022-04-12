#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

#ifndef OPTARG_H
#define OPTARG_H
#include "optarg.h"
#endif

//prints to stdout and to filestream
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

int get_random(int modulo) {
    return rand() % modulo;
}

//randomly switches pointers of an array
void randomize_list(char * list[], int len_list,  int rounds) {
    srand(time(NULL));
    for (int i = 0; i < rounds; i++) {
        for (int j = 0; j < len_list; j++ ) {
            int rand1 = rand() % len_list;
            int rand2 = rand() % len_list;
            char * buf = list[rand1];
            list[rand1] = list[rand2];
            list[rand2] = buf;
        }
    }
}

//reads file line by line
void read_file(FILE * fp, char * user_list[], size_t len_list) {
    char line[LINE_LENGHT];

    for (int i=0; i < len_list; i++) {
        if (fgets(line, LINE_LENGHT-1, fp) != NULL) {
            len_list ++;
            user_list[i] = malloc(strlen(line)+1);
            strncpy(user_list[i], line,  strlen(line));
        }
    }

    fclose(fp);
}

//returns lines in a file
int count_lines_of_file(FILE * fp) {
    int lines = 0;
    char ch;
    while(!feof(fp)) {   
        ch = fgetc(fp);
        if(ch == '\n') {
            lines++;
        }
    }
    fseek(fp, 0, SEEK_SET);
    return lines;
}

//assigns users to groups with specified size
int create_groups(Arguments * args) {
    FILE * output_file_ptr = fopen(args->output_path, "w");
    FILE * fp = fopen(args->input_path, "r");

    if (fp == NULL) {
        fprintf(stderr, "FILE not found error");
        exit(EXIT_FAILURE);
    }

    size_t len_list = count_lines_of_file(fp);
    char ** user_list = malloc(sizeof(char *) * len_list);

    read_file(fp, user_list, len_list);

    randomize_list(user_list, len_list, 10);

    int overlap = len_list % args->group_size;
    int groups = len_list / args->group_size;
    int overlap_org = overlap;

    //how many extra people need get assigned per group to assign everyone
    uint8_t * overlap_arr = calloc(200, sizeof(uint8_t));
    while(overlap > 0) {
        for (int i = 0; (i < groups) && overlap; i++) {
            overlap_arr[i]++;
            overlap--;
        }
    }

    //create groups
    int memberc = 0;
    for(int i = 0; i < groups; i++) {
        std_fprintf(output_file_ptr, args->quiet, "------ Group %i ------\n", i+1);

        //assign addional people
        for(int j = 0; overlap_arr[i]; j++) {
            std_fprintf(output_file_ptr, args->quiet, "%s", user_list[memberc]);
            memberc++;
            overlap_arr[i]--;
        }

        //assign the rest
        for(int j = 0; j < ((len_list-overlap_org)/groups); j++) {
            std_fprintf(output_file_ptr, args->quiet, "%s", user_list[memberc]);
            memberc++;
        }
        std_fprintf(output_file_ptr, args->quiet, "\n");
    }
    free(overlap_arr);
    for(int i=0; i < len_list; i++) {
        free(user_list[i]);
    }
    free(user_list);
    return groups;
}

int main(int argc, char * argv[]) {
    Arguments args;

    if (arg_parser(argc, argv, &args) != 0 ) {
            exit(-1);
    }
    create_groups(&args);
    //printf("I: %s O: %s S: %i Q:%i\n", args.input_path, args.output_path, args.group_size, args.quiet); 

    return 0;
}

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>

#define STD_OUT_NAME "groups.txt"

struct Options {
    char output_file[255];
    char input_file[255];
    bool verbose;
};

int std_fprintf(FILE *stream, const char *format, ...) {
    va_list args;
    int ret;

    va_start(args, format);
    vfprintf(stream, format, args);
    va_end(args);

    va_start(args, format);
    ret = vprintf(format, args);
    va_end(args);

    return ret;
}

int get_random(int modulo) {
    return rand() % modulo;
}

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

int read_file(char * user_list[]) {
    FILE * fp;
    char line[128];
    size_t len_list=0;

    fp = fopen("./anonym.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "FILE not found error");
        exit(EXIT_FAILURE);
    }

    for (int i=0; i < 128; i++) {
        if (fgets(line, 127, fp) != NULL) {
            len_list ++;
            user_list[i] = malloc(strlen(line));
            strncpy(user_list[i], line,  strlen(line));
        }
    }

    fclose(fp);
    return len_list;
}

int create_groups(group_size) {
    FILE *output_file_ptr;
    output_file_ptr = fopen("groups_outputs.txt", "w");

    char * user_list[128];
    size_t len_list = read_file(user_list);
    //int group_size = 4;

    randomize_list(user_list, len_list, 10);

    int i = 1;
    int group_counter = 0;
    int student_counter = 0;
    while ((len_list % (group_size * i)) != 0) {
        i++;
        if (i > (group_size / 2)) {
            fprintf(stderr, "Error: Could not find groups which satisfy requirements.\n");
            break;
        }
    }
    for(int j = 1; j<i ;j++) {
        group_counter++;
        std_fprintf(output_file_ptr, "\n------ Group %i ------\n", group_counter);
        for (int k = 0; k < group_size-1; k++) {
            std_fprintf(output_file_ptr, "%s", user_list[student_counter]);
            student_counter++;
        }
    }
    int groups = (len_list-i*(group_size-1)) / group_size;
    for(int j = group_counter; j <=groups; j++) {
        group_counter++;
        std_fprintf(output_file_ptr, "\n------ Group %i ------\n", group_counter);
        for (int k = 0; k < group_size; k++) {
            std_fprintf(output_file_ptr, "%s", user_list[student_counter]);
            student_counter++;
        }
    }
    return groups;
}

int main(int argc, const char * argv[]) {
    struct Options options;
    strcpy(options.output_file, STD_OUT_NAME); 
    bool i = false;

    printf("%\n", argc);
    if (argc<3) {
        printf("Usage: aufgabe1 INPUTFILE [OPTION...]");
        printf("Try `aufgabe1 --help') for more information.");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-h")) {
        printf("Usage: aufgabe1 INPUTFILE [OPTION...]\n",
                "\rGroup parser -- sort students into random groups\n",
                "\r-o    FILE    provide name of output file\n",
                "\r-q            Don't produce any output\n",
                "\r-h            Give this help list\n");
        exit(0);
    }
    size_t optind;

    for (optind = 2; optind < argc && argv[optind][0] == '-'; optind++) {
        switch (argv[optind][1]) {
            case 'o':
                printf("output file %s", argv[optind+1]);
                break;
        }
    }

    int opt;



    return 0;
}

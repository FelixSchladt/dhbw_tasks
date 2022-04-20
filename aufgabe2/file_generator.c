#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "test_ticket.h"

const char* HELPSTR = {
"\033[32mUsage\033[0m:\n\n"\
"-p <path>: REQUIRED, sets the directory the files wll be created in.\n\n"\
"-a <amount>: the amount of files that will be created.\n\n"\
"-d <seconds>: the delay between each file bing created.\n\n"
};

static void checkDir(const char* dir) {
	/*
	 * Check if the pased dir exists and creates it if not.
	 */
	struct stat sb;

	if (stat(dir, &sb) != 0 
	    || !S_ISDIR(sb.st_mode)) {

		mkdir(dir, 0777);
		printf("Create directory: \033[32m%s\033[0m\n", dir);

	}

}

static void createFiles(const char* dir, int amount, int delay) {
	/*
	 * Creates a given amount of files in a given directory
	 * with a given delay between creations
	 */
    char ticket[256];
	for (int i = 0; i < amount; i++) {
        get_buchung(ticket);
		char* path = malloc(strlen(dir) + 1 + sizeof(amount));
		sprintf(path, "%s/%i", dir, i);

		FILE* file = fopen(path, "w");
		printf("->Created \033[2m%s\033[0m\n", path);
		fprintf(file, "%s", ticket);

		fclose(file);
		free(path);

		sleep(delay);

	}

}

int main(int argc, char** argv) {
	int c = { 0 };
	int amount = { 50 };
	int delay = { 1 };
	bool hasDir = { false };
	char* dir;

	while((c = getopt(argc, argv, "p:a:d:h")) != -1) {
		switch(c) {
			case 'p':
				dir = malloc(strlen(optarg)+1);
				strcpy(dir, optarg);
				hasDir = true;
				break;

			case 'a':
				amount = atoi(optarg);
				break;

			case 'd':
				delay = atoi(optarg);
				break;

			case 'h':
				printf("%s", HELPSTR);
				exit(0);

			case '?':
				printf("\033[33mERROR: \033[0m Unknown parameters\n");
				break;

		}

	} 

	if (hasDir) {
		printf("Creating \033[32m%i\033[0m files in \033[32m%s\033[0m\n", amount, dir);
		checkDir(dir);
		createFiles(dir, amount, delay);
	    free(dir);

    } else {
        puts("Invalid usage: Please specifiy directory with -p PATH");
    }

	return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "replaceStr.h"

#define BUFFER 512


char *readFile(char *morseCode) {
    FILE *fp = fopen("morseCode.txt", "r");

    if (fp == NULL) {
        perror("file not found");
        exit(-1);
    }

    fgets(morseCode, BUFFER, fp);

    fclose(fp);

    return morseCode;
}

void morseCodeToText(char *morseCode) {
    morseCode = replaceStr(morseCode, "       ", ":");
    char *morseWords = strtok(morseCode, ":");

    uint8_t i = 0;
    char *morseData[64];
    while (morseWords != NULL) {
        morseData[i] = morseWords;
        // printf("%s\n", morseData[i]);
        morseWords = strtok(NULL, ":");
        i++;

    }


}

void textToMorseCode() {

}


int main() {
    system("clear");
    puts("Welcome to morse code generator!");
    puts("Convert morse code to Text [M]");
    puts("Generate morse code from Text [T]");
    puts("Quit [Q]");

    char input;
    printf("\nEnter action: ");
    scanf("%c", &input);

    if (input == 'm' || input == 'M') {
        char morseCode[BUFFER];
        readFile(morseCode);
        morseCodeToText(morseCode);
    } else if (input == 't' || input == 'T') {
        textToMorseCode();
    } else if (input == 'q' || input == 'Q') {
        exit(0);
    }

    return 0;
}

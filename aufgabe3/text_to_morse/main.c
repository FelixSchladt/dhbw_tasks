#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void text_morse(char ** morse_arr) {
    //char * morse_arr[128];
    for (int i = 0; i < 128; i++) {
        morse_arr[i] = (char*)malloc(8 * 8);
        strcpy(morse_arr[i], " ");
    }

    int i = 48;
    strcpy(morse_arr[0+i], "-----"); //0
    strcpy(morse_arr[1+i], ".----"); //1
    strcpy(morse_arr[2+i], "..---"); //2
    strcpy(morse_arr[3+i], "...--"); //3
    strcpy(morse_arr[4+i], "....-"); //4
    strcpy(morse_arr[5+i], "....."); //5
    strcpy(morse_arr[6+i], "-...."); //6
    strcpy(morse_arr[7+i], "--..."); //7
    strcpy(morse_arr[8+i], "---.."); //8
    strcpy(morse_arr[9+i], "----."); //9


    for(; i < 90; i  = i + 32) {
    strcpy(morse_arr[17+i], ".-"); //A
    strcpy(morse_arr[18+i], "-..."); //B
    strcpy(morse_arr[19+i], "-.-."); //c
    strcpy(morse_arr[20+i], "-.."); //d
    strcpy(morse_arr[21+i], "."); //e
    strcpy(morse_arr[22+i], "..-."); //f
    strcpy(morse_arr[23+i], "--."); //g
    strcpy(morse_arr[24+i], "...."); //h
    strcpy(morse_arr[25+i], ".."); //i
    strcpy(morse_arr[26+i], ".---"); //j
    strcpy(morse_arr[27+i], "-.-"); //k
    strcpy(morse_arr[28+i], ".-.."); //l
    strcpy(morse_arr[29+i], "--"); //m
    strcpy(morse_arr[30+i], "-."); //n
    strcpy(morse_arr[31+i], "---"); //o
    strcpy(morse_arr[34+i], ".-."); //r
    strcpy(morse_arr[35+i], "..."); //s
    strcpy(morse_arr[36+i], "-"); //t
    strcpy(morse_arr[37+i], "..-"); //u
    strcpy(morse_arr[38+i], "...-"); //v
    strcpy(morse_arr[39+i], ".--"); //w
    strcpy(morse_arr[40+i], "-..-"); //x
    strcpy(morse_arr[41+i], "-.--"); //y
    strcpy(morse_arr[42+i], "--.."); //z
    }

}

//am besten Char-code - offset damit der erste index 0 ist

char * char_to_morse(char ** morse_arr,  char input) {
    return morse_arr[input];
}

void text_to_morse(char * dest, char * input) { //This code seems to segfault if multiple runs are made
    //char morse_arr[128];
    char ** morse_arr = malloc(sizeof(char *) * 64);
    text_morse(morse_arr);
    char buf[8];
    char character; 
    memset(dest, '\0', sizeof(&dest));
    int counter = 0;

    while ((character = input[counter]) != '\0') {
        strcpy(buf, char_to_morse(morse_arr, character));
        //strcat(buf, " ");
        //strcat(dest, buf);
        sprintf(dest, "%s %s", dest, buf);
        //printf("Morsceode from char %c: %s\n", character, char_to_morse(morse_arr, character));
        counter++;
    }
}

void read_file(FILE * fp, char * buf) {
    //FILE * fp = fopen(filename, "r");
    //char buf[1024];
    char * line = NULL;
    size_t len = 0;
    size_t read;
    char buffer[128];

    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf(" ");
        printf("Retrieved line of length %zu:\n", read);
        //text_to_morse(buffer, line); //Segfault in text to morse
        printf("%s ", line);
    }

    fclose(fp);
    if (line)
        free(line);
}

int main() {
    char dest[1024];
    //text_to_morse(dest, "Jan Schaible");

    //puts(" ");
    //printf("%s\n", dest);
    FILE * fp = fopen("test.txt", "r");
    read_file(fp, dest);

    //printf("%s\n", dest);

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void text_morse(char morse_arr[]) {
    //char * morse_arr[128];
    for (int i = 0; i < 128; i++) {
        morse_arr[i] = *(char*)malloc(8 * 8);
    }
    strcpy(&morse_arr[0], "-----"); //0
    strcpy(&morse_arr[1], ".----"); //1
    strcpy(&morse_arr[2], "..---"); //2
    strcpy(&morse_arr[3], "...--"); //3
    strcpy(&morse_arr[4], "....-"); //4
    strcpy(&morse_arr[5], "....."); //5
    strcpy(&morse_arr[6], "-...."); //6
    strcpy(&morse_arr[7], "--..."); //7
    strcpy(&morse_arr[8], "---.."); //8
    strcpy(&morse_arr[9], "----."); //9


    strcpy(&morse_arr[17], ".-"); //A
    strcpy(&morse_arr[18], "-..."); //B
    strcpy(&morse_arr[19], "-.-."); //c
    strcpy(&morse_arr[20], "-.."); //d
    strcpy(&morse_arr[21], "."); //e
    strcpy(&morse_arr[22], "..-."); //f
    strcpy(&morse_arr[23], "--."); //g
    strcpy(&morse_arr[24], "...."); //h
    strcpy(&morse_arr[25], ".."); //i
    strcpy(&morse_arr[26], ".---"); //j
    strcpy(&morse_arr[27], "-.-"); //k
    strcpy(&morse_arr[28], ".-.."); //l
    strcpy(&morse_arr[29], "--"); //m
    strcpy(&morse_arr[30], "-."); //n
    strcpy(&morse_arr[31], "---"); //o
    strcpy(&morse_arr[32], ".--."); //p
    strcpy(&morse_arr[33], "--.-"); //q
    strcpy(&morse_arr[34], ".-."); //r
    strcpy(&morse_arr[35], "..."); //s
    strcpy(&morse_arr[36], "-"); //t
    strcpy(&morse_arr[37], "..-"); //u
    strcpy(&morse_arr[38], "...-"); //v
    strcpy(&morse_arr[39], ".--"); //w
    strcpy(&morse_arr[40], "-..-"); //x
    strcpy(&morse_arr[41], "-.--"); //y
    strcpy(&morse_arr[42], "--.."); //z
    

}

//am besten Char-code - offset damit der erste index 0 ist

void char_to_morse(char morse_arr, 
        char input) {

}



int main() {
    char morse_arr[128];
    text_morse(morse_arr);
    printf("%c\n", morse_arr[41]);
    printf("%s\n", )

}

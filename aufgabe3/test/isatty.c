#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
    
int main (int argc, char **argv) {

    char * input_buffer = malloc(8*65536);
    char * input_buffer_init = input_buffer;

    
    
    //Check for  piped content
    if (!isatty(fileno(stdin))) { 
        int i = 0;
        while(-1 != (input_buffer[i++] = getchar()));
    }
    printf("%s", input_buffer_init);
    free(input_buffer_init);
}

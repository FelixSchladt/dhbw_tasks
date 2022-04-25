#include <stdlib.h>
#include <string.h>

#include "replaceStr.h"

char *replaceStr(const char *inputString, const char *oldString, const char *newString) {
    char *result;
    int i, count = 0;
    int newStringlen = strlen(newString);
    int oldStringlen = strlen(oldString);

    // Counting the number of times old substring
    // occur in the string
    for (i = 0; inputString[i] != '\0'; i++) {
        if (strstr(&inputString[i], oldString) == &inputString[i]) {
            count++;

            // Jumping to index after the old string.
            i += oldStringlen - 1;
        }
    }

    // Making new string of enough length
    result = (char *) malloc(i + count * (newStringlen - oldStringlen) + 1);

    i = 0;
    while (*inputString) {
        // compare the substring with the result
        if (strstr(inputString, oldString) == inputString) {
            strcpy(&result[i], newString);
            i += newStringlen;
            inputString += oldStringlen;
        } else
            result[i++] = *inputString++;
    }

    result[i] = '\0';
    return result;
}

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int get_random_minute() {
    return ((rand() % 4)) * 15;
}

int get_random_hour() {
    return (rand() % 10) + 8;

}

char *get_mail(char *mail) {
    FILE *file = fopen("random_mail.txt", "r");

    char line[128];
    uint8_t line_count;
    uint8_t randnum = rand() % 100;

    while (fgets(line, 128, file)) {
        strcpy(mail, line);
        if (line_count == randnum) {
            break;
        }
        line_count++;
    }

    fclose(file);

    return mail;
}

static void init() {
    {
        //Zufallszahlen zufaelliger machen
        time_t t;
        srand((unsigned) time(&t));
    }
}

/* Returns a random line (w/o newline) from the file provided */
/*char* get_random_mail() {
    FILE *f;
    size_t lineno = 0;
    size_t selectlen;
    char selected[256]; // Arbitrary, make it whatever size makes sense 
    char current[256];
    selected[0] = '\0'; // Don't crash if file is empty 

    f = fopen("./randommail.txt", "r"); 
    while (fgets(current, sizeof(current), f)) {
        if (drand48() < 1.0 / ++lineno) {
            strcpy(selected, current);
        }
    }
    fclose(f);
    selectlen = strlen(selected);
    if (selectlen > 0 && selected[selectlen-1] == '\n') {
        selected[selectlen-1] = '\0';
    }
    return strdup(selected);
}*/

char *get_time(char *time) {
    sprintf(time, "%02d:%02d", get_random_hour(), get_random_minute());
    return time;
}

void get_buchung(char *buchung) {
    char time[6];
    char mail[128];
    init();
    get_mail(mail);
    get_time(time);
    sprintf(buchung, "%s\n%s\n", mail, time);
    printf("%s\n", buchung);
}
/*
int main(int argc, const char ** argv) {
    char buchung[256];
    get_buchung(buchung);
    //printf("%s\n", get_random_mail());
    return 0;
}*/

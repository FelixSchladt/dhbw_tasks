#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

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
        if (line_count == randnum) {
            strcpy(mail, line);
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
    sprintf(buchung, "%s%s\n", mail, time);
    printf("%s\n", buchung);
}
/*
int main(int argc, const char ** argv) {
    char buchung[256];
    get_buchung(buchung);
    //printf("%s\n", get_random_mail());
    return 0;
}*/

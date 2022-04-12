#include <stdio.h>
#include <string.h>
//#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int get_random_minute() {
     return ((rand() % 4)) * 15;
}
int get_random_hour() {
     return (rand() % 10)+8;

}

char * get_mail( char * mail ) {
    strcpy(mail, "antonia.pawlik@gmail.com");
    return mail;
}

static void init() {
    {
        //Zufallszahlen zufaelliger machen
        time_t t;
        srand((unsigned)time(&t));
    }
}

char* get_time( char * time  ) {
    sprintf(time, "%02d:%02d", get_random_hour(), get_random_minute());
    return time;
}

void get_buchung( char * buchung )  {
    char time[6];
    char mail[128];
    init();
    get_mail( mail );
    get_time( time );
    sprintf(buchung, "%s\n%s\n", mail, time);
    printf("%s\n", buchung);
}


/*int main(int argc, const char ** argv) {
    char buchung[256];
    get_buchung(buchung);
    return 0;
}*/

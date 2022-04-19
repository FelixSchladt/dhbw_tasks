#include <stdint.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <stdbool.h>

uint8_t *array;


struct Appointment {
    uint8_t hour;
    uint8_t minute;
    char email[256];
    bool test_result;
};

// TODO make appoinment typedef

struct Time_slot {
    bool occupied;
    struct Appointment ticket;
};
//TODO use appointment struct to handle all evenets.
// use list of time_slot struct to check wether time slot is already occupied
// when inotify eventhandler is triggerd by event adjust according appointment -> delete or create
// When CTRL_C signal is triggerd, evaluate all existing appoinments

void CTRL_C(const int signal)
{
    free(array);
    puts("");
    puts("Verlasse Ueberwachung");
    exit(1);
}

/*
void update_table(uint8_t * array) {
    uint8_t minutes = ;
    for (int hours = 10; hours >= 18; hours++) {

    }

}
*/

int main() {

    //Ausstieg ueber CTRL-C
    signal(SIGINT, CTRL_C);

    //Ueberwachung initialisieren
    int fd = inotify_init();

    //Pruefen ob diese erfolgreich initialisiert werden konnte
    if(fd == -1) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    //Verzeichnis ueberwachen
    int wd = inotify_add_watch(fd,"./tmp",IN_CREATE | IN_DELETE);

    //Pruefen ob diese erfolgreich initialisiert werden konnte
    if(wd == -1) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    {
        array = malloc(1024);
        int len = 0;
        /*
            for(int i = 0; i < 5; ++i)
                while ((len = read(fd, event, sizeof(struct inotify_event))) < 0) {
                    puts("Changes");
                }
        */
        for(;;) {
            len = read(fd, array, 1024);

            struct inotify_event *event = (struct inotify_event *) array;

            if(event->mask & IN_CREATE) {
                printf("Create len=%d, mask=%x, namelen=%d, name=%s\n",len, event->mask, event->len, event->name);
                update_table(array);
            } else if(event->mask & IN_DELETE)  {
                printf("Delete len=%d, mask=%x, namelen=%d, name=%s\n",len, event->mask, event->len, event->name);
                update_table(array);
            }
            else puts("Event unknown");
        }

    }
    return 0;
}

#include <stdint.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>

uint8_t *array;

void CTRL_C(const int signal)
{
    free(array);
    puts("");
    puts("Verlasse Ueberwachung");
    exit(1);
}

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

            if(event->mask & IN_CREATE) printf("Create len=%d, mask=%x, namelen=%d, name=%s\n",len, event->mask, event->len, event->name);
            else if(event->mask & IN_DELETE) printf("Delete len=%d, mask=%x, namelen=%d, name=%s\n",len, event->mask, event->len, event->name);
            else puts("Event unknown");
        }

    }
    return 0;
}

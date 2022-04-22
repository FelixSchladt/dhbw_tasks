#include <stdint.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define BUFFER 256

uint8_t *array;

typedef struct Appointment {
    uint8_t hour;
    uint8_t minute;
    char email[BUFFER];
    bool occupied;
    bool test_result;
    char name[BUFFER];
} appointment;

appointment timetable[40];

//TODO use appointment struct to handle all events.
// use list of time_slot struct to check weather time slot is already occupied
// when inotify event handler is triggered by event adjust according appointment -> delete or create
// When CTRL_C signal is triggered, evaluate all existing appointments


void print_time_slots() {
    FILE *fp = fopen("timeslots.txt", "w");
    int hour = 0;
    for (int i = 0; i < 40; i++) {
        if (i % 4 == 0) hour++;
        if (timetable[i].occupied) {
            fprintf(fp, "%02d:%02d - %s---\n", 7 + hour, (i % 4) * 15, timetable[i].email);
            //TODO fix times
        } else {
            fprintf(fp, "%02d:%02d - free\n---\n", 7 + hour, (i % 4) * 15);
        }
    }

    fclose(fp);
}

int getEventIndex(uint8_t hour, uint8_t minute) {
    uint8_t hourIndex = ((hour - 8) * 4);
    uint8_t minuteIndex = minute / 15;
    return hourIndex + minuteIndex;
}

int checkTime(uint8_t hour, uint8_t minute) {
    if (7 < hour && hour < 18 && minute % 15 == 0) {
        return true;
    } else {
        return false;
    }
}

void appendBookingCancelled(char *filename) {
    char path[BUFFER];
    sprintf(path, "tmp/%s", filename);
    FILE *file = fopen(path, "a");

    char *str = {"Ihre Buchung wurde abgelehnt."};
    fprintf(file, "%s", str);
    fclose(file);
}

void readFile(char *filename) {
    char path[50];
    sprintf(path, "tmp/%s", filename);
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        perror("file not found");
        exit(-1);
    }

    char email[BUFFER];
    fgets(email, BUFFER, file);
    char time[6];
    fgets(time, 6, file);
    time[2] = '\0';
    uint8_t hour = atoi(time);
    uint8_t minute = atoi(time + 2);
    uint8_t index = getEventIndex(hour, minute);

    if (!checkTime(hour, minute) || timetable[index].occupied) { return; }

    strcpy(timetable[index].email, email);
    timetable[index].hour = hour;
    timetable[index].minute = minute;
    timetable[index].occupied = true;
    strcpy(timetable[index].name, filename);

    fclose(file);

    appendBookingCancelled(filename);
}

void deleteEvent(char *filename) {
    for (int i = 0; i < 40; i++) {
        if (strcmp(timetable[i].name, filename)) {
            timetable[i].occupied = false;
        }
    }
}

void evaluateResults() {
    for (int i = 0; i < 40; i++) {
        bool randbool = rand() % 2;
        timetable[i].test_result = randbool;
    }
}

void collectPositiveTestResults() {
    FILE *file = fopen("positiveTests.txt", "w");
    fprintf(file, "Positive Results\n");

    for (int i = 0; i < 40; i++) {
        if (timetable[i].occupied && timetable[i].test_result) {
            fprintf(file, "%s %02d:%02d\n\n", timetable[i].email, timetable[i].hour, timetable[i].minute);
        }
    }

    fclose(file);
}

void CTRL_C(const int signal) {
    free(array);
    evaluateResults();
    // add result to file
    // report all positiv test
    collectPositiveTestResults();
    puts("");
    puts("Leave monitoring!");
    exit(1);
}

int main() {

    //Ausstieg ueber CTRL-C
    signal(SIGINT, CTRL_C);

    //Ueberwachung initialisieren
    int fd = inotify_init();

    //Pruefen ob diese erfolgreich initialisiert werden konnte
    if (fd == -1) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    //Verzeichnis ueberwachen
    int wd = inotify_add_watch(fd, "./tmp", IN_CREATE | IN_DELETE);

    //Pruefen ob diese erfolgreich initialisiert werden konnte
    if (wd == -1) {
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
        for (;;) {
            len = read(fd, array, 1024);

            struct inotify_event *event = (struct inotify_event *) array;

            if (event->mask & IN_CREATE) {
                printf("Create len=%d, mask=%x, namelen=%d, name=%s\n", len, event->mask, event->len, event->name);
                readFile(event->name);
                print_time_slots();
            } else if (event->mask & IN_DELETE) {
                printf("Delete len=%d, mask=%x, namelen=%d, name=%s\n", len, event->mask, event->len, event->name);
                deleteEvent(event->name);
                print_time_slots();
            } else puts("Event unknown");
        }

    }
    return 0;
}

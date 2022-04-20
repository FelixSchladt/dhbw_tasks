#include <stdint.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER 128

uint8_t *array;

typedef struct Appointment {
    uint8_t hour;
    uint8_t minute;
    char email[BUFFER];
    bool test_result;
} appointment;

typedef struct TimeSlot {
    bool occupied = false;
    struct Appointment ticket;
} timeslot;

timeslot timetable[40];
char email[BUFFER];
char time[6];

//TODO use appointment struct to handle all events.
// use list of time_slot struct to check weather time slot is already occupied
// when inotify event handler is triggered by event adjust according appointment -> delete or create
// When CTRL_C signal is triggered, evaluate all existing appointments

void readFile(char *filename) {
    FILE *file = fopen("tmp/%s", filename, "r");

    if (file == NULL) {
        perror("file not found");
        exit(-1);
    }

    uint8_t lineCount = 0;

    while (fgets(char line[BUFFER], BUFFER, *file)) {
        if (lineCount == 0) {
            email = line;
        } else {
            time = line;
        }
        lineCount++;
    }

    fclose(file);
}

int checkTime(uint8_t hour, uint8_t minute) {
    if (7 < hour && hour < 18 && minute % 15 == 0) {
        return true
    } else {
        return false
    }
}

int getEventIndex(uint8_t hour, uint8_t minute) {
    uint8_t hourIndex = ((hour - 8) * 4);
    uint8_t minuteIndex = minute / 15;
    return hourIndex + minuteIndex;
}

void createEvent(uint8_t index, char email[64], uint8_t hour, uint8_t minute) {
    timetable[index]->ticket.email = email;
    timetable[index]->ticket.hour = hour;
    timetable[index]->ticket.minute = minute;
    timetable[index]->occupied = true;
}

void appendBookingCancelled(char *filename) {
    FILE *file = fopen("tmp/%s", filename, "a");

    char *str = {"Ihre Buchung wurde abgelehnt."};
    fprintf(file, "%s", str);
    fclose(file);
}

void deleteEvent(uint8_t index) {
    timetable[index]->occupied = false;
}

void evaluateResults() {
    for (int i = 0; i < 40; i++) {
        bool randbool = rand() % 2;
        timetable[i]->ticket.test_result = randbool;
    }
}

void collectPositivTestResults() {
    char result[40][BUFFER] = {"Positive Testergebnisse:"};
    uint8_t lineCount = 1;
    for (int i = 0; i < 40; i++) {
        if (timetable[i].occupied && timetable[i]->ticket.test_result == true) {
            result[lineCount] = "%s %s:%s", timetable[i].ticket.email, timetable[i].ticket.hour, timetable[i].ticket.minute;
            lineCount++;
        }
    }

    FILE *file = fopen("positiveTests.txt", "w");

    fwrite(result, sizeof(char), sizeof(result), file);
    fclose(file);
}

void CTRL_C(const int signal) {
    free(array);
    evaluateResults()
    // add result to file
    // report all positiv test
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
                char *token = strtok(time, ":");
                uint8_t hour = token[0]
                uint8_t minute = token[1];
                uint8_t index = getEventIndex(hour, minute);
                if (!checkTime() || timetable[index]->occupied) {
                    appendBookingCancelled(event->name)
                } else {
                    createEvent(index, email, hour, minute);
                }
            } else if (event->mask & IN_DELETE) {
                printf("Delete len=%d, mask=%x, namelen=%d, name=%s\n", len, event->mask, event->len, event->name);
                readFile(event->name);
                char *token = strtok(time, ":");
                uint8_t hour = token[0]
                uint8_t minute = token[1];
                uint8_t index = getEventIndex(hour, minute);
                deleteEvent(index);
            } else puts("Event unknown");
        }

    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <getopt.h>

const char * const HELPTXT = {
    "Usage: group [OPTIONS] file ...\n" \
    "-h,--help                Display this information\n" \
    "-v, --version            Display Programm Information\n" \
    "-s, --group-size <count> Size of group (default 4)\n" \
    "--do-bigger              If not even create some bigger groups\n" \
    "-r, --display-raw        Don't format the output\n" \
    "-o [FILE]                Select output file\n"
    "\n" \
    "For more information please contact\n" \
    "thomas_staudacher@yahoo.de or andreas.maus@zf.com"
};

static int group_size = {4}, do_bigger = {0}, display_raw = {0};

const struct option longopts[] =
{
    //Mit der Nummer 1 wird das setzen des Flags gesteuert
    {"group-size",required_argument,&group_size,0},
    {"do-bigger",no_argument,&do_bigger,1},
    {"display-raw",no_argument,&display_raw,2},
    {"help",no_argument,NULL,'h'},
    {"version",no_argument,NULL,'v'},
    {0,0,0,0}
};

static void Help()
{
    puts(HELPTXT);
    exit(0);
}

static void Version()
{
    puts("Version from " __DATE__ ", " __TIME__);
    exit(0);
}

static void init() {
    {
        //Zufallszahlen zufaelliger machen
        time_t t;
        srand((unsigned)time(&t));
    }
}

static char *readFromFileToMapping(const char * const path, size_t *length) {
    FILE *fd = {NULL};
    char *ptr_to_mapping = {NULL};

    if(path && length) {
        if(fd = fopen(path,"rb")) {
            {
                //Groesse der Datei bestimmen (Netto)
                fseek(fd, 0L, SEEK_END);
                *length = ftell(fd);
                rewind(fd);
            }

            //Abbild der Datei in Speicher legen
            //Wir brauchen eine Speicherstelle mehr für das Endzeichen 0
            //calloc initialisiert den Speicherbereich mit 0
            if(ptr_to_mapping = calloc(*length+1,sizeof(char))) {
                fread(ptr_to_mapping, sizeof(char), *length, fd);
            }

            fclose(fd);
        }
        else {
            perror(path);
#ifdef _WIN32
            exit(ENOFILE);
#else
            exit(EBADFD);
#endif
        }
    }
    return ptr_to_mapping;
}

static void doMishMash(char **ptr_array_person, const int count_person, const int turns) {
    //Verwuerfeln
    if(ptr_array_person && (count_person > 1) && (turns > 1))
        for(int i = {0}; i < turns; ++i) {
            int a = {rand()%count_person}, b = {rand()%count_person};
            if(a == b) continue;
            else {
                //Adressen vertauschen
                char *ptr_a = {ptr_array_person[a]};
                ptr_array_person[a] = ptr_array_person[b];
                ptr_array_person[b] = ptr_a;
            }

        }
}

int countPerson(char *ptr_to_mapping) {
    //Feststellen um wieviel Personen es sich handelt
    int count_person = {0};

    if(ptr_to_mapping) {

        for(char *ptr = {ptr_to_mapping}; ptr = strchr(ptr, '\n'); ++count_person, ++ptr);

#ifndef _WIN32
        if(count_person) {
            ++count_person;
        }
#endif        
    }
    return count_person;
}

int main(int argc, char* argv[]) {
    //Strukturiert und Initialisiert die noetigen PTR und Variable erzeugen
    char *ptr_to_mapping = {NULL};
    size_t length = {0};
    int count_person = {0};
    char **ptr_array_person = {NULL};
    char *path = {NULL};
    char *output = {NULL};
    int optindex = {0};
    int c = {0};

    //Initialisieren
    init();

    //Ohne getopt die beste Variante um die Parameter abzuprüfen
    if(argc < 2) {
        fprintf(stderr,"See -h for options\n");
        return EINVAL;
    }
    else
        while((c = getopt_long(argc,argv,"hs:rvo:",longopts,&optindex)) >= 0)
        {
            switch(c)
            {
            case 0:
            case 1:
            case 2:
                //Keine spezifische Abarbeitung der LongOpts derzeit
                break;
            case 'h':
                Help();
                break;
            case 's':
                group_size = atoi(optarg);
                break;
            case 'r':
                display_raw = 1;
                break;
            case 'v':
                Version();
                break;
            case 'o':
                output = optarg;
                break;

            default:
                fprintf(stderr,"Unknown option %d", c);
                exit(-1);
            }
        }

    if (optind < argc) {
        while (optind < argc) {
            path = argv[optind++];
            break;
        }
    }

    if(ptr_to_mapping = readFromFileToMapping(path, &length)) {
        {
            //Feststellen um wieviel Personen es sich handelt
            count_person = countPerson(ptr_to_mapping);
        }

        {
            //Adressen in ein Array schreiben
            ptr_array_person = calloc(count_person,sizeof(char *));
            ptr_array_person[0] = ptr_to_mapping;
            int pos = {1};
            for(char *ptr = {ptr_to_mapping}; ptr = strchr(ptr, '\n'); ++ptr) {
                ptr_array_person[pos++] = ptr + 1;
            // falls 0xa LF oder 0xd CR von DOS im Buffer verbleibt wird er durch 0 ersetzt.               
                if((*(ptr-1) == 0xa) ||(*(ptr-1) == 0xd)) *(ptr-1) = '\0';
                *ptr = '\0'; // hier das eigentliche Ersetzen des Newline-Zeichens
                if((*(ptr+1) == 0xa) ||(*(ptr+1) == 0xd)) *(ptr+1) = '\0';
            }
        }

        {

            //Verwuerfeln
            doMishMash(ptr_array_person, count_person, 10000);
        }

        // Ausgabe des CSV-Files
        if(output)
        {
            printf("%s\n", output);
            FILE* fout = fopen(output,"wb");

            if(fout)
            {
                
                int groupnumber = {1}, count = {0}, extra = {count_person % group_size};
                bool pause = {false};

                for(int i = 0; i < count_person; ++i) {
                    if(!(count%group_size) && !pause) {
                        pause = false;
                        if(i==0)
                        {
                            fprintf(fout, "Group %d",groupnumber++);
                        }
                        else
                        {
                            fprintf(fout, "\nGroup %d",groupnumber++);
                        }

                        if(!do_bigger) ++count;
                        else if(!extra) ++count;
                        else {
                            pause = true;
                            --extra;
                        }
                    }
                    else {
                        ++count;
                        pause = false;
                    }

                    fprintf(fout, ", %s", ptr_array_person[i]);
                }
            }
            else
            {
                printf("Could not open output file: %s.\n", output);
            }

            fclose(fout);
        }
        else
        {
            printf("No output file selected.\n");
        }
        //Bei RAW ohne Formatierung ausgeben
        if(display_raw) for(int i = 0; i < count_person; ++i) puts(ptr_array_person[i]);
        else {
            int groupnumber = {1}, count = {0}, extra = {count_person % group_size};
            bool pause = {false};

            printf("Groupconstellation person = %d, groupsize = %d, create %s groups\n",count_person, group_size, (do_bigger ? "bigger" : "even"));
            for(int i = 0; i < count_person; ++i) {
                if(!(count%group_size) && !pause) {
                    pause = false;
                    printf("\nGroup %d:\n\n",groupnumber++);

                    if(!do_bigger) ++count;
                    else if(!extra) ++count;
                    else {
                        pause = true;
                        --extra;
                    }
                }
                else {
                    ++count;
                    pause = false;
                }

                puts(ptr_array_person[i]);
            }
        }

        free(ptr_array_person);
        free(ptr_to_mapping);
    }
    else {
#ifdef _WIN32
        return ENOMEM;
#else
        return ENOBUFS;
#endif
    }

    return 0;
}


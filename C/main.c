#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

static int log = 0;

static struct option const long_options[] =
{
  {"debug", no_argument, NULL, 'd'},
  {0, 0, 0, 0}
};

void usage() {
    printf("\
    You need to input some time in %%%%h%%%%m%%%%s format.\n\
           \n");
    exit(1);
}

static void parseArgs(int argc, char** argv){
    int c;
    /* Just for future me: this changes the positions of argv
     * if you input arg1 -oparg then after this parse
     * argv is -oparg arg1, why?
     */
    while ((c = getopt_long(argc, argv, "d", long_options, NULL)) != -1) {
        switch (c) {
            case 'd':
                log = 1;
                break;
            default:
                usage();
        }
    }
}

int transformHumanToSeconds(char time[]) {
    int temp = 0;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int i = 0;
    int multi = 1;
    // This is not very good
    while (time[i] != '\0') {
        if (time[i] == 'h') {
            hours = temp;
            temp = 0;
            multi = 1;
        }
        else if (time[i] == 'm') {
            minutes = temp;
            temp = 0;
            multi = 1;
        }
        else if (time[i] == 's') {
            seconds = temp;
            temp = 0;
            break;
        }
        else {
            // Same as go, you can add letters instead of numbers and works
            temp = temp * multi + time[i] - '0';
            multi *= 10;
        }
        ++i;
    }

    seconds = seconds + minutes * 60 + hours * 3600;

    if (log) {
        printf("Calculated seconds: %d\n", seconds);
    }

    return seconds;
}

void transformSecondsToHuman(int time, char* humanTime) {
    int temp;
    const int hoursInSeconds = 60 * 60;
    const int minutesInSeconds = 60;
    int hours = time / hoursInSeconds;
    time -= hoursInSeconds * hours;
    int minutes = time / minutesInSeconds;
    time -= minutesInSeconds * minutes;
    int seconds = time;

    snprintf(humanTime, 10, "%02dh%02dm%02ds", hours, minutes, seconds);
}


int main(int argc, char ** argv) {
    int timeToSleep;
    char* humanTime;

    if (argc == 1) {
        usage();
    }

    parseArgs(argc, argv);

    timeToSleep = transformHumanToSeconds(argv[1 + log]);

    //12h45m78s => 9 char + \0 for snprintf
    humanTime = (char*)malloc(sizeof(char) * 10);

    printf("Erase me\n");

    while (timeToSleep > 0) {
         // Move the cursor up 1 line and to the beginning
        printf("\033[1A\033[0G");

         // Clear the line
        printf("\033[K");

        transformSecondsToHuman(timeToSleep, humanTime);

        if (timeToSleep < 31) {
            printf("Timer: \033[31;40m%s\033[0m\n", humanTime);
        }
        else {
            printf("Timer: %s\n", humanTime); 
        }

        sleep(1);

        --timeToSleep;
    }

    printf("\033[1A\033[0G");
    printf("\033[K");
    printf("Done!\n");

    return 0;
}   

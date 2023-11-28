
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"
#include "buzzer_pitch.h"

#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"

void doHelp(void)
{
    printf("Usage:\n");
    printf("buzzertest <buzzerNo> \n");
    printf("buzzerNo: \n");
    printf("do(1),re(2),mi(3),fa(4),sol(5),ra(6),si(7),do(8) \n");
    printf("off(0)\n");
}

int main(int argc, char **argv)
{
    int freIndex;
    if (argc < 2 || buzzerInit())
    {
        printf("Error!\n");
        doHelp();
        return 1;
    }
    freIndex = atoi(argv[1]);
    printf("freIndex :%d \n", freIndex);
switch(freIndex){
    case 0:
        buzzerStopSong();break;
    case -1:
    
        buzzerPlaySong(NOTE_C5);
        usleep(10000);
        buzzerPlaySong(NOTE_E5);
        usleep(10000);
        buzzerPlaySong(NOTE_G5);
        usleep(10000);
        buzzerPlaySong(NOTE_C6);
        usleep(10000);
        buzzerStopSong();
break;
        case 1:
for(int i=0;i<8;i++){
        buzzerTone(NOTE_C5, 50);
        buzzerTone(NOTE_E5, 50);
        buzzerTone(NOTE_A5, 100);
}
for(int i=0;i<3;i++){
        buzzerTone(NOTE_B4, 50);
        buzzerTone(NOTE_E5, 50);
        buzzerTone(NOTE_A5, 100);
}
for(int i=0;i<5;i++){
        buzzerTone(NOTE_B4, 50);
        buzzerTone(NOTE_E5, 50);
        buzzerTone(NOTE_G5, 100);
}
        buzzerStopSong();
break;
case 2:
    buzzerPlaySong(NOTE_C6);
    delay_ms(500);
        buzzerStopSong();
    
default:
        buzzerStopSong();
break;
    }
    return 0;
}


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
    printf("buzzertest <buzzerNo> [buzzerpitch]\n");

    printf("ModeNo: \n");
    printf(" 0: stop music\n");
    printf("-1: very fase do-mi-sol\n");
    printf(" 1: RAP music\n");
    printf(" 2: play note for 500ms\n");
    printf(" 3: siren\n");
    printf(" 4: start sound\n");
    printf(" 5: 1 turn end\n");
    printf(" 6: wheel on the line\n");
    printf(" 7: accident sound\n");

    printf("buzzer pitch: \n");
    printf("ex) 262 = middle do\n");
}

int main(int argc, char **argv)
{
    int freIndex, frequency;
    if (argc < 3 || buzzerInit())
    {
        printf("Error!\n");
        doHelp();
        return 1;
    }
    freIndex = atoi(argv[1]);
    frequency = atoi(argv[2]);
    printf("freIndex :%d \n", freIndex);
    switch (freIndex)
    {
    case 0:
        buzzerStopSong();
        break;

    case -1:
        buzzerPlaySong(NOTE_C5);
        usleep(10000);
        buzzerPlaySong(NOTE_E5);
        usleep(10000);
        buzzerPlaySong(NOTE_G5);
        usleep(10000);
        buzzerStopSong();
        break;

    case 1: // RAP music
        for (int i = 0; i < 8; i++)
        {
            buzzerTone(NOTE_C5, 50);
            buzzerTone(NOTE_E5, 50);
            buzzerTone(NOTE_A5, 300);
        }
        for (int i = 0; i < 3; i++)
        {
            buzzerTone(NOTE_B4, 50);
            buzzerTone(NOTE_E5, 50);
            buzzerTone(NOTE_A5, 300);
        }
        for (int i = 0; i < 5; i++)
        {
            buzzerTone(NOTE_B4, 50);
            buzzerTone(NOTE_E5, 50);
            buzzerTone(NOTE_G5, 300);
        }
        buzzerStopSong();
        break;

    case 2: // play pitch
        buzzerPlaySong(frequency);
        delay_ms(500);
        buzzerStopSong();
        break;

    case 3: // siren
        for (int i = NOTE_DS3; i < NOTE_B5; i += 5)
        {
            buzzerPlaySong(i);
        }
        for (int i = NOTE_B5; i > NOTE_DS3; i -= 5)
        {
            buzzerPlaySong(i);
        }
        buzzerStopSong();
        break;
    case 4: // start sound
        buzzerTone(NOTE_A4, 500);
        buzzerTone(0, 500);
        buzzerTone(NOTE_A4, 500);
        buzzerTone(0, 500);
        buzzerTone(NOTE_A4, 500);
        buzzerTone(0, 500);
        buzzerTone(NOTE_A5, 1000);
        buzzerStopSong();
        break;
    case 5: // 1 turn end
        buzzerTone(NOTE_E4, 100);
        buzzerTone(NOTE_G4, 100);
        buzzerTone(NOTE_E5, 100);
        buzzerTone(NOTE_C5, 100);
        buzzerTone(NOTE_E5, 100);
        buzzerTone(NOTE_G5, 100);
        buzzerStopSong();
        break;
    case 6: // wheel on the line
        buzzerTone(NOTE_E3, 500);
        buzzerStopSong();
        break;
    case 7: // accident sound
        buzzerTone(NOTE_B5, 50);
        buzzerTone(0, 50);
        buzzerTone(NOTE_B5, 50);
        buzzerTone(0, 50);
        buzzerTone(NOTE_B5, 50);
        buzzerTone(0, 50);
        buzzerTone(NOTE_B5, 50);
        buzzerTone(0, 50);
        buzzerTone(NOTE_B5, 50);
        buzzerTone(0, 50);
        buzzerTone(NOTE_B5, 50);
        buzzerTone(0, 50);
        buzzerTone(NOTE_B5, 50);
        buzzerTone(0, 50);
        buzzerTone(NOTE_B5, 50);
        buzzerTone(0, 50);
        buzzerTone(NOTE_B5, 50);
        buzzerTone(0, 50);
        buzzerTone(NOTE_B5, 50);
        buzzerTone(0, 50);
        buzzerStopSong();
        break;
    default:
        buzzerStopSong();
        break;
    }
    return 0;
}

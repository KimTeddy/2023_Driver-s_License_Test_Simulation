
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"
#include "buzzer_soundeffect_defs.h"

#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"

char gBuzzerBaseSysDir[128]; /// sys/bus/platform/devices/peribuzzer.XX 가 결정됨

int findBuzzerSysPath()
{
    DIR *dir_info = opendir(BUZZER_BASE_SYS_PATH);
    int ifNotFound = 1;

    if (dir_info != NULL)
    {
        while (1)
        {
            struct dirent *dir_entry;
            dir_entry = readdir(dir_info);
            if (dir_entry == NULL)
                break;
            if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0)
            {
                ifNotFound = 0;
                sprintf(gBuzzerBaseSysDir, "%s%s/", BUZZER_BASE_SYS_PATH, dir_entry->d_name);
            }
        }
    }
    printf("find %s\n", gBuzzerBaseSysDir);
    return ifNotFound;
}
// 버저 경로 찾기: /sys/bus/platform/devices/peribuzzer.XX 의 XX를 결정하는 것

void buzzerEnable(int bEnable)
{
    char path[200];
    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);
    int fd = open(path, O_WRONLY);
    if (bEnable)
        write(fd, &"1", 1);
    else
        write(fd, &"0", 1);
    close(fd);
}

void setFrequency(int frequency)
{
    char path[200];
    sprintf(path, "%s%s", gBuzzerBaseSysDir, BUZZER_FREQUENCY_NAME);
    int fd = open(path, O_WRONLY);
    dprintf(fd, "%d", frequency);
    close(fd);
}

//---------------------------------------------------------------------------
int buzzerInit(void)
{
    int ifNotFound = 1;
    ifNotFound = findBuzzerSysPath();

    return ifNotFound;
}

int buzzerPlaySong(int scale)
{
    buzzerEnable(1);
    setFrequency(scale);

    return 0;
}

int buzzerStopSong(void)
{
    buzzerEnable(0);

    return 0;
}

int buzzerExit(void)
{
    buzzerEnable(0);
    return 0;
};

void buzzerTone(int scale, unsigned int milliseconds)
{
    if (scale != 0)
    {
        buzzerPlaySong(scale);
    }
    delay_ms(milliseconds);
    buzzerStopSong();
}

void delay_ms(unsigned int milliseconds)
{
    usleep(milliseconds * 1000); // 밀리초를 마이크로초로 변환
}

void soundEffect(int soundEF)
{
    switch (soundEF)
    {
    case SE_MUTE:
        buzzerStopSong();
        break;

    case SE_CEG:
        buzzerPlaySong(NOTE_C5);
        usleep(10000);
        buzzerPlaySong(NOTE_E5);
        usleep(10000);
        buzzerPlaySong(NOTE_G5);
        usleep(10000);
        buzzerStopSong();
        break;

    case SE_MUSIC: // RAP music
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

//    case SE_PITCH: // play pitch
//        buzzerPlaySong(frequency);
//        delay_ms(500);
//        buzzerStopSong();
//        break;

    case SE_SIREN: // siren
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
    case SE_START: // start sound
        buzzerTone(NOTE_A4, 500);
        buzzerTone(0, 500);
        buzzerTone(NOTE_A4, 500);
        buzzerTone(0, 500);
        buzzerTone(NOTE_A4, 500);
        buzzerTone(0, 500);
        buzzerTone(NOTE_A5, 1000);
        buzzerStopSong();
        break;
    case SE_ENDTURN: // 1 turn end
        buzzerTone(NOTE_E4, 100);
        buzzerTone(NOTE_G4, 100);
        buzzerTone(NOTE_E5, 100);
        buzzerTone(NOTE_C5, 100);
        buzzerTone(NOTE_E5, 100);
        buzzerTone(NOTE_G5, 100);
        buzzerStopSong();
        break;
    case SE_MINUS: // wheel on the line
        buzzerTone(NOTE_E3, 500);
        buzzerStopSong();
        break;
    case SE_ACCIDENT: // accident sound
        for (int i = 0; i < 10; i++)
        {
            buzzerTone(NOTE_B5, 50);
            buzzerTone(0, 50);
        }
        buzzerStopSong();
        break;
    default:
        buzzerStopSong();
        break;
    }
}

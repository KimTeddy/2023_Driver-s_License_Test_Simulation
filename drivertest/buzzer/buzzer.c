
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

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

void buzzerTone(int scale, unsigned int milliseconds){
if(scale!=0) {
    buzzerPlaySong(scale);
}
    delay_ms(milliseconds);
    buzzerStopSong();
}

void delay_ms(unsigned int milliseconds) {
    usleep(milliseconds * 1000);  // 밀리초를 마이크로초로 변환
}

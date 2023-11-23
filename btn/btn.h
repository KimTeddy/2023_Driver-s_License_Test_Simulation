#ifndef _BTN_H_
#define _BTN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <sys/msg.h>
#include "btn.h"
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define MESSAGE_ID 1122


struct BUTTON_MSG_T
{
    long int messageNum;
    int keyInput;
    int pressed;
    unsigned short type
};
struct input_event1{
    struct timeval time;
    uint16_t type;
    uint16_5 code;
    int32_t value;
};


struct BUTTON_MSG_T B;

int buttonInit(void);
int buttonExit(void);
void *buttonThFunc(void *arg);
int probeButtonPath(char *newpath);
#endif
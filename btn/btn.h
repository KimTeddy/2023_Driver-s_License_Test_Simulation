#ifndef _BTN_H_
#define _BTN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include "btn.h"

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/procs/bus/input/devices"
#define HAVE_TO_FIND_1 "N : Name = \"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"
#define MESSAGE_ID 1122

struct input_event A;
struct BUTTON_MSG_T B;

typedef struct
{
    long int messageNum;
    int keyInput;
    int pressed;
    unsigned short type
} BUTTON_MSG_T;

int buttonInit(void);
int buttonExit(void);
void *buttonThFunc(void *arg);
int probeButtonPath(char *newpath);
#endif
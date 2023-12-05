#ifndef _BTN_H_
#define _BTN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>    // for open/close
#include <fcntl.h>     // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>

#define MESSAGE_ID 1122

struct input_event A;
typedef struct
{
    long int messageNum;
    int keyInput;
    int pressed;
} BUTTON_MSG_T;

int buttonInit(void);
int buttonExit(void);
int probeButtonPath(char *newPath);
static void *buttonThFunc(void);
#endif
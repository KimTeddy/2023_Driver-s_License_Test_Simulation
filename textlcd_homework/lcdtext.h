#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>

#ifndef _TEXTLCD_H_
#define _TEXTLCD_H_
#define CMD_WRITE_STRING 0x20
#define CMD_DATA_WRITE_BOTH_LINE 0
#define CMD_WRITE_STRING 0x20
#define CMD_DATA_WRITE_BOTH_LINE 0
#define NUM_ROWS 2
#define NUM_COLS 16

void lcdtextwrite(const char *str1, const char *str2, int lineFlag);


#endif

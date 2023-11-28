#ifndef __TEXTLCD_H__
#define __TEXTLCD_H__
#define LINE_NUM 2
#define COLUMM_NUM 16
#define TEXTLCD_DRV "/dev/peritextlcd"

#define LINE_BUFF_NUM (COLUMM_NUM + 4)  
//for dummy
#define MODE_CMD 0
#define MODE_DATA 1

#define CMD_DISPLAY_MODE 0x10
    #define BIT_DISPLAY_MODE_CURSOR_DISP 0x01
    #define BIT_DISPLAY_MODE_CURSOR_BLINK 0x02
    #define BIT_DISPLAY_MODE_DISP_ENABLE 0x04

#define CMD_CURSOR_MOVE_MODE 0x11
    #define CURSOR_MOVE_MODE_ENABLE 0x01
    #define CURSOR_MOVE_MODE_RIGHT_DIR 0x02

#define CMD_CURSOR_MOVE_POSITION 0x12
    #define CURSOR_MOVE_X_MASK 0x3F
    #define CURSOR_MOVE_Y_MASK 0xC0

#define CMD_WRITE_STRING 0x20
    #define CMD_DATA_WRITE_BOTH_LINE 0
    #define CMD_DATA_WRITE_LINE_1 1
    #define CMD_DATA_WRITE_LINE_2 2
#define CMD_TEST_GPIO_HIGH 0x30
#define CMD_TEST_GPIO_LOW 0x31

//이것저것 강의자료에 있는 것들 define해주기

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct TextLCD_tag
{
    unsigned char cmd;
    unsigned char cmdData;
    unsigned char reserved[2];

    char TextDate[LINE_NUM]{LINE_BUFF_NUM};
}stTextLCD, *pStTextLCD;

int lcdwrite(const char *str0, const char *str1, int line);
//lcd에 문구 적을 수 있는 함수

#endif
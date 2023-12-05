#include "lcdtext.h"
#include "textlcddrv.h"

unsigned int linenum = 0;
stTextLCD stlcd; // stTextLCD 구조체를 가지고 드라이버와 인터페이스
int fd;
int len;

int main(int argc , char **argv)
{
memset(&stlcd,0,sizeof(stTextLCD)); // 구조체 초기화
if (argc < 3 ) { // line 정보와 쓸 정보를 확인
perror(" Args number is less than 2\n");
return 1;
}
linenum = strtol(argv[1],NULL,10);
printf("linenum :%d\n", linenum);
if ( linenum == 1)
stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
else if ( linenum == 2)
stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
else {
printf("linenum : %d wrong . range (1 ~ 2)\n", linenum);
return 1; }
len = strlen(argv[2]);
if ( len > COLUMN_NUM)
memcpy(stlcd.TextData[stlcd.cmdData - 1], argv[2], COLUMN_NUM);
else
memcpy(stlcd.TextData[stlcd.cmdData - 1], argv[2], len);
stlcd.cmd = CMD_WRITE_STRING;

lcdtextwrite(stlcd.TextData[0], stlcd.TextData[1], linenum);
}


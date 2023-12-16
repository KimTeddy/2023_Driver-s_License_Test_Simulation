#include "lcdtext.h"
stTextLCD stlcd;
int fd;
int len1;
int len2;

int txtlcd_Init(void)
{
    fd = open("/dev/peritextlcd", O_RDWR);
    if (fd < 0)
    {
        perror("driver (//dev//peritextlcd) open error.\n");
        return 1;
    }
    memset(&stlcd, 0, sizeof(stTextLCD));
}
void lcdtextwrite(const char *str1, const char *str2, int lineFlag)
{
    printf("linenum :%d\n", lineFlag);

    if (lineFlag == 1)
    { // first line
        stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
        printf("LCD Write:%s\n", str1);
        len1 = strlen(str1);
        if (len1 > COLUMN_NUM)
        {
            memcpy(stlcd.TextData[stlcd.cmdData - 1], str1, COLUMN_NUM);
        }
        else
        {
            memcpy(stlcd.TextData[stlcd.cmdData - 1], str1, len1);
        }
    }
    else if (lineFlag == 2)
    { // second line
        stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
        printf("LCD Write:%s\n", str2);
        len2 = strlen(str2);
        if (len2 > COLUMN_NUM)
        {
            memcpy(stlcd.TextData[stlcd.cmdData - 1], str2, COLUMN_NUM);
        }
        else
        {
            memcpy(stlcd.TextData[stlcd.cmdData - 1], str2, len2);
        }
    }
    else if(lineFlag == 0)
    {
        //both linelcdtextwrite(str1, str2,0);
         stlcd.cmdData = CMD_DATA_WRITE_BOTH_LINE;
        len1 = strlen(str1);
        len2 = strlen(str2);
        if (len2 > COLUMN_NUM)
        {
            memcpy(stlcd.TextData[stlcd.cmdData - 1], str2, COLUMN_NUM);
            memcpy(stlcd.TextData[stlcd.cmdData - 1], str1, COLUMN_NUM);
        }
        else
        {
            memcpy(stlcd.TextData[stlcd.cmdData - 1], str1, len1);
            memcpy(stlcd.TextData[stlcd.cmdData - 1], str2, len2);
        }
    }
    else
    {
        printf("linenum : %d  wrong .  range (1 ~ 2)\n", lineFlag);
    }

    stlcd.cmd = CMD_WRITE_STRING;

    write(fd, &stlcd, sizeof(stTextLCD));
}
void txtlcd_off(void)
{
    char str[] = {"                          "};
    lcdtextwrite(str,str, 1);
    lcdtextwrite(str,str, 2);
    close(fd);
}

#include "lcdtext.h"
#include "textlcddrv.h"

int fd;
stTextLCD stlcd;
unsigned int linenum = 0;

int lcdtextwrite(const char* str1, const char* str2, int lineFlag)
{
        fd = open("/dev/peritextlcd", O_RDWR); // open driver
        if (fd < 0) {
                perror("driver (//dev//peritextlcd) open error.\n");
                return 1;
        }
        str1 = stlcd.TextData[0];
        str2 = stlcd.TextData[1];
        if (lineFlag == 1) {
                write(fd, str1, sizeof(stTextLCD));
        }
        else if (lineFlag == 2){
                write(fd, str2, sizeof(stTextLCD));
        }
        close(fd);
        return 0;
}



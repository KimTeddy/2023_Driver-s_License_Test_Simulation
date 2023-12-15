#include "lcdtext.h"
#include "textlcddrv.h"

stTextLCD st;
int fd;
int len1;
int len2;

void txtlcd_Init(void)
{
    fd = open("/dev/peritextlcd", O_RDWR);
    if (fd < 0)
    {
        perror("driver (//dev//peritextlcd) open error.\n");
        return 1;
    }
    memset(&st, 0, sizeof(stTextLCD));
}
void lcdtextwrite(const char *str1, const char *str2, int lineFlag)
{
    printf("linenum => %d\n", &lineFlag);

    if (lineFlag == 1)
    { // first line
        st.cmdData = CMD_DATA_WRITE_LINE_1;
        len1 = strlen(str1);
        if (len1 > COLUMN_NUM)
        {
            memcpy(st.TextData[st.cmdData - 1], str1, COLUMN_NUM);
        }
        else
        {
            memcpy(st.TextData[st.cmdData - 1], str1, len1);
        }
    }
    else if (lineFlag == 2)
    { // second line
        st.cmdData = CMD_DATA_WRITE_LINE_2;
        len2 = strlen(str1);
        if (len2 > COLUMN_NUM)
        {
            memcpy(st.TextData[st.cmdData - 1], str2, COLUMN_NUM);
        }
        else
        {
            memcpy(st.TextData[st.cmdData - 1], str2, len2);
        }
    }
    else
    {
        printf("linenum : %d  wrong . choose the number 1 or 2 \n", lineFlag);
    }
    st.cmd = CMD_WRITE_STRING;
    write(fd, &st, sizeof(stTextLCD));
}
void txtlcd_Exit(void)
{
    //char str[0] = '\0';
    char *str = " ";  // 배열의 모든 요소를 '\0'으로 초기화
    lcdtextwrite(str,str, 1);
    lcdtextwrite(str,str, 2);
    close(fd);
}


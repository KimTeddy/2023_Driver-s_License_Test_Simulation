#include "lcdtext.h"
#include "textlcddrv.h"

unsigned int linenum = 0;
stTextLCD st; // stTextLCD 구조체를 가지고 드라이버와 인터페이스
int fd;
char str[LINE_NUM][COLUMN_NUM];
char str_mid1[LINE_NUM][COLUMN_NUM+4];
char str_mid2[LINE_NUM][COLUMN_NUM+4];
char str1[LINE_NUM][COLUMN_NUM];
char str2[LINE_NUM][COLUMN_NUM];
int i = 0, c = 0;

int main()
{
 txtlcd_Init();
 printf("textlcdtest ");
 scanf("%d",&lineFlag);
 if(lineFlag==1){ 
        fgets(str_mid1, sizeof(str_mid1), stdin);
        for(; i < strlen(str_mid1); i++)
        {
          if (str_mid1[i] != '\'')
                {
                        str1[c] = str_mid1[i];
                        c++;
                }
        }
        str1[c]='\0'; 
        str2[0]='\0';
        }
 else if(lineFlag==2){ 
        fgets(str_mid2, sizeof(str_mid2), stdin);
                for(; i < strlen(str_mid2); i++)
        {
          if (str_mid2[i] != '\'')
                {
                        str1[c] = str_mid2[i];
                        c++;
                }
        }
        str2[c] = '\0'; 
        }
//lcdtextwrite(str1, str2, lineFlag);
lcdtextwrite( "PRESS START", , 1);
lcdtextwrite( "PRESS START", "0xff", 2);
txtlcd_Exit();
}

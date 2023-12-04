#include "lcdtext.h"

char textlcd[NUM_ROWS][NUM_COLS] = {};
int len;
int lineFlag;

int ledtextinit(void){
	   lcd_fd = open("/dev/peritextlcd", O_RDWR);
    if (lcd_fd == -1) {
        perror("Error opening LCD device");
        return 1;
    }
}

void lcdtextwrite(const char *str1, const char *str2, int lineFlag) {		
    // 전달된 문자열을 textlcd 배열에 복사
    if (lineFlag == 1) {
    	len = strlen(str1);
    	if(len>NUM_COLS)
        memcpy(textlcd[0],str1,NUM_COLS);
        else{
        memcpy(textlcd[0],str1,len);
		textlcd[0][len] = '\0';
	}
        textlcd[1][0] = '\0';
    } else if (lineFlag == 2) {
        len = strlen(str2);
    	if(len>NUM_COLS)
        memcpy(textlcd[1],str2,NUM_COLS);
        else
	{ memcpy(textlcd[1],str2,len);
         textlcd[1][len] = '\0'; // Null-terminate the string}
    } else {
        printf("choose 1 or 2\n");
        return;
    }
            // LCD 장치 파일 닫기
}
int lcdtextexit(void){
	 textlcd[0][0] = '\0';
    textlcd[1][0] = '\0';
	len=0;
	lineFlag=0;
	close(lcd_fd);
	return 0;
}

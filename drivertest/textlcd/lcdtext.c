#include "lcdtext.h"
    char textlcd[NUM_ROWS][NUM_COLS] = {};
	int len;

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
    	len = strlen(textlcd[0]);
    	if(len>NUM_COLS)
        memcpy(str1,textlcd[0],NUM_COLS);
        else
        memcpy(str1,textlcd[0],len);
        textlcd[1][0] = '\0';
    } else if (lineFlag == 2) {
        len = strlen(textlcd[1]);
    	if(len>NUM_COLS)
        memcpy(str1,textlcd[1],NUM_COLS);
        else
        memcpy(str1,textlcd[1],len);
        
    } else {
        printf("choose 1 or 2\n");
        return;
    }
            // LCD 장치 파일 닫기
}
int lcdtextexit(void){
	textlcd[NUM_ROWS][NUM_COLS] = {};
	len=0;
	str1={};
	str2={};
	lineFlag=0;
	close(lcd_fd);
	return 0;
}

// lcdtext.c


#include "lcdtext.h"

// LCD 디바이스의 파일 디스크립터


void lcdtextwrite(const char *str1, const char *str2, int lineFlag) {
    char textlcd[NUM_ROWS][NUM_COLS + 1] = {0};

    // 전달된 문자열을 textlcd 배열에 복사
    if (lineFlag == 1) {
        snprintf(textlcd[0], sizeof(textlcd[0]), "%s", str1);
       [NUM_ROWS][NUM_COLS + 1] = {0};
       textlcd[NUM_ROWS][1] = {0};
    } else if (lineFlag == 2) {
        snprintf(textlcd[1], sizeof(textlcd[1]), "%s", str2);
        textlcd[NUM_ROWS][0] = {0};
    } else {
        printf("choose 1 or 2\n");
        return;
    }

}



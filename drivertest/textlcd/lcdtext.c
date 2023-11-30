#include "lcdtext.h"

void lcdtextwrite(const char *str1, const char *str2, int lineFlag) {
    char textlcd[NUM_ROWS][NUM_COLS + 1] = {0};

    // 전달된 문자열을 textlcd 배열에 복사
    if (lineFlag == 1) {
        snprintf(textlcd[0], sizeof(textlcd[0]), "%s", str1);
        
    } else if (lineFlag == 2) {
        snprintf(textlcd[1], sizeof(textlcd[1]), "%s", str2);
    } else {
        printf("choose 1 or 2\n");
        return;
    }

}

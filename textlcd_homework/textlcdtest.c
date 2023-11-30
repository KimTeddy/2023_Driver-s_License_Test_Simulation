// textlcdtest.c

#include <stdio.h>
#include <stdlib.h>
#include "lcdtext.h"

int main() {
    char str1[NUM_COLS + 1];
    char str2[NUM_COLS + 1];
    int lineFlag;

    // 사용자로부터 입력 받기
    printf("textlcdtest ");
    scanf("%d %16[^\n]", &lineFlag, lineFlag == 1 ? str1 : str2);

    if (lineFlag != 1 && lineFlag != 2) {
        printf("Invalid line number. Please enter 1 or 2.\n");
        return 1;
    }
    // lcdtextwrite 함수 호출
    lcdtextwrite(str1, str2, lineFlag);

    return 0;
}

// lcdtext.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>
#include "lcdtext.h"

// LCD 디바이스의 파일 디스크립터
int lcd_fd;

int main() {
    // LCD 장치 파일 열기
    lcd_fd = open("/dev/peritextlcd", O_RDWR);
    if (lcd_fd == -1) {
        perror("Error opening LCD device");
        return 1;
    }
//////////////////////////////////////////////////////////////
    char str1[NUM_COLS + 1];
    char str2[NUM_COLS + 1];
    int lineFlag;

    // 사용자로부터 입력 받기
    printf("Enter line number (1 or 2) and 'text' : ");
    scanf("%d ", &lineFlag);  // 숫자 입력
    fgets(lineFlag == 1 ? str1 : str2, sizeof(str1), stdin);

    // 문자열에서 개행 문자 제거
    size_t len1 = strlen(str1);
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
    }

    size_t len2 = strlen(str2);
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
    }

    // lcdtextwrite 함수 호출
    lcdtextwrite(str1, str2, lineFlag);

    // LCD 장치 파일 닫기
    close(lcd_fd);

    return 0;
}



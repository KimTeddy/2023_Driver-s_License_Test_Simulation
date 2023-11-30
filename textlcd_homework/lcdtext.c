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
    lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1) {
        perror("Error opening LCD device");
        return 1;
    }

    char str1[NUM_COLS + 1];
    char str2[NUM_COLS + 1];
    int lineFlag;

    // 사용자로부터 입력 받기
    printf("Enter line number (1 or 2) and text : ");
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

// lcdtextwrite 함수 정의
void lcdtextwrite(const char *str1, const char *str2, int lineFlag) {
    char textlcd[NUM_ROWS][NUM_COLS + 1] = {0};

    // 전달된 문자열을 textlcd 배열에 복사
    if (lineFlag == 1) {
        snprintf(textlcd[0], sizeof(textlcd[0]), "%s", str1);
    } else {
        snprintf(textlcd[1], sizeof(textlcd[1]), "%s", str2);
    }

    // LCD에 텍스트 출력
    struct fb_var_screeninfo vinfo;
    if (ioctl(lcd_fd, FBIOGET_VSCREENINFO, &vinfo)) {
        perror("Error reading variable information");
        return;
    }

    // 한 행당 필요한 바이트 계산
    size_t bytes_per_line = vinfo.yres_virtual * vinfo.bits_per_pixel / 8;

    // 각 행에 대해 LCD에 문자열 출력
    for (int i = 0; i < NUM_ROWS; ++i) {
        // 해당 행의 시작 위치 계산
        off_t offset = i * bytes_per_line;

        // 문자열을 LCD에 복사
        memcpy((void *)((char *)vinfo.smem_start + offset), textlcd[i], strlen(textlcd[i]));
    }

    // 화면 업데이트
    ioctl(lcd_fd, FB_ACTIVATE_VBL, NULL);
}

#include "lcdtext.h"

int lcd_fd;
int main() {

int ledtextinit();

    char str[NUM_ROWS][NUM_COLS];
    char str1[NUM_ROWS][NUM_COLS];
    char str2[NUM_ROWS][NUM_COLS];


    // 사용자로부터 입력 받기
    printf("Enter line number (1 or 2) and 'text' : ");
	scanf("%d", &lineFlag);  // 숫자 입력
	fgets(str[0], sizeof(str[0]), stdin);
	if(lineFlag ==NULL){ printf("숫자를 입력하세요");exit(1);}
	if(str[0]=='\0'){printf("문자열을 입력하세요"); exit(1);}

	char* output = str;  // 출력용 포인터를 입력과 같이 시작하게 함

	size_t len = strlen(str); //개행문자 제거
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    // 입력 문자열을 순회하면서 따옴표를 제거
    while (*str) {
        if (*str != '\'') {
            *output = *str;  // 따옴표가 아닌 경우에만 복사
            output++;
        }
        str++;
    }
    *output = '\0';
    
	if(lineFlag == 1) {
		strcpy(str1, output);;
	}
	else if(lineFlag == 2) {
		strcpy(str2, output);;
	}
      // lcdtextwrite 함수 호출
    lcdtextwrite(str1, str2, lineFlag);
    
	int lcdtextexit();
    return 0;
}

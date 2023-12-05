#include "lcdtext.h"

int lineFlag;
int main() {

ledtextinit();

    char str[NUM_ROWS][NUM_COLS];
    char str1[NUM_ROWS][NUM_COLS];
    char str2[NUM_ROWS][NUM_COLS];


    // 사용자로부터 입력 받기
    printf("Enter line number (1 or 2) and 'text' : ");
	scanf("%d", &lineFlag);  // 숫자 입력
   
	if (lineFlag != 1 && lineFlag != 2) {
        printf("Choose 1 or 2\n");
        exit(1);
    }
	fgets(str, sizeof(str), stdin);

	if(str[0]=='\0'){printf("문자열을 입력하세요"); exit(1);}

	size_t len = strlen(str); //개행문자 제거
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    // 입력 문자열을 순회하면서 따옴표를 제거
   
    char output[sizeof(str)];  // output 배열은 충분한 크기로 선언
    char *output_ptr = output;
    char *str_ptr = str;

    while (*str_ptr) {
        if (*str_ptr != '\'') {
            *output_ptr = *str_ptr;
            output_ptr++;
        }
        str_ptr++;
    }
    *output_ptr = '\0';
    
	if(lineFlag == 1) {
		strcpy(str1, output);;
	}
	else if(lineFlag == 2) {
		strcpy(str2, output);;
	}
      // lcdtextwrite 함수 호출
    lcdtextwrite(str1, str2, lineFlag);
    
lcdtextexit();
    return 0;
}

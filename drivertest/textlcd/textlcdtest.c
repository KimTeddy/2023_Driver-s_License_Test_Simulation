#include "lcdtext.h"
#include "textlcddrv.h"
int lineFlag;
int main()
{
    ledtextinit();

    char str[NUM_ROWS][NUM_COLS];
    char str1[NUM_ROWS][NUM_COLS];
    char str2[NUM_ROWS][NUM_COLS];

    // 사용자로부터 입력 받기
    printf("Enter line number (1 or 2) and 'text' : ");
    scanf("%d", &lineFlag); // 숫자 입력

    if (lineFlag != 1 && lineFlag != 2)
    {
        printf("Choose 1 or 2\n");
        exit(1);
    }
    gets(str);

    if (str[0] == '\0')
    {
        printf("문자열을 입력하세요");
        exit(1);
    }

    // 입력 문자열을 순회하면서 따옴표를 제거
    char output[sizeof(str)];
    int i = 0, c = 0; // 따옴표 제거
    for (; i < strlen(str); i++)
    {
        // if (isalnum(str[i]))  // msg 문자(a-z, A-Z, 0-9)를 제외한 모든것 제거하고 싶은 경우 사용
        if (str[i] != '\'') // msg 에서 따옴표 제외하는것이 목적일 경우
        {
            output[c] = str[i];
            c++;
        }
    }
    output[c] = '\0';

    if (lineFlag == 1)
    {
        strcpy(str1, output);
    }
    else if (lineFlag == 2)
    {
        strcpy(str2, output);
    }
    // lcdtextwrite 함수 호출
    lcdtextwrite(str1, str2, lineFlag);

    lcdtextexit();
    return 0;
}

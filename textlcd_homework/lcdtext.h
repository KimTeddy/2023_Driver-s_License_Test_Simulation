//lcdtext.h

#ifndef _TEXTLCD_H_
#define _TEXTLCD_H_
#define CMD_WRITE_STRING 0x20
#define CMD_DATA_WRITE_BOTH_LINE 0
#define CMD_WRITE_STRING 0x20
#define CMD_DATA_WRITE_BOTH_LINE 0
#define NUM_ROWS 2
#define NUM_COLS 16

void lcdtextwrite(const char *str1, const char *str2, int lineFlag) {
	
    char textlcd[NUM_ROWS][NUM_COLS + 1] = {0};

    // 전달된 문자열을 textlcd 배열에 복사
    if (lineFlag == 1) {
        snprintf(textlcd[0], sizeof(textlcd[0]), "%s", str1);
         memcpy(str1, textlcd[0], strlen(textlcd[0]));
    } else if(lineFlag ==2){ 
    snprintf(textlcd[1], sizeof(textlcd[1]), "%s", str2);
     memcpy(str2, textlcd[1], strlen(textlcd[1]));
	}
	else
	 printf("choose 1 or 2\n"); 
    printf("Enter line number (1 or 2) and 'text' : ");
    return;
}


#endif

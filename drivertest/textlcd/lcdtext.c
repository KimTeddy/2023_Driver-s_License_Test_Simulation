#include "lcdtext.h"
#include "textlcddrv.h"

int fd;
stTextLCD stlcd;
unsigned int linenum = 0;

int textlcd_display(int argc, char** argv)
{
	int len;
	memset(&stlcd, 0, sizeof(stTextLCD)); // 구조체 초기화
	if (argc < 3) { // line 정보와 쓸 정보를 확인
		perror(" Args number is less than 2\n");
		doHelp();
		return 1;
	}
	linenum = strtol(argv[1], NULL, 10);
	printf("linenum :%d\n", linenum);
	if (linenum == 1)
		stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
	else if (linenum == 2)
		stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
	else {
		printf("linenum : %d wrong . range (1 ~ 2)\n", linenum);
		return 1;
	}
	len = strlen(argv[2]);
	if (len > COLUMN_NUM)
		memcpy(stlcd.TextData[stlcd.cmdData - 1], argv[2], COLUMN_NUM);
	else
		memcpy(stlcd.TextData[stlcd.cmdData - 1], argv[2], len);
	stlcd.cmd = CMD_WRITE_STRING;
	return 0;
}

int lcdtextwrite(const char* str1, const char* str2, int lineFlag)
{
	fd = open("/dev/peritextlcd", O_RDWR); // open driver
	if (fd < 0) {
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
	str1 = stlcd.TextData[0];
	str2 = stlcd.TextData[1];
	if (lineFlag == 1) {
		write(fd, str1, sizeof(stTextLCD));
	}
	else if (lineFlag == 2){
		write(fd, str2, sizeof(stTextLCD));
	}
	close(fd);
	return 0;
}

#include <stdio.h>
#include <unistd.h>
#include "led.h"

void doHelp(void)
{
printf("ledtest <hex byte> :data bit0 operation 1=>on 0=>off\n");
printf(" ledtest 0x05 ;4th and 1th led on\n");
printf(" ledtest 0xff ;all led on\n");
printf(" ledtest 0x00 ;all led off\n");
}

int main(int argc, char** argv)
{
	int keep=1;
	if (argc < 2 ){
		perror(" Args number is less than 2\n");
		doHelp();
		return 1;
	}
		while(1) {
		ledLibInit();
		ledRead(argv[1]);
		ledLibExit();
		ledLibInit();
		ledRead(0x00);
		ledLibExit();
		ledLibInit();
		ledRead(0x01);
		ledLibExit();
		ledLibInit();
		ledRead(0x03);
		ledLibExit();
		ledLibInit();
		ledRead(0x07);
		ledLibExit();
		ledLibInit();
		ledRead(0x0f);
		ledLibExit();
		ledLibInit();
		ledRead(0x1f);
		ledLibExit();
		ledLibInit();
		ledRead(0x3f);
		ledLibExit();
		ledLibInit();
		ledRead(0x7f);
		ledLibExit();
		ledLibInit();
		ledRead(0xff);
		ledLibExit();
		}
	return 0;
}
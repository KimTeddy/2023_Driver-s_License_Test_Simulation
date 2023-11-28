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
	if (argc < 2 ){
		perror(" Args number is less than 2\n");
		doHelp();
		return 1;
	}

		ledLibInit();
		ledRead(argv[1]);
		ledLibExit();
	return 0;
}
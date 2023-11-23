#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "led.h"
static unsigned int ledValue = 0;
static int fd = 0;
unsigned int pdata=0;
int LEDdat;


int ledOnOff(int ledNum, int onOff) {
	int i = 1;
	i = i << ledNum;
	ledValue = ledValue & (~i);
	if (onOff != 0) ledValue |= i;
	LEDdat = write(fd, &ledValue, 4);
	return LEDdat;
}
int ledLibInit(void) {
	fd = open("/dev/periled", O_WRONLY);
	ledValue = 0;
	return fd;
}

int ledStatus(void) {
	return ledValue;
}

int ledLibExit(void) {
	ledValue = 0;
	ledOnOff(0, 0);
	close(fd);
	return 0;
}

int ledChange(const char data[]) {
	pdata = strtol(data, NULL, 16);
	//printf("LED Setup: 0x%X\n", pdata);

	for (int i = 0; i < 8; i++) {
		if (pdata & (0x01 << i)) {
			LEDdat = ledOnOff(i, 1);
			if (LEDdat != 4) 
				printf("setup error");
		}
		else {
			LEDdat = ledOnOff(i, 0);
			if (LEDdat != 4) 
				printf("setup error");
		}
	}
}

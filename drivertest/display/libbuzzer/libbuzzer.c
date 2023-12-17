#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include "libbuzzer.h"

//#define MAX_SCALE_STEP		8
#define BUZZER_BASE_SYS_PATH	"/sys/bus/platform/devices/"
#define BUZZER_FILENAME 		"peribuzzer"
#define BUZZER_ENABLE_NAME		"enable"
#define BUZZER_FREQUENCY_NAME	"frequency"


static char gBuzzerBaseSysDir[128];

const int musicScale[LAST_SCALE] =
{
	262, 	// do
	277,	// do+
	294,	// Re
	311,	// Re+
	330,	//E
	349,	//F
	370,	//F+
	392,	//G
	415,	//G+
	440,	//A
	466,	//A+
	494,  	//B
	2*262, 	// do
	2*277,	// do+
	2*294,	// Re
	2*311,	// Re+
	2*330,	//E
	2*349,	//F
	2*370,	//F+
	2*392,	//G
	2*415,	//G+
	2*440,	//A
	2*466,	//A+
	2*494,  	//B	
};

int findBuzzerSysPath(void)
{
}
void buzzerEnable(int bEnable)
{
}
void setFrequency(int scale) 
{
}
void libBuzzerInit(void)
{
}

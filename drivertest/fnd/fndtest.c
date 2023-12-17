#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "fnd.h"

void doHelp(void)
{
	printf("Usage:\n");
	printf("fndtest [option] [displaynum] [maxcounter]  >\n");
	printf("option   s  : static display  , displaynum range 0 ~ 999999\n");
	printf("option   t  ; time display  \n"); 
	printf("option   c  : count from 0 to maxcounter .\n");
	printf("option   o  : fnd off\n");
	printf("ex) fndtest s '123456'  ; display  '123456' \n");
	printf("ex) fndtest t 		;display current time \n");
	printf("ex) fndtest c 10 ; display counting number  from  0  to  10  with 1 Second interval.\n");
	printf("ex) fndtest 0		;display off \n");
}

#define ONE_SEG_DISPLAY_TIME_USEC	1000
// return 1 => success  , 0 => error

#define MODE_STATIC_DIS		0
#define MODE_TIME_DIS		1
#define MODE_COUNT_DIS		2

int main(int argc , char **argv)
{
	int mode ;
	int number,counter;
	
	if (argc <  2)
	{
		doHelp();
		return 1;
	}
	
	if ( argv[1][0] == 's'  )
	{
		mode = MODE_STATIC_DIS;
		if ( argc < 3 )
		{
			perror(" Args number is less than 3\n");
			doHelp();
			return 1;
		}
		number = atoi(argv[2]);
	}
	else if ( argv[1][0] == 't'  )
	{
		mode = MODE_TIME_DIS;
		if ( argc < 2 )
		{
			perror(" Args number is less than 2\n");
			doHelp();
			return 1;
		}
	}
	else if ( argv[1][0] == 'c'  )
	{
		mode = MODE_COUNT_DIS;
		if ( argc < 3 )
		{
			perror(" Args number is less than 3\n");
			doHelp();
			return 1;
		}
		number = atoi(argv[2]);
	}
	else if (argv[1][0] == 'o' )
	{
		fndOff();
		return 0; 
	}
	else
	{
		doHelp();
		perror("option error \n");
		return 1;
	}
	printf("number :%d\n",number);
	// open  driver 
	if (mode == MODE_STATIC_DIS )
	{
		fndDisp(number , 0);
	}
	else if(mode == MODE_TIME_DIS )
	{
		struct tm *ptmcur;
		time_t tTime;
		if ( -1 == time(&tTime) )
			return -1; 

		ptmcur = localtime(&tTime);

		number = ptmcur->tm_hour * 10000;
		number += ptmcur->tm_min *100;
		number += ptmcur->tm_sec;

		fndDisp(number , 0b1010);
		
	}
	else if (mode == MODE_COUNT_DIS)
	{
		counter = 0;

		while(1)
		{
			if (!fndDisp(counter , 0))
				break;

			counter++;
			sleep(1);
			if (counter > number )
				break;
		}

	}
	
	return 0;
}


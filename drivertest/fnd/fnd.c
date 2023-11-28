#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fnd.h"


typedef struct FNDWriteDataForm_tag 
{
	char	DataNumeric[FND_DATA_BUFF_LEN];
	char	DataDot[FND_DATA_BUFF_LEN];
	char	DataValid[FND_DATA_BUFF_LEN];	
}stFndWriteForm,*pStFndWriteForm;

int fnd(int number, char mode) {
	
	if (mode == MODE_STATIC_DIS ) {
	fndDisp(number , 0);
	}
	
	else if(mode == MODE_TIME_DIS ) {
		struct tm *ptmcur;
		time_t tTime;
	    if ( -1 == time(&tTime) )
			return -1;
		
		ptmcur = localtime(&tTime);
		number = ptmcur->tm_hour * 10000;
		number += ptmcur->tm_min *100;
		number += ptmcur->tm_sec;
		fndDisp(number , 0);
	}
	else if (mode == MODE_COUNT_DIS){
		int counter = 0;
	
		while(1){
			if (!fndDisp(counter , 0))
            break;
			
			counter++;
			sleep(1);
			if (counter > number ) break;
		}
	}
	return 0;
}

int fndDisp(int num , int dotflag) {
	int fd;
	int temp,i;
	stFndWriteForm stWriteData;
	
	for (i = 0; i < MAX_FND_NUM ; i++ ){
	stWriteData.DataDot[i] = (dotflag & (0x1 << i)) ? 1 : 0;
	stWriteData.DataValid[i] = 1;
	}
	// if 6 fnd
	temp = num % 1000000; stWriteData.DataNumeric[0]= temp /100000;
	temp = num % 100000; stWriteData.DataNumeric[1]= temp /10000;
	temp = num % 10000; stWriteData.DataNumeric[2] = temp /1000;
	temp = num %1000; stWriteData.DataNumeric[3] = temp /100;
	temp = num %100; stWriteData.DataNumeric[4] = temp /10;
	stWriteData.DataNumeric[5] = num %10;
	
	fd = open(FND_DRIVER_NAME,O_RDWR);
	if ( fd < 0 ){
	perror("driver open error.\n");
	return 0;
	}
	
	write(fd, &stWriteData, sizeof(stFndWriteForm));
	close(fd);
	return 1;
}

int fndOff()
{
	int fd,i;
	stFndWriteForm stWriteData;
	
	for (i = 0; i < MAX_FND_NUM ; i++ )
	{
		stWriteData.DataDot[i] =  0;  
		stWriteData.DataNumeric[i] = 0;
		stWriteData.DataValid[i] = 0;
	}
	fd = open(FND_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver open error.\n");
		return 0;
	}	
	write(fd,&stWriteData,sizeof(stFndWriteForm));
	close(fd);
	return 1;
}

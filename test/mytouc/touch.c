#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include "touch.h"

#define	INPUT_DEVICE_LIST	"/dev/input/event"
#define	PROBE_FILE			"/proc/bus/input/devices"
		
int probeTouchPath(char *newPath)
{	
	int returnValue = 0;
	int number = 0;
	#define HAVE_TO_FIND_1 "N: Name=\"WaveShare WaveShare Touchscreen\"\n"
	#define HAVE_TO_FIND_2 "H: Handlers=mouse0 event"
	
	FILE *fp = fopen(PROBE_FILE, "rt");
	while(!feof(fp)) //끝까지 읽어들인다.
  {
    char tmpStr[200]; //200자를 읽을 수 있게 버퍼
    fgets(tmpStr,200,fp); //최대 200자를 읽어봄
    //printf ("%s",tmpStr);

    if (strcmp(tmpStr,HAVE_TO_FIND_1) == 0)
    {
      printf("YES! I found!: %s\r\n", tmpStr);
      returnValue = 1; //찾음
    }

	if (
		(returnValue == 1) && //찾은 상태에서
		(strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0) //Event??을 찾았으면
    )
    {
      printf ("-->%s",tmpStr);
      printf("\t%c\r\n",tmpStr[strlen(tmpStr)-3]);
      number = tmpStr[strlen(tmpStr)-3] - '0'; 
      //Ascii character '0'-'9' (0x30-0x39) 
      //to interger(0)
      break;
    }
  }
  fclose(fp);
  if (returnValue == 1)
  sprintf (newPath,"%s%d",INPUT_DEVICE_LIST,number);
  return returnValue;
}

static pthread_t touchTh_id;
static int fd = 0;
static int msgID;

void *touchThFunc(void* args)
{
	int x = 0;
	int y = 0;
	struct input_event stEvent;
	BUTTON_MSG_S sendMsg;
	sendMsg.messageNum = 1;
	sendMsg.keyInput = 999;
	printf ("Touch Thread Ready\r\n");
	while (1)
	{
		read(fd, &stEvent, sizeof (stEvent));
		if (stEvent.type == EV_ABS)
		{
			// 뭔가 좌표값이 들어올것만 같다.
			if (stEvent.code == ABS_MT_POSITION_X)
			{
				x = stEvent.value;
				//printf ("you touch X : %d\r\n",stEvent.value);
			}
			else if (stEvent.code == ABS_MT_POSITION_Y)
			{
				y = stEvent.value;
				//printf ("you touch Y: %d\r\n",stEvent.value);
			}
		} 
		else if ( (stEvent.type == EV_KEY) && (stEvent.code==BTN_TOUCH) )
		{
			sendMsg.x = x;
			sendMsg.y = y;
			// 좌표 입력이 끝났다.
			if (stEvent.value == 0)
			{
				sendMsg.pressed = 0;
				//printf ("You finished Touch!\r\n");
			}
			else if (stEvent.value ==1)
			{
				sendMsg.pressed = 1;
				//printf ("You touch Now!\r\n");
			}
			msgsnd(msgID, &sendMsg, sizeof (BUTTON_MSG_S) - sizeof (long int), 0);
		}
		/*
		if ((stEvent.value == 0) && (stEvent.type == EV_KEY) )
		{
			//printf ("Key Unpressed: %d\r\n",stEvent.code);
			BUTTON_MSG_S newMsg;
			newMsg.messageNum = 1;
			newMsg.keyInput = stEvent.code;
			msgsnd(msgID, &newMsg, sizeof(BUTTON_MSG_S) - sizeof(long int), 0);
		}
		*/
	}
}


int touchInit(void)
{
	char touchPath[1024];
	if (probeTouchPath(touchPath) == 0)
	{
		printf ("Device Touch Open Failed\r\n");
		return 0;
	}
	fd=open (touchPath, O_RDONLY);
	msgID = msgget (MESSAGE_ID2, IPC_CREAT|0666);
	BUTTON_MSG_S trashCan;
	while (	msgrcv (msgID, &trashCan, sizeof(BUTTON_MSG_S) - sizeof(long int), 0, IPC_NOWAIT) >= 0	)
	{
		printf ("Cleaning Messages...\r\n");
	}
	pthread_create(&touchTh_id, NULL, touchThFunc, NULL);
	return 1;
}

int touchExit(void)
{
	pthread_cancel(touchTh_id);
}



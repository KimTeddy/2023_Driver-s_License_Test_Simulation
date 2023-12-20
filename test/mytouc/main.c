#include <sys/ipc.h>
#include <stdio.h>
#include "touch.h"

int main (void)
{
	touchInit();

	int msgID = msgget( MESSAGE_ID, IPC_CREAT|0666);
	BUTTON_MSG_T recvMsg;
	while (1)
	{
		msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		//이떄는 터치가 일어나거나 아니면 터리가 끝날때만 여기에 들어옴!
		switch (recvMsg.keyInput)
		{
			case 999:
				if (recvMsg.pressed == 1)
				{
/*
					if( recvMsg.x>410 && recvMsg.x<545 && recvMsg.y > 40 && recvMsg.y < 540 )
					//START
					{
						printf("START\r\n");
					}
					else if(recvMsg.x>600 && recvMsg.x<720 && recvMsg.y > 40 && recvMsg.y < 540)
					//Manual
					{
						printf("MANUAL\r\n");
					}
					else if(recvMsg.x>770 && recvMsg.x<900 && recvMsg.y > 40 && recvMsg.y < 540)
					//Leader Board
					{
						printf("LEADER BOARD\r\n");
					}
				}
			*/	
				{
					if (recvMsg.x <100 && recvMsg.y < 100)
					{
						printf ("You touched %d  %d\r\n", recvMsg.x, recvMsg.y);
					}
					else if (recvMsg.x > 500 && recvMsg.y < 100)
					{
						printf ("You touched %d  %d\r\n", recvMsg.x, recvMsg.y);
					}
					else if (recvMsg.x <100 && recvMsg.y>300)
					{
						printf ("You touched %d  %d\r\n", recvMsg.x, recvMsg.y);
					}
					else if (recvMsg.x > 500 && recvMsg.y > 300)
					{
						printf ("You touched %d  %d\r\n", recvMsg.x, recvMsg.y);
					}
					else
					{
						printf ("You touched anywhere... maybe center? :%d %d\r\n",recvMsg.x, recvMsg.y);
					}
				}
				
			break;
		}
	
	}
}

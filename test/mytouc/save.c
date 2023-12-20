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
			
				
/*
case(1)
int scBTN_Start = 0, scBTN_Manual = 0, scBTN_Leaderbd = 0; // 스크린터치로 인식할 시작/코스설명/리더보드 버튼 변수

case(2)
int scBTN_prevpage =0, scBTN_Nextpage = 0, scBTN_gotomain=0, scBTN_gotostart=0; // 메뉴얼 안에서 이전 이후 페
이지, 메인이동, 시작이동 버튼변수

case(3)
int scBTN_startup=0, scBTN_Wiper = 0, scBTN_Lightup =0, scBTN_Lightdown =0; 
// 스크린터치 버튼으로 감지할 변수들. (토글작동해야함)
*/
/*
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
*/
			break;
		}
	
	}

}


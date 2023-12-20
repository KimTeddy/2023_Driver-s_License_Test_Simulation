#include <sys/ipc.h>
#include <stdio.h>
#include "touch.h"

int main (void)
{
	touchInit();

	int first = 0;
	int second = 0;
	int third = 0;
	// 구간을 구분할 수 있도록 트리거를 설정.
	
	int scBTN_Start = 0;
	int scBTN_Manual = 0;
	int scBTN_Leaderbd = 0;
	//first 부분에서 동작하는 변수들


	int scBTN_prevpage = 0;
	int scBTN_Nextpage = 0;
	int scBTN_gotomain = 0;
	int scBTN_gotostart = 0;
	// second 부분에서 동작하는 변수들
	
	int scBTN_startup = 0;
	int scBTN_Wiper = 0;
	int scBTN_Lightup = 0;
	int scBTN_Lightdown = 0;
	//third 부분에서 동작하는 변수들

	int msgID = msgget( MESSAGE_ID, IPC_CREAT|0666);
	BUTTON_MSG_T recvMsg;
	while (1)
	{
		msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		//이떄는 터치가 일어나거나 아니면 터리가 끝날때만 여기에 들어옴!
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


		switch (recvMsg.keyInput)
		{
			case 999:
				if (recvMsg.pressed == 1)
				{
					if(first)
					{
						if( recvMsg.x>410 && recvMsg.x<545 && recvMsg.y > 40 && recvMsg.y < 540 )
						// START버튼 눌리면 start = 1로 설정
						{
							scBTN_Start = 1;
							printf("START\r\n");
						}
						else if(recvMsg.x>600 && recvMsg.x<720 && recvMsg.y > 40 && recvMsg.y < 540)
						//Manual 버튼 터치되면 Manual = 1로 설정
						{
							scBTN_Manual = 1;
							printf("MANUAL\r\n");
						}
						else if(recvMsg.x>770 && recvMsg.x<900 && recvMsg.y > 40 && recvMsg.y < 540)
						//Leader Board 버튼 터치되면 Leaderbd = 1로 설정
						{
							scBTN_Leaderbd = 1;
							printf("LEADER BOARD\r\n");
						}
					}

					}
					else if(second)
					{
						if(recvMsg.x > 670 && recvMsg.x < 750 && recvMsg.y > 50 && recvMsg.y < 530)
						{
							//Test start 버튼의 영역이 터치가 되면 Start = 1로 설정해주기
							scBTN_gotostart= 1;
							printf("Test Start\r\n");
							
						}
						else if(recvMsg.x > 787 && recvMsg.x < 846 && recvMsg.y > 400 && recvMsg.y < 530)
						{
							// MAIN SCREEN 버튼 영역 터치 디면 gotomain = 1로 설정
							scBTN_gotomain = 1;
							printf("Main Screen\r\n");
						}
						else if(recvMsg.x > 920 && recvMsg.x < 985 && recvMsg.y > 410 && recvMsg.y < 550)
						{
							//prev 화살표 버튼 눌리면 prevpage 1로 설정.
							scBTN_prevpage = 1;
							printf("Prev Page\r\n");
						}
						else if (recvMsg.x > 925 && recvMsg.x < 985 && recvMsg.y > 10 && recvMsg.y < 150)
						{
							//next 버튼 영역 터치되면 nextpage = 1로 설정
							scBTN_Nextpage = 1;
							printf("Next Page\r\n");
						}
						

					}
					else if(third)
					{
						if(recvMsg.x > 915 && recvMsg.x < 955 && recvMsg.y > 70 && recvMsg.y < 130)
						{
							//start_up 버튼의 영역이 터치가 되면 start_up = 1로 설정해주기
							scBTN_startup= 1;
							printf("Engine Start\r\n");
							
						}
						else if(recvMsg.x > 785 && recvMsg.x < 840 && recvMsg.y > 30 && recvMsg.y < 180)
						{
							// wiper 버튼 영역 터치 디면 wiper = 1로 설정
							scBTN_Wiper = 1;
							printf("Wiper\r\n");
						}
						else if(recvMsg.x > 787 && recvMsg.x < 846 && recvMsg.y > 400 && recvMsg.y < 530)
						{
							//lightup 버튼 눌리면 lightup = 1로 설정.
							scBTN_Lightup = 1;
							printf("High beam\r\n");
						}
						else if (recvMsg.x > 915 && recvMsg.x < 965 && recvMsg.y > 400 && recvMsg.y < 560)
						{
							//lightdown 버튼 영역 터치되면 lightdown = 1로 설정
							scBTN_Lightdown = 1;
							printf("Light down\r\n");
						}
					}

			break;
				}
	
		}

	}
}

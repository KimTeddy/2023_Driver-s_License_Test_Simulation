#include "textlcd.h"
#include "lcdtext.h"
#include "simuwork.h"
/*
#define CRS_MAIN 0  //메인 메뉴 단게
#define CRS_START 1 // 코스 시작 전 대기 (게임 시작 전 -> ~설명 단계~)
#define CRS_BASIC 2 //기본 조작 단계
#define CRS_UP 3    //경사로
#define CRS_JUNCTION 4  //교차로
#define CRS_PARKING 5   //주차
#define CRS_EMERGENCY 6 //돌발
#define CRS_ACCEL 7     //가속 구간
*/

//lcdtextwrite(str1, str2, lineFlag);
// lineflag 1 쓰면 두번 째 줄은 0으로 초기화, 1번째 줄에만 입력
// lineflag 2 쓰면 첫번 째 줄은 0으로 초기화, 2번째 줄에만 입력
// 네모는 0xff인가?
void crs_lcd()	//함수 이름 수정필요하면 하세요.
{
	char str_cnt[100];
  	int cnt = 0;
	txtlcd_Init();	//txtlcd 초기화
	while (1)
	{
		if(cnt >= 59)
		{
			cnt = 100;
		}
		else if(cnt >= 159)
		{
			cnt = 200;
		}
		else if(cnt >= 259)
		{
			cnt = 300;
		}
		else if(cnt >= 359)
		{
			cnt = 400;
		}
		else if(cnt >= 459)
		{
			cnt = 500;
		}
		else if(cnt >= 559)
		{
			cnt = 600;
		}
		else if(cnt >= 659)
		{
			cnt = 700
		}
		else if(cnt >= 759)
		{
			cnt = 800;
		}
		else if(cnt = 859)
		{
			cnt = 900;
		}
		else if(cnt >= 959)
		{
			cnt = 1000;
		}
		else if(cnt >= 1059)
		{
			cnt = 0;
		}
		
		cnt += 1;
		sprintf(str_cnt, "              %d", cnt);
		sleep(1);
		
		if (CRS_MAIN)
		{
		  	lcdtextwrite( "PRESS START", "CAR S", 1);
			lcdtextwrite( "PRESS START", str_cnt, 2);
 			// lcdtextwrite( "PRESS START", "CAR S", 2);
			//MAIN에서는 LCD 윗단에는 "PRESS START" 출력, 
			
		}
		else if (CRS_START)	
		{
			lcdtextwrite( "BEGIN         ", "CAR SI", 1);
			lcdtextwrite( "BEGIN         ", str_cnt, 2);
  			//lcdtextwrite( "BEGIN         ", "CAR SI", 2);
			//START부분에서는 윗단에 "" 출력,
			//아랫부분 네모 0개
		}
		else if (CRS_BASIC)
		{
			lcdtextwrite( "CAR COMPONENT", "CAR SIM", 1);
			lcdtextwrite( "CAR COMPONENT", str_cnt, 2);
  			//lcdtextwrite( "CAR COMPONENT", "CAR SIM", 2);
			//윗단에 "CAR COMPONENT"
			// 네모 2개
		}
		else if (CRS_UP)
		{
			lcdtextwrite( "UP HILL        ", "CAR SIMU", 1);
			lcdtextwrite( "UP HILL        ", str_cnt, 2);
  			//lcdtextwrite( "UP HILL        ", "CAR SIMU", 2);
			// 윗단에 "UP HILL" 
		}
		else if (CRS_JUNCTION)
		{
			lcdtextwrite( "JUNCTION   ", "CAR SIMUL", 1);
			lcdtextwrite( "JUNCTION   ", str_cnt, 2);
  			//lcdtextwrite( "JUNCTION   ", "CAR SIMUL", 2);
			// "JUNCTION"
		}
		else if (CRS_PARKING)
		{
			lcdtextwrite( "PARKING         ", "CAR SIMULA", 1);
			lcdtextwrite( "PARKING         ", str_cnt, 2);
  			//lcdtextwrite( "PARKING         ", "CAR SIMULA", 2);
			// "PARKING"
		}
		else if (CRS_EMERGENCY)
		{
			lcdtextwrite( "EMERGENCY         ", "CAR SIMULAT", 1);
			lcdtextwrite( "EMERGENCY         ", str_cnt, 2);
  			//lcdtextwrite( "EMERGENCY         ", "CAR SIMULAT", 2);
			// "EMERGENCY"
		}
		else if (CRS_ACCEL)
		{
			lcdtextwrite( "ACCELATE         ", "CAR SIMULATO", 1);
			lcdtextwrite( "ACCELATE         ", str_cnt, 2);
  			//lcdtextwrite( "ACCELATE         ", "CAR SIMULATO", 2);
			// "ACCELERATE"
		}
		else if (CRS_END)
		{
			lcdtextwrite( "END                  ", "CAR SIMULATOR", 1);
			lcdtextwrite( "END                  ", str_cnt, 2);
  			//lcdtextwrite( "END                  ", "CAR SIMULATOR", 2);
			// "END"
		}
	}

	txtlcd_Exit();	//게임 종료시 txtlcd도 꺼지도록 설정?
}


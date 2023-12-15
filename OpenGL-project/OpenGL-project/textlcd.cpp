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
	txtlcd_Init();	//txtlcd 초기화
	while (1)
	{
		if (CRS_MAIN)
		{
			lcdtextwrite( "PRESS START", , 1);
			lcdtextwrite( "PRESS START", "0xff", 2);
			//MAIN에서는 LCD 윗단에는 "PRESS START" 출력, 
			//아랫부분은 네모 0개
		}
		else if (CRS_START)	//시작 버튼이 눌리고 ~설명 부분~
		{
			lcdtextwrite( "", , 1);
			lcdtextwrite( , , 2);
			//START부분에서는 윗단에 "" 출력,
			//아랫부분 네모 0개
		}
		else if (CRS_BASIC)
		{
			lcdtextwrite( "CAR COMPONENT", , 1);
			//윗단에 "CAR COMPONENT"
			// 네모 2개
		}
		else if (CRS_UP)
		{
			lcdtextwrite( "UP HILL", , 1);
			// 윗단에 "UP HILL" 
			// 네모 4개
		}
		else if (CRS_JUNCTION)
		{
			lcdtextwrite( "JUNCION", , 1);
			// "JUNCTION"
			// 네모 6개
		}
		else if (CRS_PARKING)
		{
			lcdtextwrite( "PARKING", , 1);
			// "PARKING"
			// 네모 8개
		}
		else if (CRS_EMERGENCY)
		{
			lcdtextwrite( "CRS_EMERGENCY", , 1);
			// "EMERGENCY"
			// 네모 10개
		}
		else if (CRS_ACCEL)
		{
			lcdtextwrite( "ACCELERATE", , 1);
			// "ACCELERATE"
			// 네모 12개
		}
		else if (CRS_END)
		{
			lcdtextwrite( "END", , 1);
			// "END"
			// 네모 16개
		}
	}

	txtlcd_Exit();	//게임 종료시 txtlcd도 꺼지도록 설정?
}
#include "textlcd.h"

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

void crs_lcd()	//함수 이름 수정필요하면 하세요.
{
	while (1)
	{
		if (CRS_MAIN)
		{
			//MAIN에서는 LCD 윗단에는 "PRESS START" 출력, 
			//아랫부분은 네모 0개
		}
		else if (CRS_START)	//시작 버튼이 눌리고 ~설명 부분~
		{
			//START부분에서는 윗단에 "" 출력,
			//아랫부분 네모 0개
		}
		else if (CRS_BASIC)
		{
			//윗단에 "CAR COMPONENT"
			// 네모 2개
		}
		else if (CRS_UP)
		{
			// 윗단에 "UP HILL" 
			// 네모 4개
		}
		else if (CRS_JUNCTION)
		{
			// "JUNCTION"
			// 네모 6개
		}
		else if (CRS_PARKING)
		{
			// "PARKING"
			// 네모 8개
		}
		else if (CRS_EMERGENCY)
		{
			// "EMERGENCY"
			// 네모 10개
		}
		else if (CRS_ACCEL)
		{
			// "ACCELERATE"
			// 네모 12개
		}
		else if (CRS_END)
		{
			// "END"
			// 네모 16개
		}
	}

}
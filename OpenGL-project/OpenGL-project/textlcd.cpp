#include "textlcd.h"


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
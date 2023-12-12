#include "textlcd.h"
#include "lcdtext.h"
#include "simuwork.h"
/*
#define CRS_MAIN 0  //¸ÞÀÎ ¸Þ´º ´Ü°Ô
#define CRS_START 1 // ÄÚ½º ½ÃÀÛ Àü ´ë±â (°ÔÀÓ ½ÃÀÛ Àü -> ~¼³¸í ´Ü°è~)
#define CRS_BASIC 2 //±âº» Á¶ÀÛ ´Ü°è
#define CRS_UP 3    //°æ»ç·Î
#define CRS_JUNCTION 4  //±³Â÷·Î
#define CRS_PARKING 5   //ÁÖÂ÷
#define CRS_EMERGENCY 6 //µ¹¹ß
#define CRS_ACCEL 7     //°¡¼Ó ±¸°£
*/

void crs_lcd()	//ÇÔ¼ö ÀÌ¸§ ¼öÁ¤ÇÊ¿äÇÏ¸é ÇÏ¼¼¿ä.
{
	while (1)
	{
		if (CRS_MAIN)
		{
			//MAIN¿¡¼­´Â LCD À­´Ü¿¡´Â "PRESS START" Ãâ·Â, 
			//¾Æ·§ºÎºÐÀº ³×¸ð 0°³
		}
		else if (CRS_START)	//?œìž‘ ë²„íŠ¼???Œë¦¬ê³?~?¤ëª… ë¶€ë¶?
		{
			//STARTºÎºÐ¿¡¼­´Â À­´Ü¿¡ "" Ãâ·Â,

		}
		else if (CRS_BASIC)
		{
			//À­´Ü¿¡ "CAR COMPONENT"

		}
		else if (CRS_UP)
		{
			// À­´Ü¿¡ "UP HILL" 
			// ³×¸ð 4°³
		}
		else if (CRS_JUNCTION)
		{
			// "JUNCTION"
		}
		else if (CRS_PARKING)
		{
			// "PARKING"
		}
		else if (CRS_EMERGENCY)
		{
			// "EMERGENCY"
		}
		else if (CRS_ACCEL)
		{
			// "ACCELERATE"
		}
		else if (CRS_END)
		{
			// "END"
		}
	}

}
#include "lcdtext.h"

int main(){
  
  txtlcd_Init();
  //BASIC UP JUNCTION PARIKNG EMERGENCY ACCEL END
  int CRS_MAIN = 0;
  int CRS_START = 0;
  int CRS_BASIC = 0;
  int CRS_UP = 0;
  int CRS_JUNCTION = 0;
  int CRS_PARKING = 0;
  int CRS_EMERGENCY = 0;
  int CRS_ACCEL = 0;
  int CRS_END = 0;
  const char* str1 = "hello";
  const char* str2 = "embedded system";
  
  char str_cnt[100];
  int cnt = 0;
while (1)
	{
		if(cnt >= 59)
		{
			cnt = 100;
      CRS_MAIN = 1;
		}
		else if(cnt >= 159)
		{
			cnt = 200;
      CRS_MAIN = 0;
      CRS_START = 1;
		}
		else if(cnt >= 259)
		{
			cnt = 300;
      CRS_START = 0;
      CRS_BASIC = 1;
		}
		else if(cnt >= 359)
		{
			cnt = 400;
      CRS_BASIC = 0;
      CRS_UP = 1;
		}
		else if(cnt >= 459)
		{
			cnt = 500;
      CRS_UP = 0;
      CRS_JUNCTION = 1;
      CRS_PARKING = 0;
		}
		else if(cnt >= 559)
		{
			cnt = 600;
      CRS_PARKING = 1;
      CRS_EMERGENCY = 0;
    }
		else if(cnt >= 659)
		{
			cnt = 700;
      CRS_EMERGENCY = 1;
      CRS_ACCEL = 0;
		}
		else if(cnt >= 759)
		{
			cnt = 800;
      CRS_ACCEL = 1;
      CRS_END = 0;
		}
		else if(cnt = 859)
		{
			cnt = 900;
      CRS_END = 1;
		}
		else if(cnt >= 959)
		{
			cnt = 1000;
      CRS_END = 0;
		}
		else if(cnt >= 1059)
		{
			cnt = 0;
		}
		
		cnt += 1;
		sprintf(str_cnt, "              %d", cnt);
		usleep(500000);
		
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
  //9 단계로 나뉨 CAR SIMULATOR
 // txtlcd_off();
 // txtlcd_Init();
 // sleep(1);
 // lcdtextwrite(str1, str2,0);

  return 0;
}

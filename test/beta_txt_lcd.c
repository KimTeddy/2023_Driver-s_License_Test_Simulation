#include "lcdtext.h"
#include <pthread.h>

  char* str1 = "hello";
  const char* str2 = "embedded system";
  
  char str_cnt0[10];
  char str_cnt1[10];
  char str_cnt2[10];
  char str_cnt3[10];
  char str_cnt[100];

  int cnt[5] = {0,};
  pthread_t tid[2];


void *txtdisplay()
  {
    while (1)
    {
     	if (CRS_MAIN)
		  {
        str1 = "PRESS START";
		   //  lcdtextwrite( "PRESS START", "CAR S", 1);
			 //  lcdtextwrite( "PRESS START", str_cnt, 2);
 			  // lcdtextwrite( "PRESS START", "CAR S", 2);
			  //MAIN에서는 LCD 윗단에는 "PRESS START" 출력, 
  
	  	}
		  else if (CRS_START)	
		  {
        str1 = "BEGIN         ";
		   //	lcdtextwrite( "BEGIN         ", "CAR SI", 1);
		   //	lcdtextwrite( "BEGIN         ", str_cnt, 2);
  	  		//lcdtextwrite( "BEGIN         ", "CAR SI", 2);
		  	//START부분에서는 윗단에 "" 출력,
		  	//아랫부분 네모 0개
		  }
		  else if (CRS_BASIC)
		  {
        str1 = "CAR COMPONENT";        
		   //	lcdtextwrite( "CAR COMPONENT", "CAR SIM", 1);
		   //	lcdtextwrite( "CAR COMPONENT", str_cnt, 2);
  	  		//lcdtextwrite( "CAR COMPONENT", "CAR SIM", 2);
		  	//윗단에 "CAR COMPONENT"
		  	// 네모 2개
		  }
		  else if (CRS_UP)
		  {
        str1 = "UP HILL        ";   
		   //	lcdtextwrite( "UP HILL        ", "CAR SIMU", 1);
		   //	lcdtextwrite( "UP HILL        ", str_cnt, 2);
  	  		//lcdtextwrite( "UP HILL        ", "CAR SIMU", 2);
		  	// 윗단에 "UP HILL" 
		  }
		  else if (CRS_JUNCTION)
		  {
        str1 = "JUNCTION   ";   
	  	 //	lcdtextwrite( "JUNCTION   ", "CAR SIMUL", 1);
	  	 //	lcdtextwrite( "JUNCTION   ", str_cnt, 2);
    			//lcdtextwrite( "JUNCTION   ", "CAR SIMUL", 2);
	  		// "JUNCTION"
	  	}
	  	else if (CRS_PARKING)
	  	{
        str1 = "PARKING         ";
	     //	lcdtextwrite( "PARKING         ", "CAR SIMULA", 1);
			 //  lcdtextwrite( "PARKING         ", str_cnt, 2);
  			//lcdtextwrite( "PARKING         ", "CAR SIMULA", 2);
			  // "PARKING"
		  }
		  else if (CRS_EMERGENCY)
		  {
        str1 = "EMERGENCY         ";
		  // 	lcdtextwrite( "EMERGENCY         ", "CAR SIMULAT", 1);
		   //	lcdtextwrite( "EMERGENCY         ", str_cnt, 2);
  	  		//lcdtextwrite( "EMERGENCY         ", "CAR SIMULAT", 2);
		  	// "EMERGENCY"
		  }
		  else if (CRS_ACCEL)
		  {
        str1 = "ACCELATE         ";
		   //	lcdtextwrite( "ACCELATE         ", "CAR SIMULATO", 1);
		  // 	lcdtextwrite( "ACCELATE         ", str_cnt, 2);
  	  		//lcdtextwrite( "ACCELATE         ", "CAR SIMULATO", 2);
		  	// "ACCELERATE"
		  }
		  else if (CRS_END)
		  {
        str1 = "END                  ";
		  //	lcdtextwrite( "END                  ", "CAR SIMULATOR", 1);
		  //	lcdtextwrite( "END                  ", str_cnt, 2);
  	  		//lcdtextwrite( "END                  ", "CAR SIMULATOR", 2);
		  	// "END"
		  }
    }
  } 

void *count()
  {
    while (1)
	  {
      //cnt += 1;
		  sprintf(str_cnt0, "%d", cnt[0]);
      sprintf(str_cnt1, "%d", cnt[1]);
      sprintf(str_cnt2, "%d", cnt[2]);
      sprintf(str_cnt3, "%d", cnt[3]);
      sprintf(str_cnt, "           %d %d%d",  cnt[2], cnt[1], cnt[0]);
		  usleep(50000);
      
      lcdtextwrite( str1, str_cnt, 1);
	    lcdtextwrite( str1, str_cnt, 2);

        
if (cnt[0] == 9) 
{
    cnt[0] = 0;
    cnt[1]++;
} 
else 
{
    cnt[0]++;
}
 // 10초 단위 검사 
               

   	if (CRS_MAIN)
		  {
        str1 = "PRESS START";
		   //  lcdtextwrite( "PRESS START", "CAR S", 1);
			 //  lcdtextwrite( "PRESS START", str_cnt, 2);
 			  // lcdtextwrite( "PRESS START", "CAR S", 2);
			  //MAIN에서는 LCD 윗단에는 "PRESS START" 출력, 
  
	  	}
		  else if (CRS_START)	
		  {
        str1 = "BEGIN         ";
		   //	lcdtextwrite( "BEGIN         ", "CAR SI", 1);
		   //	lcdtextwrite( "BEGIN         ", str_cnt, 2);
  	  		//lcdtextwrite( "BEGIN         ", "CAR SI", 2);
		  	//START부분에서는 윗단에 "" 출력,
		  	//아랫부분 네모 0개
		  }
		  else if (CRS_BASIC)
		  {
        str1 = "CAR COMPONENT";        
		   //	lcdtextwrite( "CAR COMPONENT", "CAR SIM", 1);
		   //	lcdtextwrite( "CAR COMPONENT", str_cnt, 2);
  	  		//lcdtextwrite( "CAR COMPONENT", "CAR SIM", 2);
		  	//윗단에 "CAR COMPONENT"
		  	// 네모 2개
		  }
		  else if (CRS_UP)
		  {
        str1 = "UP HILL        ";   
		   //	lcdtextwrite( "UP HILL        ", "CAR SIMU", 1);
		   //	lcdtextwrite( "UP HILL        ", str_cnt, 2);
  	  		//lcdtextwrite( "UP HILL        ", "CAR SIMU", 2);
		  	// 윗단에 "UP HILL" 
		  }
		  else if (CRS_JUNCTION)
		  {
        str1 = "JUNCTION   ";   
	  	 //	lcdtextwrite( "JUNCTION   ", "CAR SIMUL", 1);
	  	 //	lcdtextwrite( "JUNCTION   ", str_cnt, 2);
    			//lcdtextwrite( "JUNCTION   ", "CAR SIMUL", 2);
	  		// "JUNCTION"
	  	}
	  	else if (CRS_PARKING)
	  	{
        str1 = "PARKING         ";
	     //	lcdtextwrite( "PARKING         ", "CAR SIMULA", 1);
			 //  lcdtextwrite( "PARKING         ", str_cnt, 2);
  			//lcdtextwrite( "PARKING         ", "CAR SIMULA", 2);
			  // "PARKING"
		  }
		  else if (CRS_EMERGENCY)
		  {
        str1 = "EMERGENCY         ";
		  // 	lcdtextwrite( "EMERGENCY         ", "CAR SIMULAT", 1);
		   //	lcdtextwrite( "EMERGENCY         ", str_cnt, 2);
  	  		//lcdtextwrite( "EMERGENCY         ", "CAR SIMULAT", 2);
		  	// "EMERGENCY"
		  }
		  else if (CRS_ACCEL)
		  {
        str1 = "ACCELATE         ";
		   //	lcdtextwrite( "ACCELATE         ", "CAR SIMULATO", 1);
		  // 	lcdtextwrite( "ACCELATE         ", str_cnt, 2);
  	  		//lcdtextwrite( "ACCELATE         ", "CAR SIMULATO", 2);
		  	// "ACCELERATE"
		  }
		  else if (CRS_END)
		  {
        str1 = "END                  ";
		  //	lcdtextwrite( "END                  ", "CAR SIMULATOR", 1);
		  //	lcdtextwrite( "END                  ", str_cnt, 2);
  	  		//lcdtextwrite( "END                  ", "CAR SIMULATOR", 2);
		  	// "END"
		  }
  }
}
  

int main()
{
  
  txtlcd_Init();
  //BASIC UP JUNCTION PARIKNG EMERGENCY ACCEL END

  pthread_create(&tid[0], NULL ,&count, NULL);
  pthread_create(&tid[1], NULL ,&txtdisplay, NULL);

  pthread_join (tid[0], NULL);
  pthread_join (tid[1], NULL);

	return 0;

}
  //9 단계로 나뉨 CAR SIMULATOR
 // txtlcd_off();
 // txtlcd_Init();
 // sleep(1);
 // lcdtextwrite(str1, str2,0);

  


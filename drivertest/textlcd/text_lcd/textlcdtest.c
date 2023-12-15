#include "lcdtext.h"

int main(){
  
  const char* str1 = "hello";
  const char* str2 = "embedded system";
  txtlcd_Init();
  lcdtextwrite( " ", "0xff", 1);
  sleep(1);
  lcdtextwrite( "PRESS START", "CAR S", 2);
  sleep(1);
  lcdtextwrite( "BEGIN", "CAR SI", 2);
  sleep(1);
  lcdtextwrite( "CAR COMPONENT", "CAR SIM", 2);
    sleep(1);
  lcdtextwrite( "UP HILL", "CAR SIMU", 2);
    sleep(1);
  lcdtextwrite( "JUNCTION", "CAR SIMUL", 2);
    sleep(1);
  lcdtextwrite( "PARKING", "CAR SIMULA", 2);
    sleep(1);
  lcdtextwrite( "EMERGENCY", "CAR SIMULAT", 2);
    sleep(1);
  lcdtextwrite( "ACCELATE", "CAR SIMULATO", 2);
    sleep(1);
  lcdtextwrite( "END", "CAR SIMULATOR", 2);

  //9 단계로 나뉨 CAR SIMULATOR
 // txtlcd_off();
 // txtlcd_Init();
 // sleep(1);
 // lcdtextwrite(str1, str2,0);

  return 0;
}

#include "lcdtext.h"

int main(){
  
  const char* str1 = "hello";
  const char* str2 = "embedded system";
  
  char str_cnt[100];
  int cnt = 0;
  while(1)
  {

    
    sprintf(str_cnt, "              %d", cnt);
    txtlcd_Init();
    lcdtextwrite( "PRESS START", "CAR S", 1);
    lcdtextwrite( "PRESS START", str_cnt, 2);
    sleep(1);
    cnt += 1;
    sprintf(str_cnt, "              %d", cnt);
    lcdtextwrite( "BEGIN         ", "CAR SI", 1);
    lcdtextwrite( "BEGIN         ", str_cnt, 2);
    sleep(1);
    cnt += 1;
    sprintf(str_cnt, "              %d", cnt);
    lcdtextwrite( "CAR COMPONENT", "CAR SIM", 1);
    lcdtextwrite( "CAR COMPONENT", str_cnt, 2);
    sleep(1);
    cnt += 1;
    sprintf(str_cnt, "              %d", cnt);
    lcdtextwrite( "UP HILL        ", "CAR SIMU", 1);
    lcdtextwrite( "UP HILL        ", str_cnt, 2);
    sleep(1);
    cnt += 1;
    sprintf(str_cnt, "              %d", cnt);
    lcdtextwrite( "JUNCTION   ", "CAR SIMUL", 1);
    lcdtextwrite( "JUNCTION   ", str_cnt, 2);
    sleep(1);
    cnt += 1;
    sprintf(str_cnt, "              %d", cnt);
    lcdtextwrite( "PARKING         ", "CAR SIMULA", 1);
    lcdtextwrite( "PARKING         ", str_cnt, 2);
    sleep(1);
    cnt += 1;
    sprintf(str_cnt, "              %d", cnt);
    lcdtextwrite( "EMERGENCY         ", "CAR SIMULAT", 1);
    lcdtextwrite( "EMERGENCY         ", str_cnt, 2);
    sleep(1);
    cnt += 1;
    sprintf(str_cnt, "              %d", cnt);
    lcdtextwrite( "ACCELATE         ", "CAR SIMULATO", 1);
    lcdtextwrite( "ACCELATE         ", str_cnt, 2);
    sleep(1);
    cnt += 1;
    sprintf(str_cnt, "              %d", cnt);
    lcdtextwrite( "END                  ", "CAR SIMULATOR", 1);
    lcdtextwrite( "END                  ", str_cnt, 2);
    sleep(1);
    cnt += 1;
    sprintf(str_cnt, "              %d", cnt);
 }
  //9 단계로 나뉨 CAR SIMULATOR
 // txtlcd_off();
 // txtlcd_Init();
 // sleep(1);
 // lcdtextwrite(str1, str2,0);

  return 0;
}

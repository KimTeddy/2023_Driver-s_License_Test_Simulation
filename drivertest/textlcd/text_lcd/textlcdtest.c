#include "lcdtext.h"

int main(){
  
  const char* str1 = "hello";
  const char* str2 = "embedded system";
  txtlcd_Init();
  lcdtextwrite(str1, str2,1);
  sleep(1);
  lcdtextwrite(str1, str2,2);
 // txtlcd_off();
 // txtlcd_Init();
 // sleep(1);
 // lcdtextwrite(str1, str2,0);

  return 0;
}

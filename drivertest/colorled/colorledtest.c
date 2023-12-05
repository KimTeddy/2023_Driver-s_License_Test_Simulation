#include "colorled.h"

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        printf("ERR\r\n");
       printf("colorledtest RED GREEN BLUE\r\n");
       printf("ex) ./colorledtest 0~100 0~100 0~100\r\n");

        return 0;
    }
     
    
    pwmLedInit();
    
    //pwmSetPercent(atoi(argv[1]), 0);
     
    //pwmSetPercent(atoi(argv[2]), 1);
    
    //pwmSetPercent(atoi(argv[3]), 2);
    // argv로 받은 R,G,B값으로 LED를 On.
    while(1)
    {
        printf("Color showing\n");
    //빨
    pwmSetPercent(100, 0);
    pwmSetPercent(0, 1);
    pwmSetPercent(0, 2);
    sleep(1);

    //주
    pwmSetPercent(100, 0);
    pwmSetPercent(50, 1);
    pwmSetPercent(0, 2);
    sleep(1);

    //노
    pwmSetPercent(100, 0);
    pwmSetPercent(100, 1);
    pwmSetPercent(50, 2);
    sleep(1);

    //초
    pwmSetPercent(0, 0);
    pwmSetPercent(100, 1);
    pwmSetPercent(0, 2);
    sleep(1);

    //파
    pwmSetPercent(0, 0);
    pwmSetPercent(50, 1);
    pwmSetPercent(100, 2);
    sleep(1);

    //남
    pwmSetPercent(0, 0);
    pwmSetPercent(0, 1);
    pwmSetPercent(100, 2);
    sleep(1);

    //보
    pwmSetPercent(50, 0);
    pwmSetPercent(0, 1);
    pwmSetPercent(100, 2);
    sleep(1);

    //흰
    pwmSetPercent(100, 0);
    pwmSetPercent(100, 1);
    pwmSetPercent(100, 2);
    sleep(1);

    }
    pwmInactiveAll();
    return 0;
}
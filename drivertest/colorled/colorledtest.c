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
    
    pwmSetPercent(atoi(argv[1]), 0);
    // 
    pwmSetPercent(atoi(argv[2]), 1);
    //
    pwmSetPercent(atoi(argv[3]), 2);
    //
    pwmInactiveAll();

    return 0;
}
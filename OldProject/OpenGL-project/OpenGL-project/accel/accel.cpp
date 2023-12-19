#ifdef __LINUX
#include "accel.h"
#include "simuwork.h"


/*
왼쪽으로 기울이면 ACCEl 값(fisrt_accel[0]) -
오른쪽으로 기울이면 + 정도에 따라 +- 되는 값에 차이는 있음.
뒤로 기울이면 ACCEL z값(first_accel[2])이 수평으로 들었을 경우보다 -값으로 변함.
앞으로 기울이면 ACCEL z값이 +값으로 변함.

*/
void accel()
{
     int first_accel[3];
    int second_accel[3];
    printf("Set Default Value\n");
    getAccel(first_accel);

    while(simuwork == CRS_END) //게임 끝날 때 까지 반복
    {        
        
        getAccel(second_accel);
       // printf("Set Changing Value\n");
        if( first_accel[0] - second_accel[0] > 5000 ) 
        { //왼쪽으로 기운 경우 차이가 5000이상 나면 
            
            // ~ 차 방향을 오른쪽으로 바꾸는 코드 ~
            printf(" Turn Right \n");
            sleep(1);
            
        }
        else if(second_accel[0] - first_accel[0] > 5000)
        { //오른쪽으로 기운 경우 [차이가 5000이상 나면]

            // ~ 차 방향을 왼쪽으로 바꾸는 코드 ~
            printf(" Turn Left \n");
            sleep(1);
        }
        else if( first_accel[2] - second_accel[2] > 4000 && first_accel[2] - second_accel[2] < 8000 )
        { // 뒤로 기울인 경우

            // ~ 차 속도를 감소하는 코드?
            printf(" Slow Down \n");
            sleep(1);
 
        }
        else if( first_accel[2] - second_accel[2] > 8000 )
            { // 뒤로 기울인 각도가 큰 경우 (돌발에서 급 브레이크 밟은 경우)
                // ~ 차 멈추는 코드 ~
                printf(" Stop \n");
                sleep(1);
            }
        
        else if( second_accel[2] - first_accel[2] > 4000 && second_accel[2] - first_accel[2] < 8000)
        { // 앞으로 기울인 경우

            // ~차가 앞으로 진행하는 코드 ~
            printf(" Speed Up \n");
            sleep(1);
        }
        else if( second_accel[2] - first_accel[2] > 8000 )
            { // 앞으로 많이 기울인 경우 (가속 구간에서 가속)
                // ~ 차 속도를 빠르게 ~
                printf(" Speed UpUp \n");
                sleep(1);
            }
        usleep(1);
    }
}

#endif
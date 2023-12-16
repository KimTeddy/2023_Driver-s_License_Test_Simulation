#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "accelMagGyro.h"

const double RADIAN_TO_DEGREE = 180.0 / 3.141592;

int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
double angle_x, angle_y, angle_z;
double angle[3];

void calcAngle() // 각도 계산
{
    getAccel(angle);

    AcX = angle[0];
    AcY = angle[1];
    AcZ = angle[2];

    //AcX = angle[0] << 8 | angle[0];
    //AcY = angle[1] << 8 | angle[1];
    //AcZ = angle[2] << 8 | angle[2];
    
   // printf("Accel : %d %d %d \n", angle[0], angle[1], angle[2]);
   // printf("Accel : %d %d %d \n", AcX, AcY, AcZ);

    angle[1] = atan(-AcX / sqrt( pow(AcY, 2) + pow(AcZ, 2) ));
  //  printf("\nAngle x : %d , Angle y :%d \n", angle[0], angle[1]);
    angle[1] *= RADIAN_TO_DEGREE;
    angle[0] = atan(AcY/ sqrt( pow(AcX, 2) + pow(AcZ, 2) ));
  //  printf("\nAngle x : %d , Angle y :%d \n", angle[0], angle[1]);
    angle[0] *= RADIAN_TO_DEGREE; 
  //  printf("\nAngle x : %d , Angle y :%d \n", angle[0], angle[1]);
}


int main(void)
{
    int accel[3];
    int magnet[3];
    int gyro[3];
    double ang;
    int first_accel[3];
    int second_accel[3];
    printf("Set Default Value\n");
    getAccel(first_accel);

    while(1) //game이 끝날 때 까지 second_accel값 받아서 기울기 계산
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
        else if( first_accel[2] - second_accel[2] > 5000 )
        { // 뒤로 기울인 경우

            // ~ 차 속도를 감소하는 코드?
            printf(" Slow Down \n");
            sleep(1);
            if( first_accel[2] - second_accel[2] > 10000 )
            { // 뒤로 기울인 각도가 큰 경우 (돌발에서 급 브레이크 밟은 경우)
                // ~ 차 멈추는 코드 ~
                printf(" Stop \n");
                sleep(1);
            }
        }
        else if( second_accel[2] - first_accel[2] > 5000 )
        { // 앞으로 기울인 경우

            // ~차가 앞으로 진행하는 코드 ~
            printf(" Speed Up \n");
            sleep(1);
            if( second_accel[2] - first_accel[2] > 10000 )
            { // 앞으로 많이 기울인 경우 (가속 구간에서 가속)
                // ~ 차 속도를 빠르게 ~
                printf(" Speed UpUp \n");
                sleep(1);
            }
        }
        usleep(1);
    }
       return 0;
    }
 

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
//
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
    int moving;
    int moving_l;
    int moving_r;
    printf("Set Default Value\n");
    getAccel(first_accel);

    while(1) //game이 끝날 때 까지 second_accel값 받아서 기울기 계산
    {        // 나중에 1 대신 트리거 변수로 바꾸기.
        
            getAccel(second_accel);
            // printf("Set Changing Value\n");
            if( first_accel[0] - second_accel[0] > 5000 ) 
            { //왼쪽으로 기운 경우 차이가 5000이상 나면 
            
                // ~ 차 방향을 왼쪽으로 바꾸는 코드 ~//
                //rcar += 3; printf("r=%d\n", rcar); break;  왼쪽으로 기울이고 있는 동안 왼쪽으로 이동하도록
                //왼쪽이 +3
                printf("  Handle Turn Left \n");
                moving_l = 1;
                sleep(1);
            
            }

            else if(second_accel[0] - first_accel[0] > 5000)
            { //오른쪽으로 기운 경우 [차이가 5000이상 나면]

                // ~ 차 방향을 오른쪽으로 바꾸는 코드 ~
                //오른쪽이 -3
                // rcar -= 3; printf("r=%d\n", rcar); break; // 오른쪽으로 기울이고 있는 동안 오른쪽으로 이동하도록
                printf(" Handle Turn Right \n");
                moving_r = 1;
                sleep(1);
            }

            else if( !(first_accel[0] - second_accel[0] > 5000) || !(second_accel[0] - first_accel[0] > 5000))
            {
              // 핸들이 정위치면 moving_l,r을 0으로 설정.
                moving_l = 0;
                moving_r = 0;    

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
                    moving -= 3;
                    sleep(1);
                }
        
            else if( second_accel[2] - first_accel[2] > 4000 && second_accel[2] - first_accel[2] < 8000)
            {// 앞으로만 기울인 경우 [  가속도 센서의 z값이 바뀜  ]

                // ~차가 앞으로 진행하는 코드 ~
            
                moving = 1;

                /*speed = 1;  //조금만 기울인 경우 speed = 1;
                dxcar = speed * cos((180-rcar) * PI / 180.0); xcar += dxcar;
                dycar = speed * sin((180-rcar) * PI / 180.0); ycar += dycar;
                break;
                */
                printf(" Car Moving Forward \n");
                sleep(1);
            }

            else if( second_accel[2] - first_accel[2] > 8000 )
                { // 앞으로 많이 기울인 경우 (가속 구간에서 가속)
                    // ~ 차 속도를 빠르게 ~

                    moving += 2;   
                    /*
                    speed = 2;  //많이 기울인 경우 speed = 2로 설정하여 가속
                    dxcar = speed * cos((180-rcar) * PI / 180.0); xcar += dxcar;
                    dycar = speed * sin((180-rcar) * PI / 180.0); ycar += dycar;
                    break; 
                    */
                    printf(" Car Accelation! \n");
                    sleep(1);
                }
                /*
            else if(first_accel[0] - second_accel[0] > 5000 && second_accel[2] - first_accel[2] > 4000 && second_accel[2] - first_accel[2] < 8000) 
            { 
                printf(" Going Left! \n");
                sleep(1);
                //앞으로 기울인 상태에서 왼쪽으로 기울이면 악셀 + 핸들 왼쪽을 돌리면 옆으로 같이 진행하도록
                
                /*
                rcar += 3;
                speed = 1;  //조금만 기울인 경우 speed = 1;
                dxcar = speed * cos((180-rcar) * PI / 180.0); xcar += dxcar;
                dycar = speed * sin((180-rcar) * PI / 180.0); ycar += dycar;
                break;
                

            }
            else if(second_accel[0] - first_accel[0] > 5000 && second_accel[2] - first_accel[2] > 4000 && second_accel[2] - first_accel[2] < 8000) 
            { 
                printf(" Going Right! \n");
                sleep(1);
                //앞으로 기울인 상태에서 오른쪽으로 기울이면 ==> 악셀 + 핸들 오른쪽을 돌리면 옆으로 같이 진행하도록
                
                /*
                rcar -= 3;
                speed = 1;  //조금만 기울인 경우 speed = 1;
                dxcar = speed * cos((180-rcar) * PI / 180.0); xcar += dxcar;
                dycar = speed * sin((180-rcar) * PI / 180.0); ycar += dycar;
                break;
                */

    }
            usleep(1);
            
            return 0;
}
       
    
 

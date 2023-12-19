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
    int moving, moving_l, moving_r;
    int first_accel[3];
    int second_accel[3];
    // CRS로 값 받을 수 있으면 아래 두 문장 지우기, if문 아래 3문장 살리기
    printf("Set Default Value\n");
    getAccel(first_accel);



    /*
    동작원리
    -> 맨 처음에 CRS_START가 되면 사용자가 평벙하게 들고있을 때 키트의 가속도 센서 값을 받아와서 first_accel에 저장함.
    그리고 게임이 시작된 후 second_accel의 값을 계속읽어들이면서 first_accel과 비교함 first_accel과 second_accel을 비교하여
    키트가 어느 방향으로 기울여졌는지 확인하여 자동차를 움직일 수 있게함.
    앞으로 기울였다면 자동차가 앞으로 진행하고 기울인 정도가 크지 않다면 자동차는 정지 상태임 ?
    좌, 우로 기울인 상태에서는 좌, 우로 자동차가 진행하고
    *앞으로 많이 기울인 상태에서(가속 구간 speed = 2인 구간) 키트를 갑자기 뒤로 기울이면? 급브레이크 하는 것처럼 자동차가 멈추게?

    */
    if(simuwork != CRS_MAIN || CRS_MANUAL)
    //CRS_MAIN 또는 CRS_MANUAL 상태가 아니면 가속도 센서 값 받아서 핸들로서 동작 시작
    {
        //printf("Set Default Value Plz hold it for a Sec\n");
        //sleep(1);
        //getAccel(first_accel);

        while(simuwork == CRS_END) //게임 끝날 때 까지 반복
        {       
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
                    usleep(1);
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
                usleep(3);
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
                    usleep(0.5);
                }
/*
            else if(first_accel[0] - second_accel[0] > 5000 && second_accel[2] - first_accel[2] > 4000 && second_accel[2] - first_accel[2] < 8000) 
            { 
                printf(" Going Left! \n");
                sleep(1);
                //앞으로 기울인 상태에서 왼쪽으로 기울이면 악셀 + 핸들 왼쪽을 돌리면 옆으로 같이 진행하도록
                
                
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
                

            }
*/
            usleep(1);
            //만약 moving 변수에 따라서 usleep 시간 달라지는거면 여 아래에 추가하자.
        }
    }

}



#endif


/*
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q': case 'Q': exit(0); break;     //q버튼 누르면 종료
    case 'r': case 'R': glClearColor(1.0, 0.0, 0.0, 1.0); break;    // r누르면  배경색 빨간색으로?
    case 'w':
        /*acceration = true;
        if (speed < 5)
            speed += 0.1f;
        else speed = 0;
        dspeed += speed;
        speed = 1;
        dxcar = speed * cos((180-rcar) * PI / 180.0); xcar += dxcar;
        dycar = speed * sin((180-rcar) * PI / 180.0); ycar += dycar;
        break;
    case 's':
        //screen_dump();
        //ScreenCapture("strFilePath.bmp"); 
        break;
    case 'a': rcar += 3; printf("r=%d\n", rcar); break;     왼쪽으로 이동
    case 'd': rcar -= 3; printf("r=%d\n", rcar); break;     //오른쪽으로 이동
    }
    if (rcar >= 360 || rcar <= -360) rcar = 0;  // 좌,우로 자동차 방향을 수정할 때 360도 되면 0으로 바꿔줌
    glutPostRedisplay();
}
*/



/*
void keyboard(unsigned char key, int x, int y) {
    float dxcar, dycar;
    switch (key) {
    case 'a':   //왼쪽
        rcar += 3.0;
        printf("rcar=%f\n", rcar);
        break;
    case 'd':   오른쪽
        rcar -= 3.0;
        printf("rcar=%f\n", rcar);
        break;

    case 'w':   전진
        // 'w' 키를 누르면 현재 방향으로 앞으로 이동
        speed = 1;
        dxcar = speed * cos((180 - rcar) * PI / 180.0);
        dycar = speed * sin((180 - rcar) * PI / 180.0);
        xcar += dxcar;
        ycar += dycar;

        xcar_A = xcar - 5; ycar_A = ycar - 2;
        xcar_B = xcar - 5; ycar_B = ycar + 2;
        xcar_C = xcar + 5; ycar_C = ycar + 2;
        xcar_D = xcar + 5; ycar_D = ycar - 2;
    }
    if (rcar >= 360 || rcar <= -360) rcar = 0;
    glutPostRedisplay();
}

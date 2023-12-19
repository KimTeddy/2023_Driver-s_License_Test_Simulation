#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <sys/shm.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <string.h>
#include <linux/input.h>
#include <sys/msg.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/kd.h>
#include <math.h>

#include "button.h"
#include "now_level_defs.h"
#include "buzzer_soundeffect_defs.h"

#define accel_t 500000

const double RADIAN_TO_DEGREE = 180.0 / 3.141592;
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
double angle_x, angle_y, angle_z;
double angle[3];


pthread_t thread_object_1;  // 스레드 1 for rgb led
pthread_t thread_object_2;  // 스레드 2 for btn and led
pthread_t thread_object_2x; // 스레드 2x for led blink
// pthread_t thread_object_3; //스레드 3 for 7segment
pthread_t thread_object_4; // 스레드 4 for echo state(imsi)
pthread_t thread_object_5; // 스레드 5 for lcd bitmap output
pthread_t thread_object_6; // 스레드 6 for lcd overlay output
pthread_t thread_object_7; // 스레드 7 for accel work

// pthread_mutex_t lock1; // for traflight
// pthread_mutex_t lock2; // for  btnstate

int scBTN_Start = 0, scBTN_Manual = 0, scBTN_Leaderbd = 0; // 스크린터치로 인식할 시작/코스설명/리더보드 버튼 변수
int scBTN_prevpage =0, scBTN_Nextpage = 0, scBTN_gotomain=0, scBTN_gotostart=0; // 메뉴얼 안에서 이전 이후 페이지, 메인이동, 시작이동 버튼변수
int scBTN_startup=0, scBTN_Wiper = 0, scBTN_Lightup =0, scBTN_Lightdown =0; // 스크린터치 버튼으로 감지할 변수들. (토글작동해야함)
int maunalpage = 0;                                        // 코스 설명 이미지 페이지 카운팅
int testStart = 0, mainScreen = 0;

int now_level = CRS_MAIN;
// LCD에 구간 표시하기 위한 트리거 신호들
// int crs_basic = 0;     // 기본조작평가 트리거 신호
// int crs_uphill = 0;    // 경사로 구간 트리거
// int crs_junction = 0;  // 교차로 구간 트리거
// int crs_parking = 0;   // 주차구간 트리거
// int crs_emergency = 0; // 돌발구간 트리거
// int crs_accel = 0;     // 가속구간 트리거
// int crs_final = 0;     // 종료구간 트리거

// additional part
int crs_outofcrs = 0; // 구간을 벗어난 경우 트리거 ->

int simuwork = 0;
int safetybelt = 0, sidebrake = 0, leftlight = 0, rightlight = 0, emerlight = 0;
int fnddat;
int *trafLightState; // 신호등 현재 상태 확인변수
int traflights;

int *btnnowState; // 신호등 현재 상태 확인변수
int btnstate;
int ready = 0;
int ledstat, ledblink1, ledblink2, ledblink3;
int handleleft, handleright; // 방향지시등 켜있을 시 핸들 좌 우 일정 이상 꺾음 판별 (좌꺾은 후 우로) (우꺾은 후 좌로)

int testfail;
int startplace, stopplace1;

int randtest = 0;                                     // 시험 랜덤항목 설정을 위한 변수
int minuspoint = 0;                                   // 시험 감점위한 변수
int gear = 0;                                         // 기어 판별위한 변수 (0중립1전진2후진)
int uphillcnt, emergencycnt, junctioncnt, parkingcnt; // 구간별 제한시간 판별 위한 변수
int uphillstop, uphillside1, uphillside2, uphillgo;
int emergency1, emergency2, junctionpass;
int parkingpass;
int sidebreakcheck, sidebreakcheck2;
int accelcheck, accelsuccess, finalcheck, finalsuccess; // 구간내 항목 성공여부 판별 변수
int carspeed;                              // 차의 현재 속도
int alertscreen=0, failscreen=0, dirfail=0, crash=0;



int showstate = 0; // 스크린에 표시할 이미지 state 변수. 0 = 메인스크린, 1 = 메뉴얼, 2 = 리더보드, 3 = 게임진행

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

void *AccelWork(void){
   int accel[3];
    int magnet[3];
    int gyro[3];
    double ang;
    int first_accel[3];
    int second_accel[3];
    int moving = 0;
    //전진기어에서는 1씩 증가, 가속에서는 2씩 증가
    //중립에서는 0씩 증가
    int moving_l = 0;
    //좌회전시 1이 되도록
    int moving_r = 0;
    //우회전시 1이 되도록
    int break_on = 0;
    //뒤로 기울인 각도 크면 break_on = 1이 되도록
    printf("Set Default Value\n");
    getAccel(first_accel);

    while(1) //game이 끝날 때 까지 second_accel값 받아서 기울기 계산
    {        // 나중에 1 대신 트리거 변수로 바꾸기.
        
            getAccel(second_accel);
            break_on = 0; 
          //  moving_l = 0;
          //  moving_r = 0;
            // printf("Set Changing Value\n");
            if( first_accel[0] - second_accel[0] > 5000 && !(first_accel[2] - second_accel[2] < 9000 && first_accel[2] - second_accel[2] > 4000 ) ) 
            { //오른쪽으로 기운 경우 차이가 5000이상 나면 
              // 그리고 Break_on 정도로 기울이지 않았다면 Handle Turn Right
            
                // ~ 차 방향을 오른쪽으로 바꾸는 코드 ~//
                //rcar += 3; printf("r=%d\n", rcar); break;  기울이고 있는 이동하도록
                // +3
                printf("  Handle Turn Right \n");
                moving_r = 1;
                moving_l = 0;
                moving += 1;
                printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
                sleep(1);
                
            
            }

            else if(second_accel[0] - first_accel[0] > 5000 && !(first_accel[2] - second_accel[2] < 9000 && first_accel[2] - second_accel[2] > 4000 ) )
            { // 왼쪽으로 기운 경우 [차이가 5000이상 나면] 
              // && 뒤로 기울이지 않았다면 Handle Turn Left 출력

                // ~ 차 방향을 바꾸는 코드 ~
                //
                // rcar -= 3; printf("r=%d\n", rcar); break; //  기울이고 있는 동안 이동하도록
                printf(" Handle Turn Left \n");
                moving_l = 1;
                moving_r = 0;
                moving += 1;
               printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
               sleep(1);
                //sleep(1);
            }

            else if( first_accel[2] - second_accel[2] > 4000 && first_accel[2] - second_accel[2] < 9000  && !(second_accel[0] - first_accel[0] > 5000) && !(first_accel[0] - second_accel[0] > 5000)) 
            // 뒤로 기울인 경우
            // first_accel[2] - second_accel[2] > 4000 && first_accel[2] - second_accel[2] < 8000 -> 키트를 조금만 기울인 경우 : 후진기어
            // !(second_accel[0] - first_accel[0] > 5000) && !(first_accel[0] - second_accel[0] > 5000) -> 키트를 좌우로 기울이지 않았으면
            // && 키트를 왼쪽, 뒤쪽으로 돌리지 않았으면 Slow Down
            { 

                // ~ 차 속도를 감소하는 코드?
                moving -= 1;
                printf(" Slow Down \n");
                printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
                sleep(1);
                //sleep(1);
            }
            
            else if( second_accel[0] - first_accel[0] > 5000 && first_accel[2] - second_accel[2] > 4000 && first_accel[2] - second_accel[2] < 9000)
            //first_accel[2] - second_accel[2] > 4000 && first_accel[2] - second_accel[2] < 8000 -> slow down 구간 키트를 뒤로 적당히 기울인 경우  
            // 뒤로 기울인 경우
            //second_accel[0] - first_accel[0] > 5000
            // -> 핸들을 왼쪽으로 돌린 경우
            {
                moving -= 1;
                moving_l = 1;
                printf(" Reverse Left \n");
                printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
                sleep(1);

            }
            else if( first_accel[0] - second_accel[0] > 5000 && first_accel[2] - second_accel[2] > 4000 && first_accel[2] - second_accel[2] < 9000)
            //first_accel[2] - second_accel[2] > 4000 && first_accel[2] - second_accel[2] < 8000 -> slow down 구간 키트를 뒤로 적당히 기울인 경우 
            // 뒤로 기울인 경우
            // first_accel[0] - second_accel[0] > 5000 
            // -> 핸들을 오른쪽으로 돌린 경우
            {
                moving -= 1;
                moving_r = 1;
                printf(" Reverse Right \n");
                printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
                sleep(1);

            }

            else if( first_accel[2] - second_accel[2] > 9000 )
            { // 뒤로 기울인 각도가 큰 경우 (돌발에서 급 브레이크 밟은 경우)
                    // ~ 차 멈추는 코드 ~
                    printf(" Stop \n");
                    //moving -= 3;
                    break_on = 1;
                    moving_l = 0;
                    moving_r = 0;
                    //breakon
                    printf("Break On!\n");
                    printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
                    sleep(1);
                   //sleep(1);
            }
        
            else if( second_accel[2] - first_accel[2] > 4000 && second_accel[2] - first_accel[2] < 9000)
            {// 앞으로만 기울인 경우 [  가속도 센서의 z값이 바뀜  ]

                // ~차가 앞으로 진행하는 코드 ~
            
                moving += 1;
                moving_l = 0;
                moving_r = 0;
                /*speed = 1;  //조금만 기울인 경우 speed = 1;
                dxcar = speed * cos((180-rcar) * PI / 180.0); xcar += dxcar;
                dycar = speed * sin((180-rcar) * PI / 180.0); ycar += dycar;
                break;
                */
                printf(" Car Moving Forward \n");
                printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
                sleep(1);
                //sleep(1);
            }

            else if( second_accel[2] - first_accel[2] > 8000 )
                { // 앞으로 많이 기울인 경우 (가속 구간에서 가속)
                    // ~ 차 속도를 빠르게 ~

                    moving += 2;  
                    moving_l = 0;
                    moving_r = 0; 
                    /*
                    speed = 2;  //많이 기울인 경우 speed = 2로 설정하여 가속
                    dxcar = speed * cos((180-rcar) * PI / 180.0); xcar += dxcar;
                    dycar = speed * sin((180-rcar) * PI / 180.0); ycar += dycar;
                    break; 
                    */
                    printf(" Car Accelation! \n");
                    printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
                    //sleep(1);
                    sleep(1);
                }
                
            else if(first_accel[0] - second_accel[0] > 5000 && second_accel[2] - first_accel[2] > 4000 && second_accel[2] - first_accel[2] < 9000) 
            { 
                printf(" Going Left! \n");
                sleep(1);
                //앞으로 기울인 상태에서 왼쪽으로 기울이면 악셀 + 핸들 왼쪽을 돌리면 옆으로 같이 진행하도록
                moving += 1;
                moving_l = 1;
                printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
                sleep(1);
                // 전진좌 : moving + 1, moving_l = 1
                /*
                rcar += 3;
                speed = 1;  //조금만 기울인 경우 speed = 1;
                dxcar = speed * cos((180-rcar) * PI / 180.0); xcar += dxcar;
                dycar = speed * sin((180-rcar) * PI / 180.0); ycar += dycar;
                break;
                */

            }
            else if(second_accel[0] - first_accel[0] > 5000 && second_accel[2] - first_accel[2] > 4000 && second_accel[2] - first_accel[2] < 9000) 
            { 
                printf(" Going Right! \n");
                
                moving += 1;
                moving_r = 1;
                printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
                sleep(1);
                // 전진우 : moving + 1, moving_r = 1

                //앞으로 기울인 상태에서 오른쪽으로 기울이면 ==> 악셀 + 핸들 오른쪽을 돌리면 옆으로 같이 진행하도록
                
                /*
                rcar -= 3;
                speed = 1;  //조금만 기울인 경우 speed = 1;
                dxcar = speed * cos((180-rcar) * PI / 180.0); xcar += dxcar;
                dycar = speed * sin((180-rcar) * PI / 180.0); ycar += dycar;
                break;
                */
            }

            else if (second_accel[0] - first_accel[0] > 5000 && first_accel[2] - second_accel[2] > 4000 && first_accel[2] - second_accel[2] < 9000)
            //뒤로 기울이고 핸들 왼쪽 기울이면 
            // 후진좌 : moving +1, moving_l = 1
            {
                /* code */
                moving -= 1;
                moving_l = 1;
                printf("Reverse Left\n");
                printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
                sleep(1);
            }

            else if (first_accel[0] - second_accel[0] > 5000 && first_accel[2] - second_accel[2] > 4000 && first_accel[2] - second_accel[2] < 9000)
            //뒤로 기울이고 핸들 오른쪽으로 기울이면 
            // 후진우 : moving +1, moving_r = 1
            {
                 /* code */
                moving -= 1;
                moving_r = 1;
                printf("Reverse Right\n");
                printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
                sleep(1);
            }
            
            else 
            {
              // 핸들이 정위치면 moving_l,r을 0으로 설정.
              // moving은 증가안하고 고정.
                moving_l = 0;
                moving_r = 0;    
                //moving -= 1;
                printf("Middle Stance\n");
                printf("Moving : %d  Moving L : %d,  Moving_r : %d\n", moving, moving_l, moving_r);
                sleep(1);
                //sleep(1);
            }

            

    }
            usleep(accel_t);
            
            return 0;
}


void *trafLight(void)
{
    pwmLedInit();
    pwmSetPercent(0, 0);
    pwmSetPercent(0, 1);
    pwmSetPercent(0, 2);
    *trafLightState = 0; // reset RGB LED state
    while (1)
    {
        if (simuwork == 1)
        { // repeat if simulation is working    // b g r
            pwmSetPercent(0, 0);
            pwmSetPercent(100, 1);
            pwmSetPercent(0, 2);
            // pthread_mutex_lock(&lock1);
            *trafLightState = 1; // LED ON R0 G100 B 0 green
            ready = 1;
            // pthread_mutex_unlock(&lock1);
            sleep(13);
            pwmSetPercent(0, 0);
            pwmSetPercent(63, 1);
            pwmSetPercent(100, 2);
            // pthread_mutex_lock(&lock1);
            *trafLightState = 2; // LED ON R100 G63 B 0 orange
            ready = 1;
            // pthread_mutex_unlock(&lock1);
            sleep(3);
            pwmSetPercent(0, 0);
            pwmSetPercent(0, 1);
            pwmSetPercent(100, 2);
            // pthread_mutex_lock(&lock1);
            *trafLightState = 3; // LED ON R100 G0 B 0 red
            ready = 1;
            // pthread_mutex_unlock(&lock1);
            sleep(6);
            pwmSetPercent(0, 0);
            pwmSetPercent(63, 1);
            pwmSetPercent(100, 2);
            // pthread_mutex_lock(&lock1);
            *trafLightState = 2; // LED ON R100 G63 B 0 orange
            ready = 1;
            // pthread_mutex_unlock(&lock1);
            sleep(3);
        }
    }
    pwmInactiveAll();
}

void *btncheck(void)
{ // btn and leds
    // reset Button flag state
    BUTTON_MSG_T Data;
    buttonInit();
    ledLibInit();
    ledOnOff(0, 0);
    int msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);

    while (simuwork == 1)
    {
        int returnValue = 0;
        returnValue = msgrcv(msgID, &Data, sizeof(Data) - sizeof(long int), 0, 0);

        if ((Data.type == EV_KEY) & (Data.pressed))
        {
            switch (Data.keyInput)
            {
            case KEY_HOME:
                if (safetybelt == 0)
                {
                    safetybelt = 1;
                    ledOnOff(0, 1);
                }
                else if (safetybelt == 1)
                {
                    safetybelt = 0;
                    ledOnOff(0, 0);
                }
                break;

            case KEY_BACK:
                if (sidebrake == 0)
                {
                    sidebrake = 1;
                    ledOnOff(1, 1);
                }
                else if (sidebrake == 1)
                {
                    sidebrake = 0;
                    ledOnOff(1, 0);
                }
                break;

            case KEY_SEARCH:
                if (leftlight == 0)
                { // 점멸 구현 방법 생각 필요 thread? process?
                    leftlight = 1;
                    ledstat = 1;
                    ledblink1 = 1;
                }
                else if (leftlight == 1)
                {
                    leftlight = 0;
                    ledstat = 1;
                    ledblink1 = 0;
                    ledstat = 0;
                }
                break;

            case KEY_MENU:
                if (rightlight == 0)
                { // 점멸 구현 방법 생각 필요 thread? process?
                    rightlight = 1;
                    ledstat = 2;
                    ledblink2 = 1;
                }
                else if (rightlight == 1)
                {
                    rightlight = 0;
                    ledstat = 2;
                    ledblink2 = 0;
                    ledstat = 0;
                }
                break;

            case KEY_VOLUMEUP:
                if (emerlight == 0)
                { // 점멸 구현 방법 생각 필요 thread? process?
                    emerlight = 1;
                    ledstat = 3;
                    ledblink3 = 1;
                }
                else if (emerlight == 1)
                {
                    emerlight = 0;
                    ledstat = 3;
                    ledblink3 = 0;
                    ledstat = 0;
                }
                break;
            case KEY_VOLUMEDOWN: // 초기화면으로 복귀 코드
                break;
            }
        }
    }
    buttonExit();
    ledLibExit();
}

void *ledblinks(void)
{
    buzzerInit();
    while (1)
    {
        switch (ledstat)
        {
        case 1:
            if (ledblink1 == 0)
            {
                ledOnOff(3, 0);
                ledOnOff(2, 0);
            }
            else if (ledblink1 == 1)
            {
                ledOnOff(3, 1);
                ledOnOff(2, 1);
                buzzerPlaySong(220);
                usleep(5000);
                buzzerStopSong();
                usleep(500000);
                buzzerStopSong();
                ledOnOff(3, 0);
                ledOnOff(2, 0);
                buzzerPlaySong(138);
                usleep(5000);
                buzzerStopSong();
                usleep(500000);
            }
            else if (handleleft == 1)
            {
                ledblink1 = 0;
            }
            break;

        case 2:
            if (ledblink2 == 0)
            {
                ledOnOff(4, 1);
                ledOnOff(5, 1);
            }
            else if (ledblink2 == 1)
            {
                ledOnOff(4, 1);
                ledOnOff(5, 1);
                buzzerPlaySong(220);
                usleep(5000);
                buzzerStopSong();
                usleep(500000);
                ;
                ledOnOff(4, 0);
                ledOnOff(5, 0);
                buzzerPlaySong(138);
                usleep(5000);
                buzzerStopSong();
                usleep(500000);
            }
            else if (handleright == 1)
            {
                ledblink2 = 0;
            }
            break;

        case 3:
            if (ledblink3 == 0)
            {
                ledOnOff(3, 0);
                ledOnOff(4, 0);
                ledOnOff(2, 0);
                ledOnOff(5, 0);
            }
            else if (ledblink3 == 1)
            {
                ledOnOff(3, 1);
                ledOnOff(4, 1);
                ledOnOff(2, 1);
                ledOnOff(5, 1);
                buzzerPlaySong(220);
                usleep(5000);
                buzzerStopSong();
                usleep(500000);
                ledOnOff(3, 0);
                ledOnOff(4, 0);
                ledOnOff(2, 0);
                ledOnOff(5, 0);
                buzzerPlaySong(138);
                usleep(5000);
                buzzerStopSong();
                usleep(500000);
            }
            break;

        case 0: // 아무것도 안함
            break;
        }
    }
    buzzerExit();
}

void *trafLightss(void)
{ // for testing output connect.
    while (1)
    {
        // pthread_mutex_lock(&lock1); // 현 스레드작업중 타 스레드의 자원 침범을 막기 위한 lock선언
        if (ready)
        {                                                            // 완료 플래그가 올라가있다면
            int traflights = *trafLightState;                        // 공유메모리에 저장되어있는 값을 복사해옴
            printf("\x1b[36m traflight = %d \x1b[0m\n", traflights); // 출력
            ready = 0;                                               // 플래그 내림
        }
        // pthread_mutex_unlock(&lock1); // 타 스레드의 자원 접근이 가능함을 알리는 unlock선언
        usleep(1000); // 함수 작동을 1밀리초간 중지
    }
    return NULL; // NULL반환
}

/*
void* sevenseg(void) {
        //reset 7seg state
    while(1) {
        if(simuwork==1) { // repeat if simulation is working
        //100 표시
        //구간별 조건문 작성해야함
        }
    }
}
*/
/* 7 seg decoder 만들때 참고.
14,11,10,6,8,7 => 선택 자리수만 LOW, 외에는 HIGH => 3자리만 사용할것이기에 14,11,10 HIGH고정, 6,8,7번갈아가며 LOW 입력.
- 표시: 5번핀 high, 1,2,3,4,9,12,13번핀 low
0 표시: 1,2,4,9,12,13번핀 high, 3,5번핀 low
1 표시: 4,9번핀 high 1,2,3,5,12,13번핀 low
2 표시: 1,2,5,9,13번핀 high, 3,4,12번핀 low
3 표시: 2,4,5,9,13번핀 high, 1,3,12번핀 low
4 표시: 4,5,9,12번핀 high, 1,2,3,13번핀 low
5 표시: 2,4,5,12,13번핀 high, 1,3,9번핀 low
6 표시: 1,2,4,5,12,13번핀 high, 3,9번핀 low
7 표시: 4,9,12,13번핀high, 1,2,3,5번핀 low
8 표시: 1,2,4,5,9,12,13번핀 high, 3번핀 low
9 표시: 2,3,4,5,9,12,13번핀 high, 1번핀 low
*/

void *ScreenOutput(void)
{
    int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;
    int cols = 0, rows = 0;
    char *data;
    char bmpfile[200];
    int nums = 0;
    // remove cursor
    int conFD = open("/dev/tty0", O_RDWR);
    ioctl(conFD, KDSETMODE, KD_GRAPHICS);
    close(conFD);

    // FrameBuffer init
    if (fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0)
    {
        printf("FrameBuffer Init Failed\r\n");
        return 0;
    }
    while (1)
    {
        switch (showstate)
        {
        case 0:
        {
            fb_clear();
            // FileRead
            if (read_bmp("mainscreen.bmp", &data, &cols, &rows) < 0)
            { // mainscreen.bmp 출력
                printf("File open failed\r\n");
                return 0;
            }
            // FileWrite
            fb_write(data, cols, rows);
            close_bmp();
        }
        break;
        case 1:
        {
            fb_clear();
            while (now_level == CRS_MANUAL) // 메뉴얼 표시상태
            {
                usleep(1000000); // 1초 대기
                strcpy(bmpfile, "manual");
                snprintf(bmpfile, sizeof(bmpfile), "%d", maunalpage); // maunalpage 변수로 페이지 확인
                strcat(bmpfile, ".bmp");
                // FileRead
                if (read_bmp(bmpfile, &data, &cols, &rows) < 0)
                { // manual숫자.bmp 출력
                    printf("File open failed\r\n");
                    return 0;
                }
                // FileWrite
                fb_write(data, cols, rows);
                close_bmp();
            }
        }

        case 2:
        {
            fb_clear();
            while (리더보드 표시상태)
            {                    // 리더보드 어떻게 만들지.... 점수 기록되면 도트 찍히게 해야하나?
                usleep(1000000); // 1초 대기
                strcpy(bmpfile, "leaderboard");
                snprintf(bmpfile, sizeof(bmpfile), "%d", leaderboard); // leaderboard 변수로 페이지 확인
                strcat(bmpfile, ".bmp");
                // FileRead
                if (read_bmp(bmpfile, &data, &cols, &rows) < 0)
                { // leaderboard숫자.bmp 출력
                    printf("File open failed\r\n");
                    return 0;
                }
                // FileWrite
                fb_write(data, cols, rows);
                close_bmp();
            }
        }

        case 3:
        {
            fb_clear();
            while (simuwork == 1)
            {                   // 게임 진행중일 때
                usleep(100000); // 0.1초 대기 10fps
                strcpy(bmpfile, "");
                snprintf(bmpfile, sizeof(bmpfile), "%d", nums); // nums변수로 현재 프레임확인
                strcat(bmpfile, ".bmp");
                // FileRead
                if (read_bmp(bmpfile, &data, &cols, &rows) < 0)
                { // 숫자.bmp 출력
                    printf("File open failed\r\n");
                    return 0;
                }
                // FileWrite
                fb_write(data, cols, rows);
                close_bmp();
            }
        }

        default:
            break;
        }
    }
}

void *ScreenOverlay(void)
{
    int screen_width2;
    int screen_height2;
    int bits_per_pixel2;
    int line_length2;
    int cols2 = 0, rows2 = 0;
    char *data2;
    char bmpfile2[200];
    int nums2 = 0;
    int nums3 = 0;
    int nums4 = 0;

    // FrameBuffer init
    if (fb_init2(&screen_width2, &screen_height2, &bits_per_pixel2, &line_length2) < 0)
    {
        printf("FrameBuffer0 Init Failed\r\n");
        return 0;
    }

    fb_clear2(0, 0, 1024, 600);

    while (1)
    {
        switch (showstate)
        {
        case 0:
        {
            fb_clear2();
            strcpy(bmpfile2, "overlaymainscreen");
            strcat(bmpfile2, nums2);
            strcat(bmpfile2, ".bmp");

            // FileRead
            if (read_bmp(bmpfile2, &data2, &cols2, &rows2) < 0)
            {
                printf("File open failed\r\n");
                return 0;
            }
            // FileWrite
            fb_write2(data2, cols2, rows2, 0, 0);

            close_bmp();
        }
        break;
        case 1:
        {
            fb_clear2();
            strcpy(bmpfile2, "overlaymanual");
            strcat(bmpfile2, nums3);
            strcat(bmpfile2, ".bmp");

            // FileRead
            if (read_bmp(bmpfile2, &data2, &cols2, &rows2) < 0)
            {
                printf("File open failed\r\n");
                return 0;
            }
            // FileWrite
            fb_write2(data2, cols2, rows2, 0, 0);

            close_bmp();
        }
        break;

        case 2:
        {
            fb_clear2();
            strcpy(bmpfile2, "overlayleaderboard");
            strcat(bmpfile2, ".bmp");

            // FileRead
            if (read_bmp(bmpfile2, &data2, &cols2, &rows2) < 0)
            {
                printf("File open failed\r\n");
                return 0;
            }
            // FileWrite
            fb_write2(data2, cols2, rows2, 0, 0);

            close_bmp();
        }
        break;

        case 3:
        {
            strcpy(bmpfile2, "overlaygame");
            strcat(bmpfile2, nums4);
            strcat(bmpfile2, ".bmp");

            // FileRead
            if (read_bmp(bmpfile2, &data2, &cols2, &rows2) < 0)
            {
                printf("File open failed\r\n");
                return 0;
            }
            // FileWrite
            fb_write2(data2, cols2, rows2, 0, 0);

            close_bmp();
        }
        break;

        default:
            break;
        }
    }
}

void showMainScreen()
{
    showstate = 0; // 메인 화면 출력. 디자인 구상 UI idea에 구상 올려둠 / 버튼 표시로 버튼을 누르면 위의 변수 바뀜.
    while (1)
    {
        if (scBTN_Start)
            driveTest();
        else if (scBTN_Manual)
            showManual();
        else if (scBTN_Leaderbd)
            showLeaderBoard();
    }
}

void driveTest()
{                   // 시험 코스 진행할 것 작성   while문으로 구간 판별후 반복조건문 탈출하게 작성해야함.
    maunalpage = 0; // 메뉴얼 시작은 선택페이지로.
    showstate = 1;  // 화면에 메뉴얼 출력. 메뉴얼 0페이지는 시험 시작전 코스설명 yes no 선택페이지로. 1페이지부터 코스설명.
    int next = 1;   // teststart = 1, mainmenu = 2 : default teststart
    // 시험을 시작하기에 앞서 코스 설명을 진행하겠습니다. (스킵 여부 물어서 스킵 가능하게.)
    if (now_level==CRS_MANUAL)
        next = showManual();
    // 화면의 시작하기를 누를경우(testStart)
    if (next == 1)
    {
         scBTN_Start = 0;
         nums=0; // 게임화면 0으로 시작
        showstate = 3; // 화면에 운전이미지 표시 시작.0번은 시작위치.
        next = 0;
        // 돌발 및 기본조작 랜덤설정
        srand((unsigned int)time(NULL));
         randtest = rand() % 4; // random num 0~3
         // 시험 내용 작성
         printf("지금부터 운전면허 기능시험을 시작합니다."); // 화면에 띄울 수 있으면 띄우기.
            // 기본조작시험
            //crs_basic = 1; // 기본조작평가 트리거
        printf("기본조작평가를 시작합니다.\n");
         //
        switch (randtest)
        {
        case 0: // 상향등, 와이퍼 체크
        {
            printf("전조등테스트: 3초 안에 상향등을 켜십시오\n");
            sleep(3);
            if (scBTN_Lightup == 1)
            {
                pritnf("상향등 확인.\n");
                sleep(1);
            }
            else if ((scBTN_Lightup == 0) | (scBTN_Lightdown == 1))
            {
                pritnf("전조등 조작실패. 5점 감점.\n");
                minuspoint = minuspoint + 5;
                sleep(1);
            }
            printf("와이퍼조작테스트: 3초 안에 와이퍼를 켜십시오\n");
            sleep(3);
            if (scBTN_Wiper == 1)
            {
                pritnf("와이퍼 켜짐 확인.\n");
                sleep(1);
            }
            else if (scBTN_Wiper == 0)
            {
                pritnf("와이퍼 조작실패. 5점 감점.\n");
                minuspoint = minuspoint + 5;
                sleep(1);
            }
        }
        break;
        case 1: //  하향등, 방향지시등 좌측 체크
        {
            printf("전조등테스트: 3초 안에 하향등을 켜십시오\n");
            sleep(3);
            if (scBTN_Lightdown == 1)
            {
                pritnf("하향등 확인.\n");
                sleep(1);
            }
            else if ((scBTN_Lightdown == 0) | (scBTN_Lightup == 1))
            {
                pritnf("전조등 조작실패. 5점 감점.\n");
                minuspoint = minuspoint + 5;
                sleep(1);
            }
            printf("방향지시등조작테스트: 3초 안에 좌측 방향지시등을 켜십시오\n");
            sleep(3);
            if (leftlight == 1)
            {
                pritnf("좌측 방향지시등 켜짐 확인.\n");
                sleep(1);
            }
            else if ((leftlight == 0) | (rightlight == 1))
            {
                pritnf("방향지시등 조작실패. 5점 감점.\n");
                minuspoint = minuspoint + 5;
                sleep(1);
            }
        }
        break;
        case 2: // 전진기어 와이퍼 체크
        {
            printf("기어조작테스트: 3초 안에 기어를 중립에서 전진기어로 바꾸십시오\n");
        sleep(3);
        if(gear==1) {
            pritnf("전진기어 확인.\n");
            sleep(1);
        }
        else if((gear==0)|(gear==2)) { 
            pritnf("기어 조작실패. 5점 감점.\n");
            minuspoint=minuspoint+5;
            sleep(1);
        }
            printf("와이퍼조작테스트: 3초 안에 와이퍼를 켜십시오\n");
            sleep(3);
            if (scBTN_Wiper == 1)
            {
                pritnf("와이퍼 켜짐 확인.\n");
                sleep(1);
            }
            else if (scBTN_Wiper == 0)
            {
                pritnf("와이퍼 조작실패. 5점 감점.\n");
                minuspoint = minuspoint + 5;
                sleep(1);
            }
        }
        break;
        case 3: // 후진기어 우측방향지시등 체크
        {
            printf("기어조작테스트: 3초 안에 기어를 중립에서 후진기어로 바꾸십시오\n");
        sleep(3);
        if(gear==2) {
            pritnf("후진기어 확인.\n");
            sleep(1);
        }
        else if((gear==0)|(gear==1)) { 
            pritnf("기어 조작실패. 5점 감점.\n");
            minuspoint=minuspoint+5;
            sleep(1);
        }
            printf("방향지시등조작테스트: 3초 안에 우측 방향지시등을 켜십시오\n");
            sleep(3);
            if (rightlight == 1)
            {
                pritnf("우측 방향지시등 켜짐 확인.\n");
                sleep(1);
            }
            else if ((rightlight == 0) | (leftlight == 1))
            {
                pritnf("방향지시등 조작실패. 5점 감점.\n");
                minuspoint = minuspoint + 5;
                pthread_join(thread_object_5, NULL);
                sleep(1);
            }
        }
        break;
        default:
            printf("random init failed");
        }
        printf("기본조작테스트가 끝났습니다. 좌측 방향지시등을 켠 후 10초내에 출발하십시오.\n");
        sleep(10);
        if (nums<=27) // 출발선 이전
        {
            pritnf("출발실패. 실격하셨습니다.\n");
            testfail = 1;
            failscreen =1;
        }
        while(nums<=78) {usleep(1000);}
       if (nums>=78) now_level = CRS_UPHILL;
        uphillcnt = 0;
        printf("경사구간평가를 시작합니다.\n");
        printf("지정된 위치에 정차 후 사이드브레이크를 올린 후, 삑 소리가 나면 사이드브레이크를 내리고 진행하십시오.\n");
        while (1)
        {
            if (uphillcnt >= 300 || num>=111)
            {
                pritnf("경사구간 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            usleep(100000);
            if (num<=110 && num>=102 && sidebrake) break; // 경사구간 선 안에 위치한경우
            else uphillcnt++;
        }
        while (1)
        {
            if (uphillcnt >= 300 || (num>=111 && sidebrake==0) )
            {
                pritnf("경사구간 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            usleep(100000);
            if (sidebrake==0) break;
            else uphillcnt++;
        }
        while (1)
        {
            if (uphillcnt >= 300)
            {
                pritnf("경사구간 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            usleep(100000);
            if (nums>=115) break;
            else uphillcnt++;
        }

         while(nums<=166) {usleep(1000);}

         while(1) {
            dirfail=0;
            if(nums<=186 && nums>=166 && moving_l==0) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=187) break;
         }

         while(nums<=218) {usleep(1000);}

          while(1) {
            dirfail=0;
            if(nums<=237 && nums>=218 && moving_l==0) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=238) break;
         }

         while(nums<=250) {usleep(1000);}

         // 돌발구간A
         if (randtest == 0)
         {
            now_level = CRS_EMERGENCY_A;
            emergencycnt = 0;

            // 버저로 돌발 소리 내는 코드 필요
            alertscreen=1;
            while (1)
            {
                if (emergencycnt >= 100)
                {
                    pritnf("돌발구간 실패. 10점감점되었습니다.\n");
                    minuspoint = minuspoint + 10;
                }
                usleep(100000);
                if (emerlight == 1) break;
                else emergencycnt++;
            }
            while (1)
            {
                if (emergencycnt >= 100)
                {
                    pritnf("돌발구간 실패. 10점감점되었습니다.\n");
                    minuspoint = minuspoint + 10;
                }
                usleep(100000);
                if (carspeed == 0) break;
                else emergencycnt++;
            }
            alertscreen=0;
         }

         while(nums<=279) {usleep(1000);}

         // 교차로구간1
         now_level = CRS_JUNCTION_1;
         // crs_junction = 1;
         junctioncnt = 0;
         printf("교차로구간 평가를 시작합니다.\n");
         while (1)
         {
            if (junctioncnt >= 300)
            {
                pritnf("교차로 30초 이내 통과 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen
            }
            usleep(100000);
            if(nums<=346 && nums>=280 && traflight==3) // 적색신호등과 차량교차로 내 위치 판별 true
            {
                pritnf("신호위반 발생! 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            if (nums>=347) break;// 차량이 교차로지난 위치에 위치함 판별 true
            else
                junctioncnt++;
         }
        
         while(nums<=362) {usleep(1000);}

         now_level = CRS_PARKING;
         parkingcnt = 0;
         printf("주차구간 평가를 시작합니다.\n");
         while (1)
         {
            if (parkingcnt >= 300)
            {
                pritnf("주차 30초 이내 통과 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            
            while(1) {
            usleep(100000);
            if (parkingcnt >= 300)
            {
                pritnf("주차 30초 이내 통과 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            dirfail=0;
            if(nums<=426 && nums>=373 && moving_r==0) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=426) break;
            else parkingcnt++;
         }

         while(nums<=450) {
            usleep(100000);
            if (parkingcnt >= 300)
            {
                pritnf("주차 30초 이내 통과 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            else parkingcnt++;
            }

        while(1) {
            usleep(100000);
            if (parkingcnt >= 300)
            {
                pritnf("주차 30초 이내 통과 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            dirfail=0;
            if(nums<=494 && nums>=451 && gear==2) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=494) break;
            else parkingcnt++;
         }
        while(1) {
            usleep(100000);
            if (parkingcnt >= 300)
            {
                pritnf("주차 30초 이내 통과 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            dirfail=0;
            if(nums<=530 && nums>=495 && ( gear!=2 || moving_l==0 )) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=530) break;
            else parkingcnt++;
         }
         while(1) {
            usleep(100000);
            if (parkingcnt >= 300)
            {
                pritnf("주차 30초 이내 통과 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            dirfail=0;
            if(nums<=547 && nums>=531 && ( gear!=2 || moving_b==0)) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=547) break;
            else parkingcnt++;
         }

         while (1)
         {
            if (parkingcnt >= 300 || num>=561)
            {
                pritnf("주차 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            usleep(100000);
            if (num<=561 && num>=547 && sidebrake) break; // 주차 선 안에 위치한경우
            else parkingcnt++;
         }

         while(nums<=564) {
            usleep(100000);
            if (parkingcnt >= 300)
            {
                pritnf("주차 30초 이내 통과 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            else parkingcnt++;
            }

         while(1) {
            dirfail=0;
            if(nums<=588 && nums>=565 && moving_r==0) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=588) break;
         }

         while(nums<=598) {usleep(1000);}

         while(1) {
            dirfail=0;
            if(nums<=617 && nums>=599 && moving_r==0) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=617) break;
         }

         while(nums<=620) {usleep(1000);}

         // 돌발구간B
         if (randtest == 0)
         {
            now_level = CRS_EMERGENCY_B;
            emergencycnt = 0;

            // 버저로 돌발 소리 내는 코드 필요
            alertscreen=1;
            while (1)
            {
                if (emergencycnt >= 100)
                {
                    pritnf("돌발구간 실패. 10점감점되었습니다.\n");
                    minuspoint = minuspoint + 10;
                }
                usleep(100000);
                if (emerlight == 1) break;
                else emergencycnt++;
            }
            while (1)
            {
                if (emergencycnt >= 100)
                {
                    pritnf("돌발구간 실패. 10점감점되었습니다.\n");
                    minuspoint = minuspoint + 10;
                }
                usleep(100000);
                if (carspeed == 0) break;
                else emergencycnt++;
            }
            alertscreen=0;
         }

         
         while(nums<=644) {usleep(1000);}
            // crs_emergency = 0;


            while(1) {
            dirfail=0;
            if(nums<=664 && nums>=644 && moving_r==0) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=664) break;
         }

         while(nums<=687) {usleep(1000);}

        while(1) {
            dirfail=0;
            if(nums<=707 && nums>=687 && moving_r==0) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=707) break;
         }

         while(nums<=771) {usleep(1000);}

        while(1) {
            dirfail=0;
            if(nums<=787 && nums>=771 && moving_r==0) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=787) break;
         }

         while(nums<=803) {usleep(1000);}
        
        // 교차로구간2

        
        now_level = CRS_JUNCTION_2;
         // crs_junction = 1;
         junctioncnt = 0;
         printf("교차로구간 평가를 시작합니다.\n");
         while (1)
         {
            if (junctioncnt >= 300)
            {
                pritnf("교차로 30초 이내 통과 실패. 실격하셨습니다.\n");
                testfail = 1;
                failscreen
            }
            usleep(100000);



            if(nums<=870 && nums>=840 && (traflight==3 || leftlight==0)) // 적색신호등과 차량교차로 내 위치 판별 true
            {
                pritnf("신호위반 발생! 실격하셨습니다.\n");
                testfail = 1;
                failscreen =1;
            }
            if (nums>=870) break;// 차량이 교차로지난 위치에 위치함 판별 true
            else
                junctioncnt++;
         }
        
         while(nums<=875) {usleep(1000);}



        // crs_junction = 0;

        // 돌발구간C
        
        if (randtest == 0)
        {
            now_level = CRS_EMERGENCY_C;
            emergencycnt = 0;

            // 버저로 돌발 소리 내는 코드 필요
            alertscreen=1;
            while (1)
            {
                if (emergencycnt >= 100)
                {
                    pritnf("돌발구간 실패. 10점감점되었습니다.\n");
                    minuspoint = minuspoint + 10;
                }
                usleep(100000);
                if (emerlight == 1) break;
                else emergencycnt++;
            }
            while (1)
            {
                if (emergencycnt >= 100)
                {
                    pritnf("돌발구간 실패. 10점감점되었습니다.\n");
                    minuspoint = minuspoint + 10;
                }
                usleep(100000);
                if (carspeed == 0) break;
                else emergencycnt++;
            }
            alertscreen=0;
        }
            
            // crs_emergency = 0;
        }

        while(nums<=955) {usleep(1000);}

        while(1) {
            dirfail=0;
            if(nums<=979 && nums>=955 && moving_l==0) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=979) break;
         }

         while(nums<=1008) {usleep(1000);}

        while(1) {
            dirfail=0;
            if(nums<=1032 && nums>=1008 && moving_l==0) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=1032) break;
         }

         while(nums<=1045) {usleep(1000);}

        // 가속구간
        now_level = CRS_ACCEL;
        // crs_accel = 1;
        carspeedmax = 0;
        accelcheck =0;
        while (1)
        {
            if (carsspeed == 0)
            {
                pritnf("가속구간내 정지. 실격하셨습니다.\n");
                testfail = 1;
            }
            if ((carspeed == 2) && nums<=1080 )
            {
                accelcheck++;
            }
            if(nums>=1080) break;
        }
        if (accelcheck <= 5)
        {
            pritnf("가속구간 실패. 10점감점되었습니다.\n");
            minuspoint = minuspoint + 10;
        }
        // crs_accel = 0;

        // 돌발구간D
        
        if (randtest == 0)
        {
            now_level = CRS_EMERGENCY_D;
            emergencycnt = 0;

            // 버저로 돌발 소리 내는 코드 필요
            alertscreen=1;
            while (1)
            {
                if (emergencycnt >= 100)
                {
                    pritnf("돌발구간 실패. 10점감점되었습니다.\n");
                    minuspoint = minuspoint + 10;
                }
                usleep(100000);
                if (emerlight == 1) break;
                else emergencycnt++;
            }
            while (1)
            {
                if (emergencycnt >= 100)
                {
                    pritnf("돌발구간 실패. 10점감점되었습니다.\n");
                    minuspoint = minuspoint + 10;
                }
                usleep(100000);
                if (carspeed == 0) break;
                else emergencycnt++;
            }
            alertscreen=0;
        }

        while(nums<=1100) {usleep(1000);}


        while(1) {
            dirfail=0;
            if(nums<=1132 && nums>=1108 && moving_l==0) {
                if(dirfail>=5) {crash=1; testfail =1; }
                else dirfail++;
            }
            if(nums>=1132) break;
         }

         while(nums<=1154) {usleep(1000);}


        // 종료구간
        crs_final = 1;
        while (1)
        {
            if ((nums<=1175 && nums>=1210) & (rightlight))
                finalsuccess = 1;
            finalcheck == 1;
            else if ((finalplace) & (!rightlight)) finalsuccess = 0;
        }
        if (finalsuccess == 0)
        {
            pritnf("종료구간 방향지시등 조작 실패. 5점감점되었습니다.\n");
            minuspoint = minuspoint + 5;
        }
    }
    else if (next == 2)
        return;
}

int showManual()
{ // 코스 설명 작성
    scBTN_Manual = 0;
    maunalpage = 1;
    showstate = 1;
    // 코스 설명 구간별로 이미지로 작성해서 띄우면 좋을것 같다고 생각.
    // 구간별 점수 및 전역 감점및 실격 요소, 제한시간 등 안내. 이미지 수동으로 넘기는 방식으로.
    while (testStart != 1 | mainScreen != 1)
    { // 마지막페이지에서 메인화면 혹은 시험 시작을 선택할 때 까지 대기.
        if (maunalpage == 마지막페이지)
        {

            if (scBTN_Start) ; // 시험시작으로 코스설명에 진입했을경우 testStart(시작하기)버튼과 mainScreen(메인화면) 버튼 표시
            else ;           // 메인화면에서 설명보기로 진입했을경우 mainScreen(메인화면) 버튼 표시
        }
    }
    if (testStart)
        return 1; // 시험시작 선택시 1(teststart) 리턴.
    else if (mainScreen)
        return 2; // 메인화면 선택시 2(mainmenu) 리턴.
}

void showLeaderBoard()
{ // 리더보드 내용 작성
    showstate = 2;
    // 디자인 구상 UI idea에 구상 올려둠
    while (mainscreen != 1)
    {
    }
    return;
}

void addLeaderBoard() {} // 리더보드 편집 함수 작성

int main(void)
{
    simuwork = 1;
    int shmID = shmget((key_t)7777, sizeof(int), IPC_CREAT | 0666); // 공유메모리 생성 요청, 이미 존재한다면 식별자 반환
    if (shmID == -1)
    {
        printf("\x1b[31mShared Memory Creating Failed!\x1b[0m\r\n"); // 생성 실패시 알림
        return 1;
    }
    trafLightState = (int *)shmat(shmID, (void *)NULL, 0); // 공유메모리에 접근이 가능하도록 공유메모리 주소값으로 포인터 초기화

    pthread_create(&thread_object_1, NULL, trafLight, NULL);
    pthread_create(&thread_object_2, NULL, btncheck, NULL);
    pthread_create(&thread_object_2x, NULL, ledblinks, NULL);
    pthread_create(&thread_object_4, NULL, trafLightss, NULL);
    pthread_create(&thread_object_5, NULL, ScreenOutput, NULL);
    pthread_create(&thread_object_6, NULL, ScreenOverlay, NULL);
    pthread_create(&thread_object_7, NULL, AccelWork, NULL);
    // pthread_create(&thread_object_3, NULL, sevenseg, NULL);

    showMainScreen();

    pthread_join(thread_object_1, NULL);
    pthread_join(thread_object_2, NULL);
    pthread_join(thread_object_2x, NULL);
    // pthread_join(thread_object_3, NULL);
    pthread_join(thread_object_4, NULL);
    pthread_join(thread_object_5, NULL);
    pthread_join(thread_object_6, NULL);
    pthread_join(thread_object_7, NULL);
    // shmdt(trafLightState); // 공유메모리 연결 해제

    //  return 0; // 프로그램 종료
}

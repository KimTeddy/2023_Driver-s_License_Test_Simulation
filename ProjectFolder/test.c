#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <sys/shm.h>
#include "button.h"

pthread_t thread_object_1; //스레드 1 for rgb led
pthread_t thread_object_2; //스레드 2 for btn and led
pthread_t thread_object_2x; //스레드 2x for led blink
//pthread_t thread_object_3; //스레드 3 for 7segment
pthread_t thread_object_4; //스레드 4 for echo state(imsi)

//pthread_mutex_t lock1; // for traflight
//pthread_mutex_t lock2; // for  btnstate

int simuwork=0;
int safetybelt=0, sidebrake=0, leftlight=0, rightlight=0, emerlight=0;
int fnddat;
int leddata=0b00000000;
int* trafLightState; // 신호등 현재 상태 확인변수
int traflights;

int* btnnowState; // 신호등 현재 상태 확인변수
int btnstate;
int ready=0;
int ledstat, ledblink1, ledblink2, ledblink3;
int handleleft, handleright; // 방향지시등 켜있을 시 핸들 좌 우 일정 이상 꺾음 판별

void* trafLight(void) {
    pwmLedInit();   
    pwmSetPercent(0, 0);
    pwmSetPercent(0, 1);
    pwmSetPercent(0, 2);
    *trafLightState=0; //reset RGB LED state
    while(1) {
        if(simuwork==1) { // repeat if simulation is working    // b g r
        pwmSetPercent(0, 0);
        pwmSetPercent(100, 1);
        pwmSetPercent(0, 2);
        //pthread_mutex_lock(&lock1);
        *trafLightState=1;//LED ON R0 G100 B 0 green
        ready=1;
        //pthread_mutex_unlock(&lock1);
        sleep(13);
        pwmSetPercent(0, 0);
        pwmSetPercent(63, 1);
        pwmSetPercent(100, 2);
        //pthread_mutex_lock(&lock1);
        *trafLightState=2; //LED ON R100 G63 B 0 orange
        ready=1;
        //pthread_mutex_unlock(&lock1);
        sleep(3);
        pwmSetPercent(0, 0);
        pwmSetPercent(0, 1);
        pwmSetPercent(100, 2);
        //pthread_mutex_lock(&lock1);
        *trafLightState=3;//LED ON R100 G0 B 0 red
        ready=1;
        //pthread_mutex_unlock(&lock1);
        sleep(6);
        pwmSetPercent(0, 0);
        pwmSetPercent(63, 1);
        pwmSetPercent(100, 2);
        //pthread_mutex_lock(&lock1);
        *trafLightState=2; //LED ON R100 G63 B 0 orange
        ready=1;
        //pthread_mutex_unlock(&lock1);
        sleep(3);
        }
    }
    pwmInactiveAll();
}


void* btncheck(void) { //btn and leds
    //reset Button flag state

        BUTTON_MSG_T Data;
        buttonInit();
        ledLibInit();
        ledOnOff(0, 0);
        int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);


while(simuwork==1)
{
    int returnValue = 0;
    returnValue = msgrcv(msgID, &Data, sizeof(Data) - sizeof(long int), 0, 0);
		
if((Data.type== EV_KEY) & (Data.pressed)){
    switch(Data.keyInput)
    {
        case KEY_HOME: if(safetybelt==0) {
                safetybelt=1;
                ledOnOff(0, 1);}
            else if(safetybelt==1) {
                safetybelt=0;
                ledOnOff(0, 0);} break;

        case KEY_BACK: if(sidebrake==0) {
                sidebrake=1;
                ledOnOff(1, 1);}
            else if(sidebrake==1) {
                sidebrake=0;
                ledOnOff(1, 0);} break;

        case KEY_SEARCH: if(leftlight==0) { // 점멸 구현 방법 생각 필요 thread? process?
                leftlight=1;
                ledstat=1;
                ledblink1=1;
                }
            else if(leftlight==1) {
                leftlight=0;
                ledstat=1;
                ledblink1=0;
                ledstat=0;
                } break;

        case KEY_MENU: if(rightlight==0) { // 점멸 구현 방법 생각 필요 thread? process?
                rightlight=1;
                ledstat=2;
                ledblink2=1;
                }
            else if(rightlight==1) {
                rightlight=0;
                ledstat=2;
                ledblink2=0;
                ledstat=0;
                } break;

        case KEY_VOLUMEUP: if(emerlight==0) { // 점멸 구현 방법 생각 필요 thread? process?
                emerlight=1;
                ledstat=3;
                ledblink3=1;
                }
            else if(emerlight==1) {
                emerlight=0;
                ledstat=3;
                ledblink3=0;
                ledstat=0;
                } break;
        case KEY_VOLUMEDOWN: // 초기화면으로 복귀 코드 
        break;
    }

} 
} 
    buttonExit();
    ledLibExit();
    }

void* ledblinks(void) {
    buzzerInit();
    while(1) {
        switch(ledstat)
    {
        case 1: if(ledblink1==0) {
                ledOnOff(3, 0);
                ledOnOff(2, 0);}
            else if(ledblink1==1) {
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
                usleep(500000);}
            else if(handleleft==1) {
                ledblink1=0;} break;

        case 2: if(ledblink2==0) {
                ledOnOff(4, 1);
                ledOnOff(5, 1);}
            else if(ledblink2==1) {
                ledOnOff(4, 1);
                ledOnOff(5, 1);
                buzzerPlaySong(220);
                usleep(5000);
                buzzerStopSong();
                usleep(500000);;
                ledOnOff(4, 0);
                ledOnOff(5, 0);
                buzzerPlaySong(138);
                usleep(5000);
                buzzerStopSong();
                usleep(500000);}
                else if(handleright==1) {
                ledblink2=0;} break;

        case 3: if(ledblink3==0) {
                ledOnOff(3, 0);
                ledOnOff(4, 0);
                ledOnOff(2, 0);
                ledOnOff(5, 0);}
            else if(ledblink3==1) {
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
                usleep(500000);} break;

         case 0: //아무것도 안함
        break;                        
    }
    }
    buzzerExit();
}


void* trafLightss(void) {
    while(1) {
        //pthread_mutex_lock(&lock1); // 현 스레드작업중 타 스레드의 자원 침범을 막기 위한 lock선언
        if(ready) { // 완료 플래그가 올라가있다면
            int traflights = *trafLightState; //공유메모리에 저장되어있는 값을 복사해옴
            printf("\x1b[36m traflight = %d \x1b[0m\n", traflights); // 출력
            ready = 0; //플래그 내림
        }
        //pthread_mutex_unlock(&lock1); // 타 스레드의 자원 접근이 가능함을 알리는 unlock선언
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


int main(void) {
simuwork = 1;
int shmID = shmget((key_t)7777,sizeof(int), IPC_CREAT|0666); //공유메모리 생성 요청, 이미 존재한다면 식별자 반환
    if (shmID==-1) {
        printf("\x1b[31mShared Memory Creating Failed!\x1b[0m\r\n"); // 생성 실패시 알림
        return 1;
    }
    trafLightState = (int*)shmat(shmID, (void*)NULL, 0); // 공유메모리에 접근이 가능하도록 공유메모리 주소값으로 포인터 초기화




pthread_create(&thread_object_1, NULL, trafLight, NULL);
pthread_create(&thread_object_2, NULL, btncheck, NULL);
pthread_create(&thread_object_2x, NULL, ledblinks, NULL);
pthread_create(&thread_object_4, NULL, trafLightss, NULL);
//pthread_create(&thread_object_3, NULL, sevenseg, NULL);

pthread_join(thread_object_1, NULL);
pthread_join(thread_object_2, NULL);
pthread_join(thread_object_2x, NULL);
//pthread_join(thread_object_3, NULL);
pthread_join(thread_object_4, NULL);
 //shmdt(trafLightState); // 공유메모리 연결 해제

  //  return 0; // 프로그램 종료

}
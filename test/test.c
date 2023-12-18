#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <sys/shm.h>
#include "button.h"
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <string.h>
#include <linux/input.h>
#include <sys/msg.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>

pthread_t thread_object_1; //스레드 1 for rgb led
pthread_t thread_object_2; //스레드 2 for btn and led
pthread_t thread_object_2x; //스레드 2x for led blink
//pthread_t thread_object_3; //스레드 3 for 7segment
pthread_t thread_object_4; //스레드 4 for echo state(imsi)
pthread_t thread_object_5; //스레드 5 for lcd bitmap output


//pthread_mutex_t lock1; // for traflight
//pthread_mutex_t lock2; // for  btnstate

int scBTN_Start=0, scBTN_Manual=0, scBTN_Leaderbd=0; // 스크린터치로 인식할 시작/코스설명/리더보드 버튼 변수
int maunalpage=0; // 코스 설명 이미지 페이지 카운팅
int testStart=0, mainScreen=0;

// LCD에 구간 표시하기 위한 트리거 신호들
int crs_basic = 0; //기본조작평가 트리거 신호
int crs_uphill = 0; //경사로 구간 트리거
int crs_junction = 0; //교차로 구간 트리거
int crs_parking = 0; //주차구간 트리거
int crs_emergency = 0; //돌발구간 트리거
int crs_accel = 0; //가속구간 트리거
int crs_final =0; // 종료구간 트리거 

//additional part 
int crs_outofcrs = 0; //구간을 벗어난 경우 트리거 ->  

int simuwork=0;
int safetybelt=0, sidebrake=0, leftlight=0, rightlight=0, emerlight=0;
int fnddat;
int* trafLightState; // 신호등 현재 상태 확인변수
int traflights;

int* btnnowState; // 신호등 현재 상태 확인변수
int btnstate;
int ready=0;
int ledstat, ledblink1, ledblink2, ledblink3;
int handleleft, handleright; // 방향지시등 켜있을 시 핸들 좌 우 일정 이상 꺾음 판별 (좌꺾은 후 우로) (우꺾은 후 좌로)

int randtest=0; //시험 랜덤항목 설정을 위한 변수
int minuspoint=0; // 시험 감점위한 변수
int gear=0; //기어 판별위한 변수 (0중립1전진2후진)
int uphillcnt,emergencycnt,junctioncnt,parkingcnt  //구간별 제한시간 판별 위한 변수
int uphillstop,uphillside1,uphillside2,uphillgo,emergency1,emergency2,junctionpass,sidebreakcheck,sidebreakcheck2,accelcheck,accelsuccess,finalcheck,finalsuccess; //구간내 항목 성공여부 판별 변수
int carspeed, carspeedmax; //차의 현재 속도와 기록된 최고속도 변수

int showstate=0; //스크린에 표시할 이미지 state 변수. 0 = 메인스크린, 1 = 메뉴얼, 2 = 리더보드, 3 = 게임진행


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


void* trafLightss(void) {   // for testing output connect.
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

void* ScreenOutput(void) {
    int screen_width;
    int screen_height;
    int bits_per_pixel;
    int line_length;
    int cols = 0, rows = 0;
	char *data;
    char bmpfile[200];
    int nums=0;
    int testingnow=1;
	//FrameBuffer init
    if ( fb_init(&screen_width, &screen_height, &bits_per_pixel, &line_length) < 0 )
	{
		printf ("FrameBuffer Init Failed\r\n");
		return 0;
	}
        switch (showstate)
        {
        case 0: {
            fb_clear();
            //FileRead
            if (read_bmp("mainscreen.bmp", &data, &cols, &rows) < 0) {  //mainscreen.bmp 출력
		        printf ("File open failed\r\n");
		        return 0;
                }
	        //FileWrite
	        fb_write(data, cols,rows); 
	        close_bmp();
        }
            break;
        case 1: {
            fb_clear();
            while(메뉴얼 표시상태) {
            usleep(1000000); //1초 대기
            strcpy(bmpfile, "manual");
            snprintf(bmpfile, sizeof(bmpfile), "%d", maunalpage);  // maunalpage 변수로 페이지 확인
            strcat(bmpfile, ".bmp");
            //FileRead
            if (read_bmp(bmpfile, &data, &cols, &rows) < 0) {  //manual숫자.bmp 출력
		        printf ("File open failed\r\n");
		        return 0;
                }
	        //FileWrite
	        fb_write(data, cols,rows); 
	        close_bmp();      
            }      
        }

        case 2: {
            fb_clear();
            while(리더보드 표시상태) {    //리더보드 어떻게 만들지.... 점수 기록되면 도트 찍히게 해야하나?
            usleep(1000000); //1초 대기
            strcpy(bmpfile, "leaderboard");
            snprintf(bmpfile, sizeof(bmpfile), "%d", leaderboard);  // leaderboard 변수로 페이지 확인
            strcat(bmpfile, ".bmp");
            //FileRead
            if (read_bmp(bmpfile, &data, &cols, &rows) < 0) {  //leaderboard숫자.bmp 출력
		        printf ("File open failed\r\n");
		        return 0;
                }
	        //FileWrite
	        fb_write(data, cols,rows); 
	        close_bmp();      
            }
        }

        case 3: {
            fb_clear();
            while(simuwork==1) {    //게임 진행중일 때
            usleep(500000); //0.5초 대기
            strcpy(bmpfile, "");
            snprintf(bmpfile, sizeof(bmpfile), "%d", nums);  // nums변수로 현재 프레임확인
            strcat(bmpfile, ".bmp");
            //FileRead
            if (read_bmp(bmpfile, &data, &cols, &rows) < 0) {  //숫자.bmp 출력
		        printf ("File open failed\r\n");
		        return 0;
                }
	        //FileWrite
	        fb_write(data, cols,rows); 
	        close_bmp();      
            }
        }


        default:
            break;
        }

}


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
pthread_create(&thread_object_5, NULL, ScreenOutput, NULL);
//pthread_create(&thread_object_3, NULL, sevenseg, NULL);

showMainScreen();






pthread_join(thread_object_1, NULL);
pthread_join(thread_object_2, NULL);
pthread_join(thread_object_2x, NULL);
//pthread_join(thread_object_3, NULL);
pthread_join(thread_object_4, NULL);
pthread_join(thread_object_5, NULL);
 //shmdt(trafLightState); // 공유메모리 연결 해제

  //  return 0; // 프로그램 종료

}

void showMainScreen() {
    showstate = 0;//메인 화면 출력. 디자인 구상 UI idea에 구상 올려둠 / 버튼 표시로 버튼을 누르면 위의 변수 바뀜.
    while(1) {
    if(scBTN_Start) driveTest();
    else if(scBTN_Manual) showManual();
    else if(scBTN_Leaderbd) showLeaderBoard();
    }
}

void driveTest () { //시험 코스 진행할 것 작성   while문으로 구간 판별후 반복조건문 탈출하게 작성해야함.
maunalpage = 0; // 메뉴얼 시작은 선택페이지로.
showstate = 1; //화면에 메뉴얼 출력. 메뉴얼 0페이지는 시험 시작전 코스설명 yes no 선택페이지로. 1페이지부터 코스설명.
int next=1; // teststart = 1, mainmenu = 2 : default teststart
//시험을 시작하기에 앞서 코스 설명을 진행하겠습니다. (스킵 여부 물어서 스킵 가능하게.)
if(manualSkip==0) next=showManual();
//화면의 시작하기를 누를경우(testStart)
if(next==1) {
    scBTN_Start = 0;
    showstate = 3; //화면에 운전이미지 표시 시작.0번은 시작위치.
    next=0;
    //돌발 및 기본조작 랜덤설정
    srand((unsigned int)time(NULL));
    randtest = rand() % 4 ;  // random num 0~3
    //시험 내용 작성
    printf("지금부터 운전면허 기능시험을 시작합니다.") // 화면에 띄울 수 있으면 띄우기.
    
    //기본조작시험
    crs_basic = 1; //기본조작평가 트리거
    printf("기본조작평가를 시작합니다.\n");
    switch(randtest) {
    case 0:  //전진기어 좌측방향지시등 체크
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
        printf("방향지시등조작테스트: 3초 안에 좌측 방향지시등을 켜십시오\n");
        sleep(3);
        if(leftlight==1) {
            pritnf("좌측 방향지시등 켜짐 확인.\n");
            sleep(1);
        }
        else if((leftlight==0)|(rightlight==1)) { 
            pritnf("방향지시등 조작실패. 5점 감점.\n");
            minuspoint=minuspoint+5;
            sleep(1);
        }
    }
    break;
    case 1: //후진기어 좌측방향지시등 체크
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
        printf("방향지시등조작테스트: 3초 안에 좌측 방향지시등을 켜십시오\n");
        sleep(3);
        if(leftlight==1) {
            pritnf("좌측 방향지시등 켜짐 확인.\n");
            sleep(1);
        }
        else if((leftlight==0)|(rightlight==1)) { 
            pritnf("방향지시등 조작실패. 5점 감점.\n");
            minuspoint=minuspoint+5;
            sleep(1);
        }
    }
    break;
    case 2: //전진기어 우측방향지시등 체크
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
        printf("방향지시등조작테스트: 3초 안에 우측 방향지시등을 켜십시오\n");
        sleep(3);
        if(rightlight==1) {
            pritnf("우측 방향지시등 켜짐 확인.\n");
            sleep(1);
        }
        else if((rightlight==0)|(leftlight==1)) { 
            pritnf("방향지시등 조작실패. 5점 감점.\n");
            minuspoint=minuspoint+5;
            sleep(1);
        }
    }
    break;
    case 3: //후진기어 우측방향지시등 체크
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
        if(rightlight==1) {
            pritnf("우측 방향지시등 켜짐 확인.\n");
            sleep(1);
        }
        else if((rightlight==0)|(leftlight==1)) { 
            pritnf("방향지시등 조작실패. 5점 감점.\n");
            minuspoint=minuspoint+5;
            sleep(1);
        }
    }
    break;
    default : printf("random init failed");
    }
    printf("기본조작테스트가 끝났습니다. 켜있던 방향지시등을 끄고, 좌측 방향지시등을 켠 후 10초내에 출발하십시오.\n");
    sleep(10) pritnf("출발실패. 5점 감점.\n");
    if(startplace) {
        pritnf("출발실패. 실격하셨습니다.\n");
        testfail = 1;
    }
    crs_basic = 0;
    //경사정차시험
    crs_uphill = 1;
    uphillcnt=0;
    uphillstop=0;
    uphillside1=0;
    uphillside2=0;
    printf("경사구간평가를 시작합니다.\n");
    printf("지정된 위치에 정차 후 사이드브레이크를 올린 후, 삑 소리가 나면 사이드브레이크를 내리고 진행하십시오.\n");
    while(uphillstop==0) {
        if(uphillcnt>=300) {
           pritnf("경사구간 실패. 실격하셨습니다.\n");
           testfail = 1;
        }
        usleep(100000);
        if(stopplace1) {
            uphillstop=1;
        }
        else uphillstop=0;
        uphillcnt++
    }
    while(uphillside1==0) {
        if(uphillcnt>=300) {
           pritnf("경사구간 실패. 실격하셨습니다.\n");
           testfail = 1;
        }
        usleep(100000);
        if(sidebrake) {
            uphillside1=1;
        }
        else uphillside1=0;
        uphillcnt++;
    }
    while(uphillside2==0) {
        if(uphillcnt>=300) {
           pritnf("경사구간 실패. 실격하셨습니다.\n");
           testfail = 1;
        }
        usleep(100000);
        if(sidebrake==0) {
            uphillside2=1;
        }
        else uphillside2=0;
        uphillcnt++;
    }
    while(uphillgo==0) {
        if(uphillcnt>=300) {
           pritnf("경사구간 실패. 실격하셨습니다.\n");
           testfail = 1;
        }
        usleep(100000);
        if(stopplace1==0) {
            uphillgo=1;
        }
        else uphillgo=0;
        uphillcnt++;
    }
    crs_uphill = 0;

    //돌발구간A
    if(randtest==0) { 
        emergencycnt=0;
        crs_emergency = 1;
        emergency1=0;
        emergency2=0;

        //버저로 돌발 소리 내는 코드 필요
        while(emergency1==0) {
        if(emergencycnt>=100) {
           pritnf("돌발구간 실패. 10점감점되었습니다.\n");
           minuspoint = minuspoint + 10;
        }
        usleep(100000);
        if(emerlight==1) {
            emergency1=1;
        }
        else emergency1=0;
        emergencycnt++;
    }
    while(emergency2==0) {
        if(emergencycnt>=100) {
           pritnf("돌발구간 실패. 10점감점되었습니다.\n");
           minuspoint = minuspoint + 10;
        }
        usleep(100000);
        if(carspeed==0) {
            emergency2=1;
        }
        else emergency2=0;
        emergencycnt++;
    }
        crs_emergency = 0;
    }

    //교차로구간1

    crs_junction = 1;
    junctioncnt = 0;
    junctionpass = 0;
    printf("교차로구간 평가를 시작합니다.\n");
    while(junctionpass==0) {
    if(junctioncnt>=300) {
        pritnf("교차로 30초 이내 통과 실패. 실격하셨습니다.\n");
        testfail = 1;
    }
    usleep(100000);
    if(적색신호등과 차량교차로 내 위치 판별 true) {
        pritnf("신호위반 발생! 실격하셨습니다.\n");
           testfail = 1;
    }
    if(차량이 교차로지난 위치에 위치함 판별 true) {
        junctionpass =1;
    }
    else junctioncnt++;
    
    }
    crs_junction = 0;

    //주차구간
    crs_parking = 1;
    parkingcnt = 0;
    parkingpass = 0;
    printf("주차구간 평가를 시작합니다.\n");
    while(parkingplace==0) {
        if(parkingcnt>=300) {
            pritnf("주차 30초 이내 통과 실패. 실격하셨습니다.\n");
            testfail = 1;
        }
        usleep(100000);
        if(차량이 주차칸 위치에 위치함 판별 true) parkingpass =1;
        else parkingcnt++;
    }
    while(sidebreakcheck=0) {
        if(parkingcnt>=300) {
            pritnf("주차 30초 이내 통과 실패. 실격하셨습니다.\n");
            testfail = 1;
        }
        usleep(100000);
        if(sidebrake) sidebreakcheck=1;
        else parkingcnt++;
        }
    while(sidebreakcheck2=0) {
        if(parkingcnt>=300) {
            pritnf("주차 30초 이내 통과 실패. 실격하셨습니다.\n");
            testfail = 1;
        }
        usleep(100000);
        if(sidebrake==0) sidebreakcheck2=1;
        else parkingcnt++;
        }
    
    crs_parking = 0;

    //돌발구간B
    if(randtest==1) { 
        emergencycnt=0;
        crs_emergency = 1;
        emergency1=0;
        emergency2=0;
        //버저로 돌발 소리 내는 코드 필요
        while(emergency1==0) {
        if(emergencycnt>=100) {
           pritnf("돌발구간 실패. 10점감점되었습니다.\n");
           minuspoint = minuspoint + 10;
        }
        usleep(100000);
        if(emerlight==1) {
            emergency1=1;
        }
        else emergency1=0;
        emergencycnt++;
    }
    while(emergency2==0) {
        if(emergencycnt>=100) {
           pritnf("돌발구간 실패. 10점감점되었습니다.\n");
           minuspoint = minuspoint + 10;
        }
        usleep(100000);
        if(carspeed==0) {
            emergency2=1;
        }
        else emergency2=0;
        emergencycnt++;
    }
        crs_emergency = 0;
    }
    //교차로구간2
    crs_junction = 1;
    junctioncnt = 0;
    junctionpass = 0;
    printf("교차로구간 평가를 시작합니다.\n");
    while(junctionpass==0) {
    if(junctioncnt>=300) {
        pritnf("교차로 30초 이내 통과 실패. 실격하셨습니다.\n");
        testfail = 1;
    }
    usleep(100000);
    if(적색신호등과 차량교차로 내 위치 판별 true) {
        pritnf("신호위반 발생! 실격하셨습니다.\n");
           testfail = 1;
    }
    if(차량이 교차로지난 위치에 위치함 판별 true) {
        junctionpass =1;
    }
    else junctioncnt++;
    
    }
    crs_junction = 0;

    //돌발구간C
    if(randtest==2) { 
        emergencycnt=0;
        crs_emergency = 1;
        emergency1=0;
        emergency2=0;
        //버저로 돌발 소리 내는 코드 필요
        while(emergency1==0) {
        if(emergencycnt>=100) {
           pritnf("돌발구간 실패. 10점감점되었습니다.\n");
           minuspoint = minuspoint + 10;
        }
        usleep(100000);
        if(emerlight==1) {
            emergency1=1;
        }
        else emergency1=0;
        emergencycnt++;
    }
    while(emergency2==0) {
        if(emergencycnt>=100) {
           pritnf("돌발구간 실패. 10점감점되었습니다.\n");
           minuspoint = minuspoint + 10;
        }
        usleep(100000);
        if(carspeed==0) {
            emergency2=1;
        }
        else emergency2=0;
        emergencycnt++;
    }
        crs_emergency = 0;
    }    
    //가속구간
    crs_accel = 1;
    carspeedmax=0;
    accelcheck =0;
    accelsuccess=0;
    while(accelcheck==0) {
        if(carsspeed == 0) {
            pritnf("가속구간내 정지. 실격하셨습니다.\n");
           testfail = 1;
        }
        if((carspeedmax == 50)&(accelfin)) { accelsuccess = 1; accelcheck=1; } //가속구간돌입시 0.1초마다 현재 스피드 저장하는 함수필요
        else if((carspeedmax <=49)&(accelfin)) { accelsuccess = 0; accelcheck=1; } //accelfin = 가속구간 종료지점 통과감지
    }
    if(accelsuccess==0) {
           pritnf("가속구간 실패. 10점감점되었습니다.\n");
           minuspoint = minuspoint + 10;
        }
    crs_accel = 0;    

    //돌발구간D
    if(randtest==3) { 
        emergencycnt=0;
        crs_emergency = 1;
        emergency1=0;
        emergency2=0;
        //버저로 돌발 소리 내는 코드 필요
        while(emergency1==0) {
        if(emergencycnt>=100) {
           pritnf("돌발구간 실패. 10점감점되었습니다.\n");
           minuspoint = minuspoint + 10;
        }
        usleep(100000);
        if(emerlight==1) {
            emergency1=1;
        }
        else emergency1=0;
        emergencycnt++;
    }
    while(emergency2==0) {
        if(emergencycnt>=100) {
           pritnf("돌발구간 실패. 10점감점되었습니다.\n");
           minuspoint = minuspoint + 10;
        }
        usleep(100000);
        if(carspeed==0) {
            emergency2=1;
        }
        else emergency2=0;
        emergencycnt++;
    }
        crs_emergency = 0;
    }    
    //종료구간
    crs_final = 1;
    finalcheck =0;
    finalsuccess = 0;
    while(finalcheck == 0) {
        if((finalplace)&(rightlight)) finalsuccess=1 ;finalcheck ==1;
        else if((finalplace)&(!rightlight)) finalsuccess=0 ;finalcheck ==1;
    }
    if(finalsuccess==0) {
        pritnf("종료구간 방향지시등 조작 실패. 5점감점되었습니다.\n");
           minuspoint = minuspoint + 5;
    }
}
else if(next==2) return;
}

int showManual () { //코스 설명 작성
scBTN_Manual=0;
maunalpage = 1;
showstate = 1;
 // 코스 설명 구간별로 이미지로 작성해서 띄우면 좋을것 같다고 생각.
 // 구간별 점수 및 전역 감점및 실격 요소, 제한시간 등 안내. 이미지 수동으로 넘기는 방식으로.
 while(testStart!=1 | mainScreen!=1) { // 마지막페이지에서 메인화면 혹은 시험 시작을 선택할 때 까지 대기.
 if(maunalpage==마지막페이지) {
    
 if(scBTN_Start) // 시험시작으로 코스설명에 진입했을경우 testStart(시작하기)버튼과 mainScreen(메인화면) 버튼 표시
 else  //메인화면에서 설명보기로 진입했을경우 mainScreen(메인화면) 버튼 표시

 }
 }
 if(testStart) return 1;  //시험시작 선택시 1(teststart) 리턴.
else if(mainScreen) return 2; //메인화면 선택시 2(mainmenu) 리턴.
}

void showLeaderBoard () { //리더보드 내용 작성
showstate = 2;
//디자인 구상 UI idea에 구상 올려둠
    while(mainscreen!=1) {}
    return;
}

void addLeaderBoard () {} //리더보드 편집 함수 작성


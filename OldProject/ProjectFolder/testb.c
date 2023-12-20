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
#include <sys/ipc.h>
#include <ctype.h>

#include "touch.h"
#include "button.h"
#include "now_level_defs.h"
#include "buzzer_soundeffect_defs.h"
#include "fnd.h"

#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)
#define FND_DRIVER_NAME "/dev/perifnd"
#define BLINK_DELAY_MS 500

#define accel_t 500000

const double RADIAN_TO_DEGREE = 180.0 / 3.141592;
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
double angle_x, angle_y, angle_z;
double angle[3];

  char* str1 = "hello              ";
  const char* str2 = "embedded system";
  
  char str_cnt0[10];
  char str_cnt1[10];
  char str_cnt2[10];
  char str_cnt3[10];
  char str_cnt[100];

  int cnt[5] = {0,};
pthread_t tid[2];

pthread_t thread_object_1;  // 스레드 1 for rgb led
pthread_t thread_object_2;  // 스레드 2 for btn and led
pthread_t thread_object_2x; // 스레드 2x for led blink
pthread_t thread_object_3; //스레드 3 for 7segment
pthread_t thread_object_4; // 스레드 4 for echo state(imsi)
pthread_t thread_object_5; // 스레드 5 for lcd bitmap output
pthread_t thread_object_6; // 스레드 6 for lcd overlay output
pthread_t thread_object_7; // 스레드 7 for accel work
pthread_t thread_object_8; // 스레드 8 for accel connect to num
pthread_t thread_object_9; // 스레드 9 for touchscreen
pthread_t thread_object_10; // 스레드 10 for buzzerwork
pthread_t thread_object_11; // 스레드 11 for textlcd

int scBTN_Start = 0, scBTN_Manual = 0, scBTN_Leaderbd = 0; // 스크린터치로 인식할 시작/코스설명/리더보드 버튼 변수
int scBTN_prevpage =0, scBTN_Nextpage = 0, scBTN_gotomain=0, scBTN_gotostart=0; // 메뉴얼 안에서 이전 이후 페이지, 메인이동, 시작이동 버튼변수
int scBTN_startup=0, scBTN_Wiper = 0, scBTN_Lightup =0, scBTN_Lightdown =0; // 스크린터치 버튼으로 감지할 변수들. (토글작동해야함)
int manualpage = 0;                                        // 코스 설명 이미지 페이지 카운팅
int testStart = 0, mainScreen = 0;
int simufin=0;

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

int prev_level = CRS_MAIN;
int simuwork = 0;
int safetybelt = 0, sidebrake = 1, leftlight = 0, rightlight = 0, emerlight = 0;
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
int gear = 1;                                         // 기어 판별위한 변수 (0중립1전진2후진)
int uphillcnt, emergencycnt, junctioncnt, parkingcnt; // 구간별 제한시간 판별 위한 변수
int uphillstop, uphillside1, uphillside2, uphillgo;
int emergency1, emergency2, junctionpass;
int parkingpass;
int sidebreakcheck, sidebreakcheck2;
int accelcheck, accelsuccess, finalcheck, finalsuccess; // 구간내 항목 성공여부 판별 변수
int carspeed;                              // 차의 현재 속도
int alertscreen=0, failscreen=0, dirfail=0, crash=0;
int reverseframe=0; //후진판정구간 프레임 진행 정상화 변수
int startcnt=0;
int leftlightpass=0;
char overlayname[30];

int gameoverlaycheck=0;

int nums = 0;
int nums2 = 0;
int nums3 = 0;
int nums4 = 0;
int nums5 = 0;
int leaderboard=0;

// 메인 코드에 넣을 것
int c_score = 100; // 처음 점수는 만점
int dispnum = 0;
void ScoreAnim();

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
    int moving_f = 0;
    int moving_b = 0;

*trafLightState = 0; // reset RGB LED state


int showstate = 0; // 스크린에 표시할 이미지 state 변수. 0 = 메인스크린, 1 = 메뉴얼, 2 = 리더보드, 3 = 게임진행, 4 = 기능테스트
/*
	int first = 0;
	// scBTN_Start, Manual, Leaderbd 나오는 화면
	int second = 0;
	// scBTN_prevpage, Nextpage, gotomain, gotostart 나오는 화면
	int third = 0;
	// scBTN_startup, Wiper, Lightup, Lightdown 나오는 화면 
	// 화면에 따라 구간을 구분할 수 있는 트리거를 설정.
*/
/*
void *txtdisplay(void)
  {
    while (1)
    {
   	    if (now_level == CRS_MAIN)
		{
            str1 = "PRESS START";
		   //  lcdtextwrite( "PRESS START", "CAR S", 1);
			 //  lcdtextwrite( "PRESS START", str_cnt, 2);
 			  // lcdtextwrite( "PRESS START", "CAR S", 2);
			  //MAIN에서는 LCD 윗단에는 "PRESS START" 출력, 
  
	  	}
        else if(now_level == CRS_MANUAL)
        {
            str1 = "MANUAL        ";

        }  
		else if (now_level == CRS_START)	
		{
            str1 = "BEGIN         ";
		   //	lcdtextwrite( "BEGIN         ", "CAR SI", 1);
		   //	lcdtextwrite( "BEGIN         ", str_cnt, 2);
  	  		//lcdtextwrite( "BEGIN         ", "CAR SI", 2);
		  	//START부분에서는 윗단에 "" 출력,
		  	//아랫부분 네모 0개
		}
		else if (now_level == CRS_BASIC)
		{
            str1 = "CAR COMPONENT";        
		   //	lcdtextwrite( "CAR COMPONENT", "CAR SIM", 1);
		   //	lcdtextwrite( "CAR COMPONENT", str_cnt, 2);
  	  		//lcdtextwrite( "CAR COMPONENT", "CAR SIM", 2);
		  	//윗단에 "CAR COMPONENT"
		  	// 네모 2개
		}
		else if (now_level == CRS_UPHILL)
		{
            str1 = "UP HILL        ";   
		   //	lcdtextwrite( "UP HILL        ", "CAR SIMU", 1);
		   //	lcdtextwrite( "UP HILL        ", str_cnt, 2);
  	  		//lcdtextwrite( "UP HILL        ", "CAR SIMU", 2);
		  	// 윗단에 "UP HILL" 
		}
		else if (now_level == CRS_JUNCTION_1|| now_level == CRS_JUNCTION_2 )
		{
            str1 = "JUNCTION   ";   
	  	 //	lcdtextwrite( "JUNCTION   ", "CAR SIMUL", 1);
	  	 //	lcdtextwrite( "JUNCTION   ", str_cnt, 2);
    			//lcdtextwrite( "JUNCTION   ", "CAR SIMUL", 2);
	  		// "JUNCTION"
	  	}
	  	else if (now_level == CRS_PARKING)
	  	{
            str1 = "PARKING         ";
	     //	lcdtextwrite( "PARKING         ", "CAR SIMULA", 1);
			 //  lcdtextwrite( "PARKING         ", str_cnt, 2);
  			//lcdtextwrite( "PARKING         ", "CAR SIMULA", 2);
			  // "PARKING"
		}
		else if (now_level == CRS_EMERGENCY_A||now_level == CRS_EMERGENCY_B|| now_level == CRS_EMERGENCY_C||now_level == CRS_EMERGENCY_D)
		{
            str1 = "EMERGENCY         ";
         
		  // 	lcdtextwrite( "EMERGENCY         ", "CAR SIMULAT", 1);
		   //	lcdtextwrite( "EMERGENCY         ", str_cnt, 2);
  	  		//lcdtextwrite( "EMERGENCY         ", "CAR SIMULAT", 2);
		  	// "EMERGENCY"
		}
		else if (now_level == CRS_ACCEL)
		{
            str1 = "ACCELATE         ";
		   //	lcdtextwrite( "ACCELATE         ", "CAR SIMULATO", 1);
		  // 	lcdtextwrite( "ACCELATE         ", str_cnt, 2);
  	  		//lcdtextwrite( "ACCELATE         ", "CAR SIMULATO", 2);
		  	// "ACCELERATE"
		}
	    else if (now_level == CRS_END)
		{
            str1 = "END                  ";
		  //	lcdtextwrite( "END                  ", "CAR SIMULATOR", 1);
		  //	lcdtextwrite( "END                  ", str_cnt, 2);
  	  		//lcdtextwrite( "END                  ", "CAR SIMULATOR", 2);
		  	// "END"
	    }
    }
  } 
*/
/*---------------------------------------바이패스--------------------------------------*/

int satetybelt_bypass = 0;
//int safetybelt = 0;
//int testfail = 0;

while (satetybelt_bypass==1) {
    testfail = 0;
 if(satetybelt_bypass == 0)
 {
     beake;
 }
}
if (satetybelt_bypass == 0 && safetybelt == 0) {
    testfail = 1;
}

int sidebrake_bypass = 0;
//int sidebrake = 1;
//int minuspoint = 0;

while (sidebrake_bypass == 1) {
    minuspoint = 0;
    if (sidebrake_bypass == 0)
    { 
        break; 
    }
}
if (sidebrake_bypass == 0 && sidebrake == 1) {
    minus_point += 5;
}

/*---------------------------------------바이패스--------------------------------------*/
void *count(void)
  {

    while (1)
	{
      //cnt += 1;
        if (cnt[0] == 9) 
        {
            cnt[0] = 0;
            cnt[1]++;
        }
        else 
        {
            cnt[0]++;
        }
 // 10초 단위 검사 
   	    if (now_level == CRS_MAIN)
		{
            str1 = "PRESS START";
	  	}
        else if(now_level == CRS_MANUAL)
        {
            str1 = "MANUAL        ";
        }  
		else if (now_level == CRS_START)	
		{
            str1 = "BEGIN         ";
		}
		else if (now_level == CRS_BASIC)
		{
            str1 = "CAR COMPONENT";
		}
        //CAR COMPONENT에서 다음으로 안 넘어가고 시간도 멈춤..
		else if (now_level == CRS_UPHILL)
		{
            str1 = "UP HILL        ";
		}
		else if (now_level == CRS_JUNCTION_1 || now_level == CRS_JUNCTION_2 )
		{
            str1 = "JUNCTION   ";
	  	}
	  	else if (now_level == CRS_PARKING)
	  	{
            str1 = "PARKING         ";
		}
		else if (now_level == CRS_EMERGENCY_A || now_level == CRS_EMERGENCY_B || now_level == CRS_EMERGENCY_C || now_level == CRS_EMERGENCY_D)
		{
            str1 = "EMERGENCY         ";
		}
		else if (now_level == CRS_ACCEL)
		{
            str1 = "ACCELATE         ";
		}
	    else if (now_level == CRS_END)
		{
            str1 = "END                  ";
	    }
        sprintf(str_cnt0, "%d", cnt[0]);
        sprintf(str_cnt1, "%d", cnt[1]);
        sprintf(str_cnt2, "%d", cnt[2]);
        sprintf(str_cnt3, "%d", cnt[3]);
        sprintf(str_cnt, "           %d:%d%d",  cnt[2], cnt[1], cnt[0]);
		usleep(50000);    //테스트용
        //sleep(1);       //시연용
        lcdtextwrite( str1, str_cnt, 1);
	    lcdtextwrite( str1, str_cnt, 2);
        //sprintf(str1, "%s", "PRESS START");
    }  
}
  

void *textlcd()
{
  txtlcd_Init();
  //BASIC UP JUNCTION PARIKNG EMERGENCY ACCEL END

  pthread_create(&tid[0], NULL ,&count, NULL);
  //pthread_create(&tid[1], NULL ,&txtdisplay, NULL);

  pthread_join (tid[0], NULL);
  //pthread_join (tid[1], NULL);
}
  //9 단계로 나뉨 CAR SIMULATOR
 // txtlcd_off();
 // txtlcd_Init();
 // sleep(1);
 // lcdtextwrite(str1, str2,0);


void *buzzerwork(void) {
    while(1) {
        if(now_level == CRS_START && (now_level != prev_level) )
// MANUAL에서 START로 넘어가면
{
    soundEffect(SE_START);
    // START 단계에서는 START 소리 출력
    prev_level = now_level;
}

else if(now_level == CRS_EMERGENCY_A || now_level == CRS_EMERGENCY_B || now_level == CRS_EMERGENCY_C || now_level == CRS_EMERGENCY_D && now_level != prev_level)
{
    soundEffect(SE_ACCIDENT);
    // EMERGENCY 단계에서는 ACCIDENT 소리 출력
    prev_level = now_level;
}

else if(now_level != prev_level)
//now_level이 넘어가서 prev_level과 달라지면 now_level이 변한 것
{
    soundEffect(SE_ENDTURN);
    //level이 바뀌면 TURN바뀌는 소리를 버저로 출력
    prev_level = now_level;
    // prev_level도 다음 level로 바꿔주기
}
    }
}


void *fndwork(void) {
	while (1)
	{
		if (simuwork == 1)
			dispnum = c_score * 1000;
		int off_main[6] = {1, 1, 1, 0, 0, 0};
		if (c_score < 100)
			off_main[0] = 0;
		if (c_score < 10)
			off_main[1] = 0;
		fndDisp_canoff(dispnum, 0b1000, off_main);

		if (minuspoint > 0)
			ScoreAnim();
	}
}

void ScoreAnim()
{
	int off4_backup = 0, off5_backup = 0;
	int off[6] = {1, 1, 1, 0, 1, 1};
	dispnum = c_score * 1000 + minuspoint;

	if (minuspoint < 10)
		off[4] = 0;
	if (c_score < 100)
		off[0] = 0;
	if (c_score < 10)
		off[1] = 0;
	fndDisp_canoff(dispnum, 0b1000, off); // (현재점수 -까일점수)

	off4_backup = off[4];
	off5_backup = off[5];
	for (int i = 0; i < 8; i++)
	{
		if (off4_backup == 1)
			off[4] ^= 1;
		if (off5_backup == 1)
			off[5] ^= 1;
		fndDisp_canoff(dispnum, 0b1000, off);
		usleep(250000); // 0.5초
	}
	off[4] = off4_backup;
	off[5] = off5_backup;

	while (minuspoint > 0)
	{
		if (c_score < 100) // 현재 점수가 100보다 작으면 100의자리 LED 꺼짐
			off[0] = 0;
		if (c_score < 10) // 현재 점수가 10보다 작으면 10의자리 LED 꺼짐
			off[1] = 0;
		if (minuspoint < 10) // 감점할 점수가 10보다 작으면 10의자리 LED 꺼짐
			off[4] = 0;


		dispnum = c_score * 1000 + minuspoint;
		fndDisp_canoff(dispnum, 0b1000, off);
		usleep(70000); // 0.07초
		--minuspoint;
		--c_score;

		printf("number :%d\n", c_score);
	}

	dispnum = c_score * 1000;
	off[5] = 0; // minuspoint 다 처리됐으니 1의 자리도 끄기
	fndDisp_canoff(dispnum, 0b1000, off);

	if (c_score < 80)
		testfail = 1;
}

void *touchscreen(void)
{
    touchInit();

	/*
	int scBTN_Start = 0;
	int scBTN_Manual = 0;
	int scBTN_Leaderbd = 0;
	//first 부분에서 동작하는 변수들


	int scBTN_prevpage = 0;
	int scBTN_Nextpage = 0;
	int scBTN_gotomain = 0;
	int scBTN_gotostart = 0;
	// second 부분에서 동작하는 변수들
	
	int scBTN_startup = 0;
	int scBTN_Wiper = 0;
	int scBTN_Lightup = 0;
	int scBTN_Lightdown = 0;
	//third 부분에서 동작하는 변수들
*/

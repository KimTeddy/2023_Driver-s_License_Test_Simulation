#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <sys/shm.h>

int scBTN_Start=0, scBTN_Manual=0, scBTN_Leaderbd=0; // 스크린터치로 인식할 시작/코스설명/리더보드 버튼 변수
int page; // 코스 설명 이미지 페이지 카운팅
int testStart=0, mainScreen=0;

// LCD에 구간 표시하기 위한 트리거 신호들
int crs_basic = 0; //기본조작평가 트리거 신호
int crs_uphill = 0; //경사로 구간 트리거
int crs_junction = 0; //교차로 구간 트리거
int crs_parking = 0; //주차구간 트리거
int crs_emergency = 0; //돌발구간 트리거
int crs_accel = 0; //가속구간 트리거

//additional part 
int crs_outofcrs = 0; //구간을 벗어난 경우 트리거 ->  

void showMainScreen() {
    //메인 화면 출력. 디자인 구상 UI idea에 구상 올려둠 / 버튼 표시로 버튼을 누르면 위의 변수 바뀜.
    while(1) {
    if(scBTN_Start) driveTest();
    else if(scBTN_Manual) showManual();
    else if(scBTN_Leaderbd) showLeaderBoard();
    }
}


void driveTest () { //시험 코스 진행할 것 작성
int next=1; // teststart = 1, mainmenu = 2 : default teststart
//시험을 시작하기에 앞서 코스 설명을 진행하겠습니다. (스킵 여부 물어서 스킵 가능하게.)
if(manualSkip==0) next=showManual();
//화면의 시작하기를 누를경우(testStart)
if(next==1) {
    scBTN_Start = 0;
    next=0;
    //시험 내용 작성

}
else if(next==2) return;
}


int showManual () { //코스 설명 작성
scBTN_Manual=0;
 // 코스 설명 구간별로 이미지로 작성해서 띄우면 좋을것 같다고 생각.
 // 구간별 점수 및 전역 감점및 실격 요소, 제한시간 등 안내. 이미지 수동으로 넘기는 방식으로.
 while(testStart!=1 | mainScreen!=1) { // 마지막페이지에서 메인화면 혹은 시험 시작을 선택할 때 까지 대기.
 if(page==마지막페이지) {
    
 if(scBTN_Start) // 시험시작으로 코스설명에 진입했을경우 testStart(시작하기)버튼과 mainScreen(메인화면) 버튼 표시
 else  //메인화면에서 설명보기로 진입했을경우 mainScreen(메인화면) 버튼 표시

 }
 }
 if(testStart) return 1;  //시험시작 선택시 1(teststart) 리턴.
else if(mainScreen) return 2; //메인화면 선택시 2(mainmenu) 리턴.
}



void showLeaderBoard () { //리더보드 내용 작성
//디자인 구상 UI idea에 구상 올려둠
    while(mainscreen!=1) {}
    return;
}

void addLeaderBoard () {} //리더보드 편집 함수 작성



int main() {  // 여기에 이후에 thread 이동 예정.  
    while(1) {
   showMainScreen(); //메인 화면 출력 및 시험 진행
    }
}
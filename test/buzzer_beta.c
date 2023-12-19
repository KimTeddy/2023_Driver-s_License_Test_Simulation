
// now_level의 변화를 알기 위한 prev_level 변수
/* 각 상태별로 정의된 것들
#define SE_MUTE     -1 // mute
#define SE_CEG       0 // 도미솔
#define SE_MUSIC     1 // MISIC(for test)
#define SE_PITCH     2 // play pitch
#define SE_SIREN     3 // siren
#define SE_START     4 // start sound
#define SE_ENDTURN   5 // 1 turn end
#define SE_MINUS     6 // wheel on the line
#define SE_ACCIDENT  7 // accident sound


#define CRS_MAIN		 0   //메인 메뉴
#define CRS_MANUAL		 1   //설명
#define CRS_START		 2   //시뮬레이션 시작 -> START 소리 출력
#define CRS_BASIC		 3   //기본 조작 단계
#define CRS_UPHILL		 4   //경사로
#define CRS_JUNCTION_1	 5   //교차로1
#define CRS_PARKING		 6   //주차
#define CRS_JUNCTION_2	 7   //교차로2

EMERGENCY 부분에서는 ACCIDENT 소리
#define CRS_EMERGENCY_A	 8   //돌발1 
#define CRS_EMERGENCY_B	 9   //돌발2
#define CRS_EMERGENCY_C	10   //돌발3
#define CRS_EMERGENCY_D	11   //돌발4
#define CRS_ACCEL		12   //가속 구간
#define CRS_END		    13   //종료


*/
int prev_level = now_level;
if(now_level == CRS_START)
// MANUAL에서 
{
    soundEffect(SE_START);
    // START 단계에서는 START 소리 출력
    prev_level = now_level;
}

else if(now_level == CRS_EMERGENCY_A || CRS_EMERGENCY_B || CRS_EMERGENCY_C || CRS_EMERGENCY_D)
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
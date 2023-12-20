//"100  "-> 유지하다가    깜빡"100 -5","99 -4","98 -3", "97 -3", "96 -2", "95 -1"깜빡       "95    "->유지
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fnd.h"

#define MAX_FND_NUM 6
#define FND_DATA_BUFF_LEN (MAX_FND_NUM + 2)
#define FND_DRIVER_NAME "/dev/perifnd"
#define BLINK_DELAY_MS 500

// 메인 코드에 넣을 것
int c_score = 100; // 처음 점수는 만점
int minuspoint = 0;
int dispnum = 0;

// 그냥 테스트용 변수(이미 있는 것 포함)
int simuwork = 1;
int testfail = 0;
int fortest = 0;
void ScoreAnim();

// c_score변수는 100이고 minuspoint 변수에 5를 받았을때
int main()
{
		if (simuwork == 1)
			dispnum = c_score * 1000;
		int off_main[6] = {1, 1, 1, 0, 0, 0};
		if (c_score < 100)
			off_main[0] = 0;
		if (c_score < 10)
			off_main[1] = 0;
		fndDisp_canoff(dispnum, 0b1000, off_main);
	 usleep(900000);

	minuspoint = 5;
		ScoreAnim();
	minuspoint = 15;
		ScoreAnim();
	minuspoint = 10;
		ScoreAnim();
		/*
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
	}*/
	return 0;
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

		// if (fortest)
		// {
		// 	minuspoint += 5;
		// 	fortest = 0;
		// }

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


// minuspoint = 5;
// ScoreAnim();
// fortest = 1;
// minuspoint = 10;
// ScoreAnim();
// minuspoint = 15;
// ScoreAnim();
// minuspoint = 45;
// ScoreAnim();




// while (testfail == 1) // 실격일때, wasted
// {
// 	char ch[7] = "wasted";
// 	fndDisp_ch(ch);
// }
// while (minuspoint != 0) // minuspoint 변수에 0이 아닌 숫자가 들어온다
//{
// switch (minuspoint)
// {
// case 5: //-5 포인트가 되었을때,
// {
// 	for (int i = 0; i < 6; i++)
// 	{ // 0~5까지 6번 돌아

// 		snprintf(buffer, sizeof(buffer), "%3d-%2d", c_score, minuspoint);
// 		fndDisp_ch(buffer);
// 		usleep(500000); // 0.5초 = 500000 마이크로초
// 		fndDisp_ch(zero);
// 		fndDisp(minuspoint, 0);
// 		usleep(500000); // 0.5초 = 500000 마이크로초
// 		--minuspoint;
// 		--c_score;
// 	}
// }
// break;
// case 7:
// {
// 	for (int i = 0; i < 7; i++)
// 	{ // 0~6까지 7번 돌아

// 		snprintf(buffer, sizeof(buffer), "%3d-%2d", c_score, minuspoint);
// 		fndDisp_ch(buffer); //(현재점수 -까일점수)
// 		usleep(500000);		// 0.5초 = 500000 마이크로초
// 		fndDisp_ch(zero);
// 		fndDisp(minuspoint, 0); // 다 꺼짐
// 		usleep(500000);			// 0.5초 = 500000 마이크로초
// 		--minuspoint;
// 		--c_score;
// 	}
// }
// break;
// case 10:
// {
// 	for (int i = 0; i < 10; i++)
// 	{ // 0~9까지 10번 돌아

// 		snprintf(buffer, sizeof(buffer), "%3d-%2d", c_score, minuspoint);
// 		fndDisp_ch(buffer); //(현재점수 -까일점수)
// 		usleep(500000);		// 0.5초 = 500000 마이크로초
// 		fndDisp_ch(zero);
// 		fndDisp(minuspoint, 0); // 다 꺼짐
// 		usleep(500000);			// 0.5초 = 500000 마이크로초
// 		--minuspoint;
// 		--c_score;
// 	}
// }
// break;
//}
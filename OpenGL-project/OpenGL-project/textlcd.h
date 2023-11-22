#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define CRS_MAIN 0  //메인 메뉴 단게
#define CRS_START 1 // 코스 시작 전 대기 (게임 시작 전 -> ~설명 단계~)
#define CRS_BASIC 2 //기본 조작 단계
#define CRS_UP 3    //경사로
#define CRS_JUNCTION 4  //교차로
#define CRS_PARKING 5   //주차
#define CRS_EMERGENCY 6 //돌발
#define CRS_ACCEL 7     //가속 구간
#define CRS_END 8	//종료

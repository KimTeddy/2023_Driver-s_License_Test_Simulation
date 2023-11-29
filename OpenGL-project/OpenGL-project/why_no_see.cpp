#ifdef __LINUX//리눅스전용
#include "GL/freeglut.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/shm.h>
#else//윈도우전용
#include <GL/glut.h>
#include <iostream>
using namespace std;
#endif

//공통
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simuwork.h"

#ifdef __LINUX//리눅스 전용 코딩
pthread_t thread_object_1; //스레드 1 for rgb led
pthread_t thread_object_2; //스레드 2 for btn and led
pthread_t thread_object_3; //스레드 3 for 7segment
#endif

#define PI 3.141592
////////////경로 변수
float whitepath1[][6] = {
    {-87, -0.5, 9, -87, -0.5, 45},
    {-87, -0.5, 55,  91, -0.5, 55},
    {91, -0.5, 55,   91, -0.5, -61},
    {91, -0.5, -61,   -97, -0.5, -61},
    {-76, -0.5, 9,   -76, -0.5, 36},
    {-76, -0.5, 36,   -9, -0.5, 36},
    {-9, -0.5, 36,   -9, -0.5, 9},
    {-76, -0.5, 9,   -9, -0.5, 9},
    {9, -0.5, 9,   9, -0.5, 36},
    {9, -0.5, 36,  73, -0.5, 36},
    {73, -0.5, 36,  73, -0.5, 9},
    {9, -0.5, 9,  73, -0.5, 9},
    {9, -0.5, -43,  9, -0.5, -9},
    {9, -0.5, -9,  73, -0.5, -9},
    {73, -0.5, -9,  73, -0.5, -43},
    {9, -0.5, -43,   73, -0.5, -43},
    {-76, -0.5, -43,   -76, -0.5, -9},
    {-76, -0.5, -9,   -9, -0.5, -9},
    {-9, -0.5, -9,  -9, -0.5, -43},
    {-76, -0.5, -43,   -9, -0.5, -43}
};
//주황 경로 좌표(바퀴가 닿으면 -5출력)
float lines[][6] = {
    {-87, -0.5, 9,  -87, -0.5, 45},
    {-87, -0.5, 45,  82, -0.5, 45},
    {82, -0.5, 45,  82, -0.5, 9},
    {0, -0.5, 36,  0, -0.5, 36},
    {-17, -0.5, 0,  -87, -0.5, 0},
    {-87, -0.5, 0,  -87, -0.5, -52},
    {-87, -0.5, -52,  82, -0.5, -52},
    {82, -0.5, -52,  82, -0.5, -9},
    {0, -0.5, -52,  0, -0.5, -12},
    {7, -0.5, 0, 67, -0.5, 0}
};
float rqLines1[][6] = {
    {-97, -0.5, 26,  -73, -0.5, 26},
    {-19, -0.5, 0,  -19, -0.5, 9},
    {67, -0.5, 0,  67, -0.5, 9},
    {9, -0.5, 0,  9, -0.5, -9},
    {-9, -0.5, -17,  0, -0.5, -17},
    {73, -0.5, 9,  91, -0.5, 9}
};
//////////////
int simuwork = 0; //시뮬레이션 게임(?) 동작 여부 확인변수
int safetybelt = 0, sidebrake = 0, leftlight = 0, rightlight = 0, emerlight = 0; // 안전벨트, 사이드브레이크, 방향지시등좌, 우, 비상등 변수
int fnddat; // FND(7segment) 데이터 변수

//이거 신경 안 써도 됨
int Width, Height;
int mouse_x = 0;//마지막으로 클릭한 위치
int mouse_y = 0;
int rotationX = 0, rotationY = 0;
float view_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };

//이게 전부 자동차 관련
float dspeed, speed;
float dxcar = 0, dycar = 0, xcar = 0, ycar = 0;//이동
float rcar;//로테이션
bool acceration = false;

void perspective(GLdouble fovy, GLdouble zfar);
void changeSize(int w, int h);

void perspective(GLdouble fovy = 75.0, GLdouble zfar = 500.0) {
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, (double)Width / (double)Height, 1.0, zfar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void changeSize(int w, int h) {
    if (h == 0)  h = 1;
    Width = w;
    Height = h;
    //float ratio = w * 1.0 / h;
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glViewport(0, 0, w, h);
    //gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    //glMatrixMode(GL_MODELVIEW);
    perspective();
}
void idle() {
    //acceration = false;
}
void Timer(int val) {
    if (acceration == true)
    {
        if (speed >= 0)speed -= 0.001f;
        else speed = 0;
        dspeed += speed;
    }

    glutPostRedisplay();
    glutTimerFunc(1, Timer, 0);
}

void drawingCar() {//자동차 모델링, 이동, 회전
    // 차 앞위 부분
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(8, 3, 4);   // A
    glVertex3i(8, 3, -4);  // B
    glVertex3i(3, 3, -4);  // C
    glVertex3i(3, 3, 4);   // D
    glEnd();

    // 차 범퍼부분 
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(8, 3, 4);   // A
    glVertex3i(8, 3, -4);  // B
    glVertex3i(8, 0, -4);  // F
    glVertex3i(8, 0, 4);   // E
    glEnd();

    // 차 바퀴 기준 앞 부분 
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(8, 3, 4);   // A
    glVertex3i(6, 3, 4);   // G
    glVertex3i(6, 0, 4);   // H
    glVertex3i(8, 0, 4);   // E
    glEnd();

    // 차 바퀴 기준 앞 부분 [RIGHT]
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(8, 3, -4);   // A
    glVertex3i(6, 3, -4);   // G
    glVertex3i(6, 0, -4);   // H
    glVertex3i(8, 0, -4);   // E
    glEnd();


    // 차 바퀴 기준 윗 부분 
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(6, 3, 4);   // G
    glVertex3i(3, 3, 4);   // D
    glVertex3i(3, 1, 4);  // J
    glVertex3i(6, 1, 4);   // M
    glEnd();

    // 차 바퀴 기준 가운데 부분 
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(3, 3, 4);   // D
    glVertex3i(3, 0, 4);   // I
    glVertex3i(-3, 0, 4);   // N 
    glVertex3i(-3, 3, 4);   // O
    glEnd();

    // 차 바퀴 기준 윗 부분 [RIGHT]
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(6, 3, -4);   // G
    glVertex3i(3, 3, -4);   // D
    glVertex3i(3, 1, -4);  // J
    glVertex3i(6, 1, -4);   // M
    glEnd();

    // 차 바퀴 기준 가운데 부분 [RIGHT]
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(3, 3, -4);   // D
    glVertex3i(3, 0, -4);   // I
    glVertex3i(-3, 0, -4);   // N 
    glVertex3i(-3, 3, -4);   // O
    glEnd();

    //차 앞 유리 프레임1
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(3, 6, 4);   // P
    glVertex3i(3, 6, 3);   // V
    glVertex3i(3, 3, 3);   // T
    glVertex3i(3, 3, 4);   // D
    glEnd();
    //차 앞 유리 프레임2
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(3, 6, 4);   // P
    glVertex3i(3, 6, -4);   // Q
    glVertex3i(3, 5, -4);   // X
    glVertex3i(3, 5, 4);   // Y
    glEnd();
    //차 앞 유리 프레임3
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(3, 6, -3);   // W
    glVertex3i(3, 6, -4);   // Q
    glVertex3i(3, 3, -4);   // C
    glVertex3i(3, 3, -3);   // U
    glEnd();

    //차 앞 유리
    glColor3f(0.0, 0.0, 0.0);   //BLACK
    glBegin(GL_POLYGON);
    glVertex3i(3, 5, 3);   // R
    glVertex3i(3, 5, -3);   // S
    glVertex3i(3, 3, -3);   // U
    glVertex3i(3, 3, 3);   // T
    glEnd();

    //차 뒷 유리 프레임1
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, 4);   // P(X - 8)
    glVertex3i(-6, 6, 3);   // V
    glVertex3i(-6, 3, 3);   // T
    glVertex3i(-6, 3, 4);   // D
    glEnd();
    //차 뒷 유리 프레임2
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, 4);   // P
    glVertex3i(-6, 6, -4);   // Q
    glVertex3i(-6, 5, -4);   // X
    glVertex3i(-6, 5, 4);   // Y
    glEnd();
    //차 뒷 유리 프레임3
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, -3);   // W
    glVertex3i(-6, 6, -4);   // Q
    glVertex3i(-6, 3, -4);   // C
    glVertex3i(-6, 3, -3);   // U
    glEnd();

    //차 뒷 유리
    glColor3f(0.0, 0.0, 0.0);   //BLACK
    glBegin(GL_POLYGON);
    glVertex3i(-6, 5, 3);   // R
    glVertex3i(-6, 5, -3);   // S
    glVertex3i(-6, 3, -3);   // U
    glVertex3i(-6, 3, 3);   // T
    glEnd();

    //차 옆 유리 프레임1 
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, 4);   // A1
    glVertex3i(-5, 6, 4);   // B1
    glVertex3i(-5, 3, 4);   // C1
    glVertex3i(-6, 3, 4);   // Z
    glEnd();
    //차 옆 유리 프레임2 
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, 4);   // A1
    glVertex3i(3, 6, 4);   // P
    glVertex3i(3, 5, 4);   // Y
    glVertex3i(-6, 5, 4);   // H1
    glEnd();
    //차 옆 유리 프레임3
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(2, 6, 4);   // G1
    glVertex3i(3, 6, 4);   // P
    glVertex3i(3, 3, 4);   // D
    glVertex3i(2, 3, 4);   // F1
    glEnd();
    //차 옆 유리
    glColor3f(0.0, 0.0, 0.0);   //BLACK
    glBegin(GL_POLYGON);
    glVertex3i(-5, 5, 4);   // D1
    glVertex3i(2, 5, 4);   //E1
    glVertex3i(2, 3, 4);   // F1
    glVertex3i(-5, 3, 4);   // C1
    glEnd();

    // 차 옆 유리 프레임1 [RIGHT]
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, -4);   // A1
    glVertex3i(-5, 6, -4);   // B1
    glVertex3i(-5, 3, -4);   // C1
    glVertex3i(-6, 3, -4);   // Z
    glEnd();
    //차 옆 유리 프레임2 [RIGHT]
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, -4);   // A1
    glVertex3i(3, 6, -4);   // P
    glVertex3i(3, 5, -4);   // Y
    glVertex3i(-6, 5, -4);   // H1
    glEnd();
    //차 옆 유리 프레임3 [RIGHT]
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(2, 6, -4);   // G1
    glVertex3i(3, 6, -4);   // P
    glVertex3i(3, 3, -4);   // D
    glVertex3i(2, 3, -4);   // F1
    glEnd();
    //차 옆 유리 [RIGHT]
    glColor3f(0.0, 0.0, 0.0);   //BLACK
    glBegin(GL_POLYGON);
    glVertex3i(-5, 5, -4);   // D1
    glVertex3i(2, 5, -4);   //E1
    glVertex3i(2, 3, -4);   // F1
    glVertex3i(-5, 3, -4);   // C1
    glEnd();

    //차 뚜껑
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(3, 6, -4);   // Q
    glVertex3i(3, 6, 4);   // P
    glVertex3i(-6, 6, 4);   // A1
    glVertex3i(-6, 6, -4);   // I1
    glEnd();

    //택시 표시하는 거(뚜껑 위에)1
    glColor3f(1.0, 1.0, 0.0);   //Yellow
    glBegin(GL_POLYGON);
    glVertex3i(-3, 7, 2);   // M1
    glVertex3i(-1, 7, 2);   // N1
    glVertex3i(-1, 6, 2);   // K1
    glVertex3i(-3, 6, 2);   // J1
    glEnd();
    //택시 표시하는 거(뚜껑 위에)2
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-1, 7, 2);   // N1
    glVertex3i(-1, 7, -2);   // O1
    glVertex3i(-1, 6, -2);   // L1
    glVertex3i(-1, 6, 2);   // K1
    glEnd();
    //택시 표시하는 거(뚜껑 위에)3 O1 P1 Q1 L1
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-1, 7, -2);   // O1
    glVertex3i(-3, 7, -2);   // P1
    glVertex3i(-3, 6, -2);   // Q1
    glVertex3i(-1, 6, -2);   // L1
    glEnd();
    //택시 표시하는 거(뚜껑 위에)4 P1 M1 J1 Q1
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-3, 7, -2);   // P1
    glVertex3i(-3, 7, 2);   // M1
    glVertex3i(-3, 6, 2);   // J1
    glVertex3i(-3, 6, -2);   // Q1
    glEnd();
    //택시 표시하는 거(뚜껑 위에)5 [뚜껑] P1 O1 N1 M1
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-3, 7, -2);   // P1
    glVertex3i(-1, 7, -2);   // O1
    glVertex3i(-1, 7, 2);   // N1
    glVertex3i(-3, 7, 2);   // M1
    glEnd();

    //후면 바퀴 윗 부분 T1 O R1 S1
    glColor3f(1.0, 1.0, 1.0);   //PINK
    glBegin(GL_POLYGON);
    glVertex3i(-6, 3, 4);   // T1
    glVertex3i(-3, 3, 4);   // O
    glVertex3i(-3, 1, 4);   // R1
    glVertex3i(-6, 1, 4);   // S1
    glEnd();

    //후면 바퀴 뒷 부분 [RIGHT]
    glColor3f(1.0, 1.0, 1.0);   //PINK
    glBegin(GL_POLYGON);
    glVertex3i(-9, 3, 4);   // K
    glVertex3i(-6, 3, 4);   // T1
    glVertex3i(-6, 0, 4);   // U1
    glVertex3i(-9, 0, 4);   // L
    glEnd();

    //후면 바퀴 윗 부분 [RIGHT]
    glColor3f(1.0, 1.0, 1.0);   //PINK
    glBegin(GL_POLYGON);
    glVertex3i(-6, 3, -4);   // T1
    glVertex3i(-3, 3, -4);   // O
    glVertex3i(-3, 1, -4);   // R1
    glVertex3i(-6, 1, -4);   // S1
    glEnd();

    //후면 바퀴 뒷 부분 K T1 U1 L
    glColor3f(1.0, 1.0, 1.0);   //PINK
    glBegin(GL_POLYGON);
    glVertex3i(-9, 3, -4);   // K
    glVertex3i(-6, 3, -4);   // T1
    glVertex3i(-6, 0, -4);   // U1
    glVertex3i(-9, 0, -4);   // L
    glEnd();

    //차 트렁크
    glColor3f(1.0, 1.0, 1.0);   //RED
    glBegin(GL_POLYGON);
    glVertex3i(-9, 3, 4);   // K
    glVertex3i(-9, 3, -4);   // K(-Z)
    glVertex3i(-6, 3, -4);   // Z(-Z)
    glVertex3i(-6, 3, 4);   // Z

    glEnd();

    //차 후면 범퍼 KL,
    glColor3f(1.0, 1.0, 1.0);   // PINK
    glBegin(GL_POLYGON);
    glVertex3i(-9, 3, 4);   // K
    glVertex3i(-9, 0, 4);   // L
    glVertex3i(-9, 0, -4);   // L(-Z)
    glVertex3i(-9, 3, -4);   // K(-Z)
    glEnd();

    //차 손잡이1 [LEFT] A2 B2 C2 D2
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(2, 3, 5);   // A2
    glVertex3i(2, 2, 5);   // B2
    glVertex3i(0, 2, 5);   // C2
    glVertex3i(0, 3, 5);   // D2
    glEnd();
    //차 손잡이2 [LEFT] A2 D2 E2 F1
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(2, 3, 5);   // A2
    glVertex3i(0, 3, 5);   // D2
    glVertex3i(0, 3, 4);   // E2
    glVertex3i(2, 3, 4);   // F1
    glEnd();
    //차 손잡이2 [LEFT] D2 E2 G2 C2
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(0, 3, 5);   // D2
    glVertex3i(0, 3, 4);   // E2
    glVertex3i(0, 2, 4);   // G2
    glVertex3i(0, 2, 5);   // C2
    glEnd();
    //차 손잡이2 [LEFT] A2 F1 F2 B2
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(2, 3, 5);   // A2
    glVertex3i(2, 3, 4);   // F1
    glVertex3i(2, 2, 4);   // F2
    glVertex3i(2, 2, 5);   // B2
    glEnd();

    //차 손잡이1 [RIGHT] 
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(2, 3, -5);   // A2
    glVertex3i(2, 2, -5);   // B2
    glVertex3i(0, 2, -5);   // C2
    glVertex3i(0, 3, -5);   // D2
    glEnd();
    //차 손잡이2 [RIGHT] A2 D2 E2 F1
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(2, 3, -5);   // A2
    glVertex3i(0, 3, -5);   // D2
    glVertex3i(0, 3, -4);   // E2
    glVertex3i(2, 3, -4);   // F1
    glEnd();
    //차 손잡이2 [RIGHT] D2 E2 G2 C2
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(0, 3, -5);   // D2
    glVertex3i(0, 3, -4);   // E2
    glVertex3i(0, 2, -4);   // G2
    glVertex3i(0, 2, -5);   // C2
    glEnd();
    //차 손잡이2 [RIGHT] A2 F1 F2 B2
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(2, 3, -5);   // A2
    glVertex3i(2, 3, -4);   // F1
    glVertex3i(2, 2, -4);   // F2
    glVertex3i(2, 2, -5);   // B2
    glEnd();

    //차 바닥1
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(6, 0, -4);   // A3
    glVertex3i(8, 0, -4);   // F
    glVertex3i(8, 0, 4);   // E
    glVertex3i(6, 0, 4);   // H
    glEnd();
    //차 바닥2
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(-3, 0, -4);   // N(Z-8)
    glVertex3i(3, 0, -4);   // I(Z-8)
    glVertex3i(3, 0, 4);   // I
    glVertex3i(-3, 0, 4);   // N
    glEnd();
    //차 바닥3
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(-9, 0, 4);   // L
    glVertex3i(-9, 0, -4);   // L(Z-8)
    glVertex3i(-6, 0, -4);   // U1(Z-8)
    glVertex3i(-6, 0, 4);   // U1
    glEnd();
}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q': case 'Q': exit(0); break;
    case 'r': case 'R': glClearColor(1.0, 0.0, 0.0, 1.0); break;
    case 'w':
        /*acceration = true;
        if (speed < 5)
            speed += 0.1f;
        else speed = 0;
        dspeed += speed;*/
        speed = 1;
        dxcar = speed * cos((180 - rcar) * PI / 180.0); xcar += dxcar;
        dycar = speed * sin((180 - rcar) * PI / 180.0); ycar += dycar;
        break;
    case 's': break;
    case 'a': rcar += 3; printf("r=%f\n", rcar); break;
    case 'd': rcar -= 3; printf("r=%f\n", rcar); break;
    }
    glutPostRedisplay();
}

void drawingCar_test() {//테스트용 자동차 모델링, 이동, 회전
    glPushMatrix();
    glTranslatef(xcar, 1, ycar);//자동차 이동
    glRotatef(rcar, 0.0f, 1.0f, 0.0f);//자동차 회전
    //glRotatef(180, 0.0f, 1.0f, 0.0f);//자동차 회전
    //glBegin(GL_LINES);
    //    glColor3f(0.0, 0.0, 1.0);
    //    glVertex3f(0.0, 0.0, 0.0);  glVertex3f(-10.0, 0.0, 0.0); /* Z axis  */
    //glEnd();
    glRotatef(180, 0.0f, 1.0f, 0.0f);//자동차 회전
    drawingCar();
    //glutWireCube(5.0);
    glPopMatrix();
}
void drawScene() {//그릴 물체 전체
    // 평면 그리기
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0.0, -0.5, 0.0);
    glScalef(200.0, -0.5, 120.0);
    glutSolidCube(1.0);

    glPushMatrix();
    glColor3f(0.1, 0.1, 0.1);
    glLineWidth(2);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();

    drawingCar_test();
    //drawingCar();

    //glColor3f(1.0, 0.0, 0.6);
    //glutWireTorus(1, 3, 10, 100);
    /////////////////////////////////////////////////////////
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);  // 흰색설정
    glLineWidth(2.0);         // 두께 2 설정
    glBegin(GL_LINES);
    for (int i = 0; i < 20; ++i) {
        glVertex3f(whitepath1[i][0], whitepath1[i][1], whitepath1[i][2]);
        glVertex3f(whitepath1[i][3], whitepath1[i][4], whitepath1[i][5]);
    }
    for (int i = 0; i < 6; ++i) {
        glVertex3f(rqLines1[i][0], rqLines1[i][1], rqLines1[i][2]);
        glVertex3f(rqLines1[i][3], rqLines1[i][4], rqLines1[i][5]);
    }
    glEnd();

    glColor3f(1.0, 1.0, 0.0);  // 노란색 설정
    glBegin(GL_LINES);
    for (int i = 0; i < 10; ++i) {
        glVertex3f(lines[i][0], lines[i][1], lines[i][2]);
        glVertex3f(lines[i][3], lines[i][4], lines[i][5]);
    }
    glEnd();

    glFlush();
    /////////////////////////////////////////
}
void renderStrokeString(float x, float y, float z, float R, float G, float B, float Scale, void* font, char* string)
{
    char* c;
    glPushMatrix();
    glColor3f(R, G, B);
    glTranslatef(x, y, z);
    glScalef(Scale, Scale, Scale);
    for (c = string; *c != '\0'; c++) {
        glutStrokeCharacter(font, *c);
    }
    glPopMatrix();
}

char start[] = "START";
char info[] = "INFO";
char quit[] = "QUIT";
void main_menu() {
    glClearColor(.9f, .9f, .9f, 1.0f);//배경색

    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    glLineWidth(5);
    renderStrokeString(-20, 0 - 5, 1, 1, 1, 1, 0.1, GLUT_STROKE_ROMAN, start);
    renderStrokeString(-15, -30 - 5, 1, 1, 1, 1, 0.1, GLUT_STROKE_ROMAN, info);
    renderStrokeString(-15, -60 - 5, 1, 1, 1, 1, 0.1, GLUT_STROKE_ROMAN, quit);
    glPopMatrix();

    glColor3f(0.0, 0.3, 0.5);

    //glBegin(GL_QUADS);
    //glVertex3i(304, 0, 276);
    //glVertex3i(718, 0, 276);
    //glVertex3i(718, 0, 357);
    //glVertex3i(304, 0, 357);
    //glEnd();

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(100.0, 1.0, 20.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.3, 0.5);
    glTranslatef(0.0, 0.0, -30.0);
    glScalef(100.0, 1.0, 20.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.3, 0.5);
    glTranslatef(0.0, 0.0, -60.0);
    glScalef(100.0, 1.0, 20.0);
    glutSolidCube(1.0);
    glPopMatrix();
}

void disp() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    if (simuwork == CRS_MAIN)
    {
        perspective();
        glClearColor(.9f, .9f, .9f, 1.0f);//배경색

        glViewport(0, 0, Width, Height);

        glPushMatrix();
        gluLookAt(0.0, -100.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);//카메라 위치/바라보는 초점 위치/카메라 기울임

        glRotatef(rotationX, 1.0, 0.0, 0.0);
        glRotatef(rotationY, 0.0, 1.0, 0.0);
        glMultMatrixf(view_rotate);
        main_menu();



        glPopMatrix();
    }
    else
    {
        perspective();
        glClearColor(.9f, .9f, .9f, 1.0f);//배경색
        glLoadIdentity();

        glViewport(0, 0, Width, Height);

        glPushMatrix();
        gluLookAt(0.0, 30.0, 60.0, 0.0, -1.0, 0.0, 0.0, 1.0, 0.0);//카메라 위치/바라보는 초점 위치/카메라 기울임

        glPushMatrix();

        glRotatef(rotationX, 1.0, 0.0, 0.0);
        glRotatef(rotationY, 0.0, 1.0, 0.0);
        glMultMatrixf(view_rotate);
        drawScene();

        glPopMatrix();
        glPopMatrix();

        //---------------------------------------------------------------

        glViewport(Width * 3 / 5, Height * 3 / 5, Width * 2 / 5, Height * 2 / 5);
        //glViewport(0, Height / 2, Width/3, Height/2);
        glPushMatrix();
        gluLookAt(0.0, 60.0, 10.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);

        drawScene();
        glPopMatrix();
    }
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        cout << x << ", " << y << endl;
        mouse_x = x;
        mouse_y = y;
        simuwork++;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) //마우스 버튼에서 손 뗄 때
    {
    }
    glutPostRedisplay();
}


void motion(int x, int y)
{
    int dx = x - mouse_x;
    int dy = y - mouse_y;

    rotationX += dy;
    rotationY += dx;

    float view_rotate_init[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    for (int i = 0; i < 16; i++) {
        view_rotate[i] = view_rotate_init[i];
    }
    mouse_x = x;
    mouse_y = y;

    glutPostRedisplay();
}

#ifdef __LINUX//리눅스 전용 코딩

void* sevenseg(void) {
    //reset 7seg state
    while (1) {
        if (simuwork == 1) { // repeat if simulation is working
            //100 표시
            //구간별 조건문 작성해야함
        }
    }
}

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
#endif

int main(int argc, char** argv) {
#ifdef __LINUX//리눅스 전용 코딩
    pthread_create(&thread_object_1, NULL, trafLight, NULL);
    pthread_create(&thread_object_2, NULL, btncheck, NULL);
    pthread_create(&thread_object_2, NULL, sevenseg, NULL);

    pthread_join(thread_object_1, NULL);
    pthread_join(thread_object_2, NULL);
    pthread_join(thread_object_3, NULL);

#endif
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    /*float v[] = {
      lightDiffuse[0],  lightDiffuse[1],
      lightDiffuse[2],  lightDiffuse[3] };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, v);*/
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Embedded system");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(disp);
    glutReshapeFunc(changeSize);

    glutTimerFunc(1, Timer, 0);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);
    glutMainLoop();

    return 1;
}

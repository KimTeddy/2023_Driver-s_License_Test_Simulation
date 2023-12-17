#ifdef __LINUX//����������
#include "GL/freeglut.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/shm.h>
#else//����������
#include <GL/glut.h>
#endif
#include <iostream>
/*
#include "winnt.h"
#include "windef.h"
#include "Esent.h"
#include "wingdi.h"*/
using namespace std;

//����
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simuwork.h"

#ifdef __LINUX//������ ���� �ڵ�
pthread_t thread_object_1; //������ 1 for rgb led
pthread_t thread_object_2; //������ 2 for btn and led
pthread_t thread_object_3; //������ 3 for 7segment
#endif

#define PI 3.141592

int simuwork = 0; //�ùķ��̼� ����(?) ���� ���� Ȯ�κ���
int safetybelt = 0, sidebrake = 0, leftlight = 0, rightlight = 0, emerlight = 0; // ������Ʈ, ���̵�극��ũ, �������õ���, ��, ���� ����
int fnddat; // FND(7segment) ������ ����

//�̰� �Ű� �� �ᵵ ��
const int Width=1024, Height=600;
int mouse_x = 0;//���������� Ŭ���� ��ġ
int mouse_y = 0;
int rotationX = 0, rotationY = 0;
float view_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };

//�̰� ���� �ڵ��� ����
float dspeed, speed;
float dxcar = 0, dycar = 0, xcar = 0, ycar = 0;//�ڵ��� �̵�/��ġ
int rcar;//�����̼�
bool acceration = false;

void perspective(GLdouble fovy, GLdouble zfar);
void changeSize(int w, int h);
bool isRectangleOnLines();




void screen_dump()
{
    //W: window with H: window height
    char pixel_data[Width * Height * 300];
    glReadPixels(0, 0, Width, Height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixel_data);

    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    char buff[256];
    char filename[256] = "filename.bmp";
    FILE* out = fopen(filename, "wb");
    char* data = pixel_data;
    memset(&bf, 0, sizeof(bf));
    memset(&bi, 0, sizeof(bi));
    bf.bfType = 'MB';  bf.bfSize = sizeof(bf) + sizeof(bi) + Width * Height * 3;
    bf.bfOffBits = sizeof(bf) + sizeof(bi);
    bi.biSize = sizeof(bi);
    bi.biWidth = Width;  bi.biHeight = Height;
    bi.biPlanes = 1;  bi.biBitCount = 24;
    bi.biSizeImage = Width * Height * 3;
    fwrite(&bf, sizeof(bf), 1, out);
    fwrite(&bi, sizeof(bi), 1, out);
    fwrite(data, sizeof(unsigned char), Height * Width * 3, out);
    fclose(out);
}

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
    if (isRectangleOnLines()) {
        cout << "-5" << endl;
    }
    else {
        //std::cout << "0" << std::endl;
    }
}
void Timer(int val) {
    if(acceration == true)
    {
        if (speed >= 0)speed -= 0.001f;
        else speed = 0;
        dspeed += speed;
    }
    idle();
    glutPostRedisplay();
    glutTimerFunc(1, Timer, 0);
}
int squareVertices[4][2] = {
    {xcar - 5, ycar - 2},
    {xcar + 5, ycar - 2},
    {xcar + 5, ycar + 2},
    {xcar - 5, ycar + 2}
};

// �Ͼ� ��� ��ǥ(������ ������ -5���)
int whitepath1[][4] = {
    {-97, -61, -97, 55},
    {-97, 55 , 91, 55},
    {91, 55, 91, -61},
    {91, -61,-97, -61},
    {-76, 9 , -76, 36},
    {-76, 36, -9, 36},
    {-9, 36, -9, 9},
    {-76, 9,-9, 9},
    {9, 9, 9, 36} ,
    {9, 36, 73, 36},
    {73, 36, 73, 9},
    {9, 9 , 73, 9},
    {9, -43, 9, -9},
    {9, -9, 73, -9},
    {73, -9, 73, -43},
    {9, -43, 73, -43},
    {-76, -43, -76, -9},
    {-76, -9, -9, -9},
    {-9, -9, -9, -43},
    {-76, -43, -9, -43}
};
//��Ȳ ��� ��ǥ(������ ������ -5���)
int lines[][4] = {
    {-87, 9, -87, 45},   // 1. {-87, 9}�� {-87, 45}�� ���� ��
    {-87, 45, 82, 45},   // 2. {-87, 45}�� {82, 45}�� ���� ��
    {82, 45, 82, 9},    // 3. {82, 45}�� {82, 9}�� ���� ��
    {0, 9, 0, 36},      // 4. {0, 9}�� {0, 36}�� ���� ��
    {-17, 0, -87, 0},   // 5. {0, 9}�� {0, 36}�� ���� ��
    {-87, 0, -87, -52}, // 6. {-87, 0}�� {-87, -52}�� ���� ��
    {-87, -52, 82, -52},// 7. {-87, -52}�� {82, -52}�� ���� ��
    {82, -52, 82, -9},  // 8. {82, -52}�� {82, -9}�� ���� ��
    {0, -52, 0, -12},   // 9. {0, -52}�� {0, -12}�� ���� ��
    {7, 0, 67, 0}       // 10. {7, 0}�� {67, 0}�� ���� ��
};
int rqLines1[][4] = {
    {-97, 26, -73, 26},   // 1�� ��
    {-19, 0, -19, 9},     // 2�� ��
    {67, 0, 67, 9},       // 3�� ��
    {9, 0, 9, -9},        // 4�� ��
    {-9, -17, 0, -17},     // 5�� ��
    {73, 9, 91, 9}
};
////////////////////////////////////////////////////////////////
bool isPointOnLine(float x, float y, float x1, float y1, float x2, float y2) {
    // ���� (x1, y1) - (x2, y2) ���� �� (x, y)�� �ִ��� Ȯ��
    float minX = std::min(x1, x2);
    float maxX = std::max(x1, x2);
    float minY = std::min(y1, y2);
    float maxY = std::max(y1, y2);

    return (x >= minX && x <= maxX && y >= minY && y <= maxY);
}
bool isPointOnPath(int x, int y, int x1, int y1, int x2, int y2) {
    int minX = std::min(x1, x2);
    int maxX = std::max(x1, x2);
    int minY = std::min(y1, y2);
    int maxY = std::max(y1, y2);

    return (x >= minX && x <= maxX && y >= minY && y <= maxY);
}
///////////////////////////////////////////////////////
bool isRectangleOnLines() {
    // �簢���� �� �������� �� ���� �ִ��� Ȯ��
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (isPointOnPath(squareVertices[j][0], squareVertices[j][1],
                whitepath1[i][0], whitepath1[i][1], whitepath1[i][2], whitepath1[i][3])) {
                return true; // �簢���� �������� �� ���� �ִٸ� true ��ȯ
            }
        }
    }
    for (int k = 0; k < 10; ++k) {
        for (int t = 0; t < 4; ++t) {
            if (isPointOnLine(squareVertices[t][0], squareVertices[t][1],
                lines[k][0], lines[k][1], lines[k][2], lines[k][3])) {
                return true; // �簢���� �������� �� ���� �ִٸ� true ��ȯ
            }
        }
    }
    return false; // �簢���� �������� �� ���� ���ٸ� false ��ȯ
}
void updateSquareVertices() {
    // Update squareVertices based on the current square position
    squareVertices[0][0] = xcar - 5;
    squareVertices[0][1] = ycar - 2;
    squareVertices[1][0] = xcar + 5;
    squareVertices[1][1] = ycar - 2;
    squareVertices[2][0] = xcar + 5;
    squareVertices[2][1] = ycar + 2;
    squareVertices[3][0] = xcar - 5;
    squareVertices[3][1] = ycar + 2;
}// ���� (x1, y1) - (x2, y2) ���� �� (x, y)�� �ִ��� Ȯ��

void display_lines(int line_width = 5.0) {
    //
    glColor3f(1.0, 1.0, 1.0);  // �������
    glLineWidth(line_width);         // �β� 2 ����
    glBegin(GL_LINES);
    for (int i = 0; i < 20; ++i) {
        glVertex3f(whitepath1[i][0], 0.1, whitepath1[i][1]);
        glVertex3f(whitepath1[i][2], 0.1, whitepath1[i][3]);
    }
    for (int i = 0; i < 6; ++i) {
        glVertex3f(rqLines1[i][0], 0.1, rqLines1[i][1]);
        glVertex3f(rqLines1[i][2], 0.1, rqLines1[i][3]);
    }
    glEnd();
    //
    glColor3f(1.0, 1.0, 0.0);  // ����� ����
    glLineWidth(line_width);         // �β� 2 ����

    glBegin(GL_LINES);
    for (int i = 0; i < 10; ++i) {
        glVertex3f(lines[i][0], 0.1, lines[i][1]);
        glVertex3f(lines[i][2], 0.1, lines[i][3]);
    }
    glEnd();

    //
    glColor3f(0.0, 1.0, 0.0);  // �ʷϻ� ����
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; ++i) {
        glVertex3f(squareVertices[i][0], 0.1, squareVertices[i][1]);
    }
    glEnd();
    //

    glFlush();
}
void drawingCar() {//�ڵ��� �𵨸�, �̵�, ȸ��
    // �� ���� �κ�
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(8, 3, 4);   // A
    glVertex3i(8, 3, -4);  // B
    glVertex3i(3, 3, -4);  // C
    glVertex3i(3, 3, 4);   // D
    glEnd();

    // �� ���ۺκ� 
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(8, 3, 4);   // A
    glVertex3i(8, 3, -4);  // B
    glVertex3i(8, 0, -4);  // F
    glVertex3i(8, 0, 4);   // E
    glEnd();

    // �� ���� ���� �� �κ� 
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(8, 3, 4);   // A
    glVertex3i(6, 3, 4);   // G
    glVertex3i(6, 0, 4);   // H
    glVertex3i(8, 0, 4);   // E
    glEnd();

    // �� ���� ���� �� �κ� [RIGHT]
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(8, 3, -4);   // A
    glVertex3i(6, 3, -4);   // G
    glVertex3i(6, 0, -4);   // H
    glVertex3i(8, 0, -4);   // E
    glEnd();


    // �� ���� ���� �� �κ� 
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(6, 3, 4);   // G
    glVertex3i(3, 3, 4);   // D
    glVertex3i(3, 1, 4);  // J
    glVertex3i(6, 1, 4);   // M
    glEnd();

    // �� ���� ���� ��� �κ� 
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(3, 3, 4);   // D
    glVertex3i(3, 0, 4);   // I
    glVertex3i(-3, 0, 4);   // N 
    glVertex3i(-3, 3, 4);   // O
    glEnd();

    // �� ���� ���� �� �κ� [RIGHT]
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(6, 3, -4);   // G
    glVertex3i(3, 3, -4);   // D
    glVertex3i(3, 1, -4);  // J
    glVertex3i(6, 1, -4);   // M
    glEnd();

    // �� ���� ���� ��� �κ� [RIGHT]
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(3, 3, -4);   // D
    glVertex3i(3, 0, -4);   // I
    glVertex3i(-3, 0, -4);   // N 
    glVertex3i(-3, 3, -4);   // O
    glEnd();

    //�� �� ���� ������1
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(3, 6, 4);   // P
    glVertex3i(3, 6, 3);   // V
    glVertex3i(3, 3, 3);   // T
    glVertex3i(3, 3, 4);   // D
    glEnd();
    //�� �� ���� ������2
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(3, 6, 4);   // P
    glVertex3i(3, 6, -4);   // Q
    glVertex3i(3, 5, -4);   // X
    glVertex3i(3, 5, 4);   // Y
    glEnd();
    //�� �� ���� ������3
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(3, 6, -3);   // W
    glVertex3i(3, 6, -4);   // Q
    glVertex3i(3, 3, -4);   // C
    glVertex3i(3, 3, -3);   // U
    glEnd();

    //�� �� ����
    glColor3f(0.0, 0.0, 0.0);   //BLACK
    glBegin(GL_POLYGON);
    glVertex3i(3, 5, 3);   // R
    glVertex3i(3, 5, -3);   // S
    glVertex3i(3, 3, -3);   // U
    glVertex3i(3, 3, 3);   // T
    glEnd();

    //�� �� ���� ������1
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, 4);   // P(X - 8)
    glVertex3i(-6, 6, 3);   // V
    glVertex3i(-6, 3, 3);   // T
    glVertex3i(-6, 3, 4);   // D
    glEnd();
    //�� �� ���� ������2
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, 4);   // P
    glVertex3i(-6, 6, -4);   // Q
    glVertex3i(-6, 5, -4);   // X
    glVertex3i(-6, 5, 4);   // Y
    glEnd();
    //�� �� ���� ������3
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, -3);   // W
    glVertex3i(-6, 6, -4);   // Q
    glVertex3i(-6, 3, -4);   // C
    glVertex3i(-6, 3, -3);   // U
    glEnd();

    //�� �� ����
    glColor3f(0.0, 0.0, 0.0);   //BLACK
    glBegin(GL_POLYGON);
    glVertex3i(-6, 5, 3);   // R
    glVertex3i(-6, 5, -3);   // S
    glVertex3i(-6, 3, -3);   // U
    glVertex3i(-6, 3, 3);   // T
    glEnd();

    //�� �� ���� ������1 
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, 4);   // A1
    glVertex3i(-5, 6, 4);   // B1
    glVertex3i(-5, 3, 4);   // C1
    glVertex3i(-6, 3, 4);   // Z
    glEnd();
    //�� �� ���� ������2 
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, 4);   // A1
    glVertex3i(3, 6, 4);   // P
    glVertex3i(3, 5, 4);   // Y
    glVertex3i(-6, 5, 4);   // H1
    glEnd();
    //�� �� ���� ������3
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(2, 6, 4);   // G1
    glVertex3i(3, 6, 4);   // P
    glVertex3i(3, 3, 4);   // D
    glVertex3i(2, 3, 4);   // F1
    glEnd();
    //�� �� ����
    glColor3f(0.0, 0.0, 0.0);   //BLACK
    glBegin(GL_POLYGON);
    glVertex3i(-5, 5, 4);   // D1
    glVertex3i(2, 5, 4);   //E1
    glVertex3i(2, 3, 4);   // F1
    glVertex3i(-5, 3, 4);   // C1
    glEnd();

    // �� �� ���� ������1 [RIGHT]
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, -4);   // A1
    glVertex3i(-5, 6, -4);   // B1
    glVertex3i(-5, 3, -4);   // C1
    glVertex3i(-6, 3, -4);   // Z
    glEnd();
    //�� �� ���� ������2 [RIGHT]
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(-6, 6, -4);   // A1
    glVertex3i(3, 6, -4);   // P
    glVertex3i(3, 5, -4);   // Y
    glVertex3i(-6, 5, -4);   // H1
    glEnd();
    //�� �� ���� ������3 [RIGHT]
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(2, 6, -4);   // G1
    glVertex3i(3, 6, -4);   // P
    glVertex3i(3, 3, -4);   // D
    glVertex3i(2, 3, -4);   // F1
    glEnd();
    //�� �� ���� [RIGHT]
    glColor3f(0.0, 0.0, 0.0);   //BLACK
    glBegin(GL_POLYGON);
    glVertex3i(-5, 5, -4);   // D1
    glVertex3i(2, 5, -4);   //E1
    glVertex3i(2, 3, -4);   // F1
    glVertex3i(-5, 3, -4);   // C1
    glEnd();

    //�� �Ѳ�
    glColor3f(1.0, 1.0, 1.0);   //WHITE
    glBegin(GL_POLYGON);
    glVertex3i(3, 6, -4);   // Q
    glVertex3i(3, 6, 4);   // P
    glVertex3i(-6, 6, 4);   // A1
    glVertex3i(-6, 6, -4);   // I1
    glEnd();

    //�ý� ǥ���ϴ� ��(�Ѳ� ����)1
    glColor3f(1.0, 1.0, 0.0);   //Yellow
    glBegin(GL_POLYGON);
    glVertex3i(-3, 7, 2);   // M1
    glVertex3i(-1, 7, 2);   // N1
    glVertex3i(-1, 6, 2);   // K1
    glVertex3i(-3, 6, 2);   // J1
    glEnd();
    //�ý� ǥ���ϴ� ��(�Ѳ� ����)2
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-1, 7, 2);   // N1
    glVertex3i(-1, 7, -2);   // O1
    glVertex3i(-1, 6, -2);   // L1
    glVertex3i(-1, 6, 2);   // K1
    glEnd();
    //�ý� ǥ���ϴ� ��(�Ѳ� ����)3 O1 P1 Q1 L1
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-1, 7, -2);   // O1
    glVertex3i(-3, 7, -2);   // P1
    glVertex3i(-3, 6, -2);   // Q1
    glVertex3i(-1, 6, -2);   // L1
    glEnd();
    //�ý� ǥ���ϴ� ��(�Ѳ� ����)4 P1 M1 J1 Q1
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-3, 7, -2);   // P1
    glVertex3i(-3, 7, 2);   // M1
    glVertex3i(-3, 6, 2);   // J1
    glVertex3i(-3, 6, -2);   // Q1
    glEnd();
    //�ý� ǥ���ϴ� ��(�Ѳ� ����)5 [�Ѳ�] P1 O1 N1 M1
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-3, 7, -2);   // P1
    glVertex3i(-1, 7, -2);   // O1
    glVertex3i(-1, 7, 2);   // N1
    glVertex3i(-3, 7, 2);   // M1
    glEnd();

    //�ĸ� ���� �� �κ� T1 O R1 S1
    glColor3f(1.0, 1.0, 1.0);   //PINK
    glBegin(GL_POLYGON);
    glVertex3i(-6, 3, 4);   // T1
    glVertex3i(-3, 3, 4);   // O
    glVertex3i(-3, 1, 4);   // R1
    glVertex3i(-6, 1, 4);   // S1
    glEnd();

    //�ĸ� ���� �� �κ� [RIGHT]
    glColor3f(1.0, 1.0, 1.0);   //PINK
    glBegin(GL_POLYGON);
    glVertex3i(-9, 3, 4);   // K
    glVertex3i(-6, 3, 4);   // T1
    glVertex3i(-6, 0, 4);   // U1
    glVertex3i(-9, 0, 4);   // L
    glEnd();

    //�ĸ� ���� �� �κ� [RIGHT]
    glColor3f(1.0, 1.0, 1.0);   //PINK
    glBegin(GL_POLYGON);
    glVertex3i(-6, 3, -4);   // T1
    glVertex3i(-3, 3, -4);   // O
    glVertex3i(-3, 1, -4);   // R1
    glVertex3i(-6, 1, -4);   // S1
    glEnd();

    //�ĸ� ���� �� �κ� K T1 U1 L
    glColor3f(1.0, 1.0, 1.0);   //PINK
    glBegin(GL_POLYGON);
    glVertex3i(-9, 3, -4);   // K
    glVertex3i(-6, 3, -4);   // T1
    glVertex3i(-6, 0, -4);   // U1
    glVertex3i(-9, 0, -4);   // L
    glEnd();

    //�� Ʈ��ũ
    glColor3f(1.0, 1.0, 1.0);   //RED
    glBegin(GL_POLYGON);
    glVertex3i(-9, 3, 4);   // K
    glVertex3i(-9, 3, -4);   // K(-Z)
    glVertex3i(-6, 3, -4);   // Z(-Z)
    glVertex3i(-6, 3, 4);   // Z

    glEnd();

    //�� �ĸ� ���� KL,
    glColor3f(1.0, 1.0, 1.0);   // PINK
    glBegin(GL_POLYGON);
    glVertex3i(-9, 3, 4);   // K
    glVertex3i(-9, 0, 4);   // L
    glVertex3i(-9, 0, -4);   // L(-Z)
    glVertex3i(-9, 3, -4);   // K(-Z)
    glEnd();

    //�� ������1 [LEFT] A2 B2 C2 D2
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(2, 3, 5);   // A2
    glVertex3i(2, 2, 5);   // B2
    glVertex3i(0, 2, 5);   // C2
    glVertex3i(0, 3, 5);   // D2
    glEnd();
    //�� ������2 [LEFT] A2 D2 E2 F1
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(2, 3, 5);   // A2
    glVertex3i(0, 3, 5);   // D2
    glVertex3i(0, 3, 4);   // E2
    glVertex3i(2, 3, 4);   // F1
    glEnd();
    //�� ������2 [LEFT] D2 E2 G2 C2
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(0, 3, 5);   // D2
    glVertex3i(0, 3, 4);   // E2
    glVertex3i(0, 2, 4);   // G2
    glVertex3i(0, 2, 5);   // C2
    glEnd();
    //�� ������2 [LEFT] A2 F1 F2 B2
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(2, 3, 5);   // A2
    glVertex3i(2, 3, 4);   // F1
    glVertex3i(2, 2, 4);   // F2
    glVertex3i(2, 2, 5);   // B2
    glEnd();

    //�� ������1 [RIGHT] 
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(2, 3, -5);   // A2
    glVertex3i(2, 2, -5);   // B2
    glVertex3i(0, 2, -5);   // C2
    glVertex3i(0, 3, -5);   // D2
    glEnd();
    //�� ������2 [RIGHT] A2 D2 E2 F1
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(2, 3, -5);   // A2
    glVertex3i(0, 3, -5);   // D2
    glVertex3i(0, 3, -4);   // E2
    glVertex3i(2, 3, -4);   // F1
    glEnd();
    //�� ������2 [RIGHT] D2 E2 G2 C2
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(0, 3, -5);   // D2
    glVertex3i(0, 3, -4);   // E2
    glVertex3i(0, 2, -4);   // G2
    glVertex3i(0, 2, -5);   // C2
    glEnd();
    //�� ������2 [RIGHT] A2 F1 F2 B2
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(2, 3, -5);   // A2
    glVertex3i(2, 3, -4);   // F1
    glVertex3i(2, 2, -4);   // F2
    glVertex3i(2, 2, -5);   // B2
    glEnd();

    //�� �ٴ�1
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(6, 0, -4);   // A3
    glVertex3i(8, 0, -4);   // F
    glVertex3i(8, 0, 4);   // E
    glVertex3i(6, 0, 4);   // H
    glEnd();
    //�� �ٴ�2
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(-3, 0, -4);   // N(Z-8)
    glVertex3i(3, 0, -4);   // I(Z-8)
    glVertex3i(3, 0, 4);   // I
    glVertex3i(-3, 0, 4);   // N
    glEnd();
    //�� �ٴ�3
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
        dxcar = speed * cos((180-rcar) * PI / 180.0); xcar += dxcar;
        dycar = speed * sin((180-rcar) * PI / 180.0); ycar += dycar;
        break;
    case 's':  break;
    case 'a': rcar += 3; printf("r=%d\n", rcar); break;
    case 'd': rcar -= 3; printf("r=%d\n", rcar); break;
    }
    if (rcar >= 360 || rcar <= -360) rcar = 0;
    glutPostRedisplay();
}

void drawingCar_ok(float car_size) {//�׽�Ʈ�� �ڵ��� �𵨸�, �̵�, ȸ��
    glPushMatrix();
    glTranslatef(xcar, 1, ycar);//�ڵ��� �̵�
    glRotatef(rcar, 0.0f, 1.0f, 0.0f);//�ڵ��� ȸ��
    //glRotatef(180, 0.0f, 1.0f, 0.0f);//�ڵ��� ȸ��
    //glBegin(GL_LINES);
    //    glColor3f(0.0, 0.0, 1.0);
    //    glVertex3f(0.0, 0.0, 0.0);  glVertex3f(-10.0, 0.0, 0.0); /* Z axis  */
    //glEnd();
    glRotatef(180, 0.0f, 1.0f, 0.0f);//�ڵ��� ȸ��
    glScalef(car_size, car_size, car_size);
    drawingCar();
    //glutWireCube(5.0);
    glPopMatrix();
}

void drawScene(float car_size = 0.4, int line_width = 5) {//�׸� ��ü��
    glPushMatrix();
        display_lines(line_width);
    glPopMatrix();
// ��� �׸���
    glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        glTranslatef(0.0, -0.5, 0.0);
        glScalef(200.0, 1.0, 130.0);
        glutSolidCube(1.0);
        
        glPushMatrix();
            glColor3f(0.1, 0.1, 0.1);
            glLineWidth(2);
            glutWireCube(1.0);
        glPopMatrix();
    glPopMatrix();

    drawingCar_ok(car_size);
    //drawingCar();

    //glColor3f(1.0, 0.0, 0.6);
    //glutWireTorus(1, 3, 10, 100);
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
    glClearColor(.9f, .9f, .9f, 1.0f);//����

    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    glLineWidth(5);
    renderStrokeString(-20,   0-5, 1,     1, 1, 1, 0.1, GLUT_STROKE_ROMAN, start);
    renderStrokeString(-15, -30-5, 1,     1, 1, 1, 0.1, GLUT_STROKE_ROMAN, info);
    renderStrokeString(-15, -60-5, 1,     1, 1, 1, 0.1, GLUT_STROKE_ROMAN, quit);
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
        glClearColor(.9f, .9f, .9f, 1.0f);//����

        glViewport(0, 0, Width, Height);

        glPushMatrix();
        gluLookAt(0.0, -100.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);//ī�޶� ��ġ/�ٶ󺸴� ���� ��ġ/ī�޶� �����

        glRotatef(rotationX, 1.0, 0.0, 0.0);
        glRotatef(rotationY, 0.0, 1.0, 0.0);
        glMultMatrixf(view_rotate);
        main_menu();



        glPopMatrix();
    }
    else//�ù� ������
    {//-------------------------��ü ȭ��--------------------------------------
        perspective();
        glClearColor(.9f, .9f, .9f, 1.0f);//����
        glLoadIdentity();

        glViewport(0, 0, Width, Height);

        glPushMatrix();
        gluLookAt(  xcar -  10 * cos((180 - rcar) * PI / 180.0), 20, ycar - 10 * sin((180 - rcar) * PI / 180.0), 
                    xcar + 10 * cos((180 - rcar) * PI / 180.0), 0.1, ycar + 10 * sin((180 - rcar) * PI / 180.0), 
                    0.0, 1.0, 0.0);//ī�޶� ��ġ/�ٶ󺸴� ���� ��ġ/ī�޶� �����

        glPushMatrix();

        glRotatef(rotationX, 1.0, 0.0, 0.0);
        glRotatef(rotationY, 0.0, 1.0, 0.0);
        glMultMatrixf(view_rotate);
        drawScene();

        glPopMatrix();
        glPopMatrix();

        //-----------------------������ �� ȭ��----------------------------
        glViewport(Width * 3 / 5, Height * 3 / 5, Width * 2 / 5, Height * 2 / 5);
        //glViewport(0, Height / 2, Width/3, Height/2);
        glPushMatrix();
        gluLookAt(0.0, 90.0, 5.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);
        glDisable(GLUT_DEPTH);
        glClear(GL_DEPTH_BUFFER_BIT);
        drawScene(1.5, 2);
        glEnable(GLUT_DEPTH);
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
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) //���콺 ��ư���� �� �� ��
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

#ifdef __LINUX//������ ���� �ڵ�

void* sevenseg(void) {
    //reset 7seg state
    while (1) {
        if (simuwork == 1) { // repeat if simulation is working
            //100 ǥ��
            //������ ���ǹ� �ۼ��ؾ���
        }
    }
}
/* 7 seg decoder ���鶧 ����.
14,11,10,6,8,7 => ���� �ڸ����� LOW, �ܿ��� HIGH => 3�ڸ��� ����Ұ��̱⿡ 14,11,10 HIGH����, 6,8,7�����ư��� LOW �Է�.
- ǥ��: 5���� high, 1,2,3,4,9,12,13���� low
0 ǥ��: 1,2,4,9,12,13���� high, 3,5���� low
1 ǥ��: 4,9���� high 1,2,3,5,12,13���� low
2 ǥ��: 1,2,5,9,13���� high, 3,4,12���� low
3 ǥ��: 2,4,5,9,13���� high, 1,3,12���� low
4 ǥ��: 4,5,9,12���� high, 1,2,3,13���� low
5 ǥ��: 2,4,5,12,13���� high, 1,3,9���� low
6 ǥ��: 1,2,4,5,12,13���� high, 3,9���� low
7 ǥ��: 4,9,12,13����high, 1,2,3,5���� low
8 ǥ��: 1,2,4,5,9,12,13���� high, 3���� low
9 ǥ��: 2,3,4,5,9,12,13���� high, 1���� low
*/
#endif

int main(int argc, char** argv) {
#ifdef __LINUX//������ ���� �ڵ�
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
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Embedded system");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(disp);
    glutReshapeFunc(changeSize);

    glutTimerFunc(1, Timer, 0);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    //glutMotionFunc(motion);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}
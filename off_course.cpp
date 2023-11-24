//임시로 만든 -- 줄에 닿으면 -5반환
/*
백색줄 --------------------------------------------------------
{-97, -61}, {-97, 55},{91,55}, {91, -61},
{-73, 9},{-73, 36}, {-9, 36}, {-9, 9},
{9, 9},{9, 36}, {73, 36}, {73, 9},
{9, -43},{9, -9}, {73, -9}, {73, -43},
{-76, -43},{-73, -9}, {-44, -9}, {-44, -20}, {-32, -20}, {-32, -9}, {-9, -9}, {-9, -43},
{-97, 26}, {-73, 26},
{-19, 0}, {-19, 9},
{67, 0}, {67, 9},
{9, 9}, {9, -9},
{-9, -17}, {0, -17}

황색줄 ------------------
{-19, 0}, {-85, 0}, {82, -52}, {82, -9},
{0, 52}, {0, -9},
{-85, 9}, {-85, 45}, {82, 45}, {82, 9},
{0, 9}, {0, 36}
*/

#include <GL/glut.h>
#include <iostream>
using namespace std;

int squareX = -90; // 작은 사각형의 초기 x 좌표
int squareY = 0;   // 작은 사각형의 초기 y 좌표
int squareSize = 10; // 작은 사각형의 크기

//그 2차원 배열 -> 라인 만들 곳! (경로)




// 4개의 루프 선분의 좌표
int lineCoordinates[][2] = {
    {-97, -61},
    {-97, 55},
    {91, 55},
    {91, -61}
};

bool touchingLoop = false;

void drawSquare() {
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0); // 흰색 사각형
    glVertex2i(squareX, squareY);
    glVertex2i(squareX + squareSize, squareY);
    glVertex2i(squareX + squareSize, squareY + squareSize);
    glVertex2i(squareX, squareY + squareSize);
    glEnd();
}

void drawLoopLines() {
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 1.0, 1.0); // 흰색 루프 선

    for (int i = 0; i < sizeof(lineCoordinates) / sizeof(lineCoordinates[0]); ++i) {
        glVertex2i(lineCoordinates[i][0], lineCoordinates[i][1]);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 작은 사각형 그리기
    drawSquare();

    // 루프 선 그리기
    drawLoopLines();

    // 작은 사각형이 루프 선에 닿으면 "-5"를 출력
    if (touchingLoop) {
        std:cout << "-5" << std::endl;
    }

    glutSwapBuffers();
}

void timer(int value) {
    touchingLoop = false;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    // 키보드 입력에 따라 작은 사각형을 움직임
    switch (key) {
    case 'w':
        squareY += 5; // 위로 이동
        break;
    case 's':
        squareY -= 5; // 아래로 이동
        break;
    case 'a':
        squareX -= 5; // 왼쪽으로 이동
        break;
    case 'd':
        squareX += 5; // 오른쪽으로 이동
        break;
    }

    // 작은 사각형이 루프 선에 닿으면 1초 동안 "-5"를 출력
    for (int i = 0; i < sizeof(lineCoordinates) / sizeof(lineCoordinates[0]) - 1; ++i) {
        int x1 = lineCoordinates[i][0];
        int y1 = lineCoordinates[i][1];
        int x2 = lineCoordinates[i + 1][0];
        int y2 = lineCoordinates[i + 1][1];

        int squareCenterX = squareX + squareSize / 2;
        int squareCenterY = squareY + squareSize / 2;

        if ((squareCenterY > y1 && squareCenterY <= y2) || (squareCenterY > y2 && squareCenterY <= y1)) {
            int intersectX = ((squareCenterY - y1) * (x2 - x1)) / (y2 - y1) + x1;
            if (intersectX <= squareCenterX) {
                touchingLoop = true;
                glutTimerFunc(1000, timer, 0); // 1초 후에 타이머 콜백 함수 호출
                break;
            }
        }
    }

    // 화면을 다시 그림
    glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // 배경색을 검은색으로 지정
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100); // 좌표 시스템을 적절하게 설정
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Square and Loop Lines");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

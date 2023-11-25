#include <algorithm>
#include <GL/glut.h>

int squareX = 0; // 작은 사각형의 초기 x 좌표
int squareY = 50; // 작은 사각형의 초기 y 좌표

// 첫 번째 경로 좌표
int pathCoordinates1[][2] = {
    {-97, -61}, {-97, 55}, {91, 55}, {91, -61}
};

// 두 번째 경로 좌표
int pathCoordinates2[][2] = {
    {-73, 9}, {-73, 36}, {-9, 36}, {-9, 9}
};

// 세 번째 경로 좌표
int pathCoordinates3[][2] = {
    {9, 9}, {9, 36}, {73, 36}, {73, 9}
};

// 네 번째 경로 좌표
int pathCoordinates4[][2] = {
    {9, -43}, {9, -9}, {73, -9}, {73, -43}
};

void drawSquare() { // 작은 사각형 그리기
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0); // 흰색 사각형
    glVertex2i(squareX - 7, squareY - 2);
    glVertex2i(squareX + 7, squareY - 2);
    glVertex2i(squareX + 7, squareY + 2);
    glVertex2i(squareX - 7, squareY + 2);
    glEnd();

    // 첫 번째 경로 그리기
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 1.0, 1.0); // 흰색 선
    for (int i = 0; i < sizeof(pathCoordinates1) / sizeof(pathCoordinates1[0]); ++i) {
        glVertex2i(pathCoordinates1[i][0], pathCoordinates1[i][1]);
    }
    glEnd();

    // 두 번째 경로 그리기
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 1.0, 1.0); // 흰색 선
    for (int i = 0; i < sizeof(pathCoordinates2) / sizeof(pathCoordinates2[0]); ++i) {
        glVertex2i(pathCoordinates2[i][0], pathCoordinates2[i][1]);
    }
    glEnd();

    // 세 번째 경로 그리기
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 1.0, 1.0); // 흰색 선
    for (int i = 0; i < sizeof(pathCoordinates3) / sizeof(pathCoordinates3[0]); ++i) {
        glVertex2i(pathCoordinates3[i][0], pathCoordinates3[i][1]);
    }
    glEnd();

    // 네 번째 경로 그리기
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 1.0, 1.0); // 흰색 선
    for (int i = 0; i < sizeof(pathCoordinates4) / sizeof(pathCoordinates4[0]); ++i) {
        glVertex2i(pathCoordinates4[i][0], pathCoordinates4[i][1]);
    }
    glEnd();
}

bool isPointOnPath(int x, int y) {
    // 모든 경로의 좌표 범위 확인

    // 첫 번째 경로 확인
    for (int i = 0; i < sizeof(pathCoordinates1) / sizeof(pathCoordinates1[0]) - 1; ++i) {
        int x1 = pathCoordinates1[i][0];
        int y1 = pathCoordinates1[i][1];
        int x2 = pathCoordinates1[i + 1][0];
        int y2 = pathCoordinates1[i + 1][1];

        // 현재 점이 선분 위에 있는지 확인
        if ((y - y1) * (x2 - x1) == (y2 - y1) * (x - x1) &&
            x >= std::min(x1, x2) && x <= std::max(x1, x2) &&
            y >= std::min(y1, y2) && y <= std::max(y1, y2)) {
            return true;
        }
    }
 
    // 두 번째 경로 확인
    for (int i = 0; i < sizeof(pathCoordinates2) / sizeof(pathCoordinates2[0]) - 1; ++i) {
        int x1 = pathCoordinates2[i][0];
        int y1 = pathCoordinates2[i][1];
        int x2 = pathCoordinates2[i + 1][0];
        int y2 = pathCoordinates2[i + 1][1];

        // 현재 점이 선분 위에 있는지 확인
        if ((y - y1) * (x2 - x1) == (y2 - y1) * (x - x1) &&
            x >= std::min(x1, x2) && x <= std::max(x1, x2) &&
            y >= std::min(y1, y2) && y <= std::max(y1, y2)) {
            return true;
        }
    }

    // 세 번째 경로 확인
    for (int i = 0; i < sizeof(pathCoordinates3) / sizeof(pathCoordinates3[0]) - 1; ++i) {
        int x1 = pathCoordinates3[i][0];
        int y1 = pathCoordinates3[i][1];
        int x2 = pathCoordinates3[i + 1][0];
        int y2 = pathCoordinates3[i + 1][1];

        // 현재 점이 선분 위에 있는지 확인
        if ((y - y1) * (x2 - x1) == (y2 - y1) * (x - x1) &&
            x >= std::min(x1, x2) && x <= std::max(x1, x2) &&
            y >= std::min(y1, y2) && y <= std::max(y1, y2)) {
            return true;
        }
    }

    // 네 번째 경로 확인
    for (int i = 0; i < sizeof(pathCoordinates4) / sizeof(pathCoordinates4[0]) - 1; ++i) {
        int x1 = pathCoordinates4[i][0];
        int y1 = pathCoordinates4[i][1];
        int x2 = pathCoordinates4[i + 1][0];
        int y2 = pathCoordinates4[i + 1][1];

        // 현재 점이 선분 위에 있는지 확인
        if ((y - y1) * (x2 - x1) == (y2 - y1) * (x - x1) &&
            x >= std::min(x1, x2) && x <= std::max(x1, x2) &&
            y >= std::min(y1, y2) && y <= std::max(y1, y2)) {
            return true;
        }
    }

    return false;
}

void drawText(const char* text, int x, int y) {
    glRasterPos2i(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 작은 사각형과 네 개의 경로 그리기
    drawSquare();

    // 경로 확인 및 출력
    if (isPointOnPath(squareX - 7, squareY - 2) ||
        isPointOnPath(squareX + 7, squareY - 2) ||
        isPointOnPath(squareX + 7, squareY + 2) ||
        isPointOnPath(squareX - 7, squareY + 2)) {
        // 경로 위에 있음을 출력
        glColor3f(1.0, 0.0, 0.0); // 빨간색
        drawText("On Path", -80, -90);
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    // 키보드 입력에 따라 작은 사각형을 움직임
    switch (key) {
    case 'w':
        squareY += 1; // 위로 이동
        break;
    case 's':
        squareY -= 1; // 아래로 이동
        break;
    case 'a':
        squareX -= 1; // 왼쪽으로 이동
        break;
    case 'd':
        squareX += 1; // 오른쪽으로 이동
        break;
    }

    glutPostRedisplay(); // 다시 그리기 요청
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
    glutCreateWindow("cha gun cha gun hae bo ja");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}



--------------------------------------------------------------------------
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
//그 2차원 배열 -> 라인 만들 곳! (경로)
#include <GL/glut.h>
#include <iostream>

int squareX = 0; // 작은 사각형의 초기 x 좌표
int squareY = 50; // 작은 사각형의 초기 y 좌표
int squareSize = 10; // 작은 사각형의 크기
float rotationAngle = 0.0;

// 5개의 루프 선분의 좌표
int lineCoordinates[][5][2] = {
    {{-97, -61}, {-97,55}, {91, 55}, {91, -61}},
    {{-73, 9}, {-73, 36}, {-9, 36}, {-9, 9}},
    {{9, 9}, {9, 36}, {73, 36}, {73, 9}},
    {{9, -43}, {9, -9}, {73, -9}, {73, -43}},
    {{-73, -43}, {-73, -9}, {-9, -9}, {-9, -43}}
};

bool touchingLoop = false;

void drawSquare() {

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0); // 흰색 사각형
    glVertex2i(squareX - 7, squareY - 2);
    glVertex2i(squareX + 7, squareY - 2);
    glVertex2i(squareX + 7, squareY + 2);
    glVertex2i(squareX - 7, squareY + 2);
    glEnd();
}

void drawLoopLines() {
    for (int i = 0; i < sizeof(lineCoordinates) / sizeof(lineCoordinates[0]); ++i) {
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 1.0); // 흰색 루프 선

        for (int j = 0; j < 4; ++j) {
            glVertex2i(lineCoordinates[i][j][0], lineCoordinates[i][j][1]);
        }
        glEnd();
    }
}

bool isPointOnSegment(int px, int py, int x1, int y1, int x2, int y2) {
    return (px >= std::min(x1, x2) && px <= std::max(x1, x2) &&
        py >= std::min(y1, y2) && py <= std::max(y1, y2));
}

bool doIntersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    int o1 = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    int o2 = (x2 - x1) * (y4 - y1) - (y2 - y1) * (x4 - x1);
    int o3 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
    int o4 = (x4 - x3) * (y2 - y3) - (y4 - y3) * (x2 - x3);

    if ((o1 * o2 < 0) && (o3 * o4 < 0)) {
        return true;
    }

    if (o1 == 0 && isPointOnSegment(x3, y3, x1, y1, x2, y2)) return true;
    if (o2 == 0 && isPointOnSegment(x4, y4, x1, y1, x2, y2)) return true;
    if (o3 == 0 && isPointOnSegment(x1, y1, x3, y3, x4, y4)) return true;
    if (o4 == 0 && isPointOnSegment(x2, y2, x3, y3, x4, y4)) return true;

    return false;
}

void checkIntersection() {
    touchingLoop = false;

    for (int i = 0; i < sizeof(lineCoordinates) / sizeof(lineCoordinates[0]); ++i) {
        for (int j = 0; j < sizeof(lineCoordinates[0]) / sizeof(lineCoordinates[0][0]) - 1; ++j) {
            int x1 = lineCoordinates[i][j][0];
            int y1 = lineCoordinates[i][j][1];
            int x2 = lineCoordinates[i][j + 1][0];
            int y2 = lineCoordinates[i][j + 1][1];

            if (doIntersect(squareX, squareY, squareX, squareY + squareSize, x1, y1, x2, y2)) {
                touchingLoop = true;
                return;
            }
        }
    }
}

void drawNegativeFive() {
    glColor3f(1.0, 0.0, 0.0); // 빨간색 텍스트
    glRasterPos2i(0, 0); // 텍스트 위치
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '5');
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 작은 사각형 그리기
    drawSquare();

    // 루프 선 그리기
    drawLoopLines();

    // 작은 사각형이 루프 선에 닿으면 "-5"를 출력
    checkIntersection();

    // "-5" 표시
    if (touchingLoop) {
        drawNegativeFive();
    }

    glutSwapBuffers();
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // 60fps로 설정
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        squareY += 5; // Move up
        break;
    case 's':
        squareY -= 5; // Move down
        break;
    case 'a':
        // Rotate counterclockwise (left) around the center

        glRotatef(-10.0, squareX, squareY, 0.0);
 
        break;
    case 'd':
        // Rotate clockwise (right) around the center
        glTranslatef(squareX, squareY, 0.0);
        glRotatef(10.0, 0.0, 0.0, 0.0);
        glTranslatef(-squareX, -squareY, 0.0);
        break;
    }

    checkIntersection();
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
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

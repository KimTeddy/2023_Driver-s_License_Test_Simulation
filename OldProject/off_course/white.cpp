#include <algorithm>
#include <GL/glut.h>
#include <iostream>

int squareX = 0, squareY = 0;
int squareVertices[4][2] = {
    {squareX - 5, squareY - 2},
    {squareX + 5, squareY - 2},
    {squareX + 5, squareY + 2},
    {squareX - 5, squareY + 2}
};

// 첫 번째 경로 좌표
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

bool isPointOnPath(int x, int y, int x1, int y1, int x2, int y2) {
    int minX = std::min(x1, x2);
    int maxX = std::max(x1, x2);
    int minY = std::min(y1, y2);
    int maxY = std::max(y1, y2);

    return (x >= minX && x <= maxX && y >= minY && y <= maxY);
}
bool isRectangleOnLines() {
    // 사각형의 네 꼭짓점이 선 위에 있는지 확인
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (isPointOnPath(squareVertices[j][0], squareVertices[j][1],
                whitepath1[i][0], whitepath1[i][1], whitepath1[i][2], whitepath1[i][3])) {
                return true; // 사각형의 꼭짓점이 선 위에 있다면 true 반환
            }
        }
    }

    return false; // 사각형의 꼭짓점이 선 위에 없다면 false 반환
}
void updateSquareVertices() {
    // Update squareVertices based on the current square position
    squareVertices[0][0] = squareX - 5;
    squareVertices[0][1] = squareY - 2;
    squareVertices[1][0] = squareX + 5;
    squareVertices[1][1] = squareY - 2;
    squareVertices[2][0] = squareX + 5;
    squareVertices[2][1] = squareY + 2;
    squareVertices[3][0] = squareX - 5;
    squareVertices[3][1] = squareY + 2;
}
// 선분 (x1, y1) - (x2, y2) 위에 점 (x, y)가 있는지 확인

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);  // 흰색설정
    glLineWidth(2.0);         // 두께 2 설정

    glBegin(GL_LINES);
    for (int i = 0; i < 20; ++i) {
        glVertex2f(whitepath1[i][0], whitepath1[i][1]);
        glVertex2f(whitepath1[i][2], whitepath1[i][3]);
    }
    glEnd();

    glColor3f(0.0, 1.0, 0.0);  // 초록색 설정
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; ++i) {
        glVertex2f(squareVertices[i][0], squareVertices[i][1]);
    }
    glEnd();

    if (isRectangleOnLines()) {
        std::cout << "-5" << std::endl;
    }
    else {
        std::cout << "0" << std::endl;
    }

    glFlush();
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
    updateSquareVertices(); // Update squareVertices
    glutPostRedisplay(); // 다시 그리기 요청
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // 배경색을 검은색으로 지정
    gluOrtho2D(-100, 100, -100, 100); // 좌표 시스템을 적절하게 설정
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("cha gun cha gun hae bo ja");
    init();
    updateSquareVertices();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

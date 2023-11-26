#include <GL/glut.h>
#include <iostream>

int squareX = 0, squareY = 0;
int squareVertices[4][2] = {
    {squareX - 5, squareY - 2},
    {squareX + 5, squareY - 2},
    {squareX + 5, squareY + 2},
    {squareX - 5, squareY + 2}
};

int lines[][4] = {
    {-87, 9, -87, 45},   // 1. {-87, 9}와 {-87, 45}를 이은 선
    {-87, 45, 82, 45},   // 2. {-87, 45}와 {82, 45}를 이은 선
    {82, 45, 82, 9},    // 3. {82, 45}와 {82, 9}를 이은 선
    {0, 9, 0, 36},      // 4. {0, 9}와 {0, 36}를 이은 선
    {-17, 0, -87, 0},   // 5. {0, 9}와 {0, 36}를 이은 선
    {-87, 0, -87, -52}, // 6. {-87, 0}와 {-87, -52}를 이은 선
    {-87, -52, 82, -52},// 7. {-87, -52}와 {82, -52}를 이은 선
    {82, -52, 82, -9},  // 8. {82, -52}와 {82, -9}를 이은 선
    {0, -52, 0, -12},   // 9. {0, -52}와 {0, -12}를 이은 선
    {7, 0, 67, 0}       // 10. {7, 0}와 {67, 0}를 이은 선
};

bool isPointOnLine(float x, float y, float x1, float y1, float x2, float y2) {
    // 선분 (x1, y1) - (x2, y2) 위에 점 (x, y)가 있는지 확인
    float minX = std::min(x1, x2);
    float maxX = std::max(x1, x2);
    float minY = std::min(y1, y2);
    float maxY = std::max(y1, y2);

    return (x >= minX && x <= maxX && y >= minY && y <= maxY);
}

bool isRectangleOnLines() {
    // 사각형의 네 꼭짓점이 선 위에 있는지 확인
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (isPointOnLine(squareVertices[j][0], squareVertices[j][1],
                lines[i][0], lines[i][1], lines[i][2], lines[i][3])) {
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 0.0);  // 노란색 설정
    glLineWidth(2.0);         // 두께 2 설정

    glBegin(GL_LINES);
    for (int i = 0; i < 10; ++i) {
        glVertex2f(lines[i][0], lines[i][1]);
        glVertex2f(lines[i][2], lines[i][3]);
    }
    glEnd();

    // 움직이는 작은 사각형 그리기
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
        std::cout << "Not on lines" << std::endl;
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);  // 윈도우 크기 조절
    glutCreateWindow("OpenGL Lines");

    init();
    updateSquareVertices(); // Initial update of squareVertices
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);  // 키보드 입력 핸들링 함수 등록

    glutMainLoop();
    return 0;
}

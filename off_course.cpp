//임시로 만든 -- 사각형이 경로 이탈할 판 만들기
#include <GL/glut.h>

// 좌표 배열
int coordinates[][2] = {
    {-97, -61},
    {-97, 55},
    {91, 55},
    {91, -61}
};

void drawLines() {
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 1.0, 1.0); // 흰색 선

    for (int i = 0; i < sizeof(coordinates) / sizeof(coordinates[0]); ++i) {
        glVertex2i(coordinates[i][0], coordinates[i][1]);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLines();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // 배경색을 검은색으로 지정
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100); // 좌표 시스템을 적절하게 설정
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Line Drawing");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

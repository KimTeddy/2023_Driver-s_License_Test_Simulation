#include <algorithm>
#include <GL/glut.h>

int squareX = 0;
int squareY = 50;
int a = 0;
int b = 100;

int pathCoordinates1[][2] = {
    {-97, -61}, {-97, 55}, {91, 55}, {91, -61}
};

int pathCoordinates2[][2] = {
    {-76, 9}, {-76, 36}, {-9, 36}, {-9, 9}
};

int pathCoordinates3[][2] = {
    {9, 9}, {9, 36}, {73, 36}, {73, 9}
};

int pathCoordinates4[][2] = {
    {9, -43}, {9, -9}, {73, -9}, {73, -43}
};

int pathCoordinates5[][2] = {
    {-76, -43}, {-76, -9}, {-9, -9}, {-9, -43}
};

int whiteLines[][2][2] = {
    {-97, 26, -73, 26},   // 1번 줄
    {-19, 0, -19, 9},     // 2번 줄
    {67, 0, 67, 9},       // 3번 줄
    {9, 0, 9, -9},        // 4번 줄
    {-9, -17, 0, -17},     // 5번 줄
    {73,9,91,9}
};


void drawSquare() {

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(squareX - 5, squareY - 2);
    glVertex2i(squareX + 5, squareY - 2);
    glVertex2i(squareX + 5, squareY + 2);
    glVertex2i(squareX - 5, squareY + 2);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glLineWidth(4);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < sizeof(pathCoordinates1) / sizeof(pathCoordinates1[0]); ++i) {
        glVertex2i(pathCoordinates1[i][0], pathCoordinates1[i][1]);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glLineWidth(4);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < sizeof(pathCoordinates2) / sizeof(pathCoordinates2[0]); ++i) {
        glVertex2i(pathCoordinates2[i][0], pathCoordinates2[i][1]);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glLineWidth(4);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < sizeof(pathCoordinates3) / sizeof(pathCoordinates3[0]); ++i) {
        glVertex2i(pathCoordinates3[i][0], pathCoordinates3[i][1]);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glLineWidth(4);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < sizeof(pathCoordinates4) / sizeof(pathCoordinates4[0]); ++i) {
        glVertex2i(pathCoordinates4[i][0], pathCoordinates4[i][1]);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glLineWidth(4);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < sizeof(pathCoordinates5) / sizeof(pathCoordinates5[0]); ++i) {
        glVertex2i(pathCoordinates5[i][0], pathCoordinates5[i][1]);
    }
    glEnd();

    // 단순 흰색 줄 그리기
    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3f(1.0, 1.0, 1.0);

    for (int i = 0; i < sizeof(whiteLines) / sizeof(whiteLines[0]); ++i) {
        for (int j = 0; j < 2; ++j) {
            glVertex2i(whiteLines[i][j][0], whiteLines[i][j][1]);
        }
    }
    glEnd();

}

bool isPointOnPath(int x, int y, const int pathCoordinates[][2], int pathSize) {
    for (int i = 0; i < pathSize - 1; ++i) {
        int x1 = pathCoordinates[i][0];
        int y1 = pathCoordinates[i][1];
        int x2 = pathCoordinates[i + 1][0];
        int y2 = pathCoordinates[i + 1][1];

        if ((y - y1) * (x2 - x1) == (y2 - y1) * (x - x1) &&
            x >= std::min(x1, x2) && x <= std::max(x1, x2) &&
            y >= std::min(y1, y2) && y <= std::max(y1, y2)) {
            return true;
        }
    }

    int lastX1 = pathCoordinates[pathSize - 1][0];
    int lastY1 = pathCoordinates[pathSize - 1][1];
    int lastX2 = pathCoordinates[0][0];
    int lastY2 = pathCoordinates[0][1];

    if ((y - lastY1) * (lastX2 - lastX1) == (lastY2 - lastY1) * (x - lastX1) &&
        x >= std::min(lastX1, lastX2) && x <= std::max(lastX1, lastX2) &&
        y >= std::min(lastY1, lastY2) && y <= std::max(lastY1, lastY2)) {
        return true;
    }

    return false;
}

bool isSquareOnPath(int x, int y, const int pathCoordinates[][2], int pathSize) {
    if (isPointOnPath(x - 7, y - 2, pathCoordinates, pathSize) ||
        isPointOnPath(x + 7, y - 2, pathCoordinates, pathSize) ||
        isPointOnPath(x + 7, y + 2, pathCoordinates, pathSize) ||
        isPointOnPath(x - 7, y + 2, pathCoordinates, pathSize)) {
        return true;
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
    drawSquare();

    if (isSquareOnPath(squareX, squareY, pathCoordinates1, sizeof(pathCoordinates1) / sizeof(pathCoordinates1[0])) ||
        isSquareOnPath(squareX, squareY, pathCoordinates2, sizeof(pathCoordinates2) / sizeof(pathCoordinates2[0])) ||
        isSquareOnPath(squareX, squareY, pathCoordinates3, sizeof(pathCoordinates3) / sizeof(pathCoordinates3[0])) ||
        isSquareOnPath(squareX, squareY, pathCoordinates4, sizeof(pathCoordinates4) / sizeof(pathCoordinates4[0])) ||
        isSquareOnPath(squareX, squareY, pathCoordinates5, sizeof(pathCoordinates5) / sizeof(pathCoordinates5[0]))) {
        glColor3f(1.0, 0.0, 0.0);
        drawText("On Path", -80, -90);

    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        squareY += 1;
        break;
    case 's':
        squareY -= 1;
        break;
    case 'a':
        squareX -= 1;
        break;
    case 'd':
        squareX += 1;
        break;
    }

    glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
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

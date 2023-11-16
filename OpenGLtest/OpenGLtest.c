#include <GL/glut.h>

void drawCar() {
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
    glVertex3i(-1, 7, -1);   // O1
    glVertex3i(-1, 6, -1);   // L1
    glVertex3i(-1, 6, 2);   // K1
    glEnd();
    //�ý� ǥ���ϴ� ��(�Ѳ� ����)3 O1 P1 Q1 L1
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-1, 7, -1);   // O1
    glVertex3i(-3, 7, -1);   // P1
    glVertex3i(-3, 6, -1);   // Q1
    glVertex3i(-1, 6, -1);   // L1
    glEnd();
    //�ý� ǥ���ϴ� ��(�Ѳ� ����)4 P1 M1 J1 Q1
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-3, 7, -1);   // P1
    glVertex3i(-3, 7, 2);   // M1
    glVertex3i(-3, 6, 2);   // J1
    glVertex3i(-3, 6, -1);   // Q1
    glEnd();
    //�ý� ǥ���ϴ� ��(�Ѳ� ����)5 [�Ѳ�] P1 O1 N1 M1
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-3, 7, -1);   // P1
    glVertex3i(-1, 7, -1);   // O1
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
}

int lastX = 0;
int lastY = 0;
int rotateX = 0;
int rotateY = 0;


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -20.0);
    glRotatef(rotateX, 1.0, 0.0, 0.0);
    glRotatef(rotateY, 0.0, 1.0, 0.0);

    drawCar();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastX = x;
        lastY = y;
    }
}

void motion(int x, int y) {
    rotateX += (y - lastY);
    rotateY += (x - lastX);

    lastX = x;
    lastY = y;

    glutPostRedisplay();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Car Drawing");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutIdleFunc(idle);

    glClearColor(0.8, 0.8, 0.8, 1.0);

    glutMainLoop();

    return 0;
}

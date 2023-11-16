#include <GL/glut.h>

void drawCar() {
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
    glVertex3i(-1, 7, -1);   // O1
    glVertex3i(-1, 6, -1);   // L1
    glVertex3i(-1, 6, 2);   // K1
    glEnd();
    //택시 표시하는 거(뚜껑 위에)3 O1 P1 Q1 L1
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-1, 7, -1);   // O1
    glVertex3i(-3, 7, -1);   // P1
    glVertex3i(-3, 6, -1);   // Q1
    glVertex3i(-1, 6, -1);   // L1
    glEnd();
    //택시 표시하는 거(뚜껑 위에)4 P1 M1 J1 Q1
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-3, 7, -1);   // P1
    glVertex3i(-3, 7, 2);   // M1
    glVertex3i(-3, 6, 2);   // J1
    glVertex3i(-3, 6, -1);   // Q1
    glEnd();
    //택시 표시하는 거(뚜껑 위에)5 [뚜껑] P1 O1 N1 M1
    glColor3f(1.0, 1.0, 0.0);   //YELLOW
    glBegin(GL_POLYGON);
    glVertex3i(-3, 7, -1);   // P1
    glVertex3i(-1, 7, -1);   // O1
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

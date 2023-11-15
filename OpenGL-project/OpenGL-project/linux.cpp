#ifdef __LINUX
#include "GL/freeglut.h"
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __LINUX//리눅스 전용 코딩

#endif

#define PI 3.141592

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


void changeSize(int w, int h) {
    if (h == 0)  h = 1;
    Width = w;
    Height = h;
    float ratio = w * 1.0 / h;

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glViewport(0, 0, w, h);
    //gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    //glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, (double)w / (double)h, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle() {
    //acceration = false;
}
void Timer(int val) {
    if(acceration == true)
    {
        if (speed >= 0)speed -= 0.001f;
        else speed = 0;
        dspeed += speed;
    }

    glutPostRedisplay();
    glutTimerFunc(1, Timer, 0);
}

void drawingCar() {//자동차 모델링, 이동, 회전
    
}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q':
    case 'Q': exit(0); break;
    case 'r':
    case 'R': glClearColor(1.0, 0.0, 0.0, 1.0); break;
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
    case 's': 
        break;
    case 'a': rcar += 3;
        printf("r=%f\n", rcar);
        break;
    case 'd': rcar -= 3;
        printf("r=%f\n", rcar);
        break;
    }
    glutPostRedisplay();
}

void drawingCar_test() {//테스트용 자동차 모델링, 이동, 회전
    glPushMatrix();
    glTranslatef(xcar, 10, ycar);//자동차 이동
    glRotatef(rcar, 0.0f, 1.0f, 0.0f);//자동차 회전
    //glRotatef(180, 0.0f, 1.0f, 0.0f);//자동차 회전
    glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);  glVertex3f(-10.0, 0.0, 0.0); /* Z axis  */
    glEnd();
    glutWireCube(5.0);
    glPopMatrix();
}
void drawScene() {//그릴 물체 전체
// 평면 그리기
    glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        glTranslatef(0.0, -0.5, 0.0);
        glScalef(100.0, 1.0, 60.0);
        glutSolidCube(1.0);
        
        glPushMatrix();
            glColor3f(0.1, 0.1, 0.1);
            glLineWidth(2);
            glutWireCube(1.0);
        glPopMatrix();
    glPopMatrix();

    drawingCar_test();
    //drawingCar();

    glColor3f(1.0, 0.0, 0.6);
    glutWireTorus(1, 3, 10, 100);
}

void disp() {
    glClearColor(.9f, .9f, .9f, 1.0f);//배경색
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
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

    glViewport(Width* 3/ 5, Height* 3/ 5, Width* 2/ 5, Height* 2/ 5);
    //glViewport(0, Height / 2, Width/3, Height/2);
    glPushMatrix();
        gluLookAt(0.0, 60.0, 10.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);

        drawScene();
    glPopMatrix();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouse_x = x;
        mouse_y = y;
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
int main(int argc, char** argv) {
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
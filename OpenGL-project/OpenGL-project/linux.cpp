#ifdef __LINUX
#include "GL/freeglut.h"
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

#ifdef __LINUX//리눅스 전용 코딩

#endif

int Width, Height;

float dspeed, speed;
float dx=0, dy=0, dl;
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
//bool lightingEnabled = true;
//GLfloat lightPosition[] = { 0.0f, 2.0f, 0.0f, 1.0f };
//GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0f };
//GLfloat lightAmbient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
//void LightInit()
//{
//    glPushMatrix();
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
//    glPopMatrix();
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, lightAmbient);
//    // Global ambient light
//    float GAmbient[] = { 0.3, 0.3, 0.3, 1.0 };
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GAmbient);
//    // Enable local viewpoint
//    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
//    glShadeModel(GL_SMOOTH);
//    // Material
//    GLfloat material_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
//    GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat material_shininess[] = { 32.0 };
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
//    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
//    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
//
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_COLOR_MATERIAL);
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//}

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
//void draw_axes(float scale)
//{
//    glDisable(GL_LIGHTING);
//
//    glPushMatrix();
//    glScalef(scale, scale, scale);
//
//    glBegin(GL_LINES);
//
//    glColor3f(1.0, 0.0, 0.0);
//    glVertex3f(.8f, 0.05f, 0.0);  glVertex3f(1.0, 0.25f, 0.0); /* Letter X*/
//    glVertex3f(0.8f, .25f, 0.0);  glVertex3f(1.0, 0.05f, 0.0);
//    glVertex3f(0.0, 0.0, 0.0);  glVertex3f(1.0, 0.0, 0.0); /* X axis */
//
//    glColor3f(0.0, 1.0, 0.0);
//    glVertex3f(0.0, 0.0, 0.0);  glVertex3f(0.0, 1.0, 0.0); /* Y axis */
//
//    glColor3f(0.0, 0.0, 1.0);
//    glVertex3f(0.0, 0.0, 0.0);  glVertex3f(0.0, 0.0, 1.0); /* Z axis  */
//    glEnd();
//
//    glPopMatrix();
//
//    glEnable(GL_LIGHTING);
//}

void drawingCar() {//자동차 모델링, 이동, 회전


}

void drawingCar_test() {//테스트용 자동차 모델링, 이동, 회전
    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0);
    glutSolidCube(1.0);
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

    glRotatef(dspeed, 0.0f, 1.0f, 0.0f);

    drawingCar();

    glColor3f(1.0, 0.0, 0.6);
    glutWireTorus(1, 3, 10, 100);
}

void disp() {
    glClearColor(.9f, .9f, .9f, 1.0f);//배경색
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glViewport(0, 0, Width, Height);
    glPushMatrix();
    gluLookAt(0.0, 30.0, 60.0, 0.0, -1.0, 0.0, 0.0, 1.0, 0.0);//카메라 위치/바라보는 초점 위치/카메라 기울임

    drawScene();

    glPopMatrix();
    glViewport(Width* 3/ 5, Height* 3/ 5, Width* 2/ 5, Height* 2/ 5);
    glPushMatrix();
    gluLookAt(0.0, 90.0, 30.0, 0.0, -1.0, 0.0, 0.0, 1.0, 0.0);

    drawScene();

    glPopMatrix();
    glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q':
    case 'Q': exit(0);break;
    case 'r':
    case 'R': glClearColor(1.0, 0.0, 0.0, 1.0); break;
    case 'w':
        acceration = true;
        if (speed <= 5)
            speed += 0.1f;
        else speed = 0;
        dspeed += speed; 
        break;
    }
    glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) //마우스 버튼에서 손 뗄 때
    {
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    /*float v[] = {
      lightDiffuse[0],  lightDiffuse[1],
      lightDiffuse[2],  lightDiffuse[3] };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, v);*/
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Embedded system");

    glutDisplayFunc(disp);
    glutReshapeFunc(changeSize);

    glutTimerFunc(1, Timer, 0);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMainLoop();

    return 1;
}
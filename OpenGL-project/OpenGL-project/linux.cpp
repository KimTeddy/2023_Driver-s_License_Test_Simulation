#ifdef __LINUX
#include "GL/freeglut.h"
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

#ifdef __LINUX//리눅스 전용 코딩

#endif

float angle, speed;
bool acceration = false;

void changeSize(int w, int h) {
    if (h == 0)  h = 1;

    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
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
        angle += speed;
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
void drawingCar() {

}
void disp() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0, 90.0, 30.0, 0.0, -1.0, 0.0, 0.0, 1.0, 0.0);


    //glDisable(GL_LIGHTING);
    // 평면 그리기
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0.0, -0.5, 0.0);
    glScalef(60.0, 1.0, 60.0);
        glutSolidCube(1.0);

    glPopMatrix();

    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    
    drawingCar();

    glColor3f(1.0, 0.0, 0.6);
    glutWireTorus(1, 3, 10, 100);

    //glEnable(GL_LIGHTING);
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
        angle += speed; 
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
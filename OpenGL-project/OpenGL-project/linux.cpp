//#include "GL/freeglut.h"
#include <GL/glut.h>

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

float angle = 0.0f;
void Timer(int val) {

    angle += 0.1f;

    glutPostRedisplay();
    glutTimerFunc(1, Timer, 0);
}
void disp() {

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(0.0f, 0.0f, 10.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glRotatef(angle, 0.5f, .0f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-2.0f, -2.0f, 0.0f);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(2.0f, 0.0f, -1.0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0.0f, 2.0f, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(2.0f, 2.0f, 3.0);
    glEnd();
    glColor4f(1.0, 0.0, 0.6, 0.1);
    glutWireTorus(1, 3, 10, 100);

    angle += 0.1f;

    glutSwapBuffers();
}

int main(int argc, char** argv) {

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Lighthouse3D- GLUT Tutorial");

    // register callbacks
    glutDisplayFunc(disp);
    glutReshapeFunc(changeSize);
    //glutIdleFunc(Timer);

    glutTimerFunc(10, Timer, 0);
    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}
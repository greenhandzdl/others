#include "common.h"
#include <stdlib.h>

GLfloat x = 250.0f;
GLfloat y = 250.0f;
GLfloat size = 50.0f;
GLsizei ww = 500, wh = 500;
int shape = 0;

void drawTriangle(GLint cx, GLint cy)
{
    GLfloat yCoord = wh - cy;
    GLfloat xCoord = cx;
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(xCoord, yCoord + size);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(xCoord - size, yCoord - size);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(xCoord + size, yCoord - size);
    glEnd();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawTriangle((GLint)x, (GLint)y);
    glutSwapBuffers();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void myReshape(GLint w, GLint h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    ww = w;
    wh = h;
}

void myMouse(GLint button, GLint state, GLint wx, GLint wy)
{
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        exit(0);
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x = (GLfloat)wx;
        y = (GLfloat)wy;
        glutPostRedisplay();   // 重绘
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("mouse triangle");
    init();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}
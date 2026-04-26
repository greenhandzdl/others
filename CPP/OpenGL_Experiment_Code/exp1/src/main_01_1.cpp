/**
* @file main.cpp
 * @brief FreeGLUT Template Application
 *
 * A basic FreeGLUT template demonstrating cross-platform OpenGL setup.
 * Works on macOS (with XQuartz) and Linux.
 */

#include "common.h"


void myDisplay() {
    // 设置背景色为黑色，参数分别为红、绿、蓝、透明度
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // 清空颜色缓冲区，准备绘制新的一帧
    glClear(GL_COLOR_BUFFER_BIT);

    // 设置当前绘图颜色为红色
    glColor3f(1.0f, 1.0f, 1.0f);
    // 绘制一个矩形，左下角(-0.5, -0.5)，右上角(0.5, 0.5)
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

    // 开始绘制三角形
    glBegin(GL_TRIANGLES);
    glColor3f (1.0f, 0.0f, 0.0f);glVertex2f(0.0f,1.0f);
    glColor3f (0.0f, 1.0f, 0.0f); glVertex2f(0.8f,-0.5f);
    glColor3f (0.0f, 0.0f, 1.0f);glVertex2f(-0.8f,-0.5f);
    glEnd();

    glPointSize(5.0f); // 设置点大小
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);glVertex2f(-0.4,-0.4f);
    glColor3f(0, 1, 0);glVertex2f(0.0f,0.0f);
    glColor3f(0, 0, 1);glVertex2f(0.4f,0.4f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1, 1, 1);glVertex2f(0.4f,0.25f);
    glColor3f(1, 1, 1);glVertex2f(0.0f,-0.5f);
    glColor3f(1, 1, 1);glVertex2f(-0.4f,0.25f);
    glEnd();

    glFlush();// 立即绘图
}

int main (int argc, char *argv[]) {
    glutInit(&argc, argv);

    /*
    *- `GLUT_RGBA`：使用RGBA颜色模式（红、绿、蓝、透明度），即每个像素有红绿蓝和alpha通道。
    - `GLUT_SINGLE`：使用单缓冲区（Single Buffer），绘制内容直接显示在屏幕上，不使用双缓冲。
    */
    glutInitDisplayMode (GLUT_RGBA | GLUT_SINGLE);
    // glutInitWindowSize (640, 480);
    // glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    glutDisplayFunc (myDisplay);
    glutMainLoop();
    return 0;
}
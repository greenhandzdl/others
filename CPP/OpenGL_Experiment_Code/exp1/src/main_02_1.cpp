#include "common.h"
#include <set>
#include <vector>
#include <cmath>

static  GLfloat x = 0;
static  GLfloat y = 0;
constexpr GLfloat divXandY = 15.0; // 调鼠标偏移的

static  GLfloat PenSize = 1;
constexpr  GLfloat PenSizeRise = 0.1;

static  GLsizei wh = 512,ww =768;
constexpr GLsizei divWHandWW = 50;

// 五角星偏移，这样挺好看的
constexpr GLfloat vertX[] = {0,1.5,5,2,4,0,-4,-2,-5,-1.5};
constexpr GLfloat vertY[] = {5,2,2,-1,-5,-3,-5,-1,2,2};
constexpr GLint numVertices = sizeof(vertX) / sizeof(vertX[0]);

struct DrawQueue {
    GLint x;
    GLint y;
    GLfloat PenSize;

    DrawQueue(GLint x, GLint y, GLfloat PenSize) {
        this->x = x;
        this->y = y;
        this->PenSize = PenSize;
    }

    bool operator<(const DrawQueue& q) const {
        return PenSize == q.PenSize ?
                (x == q.x ?
                y < q.y
                : x < q.x)
                : PenSize < q.PenSize;
    }
};

struct GLColor {
    GLfloat Red;
    GLfloat Green;
    GLfloat Blue;

    GLColor (GLfloat red, GLfloat green, GLfloat blue) {
        this->Red = red;
        this->Green = green;
        this->Blue = blue;
    }
};

static std::set<DrawQueue> drawQueue;

static bool isRightClick = false;
static std::vector<DrawQueue> drawLineQueue;

constexpr GLfloat comparedNum = 0;

/*
 * 负作用：改变线粗细、改变笔画颜色
 */
void starDraw(GLint x, GLint y ,GLfloat zoom
    ,GLsizei BoldSize
    ,GLColor BoldColor,GLColor FillColor) {
    // 画一个填充的五角星吧
    glColor3f(FillColor.Red,FillColor.Green,FillColor.Blue);
    // 外部的三角形
    for (auto i = -1; i < numVertices -1; i+=2) {
        glBegin(GL_POLYGON);
        for (auto j = 0; j < 3; j++) {
            glVertex3f(vertX[i == -1? (j  ? i + j : numVertices - 1) :i+j]*zoom +x, vertY[i == -1? (j ? i + j : numVertices - 1) : i+j]*zoom +y, 0);
        }
        glEnd();
    }
    //内部的五边形
    glBegin(GL_POLYGON);
    for (auto i = -1; i < numVertices -1; i+=2) {
        glVertex3f(vertX[i == -1 ? numVertices - 1:  i] * zoom + x,vertY[i == -1 ? numVertices - 1:  i] * zoom + y,0 );
    }
    glEnd();

    glLineWidth(BoldSize);
    glColor3f(BoldColor.Red,BoldColor.Green,BoldColor.Blue);
    glBegin(GL_LINE_LOOP);
    for (auto i = 0; i < numVertices; i++) {
        glVertex3f(vertX[i]*zoom +x, vertY[i]*zoom +y, 0);
    }
    glEnd();

}

/*
 * 负作用：改变线粗细、改变笔画颜色
 */
void lineDraw(std::vector<DrawQueue>& drawLineQueue
    ,GLColor LineColor
    ,GLsizei initLineSize) {
    glColor3f(LineColor.Red,LineColor.Green,LineColor.Blue);
    glBegin(GL_LINE_STRIP);
        for (auto item : drawLineQueue) {
            glLineWidth(item.PenSize);
            glVertex3f(item.x, item.y, 0);
        }
    glEnd();
}

void myDisplay() {
    glClear (GL_COLOR_BUFFER_BIT);

    // 颜色和笔画大小提前传
    glColor3f (1.0,1.0,1.0);
    glPointSize(5);

    for (auto item : drawQueue) {
        starDraw(item.x, item.y, item.PenSize,
            5,
            GLColor(0.9,0.9,0.2),
            GLColor(1,1,0)
            );
    }

    lineDraw(drawLineQueue,GLColor(1.0,1.0,1.0),5);

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

void myReshape(GLint w, GLint h) {
    glViewport(0, 0, w, h); // 重新映射一下屏幕吧

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //这样视口不会变特别厉害
    glOrtho(-7-w/divWHandWW, 7+w/divWHandWW, -7-h/divWHandWW, 7+h/divWHandWW, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    ww = w;
    wh = h;
}

void myMouse(GLint button, GLint state, GLint wx, GLint wy) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        /* 鼠标左键按下，记录位置
         * 记错了OpenGL默认的获取坐标，只能重新写一个映射到中间的
         * 操蛋
        */
        x = (wx-ww/2)/divXandY;
        y = (-wy+wh/2)/divXandY;

        if (isRightClick) {
            if (
                drawLineQueue.empty() ||
                abs( drawLineQueue.back().x - x ) > comparedNum &&
                abs( drawLineQueue.back().y - y ) > comparedNum
                ) {
                drawLineQueue.emplace_back(DrawQueue(x,y,PenSizeRise));
                }else{
                auto penSize = drawLineQueue.back().PenSize;
                drawLineQueue.pop_back();
                drawLineQueue.emplace_back(DrawQueue(x,y,PenSize+penSize));
            }
        }else {
            drawQueue.emplace(DrawQueue(x,y,PenSize));
        }
        
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        isRightClick ^= true; // xor
    }
}

void myMotionCapture(GLint x,GLint y) {
    myMouse(GLUT_LEFT_BUTTON,GLUT_DOWN,x,y);
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '0':
            // Default 是默认的五星红旗
            drawQueue.emplace(DrawQueue(-15,10,1.25));
            drawQueue.emplace(DrawQueue(-5,13,0.5));
            drawQueue.emplace(DrawQueue(-3,6,0.5));
            drawQueue.emplace(DrawQueue(-7,1,0.5));
            drawQueue.emplace(DrawQueue(-14,-2,0.5));
            break;

        case 'u':
            PenSize += PenSizeRise;
            break;
        case 'd':
            PenSize = PenSize - PenSizeRise > 0 ? PenSize - PenSizeRise : PenSizeRise;
            break;
        case 'z':
            if (not drawLineQueue.empty()) {
                drawLineQueue.pop_back();
            }
            break;
        case 'c':
            drawQueue.clear();
            drawLineQueue.clear();
            break;
        case 'q':
            exit(0);
        default:
            break;
    }
}

int main (int argc, char *argv[]) {
    glutInit(&argc, argv);

    /*
    *- `GLUT_RGBA`：使用RGBA颜色模式（红、绿、蓝、透明度），即每个像素有红绿蓝和alpha通道。
    - `GLUT_SINGLE`：使用单缓冲区（Single Buffer），绘制内容直接显示在屏幕上，不使用双缓冲。
    */
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);//需要双缓冲区做交换
    glutInitWindowSize (ww, wh);
    glutInitWindowPosition (0, 0);
    glutCreateWindow (argv[0]);

    // glClearColor(0.3,0.3,0.3,1.0);
    glClearColor(1,0,0,1);

    glutDisplayFunc (myDisplay);
    glutReshapeFunc (myReshape);

    // 只检测一次，有没有其实无所谓（做了速率控制）
    // glutIgnoreKeyRepeat(1);

    glutMouseFunc (myMouse);
    glutMotionFunc (myMotionCapture);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
    return 0;
}
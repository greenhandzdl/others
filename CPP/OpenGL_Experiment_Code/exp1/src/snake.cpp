#define USE_FREEGLUT
#include "common.h"
#include <deque>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>

// ==================== 常量定义 ====================
constexpr int GAME_WIDTH = 60;
constexpr int GAME_HEIGHT = 40;
constexpr int WALL_THICKNESS = 1;

// 时钟：循环一次多久 (毫秒)
constexpr int CLOCK_MS = 200;

// 果实相关常量
constexpr float FRUIT_RED = 1.0f;
constexpr float FRUIT_GREEN = 0.0f;
constexpr float FRUIT_BLUE = 0.0f;
constexpr float FRUIT_SIZE = 0.8f;

// 蛇相关常量
constexpr float SNAKE_RED = 0.0f;
constexpr float SNAKE_GREEN = 1.0f;
constexpr float SNAKE_BLUE = 0.0f;
constexpr float SNAKE_SIZE = 0.6f;
constexpr int SNAKE_INITIAL_LENGTH = 5;

// 墙相关常量
constexpr float WALL_RED = 0.5f;
constexpr float WALL_GREEN = 0.5f;
constexpr float WALL_BLUE = 0.5f;
constexpr int RANDOM_WALL_COUNT = 8;

// ==================== 前向声明 ====================
void spawnFruit();

// ==================== 数据结构 ====================
struct Position {
    int x;
    int y;

    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
};

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// ==================== 全局状态 ====================
static std::deque<Position> snake;              // 双头队列管理蛇的位置
static Position fruit;                          // 果实位置
static std::vector<std::pair<Position, Position>> walls;  // 墙的线段集合
static Direction currentDir = Direction::RIGHT; // 当前移动方向
static int score = 0;                            // 吃了多少果实
static bool gameOver = false;

// ==================== 随机数生成器 ====================
static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));

// ==================== 辅助函数 ====================
Position getRandomPosition() {
    std::uniform_int_distribution<int> xDist(WALL_THICKNESS + 1, GAME_WIDTH - WALL_THICKNESS - 2);
    std::uniform_int_distribution<int> yDist(WALL_THICKNESS + 1, GAME_HEIGHT - WALL_THICKNESS - 2);
    return Position(xDist(rng), yDist(rng));
}

Position getRandomUnitVector() {
    std::uniform_int_distribution<int> dirDist(0, 3);
    int d = dirDist(rng);
    switch (d) {
        case 0: return Position(1, 0);   // 右
        case 1: return Position(0, 1);   // 上
        case 2: return Position(-1, 0);  // 左
        default: return Position(0, -1); // 下
    }
}

// ==================== 游戏初始化 ====================
void initGame() {
    snake.clear();
    score = 0;
    gameOver = false;
    currentDir = Direction::RIGHT;

    // 初始化蛇的位置（中间开始）
    int startX = GAME_WIDTH / 2;
    int startY = GAME_HEIGHT / 2;
    for (int i = 0; i < SNAKE_INITIAL_LENGTH; i++) {
        snake.emplace_front(Position(startX - i, startY));
    }

    // 生成随机墙
    walls.clear();
    for (int i = 0; i < RANDOM_WALL_COUNT; i++) {
        Position start = getRandomPosition();
        Position direction = getRandomUnitVector();
        std::uniform_int_distribution<int> lengthDist(2, 6);
        int len = lengthDist(rng);

        // 防止墙与蛇的初始位置重叠
        bool overlap = false;
        for (int j = 0; j < len; j++) {
            Position p(start.x + direction.x * j, start.y + direction.y * j);
            for (const auto& s : snake) {
                if (p == s) {
                    overlap = true;
                    break;
                }
            }
        }
        if (!overlap) {
            Position end(start.x + direction.x * len, start.y + direction.y * len);
            walls.emplace_back(start, end);
        }
    }

    // 生成第一个果实
    spawnFruit();
}

void spawnFruit() {
    Position newFruit;
    bool valid = false;
    while (!valid) {
        newFruit = getRandomPosition();
        valid = true;

        // 检查是否与蛇身体重叠
        for (const auto& s : snake) {
            if (newFruit == s) {
                valid = false;
                break;
            }
        }

        // 检查是否与墙重叠
        if (valid) {
            for (const auto& w : walls) {
                const Position& start = w.first;
                const Position& end = w.second;
                // 检查线段上的点
                int minX = std::min(start.x, end.x);
                int maxX = std::max(start.x, end.x);
                int minY = std::min(start.y, end.y);
                int maxY = std::max(start.y, end.y);

                if (newFruit.x >= minX && newFruit.x <= maxX &&
                    newFruit.y >= minY && newFruit.y <= maxY) {
                    valid = false;
                    break;
                }
            }
        }
    }
    fruit = newFruit;
}

// ==================== 游戏逻辑 ====================
void update() {
    if (gameOver) return;

    // 计算新的头部位置
    Position head = snake.front();
    Position newHead = head;

    switch (currentDir) {
        case Direction::UP:
            newHead.y += 1;
            break;
        case Direction::DOWN:
            newHead.y -= 1;
            break;
        case Direction::LEFT:
            newHead.x -= 1;
            break;
        case Direction::RIGHT:
            newHead.x += 1;
            break;
    }

    // 检查是否撞墙（边界墙）
    if (newHead.x <= WALL_THICKNESS || newHead.x >= GAME_WIDTH - WALL_THICKNESS - 1 ||
        newHead.y <= WALL_THICKNESS || newHead.y >= GAME_HEIGHT - WALL_THICKNESS - 1) {
        gameOver = true;
        std::cout << "Game Over! You ate " << score << " fruits!" << std::endl;
        return;
    }

    // 检查是否撞到中间生成的墙
    for (const auto& w : walls) {
        const Position& start = w.first;
        const Position& end = w.second;
        int minX = std::min(start.x, end.x);
        int maxX = std::max(start.x, end.x);
        int minY = std::min(start.y, end.y);
        int maxY = std::max(start.y, end.y);

        if (newHead.x >= minX && newHead.x <= maxX &&
            newHead.y >= minY && newHead.y <= maxY) {
            gameOver = true;
            std::cout << "Game Over! You ate " << score << " fruits!" << std::endl;
            return;
        }
    }

    // 检查是否撞到自己
    for (const auto& s : snake) {
        if (newHead == s) {
            gameOver = true;
            std::cout << "Game Over! You ate " << score << " fruits!" << std::endl;
            return;
        }
    }

    // 移动蛇
    snake.emplace_front(newHead);

    // 检查是否吃到果实
    if (newHead == fruit) {
        score++;
        spawnFruit();
    } else {
        snake.pop_back(); // 没吃到则移除尾部
    }
}

// ==================== 绘制函数 ====================
void drawWalls() {
    glColor3f(WALL_RED, WALL_GREEN, WALL_BLUE);
    glLineWidth(2.0f);

    // 绘制四周的墙
    glBegin(GL_LINE_LOOP);
    glVertex3f(WALL_THICKNESS, WALL_THICKNESS, 0);
    glVertex3f(GAME_WIDTH - WALL_THICKNESS - 1, WALL_THICKNESS, 0);
    glVertex3f(GAME_WIDTH - WALL_THICKNESS - 1, GAME_HEIGHT - WALL_THICKNESS - 1, 0);
    glVertex3f(WALL_THICKNESS, GAME_HEIGHT - WALL_THICKNESS - 1, 0);
    glEnd();

    // 绘制中间的随机墙
    glBegin(GL_LINES);
    for (const auto& w : walls) {
        glVertex3f(w.first.x, w.first.y, 0);
        glVertex3f(w.second.x, w.second.y, 0);
    }
    glEnd();
}

void drawSnake() {
    glColor3f(SNAKE_RED, SNAKE_GREEN, SNAKE_BLUE);
    glLineWidth(SNAKE_SIZE * 3);

    glBegin(GL_LINE_STRIP);
    for (const auto& s : snake) {
        glVertex3f(s.x, s.y, 0);
    }
    glEnd();
}

void drawFruit() {
    glColor3f(FRUIT_RED, FRUIT_GREEN, FRUIT_BLUE);
    glPointSize(FRUIT_SIZE * 5);

    glBegin(GL_POINTS);
    glVertex3f(fruit.x, fruit.y, 0);
    glEnd();
}

// ==================== 回调函数 ====================
void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 绘制游戏元素
    drawWalls();
    drawFruit();
    drawSnake();

    glFlush();
    // glutSwapBuffers();
    glutPostRedisplay();
}

void myReshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, GAME_WIDTH + 1, -1, GAME_HEIGHT + 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
        case 'W':
            if (currentDir != Direction::DOWN) {
                currentDir = Direction::UP;
            }
            break;
        case 's':
        case 'S':
            if (currentDir != Direction::UP) {
                currentDir = Direction::DOWN;
            }
            break;
        case 'a':
        case 'A':
            if (currentDir != Direction::RIGHT) {
                currentDir = Direction::LEFT;
            }
            break;
        case 'd':
        case 'D':
            if (currentDir != Direction::LEFT) {
                currentDir = Direction::RIGHT;
            }
            break;
        case 'q':
        case 'Q':
            std::cout << "You ate " << score << " fruits. Goodbye!" << std::endl;
            exit(0);
            break;
        case 'r':
        case 'R':
            initGame();
            break;
        default:
            break;
    }
}

void gameTimer(int value) {
    update();
    glutTimerFunc(CLOCK_MS, gameTimer, 0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Snake Game");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // 初始化游戏
    initGame();

    // 注册回调函数
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glutKeyboardFunc(myKeyboard);
    glutTimerFunc(CLOCK_MS, gameTimer, 0);

    glutMainLoop();
    return 0;
}
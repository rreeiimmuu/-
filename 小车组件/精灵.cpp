#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "acllib.h"

using namespace std;

// 基本精灵类
class Sprite {
public:
    ACL_Image img;
    int x, y, width, height;
    int dx, dy;
    int scoreValue;

    Sprite(const char* filename, int w, int h, int score = 0)
        : width(w), height(h), scoreValue(score) {
        loadImage(filename, &img);
        x = rand() % (640 - width);
        y = rand() % (480 - height);
        dx = (rand() % 3 + 1) * (rand() % 2 == 0 ? 1 : -1);
        dy = (rand() % 3 + 1) * (rand() % 2 == 0 ? 1 : -1);
    }

    virtual void move() {
        x += dx;
        y += dy;

        // 边界反弹
        if (x < 0 || x + width > 640) dx *= -1;
        if (y < 0 || y + height > 480) dy *= -1;
    }

    void draw() {
        putImageScale(&img, x, y, width, height);
    }

    rect getBoundingBox() {
        return {x, y, width, height};
    }

    double distanceTo(Sprite* other) {
        int cx1 = x + width / 2;
        int cy1 = y + height / 2;
        int cx2 = other->x + other->width / 2;
        int cy2 = other->y + other->height / 2;
        return sqrt(pow(cx1 - cx2, 2) + pow(cy1 - cy2, 2));
    }
};

// 自动精灵类
class AutoSprite : public Sprite {
public:
    AutoSprite(const char* filename, int w, int h, int score)
        : Sprite(filename, w, h, score) {}
};

// 追逐精灵类
class ChaserSprite : public AutoSprite {
public:
    ChaserSprite(const char* filename, int w, int h, int score)
        : AutoSprite(filename, w, h, score) {}

    void moveTowards(Sprite* target) {
        if (distanceTo(target) < 100) {
            dx = 2 * (target->x > x ? 1 : -1);
            dy = 2 * (target->y > y ? 1 : -1);
        }
        Sprite::move();
    }
};

// 躲避精灵类
class EvaderSprite : public AutoSprite {
public:
    EvaderSprite(const char* filename, int w, int h, int score)
        : AutoSprite(filename, w, h, score) {}

    void moveAwayFrom(Sprite* target) {
        if (distanceTo(target) < 100) {
            dx = 2 * (target->x < x ? 1 : -1);
            dy = 2 * (target->y < y ? 1 : -1);
        }
        Sprite::move();
    }
};

// 用户控制精灵类
class ControlledSprite : public Sprite {
public:
    ControlledSprite(const char* filename, int w, int h)
        : Sprite(filename, w, h) {}

    void move(int key) {
        switch (key) {
            case VK_UP:    y -= 5; break;
            case VK_DOWN:  y += 5; break;
            case VK_LEFT:  x -= 5; break;
            case VK_RIGHT: x += 5; break;
        }
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x + width > 640) x = 640 - width;
        if (y + height > 480) y = 480 - height;
    }
};

// 全局变量
const int WIDTH = 640, HEIGHT = 480;
ControlledSprite* userSprite;
AutoSprite* autoSprites[10];
int autoSpriteCount = 0;
int score = 0;
ACL_Sound sound;

// 碰撞检测函数
bool checkCollision(rect r1, rect r2) {
    return r1.x < r2.x + r2.w && r1.x + r1.w > r2.x &&
           r1.y < r2.y + r2.h && r1.y + r1.h > r2.y;
}

// 设置窗口和初始化
int Setup() {
    srand((unsigned)time(NULL));
    initWindow("Sprite Game", 0, 0, WIDTH, HEIGHT);
    userSprite = new ControlledSprite("user_sprite.png", 50, 50);
    loadSound("collision.wav", &sound);

    registerTimerEvent(timerEvent);
    startTimer(0, 500);
    startTimer(1, 50);

    return 0;
}

// 定时器事件处理
void timerEvent(int id) {
    switch (id) {
        case 0: // 生成自动精灵
            if (autoSpriteCount < 10) {
                int randVal = rand() % 100;
                if (randVal < 75) {
                    autoSprites[autoSpriteCount] = new AutoSprite("auto_sprite.png", 50, 50, 10);
                } else if (randVal < 95) {
                    autoSprites[autoSpriteCount] = new ChaserSprite("chaser_sprite.png", 50, 50, 20);
                } else {
                    autoSprites[autoSpriteCount] = new EvaderSprite("evader_sprite.png", 50, 50, 30);
                }
                autoSpriteCount++;
            }
            break;
        case 1: // 移动自动精灵
            for (int i = 0; i < autoSpriteCount; ++i) {
                if (autoSprites[i] != nullptr) {
                    if (ChaserSprite* chaser = dynamic_cast<ChaserSprite*>(autoSprites[i])) {
                        chaser->moveTowards(userSprite);
                    } else if (EvaderSprite* evader = dynamic_cast<EvaderSprite*>(autoSprites[i])) {
                        evader->moveAwayFrom(userSprite);
                    } else {
                        autoSprites[i]->move();
                    }
                    rect userBox = userSprite->getBoundingBox();
                    rect autoBox = autoSprites[i]->getBoundingBox();

                    if (checkCollision(userBox, autoBox)) {
                        score += autoSprites[i]->scoreValue;
                        playSound(sound, 0);
                        delete autoSprites[i];
                        autoSprites[i] = autoSprites[--autoSpriteCount];
                        autoSprites[autoSpriteCount] = nullptr;
                    }
                }
            }
            break;
    }
    beginPaint();
    clearDevice();

    userSprite->draw();
    for (int i = 0; i < autoSpriteCount; ++i) {
        if (autoSprites[i] != nullptr) {
            autoSprites[i]->draw();
        }
    }

    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    paintText(10, 10, scoreText);

    endPaint();
}

// 键盘事件处理
void keyEvent(int key, int event) {
    if (event == KEY_DOWN) {
        userSprite->move(key);
    }
}

int main() {
    Setup();
    registerKeyboardEvent(keyEvent);
    run();
    return 0;
}
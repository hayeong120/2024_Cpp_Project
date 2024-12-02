#ifndef GHOST_H
#define GHOST_H

#include "util.h"
#include <cmath>

class Player;

// ���� ���
enum GhostMode { Chase, Scatter, Frightened, Eaten };
// �߰� ���, �ػ� ���, ���� ���, ��ȹ ���

// ���� Ŭ����
class Ghost {
public:
    int x, y;               // ������ ��ǥ
    int startX, startY;     // �ʱ� ��ġ
    int speed;              // �̵� �ӵ�
    GhostMode mode;         // ���� ���
    int frightenedTimer;    // ���� ��� Ÿ�̸�

    Ghost(int startX, int startY, int startSpeed = 10000)
        : x(startX), y(startY), startX(startX), startY(startY),
        speed(startSpeed), mode(Scatter), frightenedTimer(0) {}

    // ���� �̵� �Լ�
    virtual void move(Player& player) = 0; // ���� ���� �Լ�

    void reset();         // �ʱ� ��ġ�� ����
    void enterFrightenedMode(); // ���� ���� ��ȯ
    void updateMode(int elapsedTime); // ��� ������Ʈ

};

// Blinky: �÷��̾ �Ѿư�
class Blinky : public Ghost {
public:
    Blinky(int startX, int startY, int startSpeed = 10000)
        : Ghost(startX, startY, startSpeed) {}

    void move(Player& player) override;
};

// Pinky: �÷��̾ ���� ������ 4ĭ�� �Ѿư�
class Pinky : public Ghost {
public:
    Pinky(int startX, int startY, int startSpeed = 1)
        : Ghost(startX, startY, startSpeed) {}

    void move(Player& player) override;
};

// Inky: �÷��̾���� �Ÿ��� ����Ͽ� �Ѿư�
class Inky : public Ghost {
public:
    Inky(int startX, int startY, int startSpeed = 1)
        : Ghost(startX, startY, startSpeed) {}

    void move(Player& player) override;
};

// Clyde: �ָ� �Ѱ�, ������ �������� ��
class Clyde : public Ghost {
public:
    Clyde(int startX, int startY, int startSpeed = 1)
        : Ghost(startX, startY, startSpeed) {}

    void move(Player& player) override;
};

#endif // GHOST_H
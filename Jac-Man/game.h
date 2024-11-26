#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "util.h"

// Ű���� ��
enum class KeyValue { UP, DOWN, LEFT, RIGHT, SUBMIT, NONE };

class Game {
private:
    static const int START_Y = 17;
    static const int MAP_START_Y = 14;

    // ���� ���� �Լ�
    KeyValue keyControl() const;
    void moveCursor(int& x, int& y, KeyValue key, int minY, int maxY) const;

public:
    // ������ �� �ʱ�ȭ
    Game();
    void init() const;

    // �ֿ� ���� ����
    void titleDraw() const;
    void infoDraw() const;
    int menuDraw() const;
    int maplistDraw() const;

    // ���� ���� �Լ�
    void run();
};

#endif // GAME_H

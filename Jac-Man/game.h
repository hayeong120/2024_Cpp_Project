#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "util.h"
#include "map.h"

// Ű���� ��
enum class KeyValue { UP, DOWN, LEFT, RIGHT, SUBMIT, NONE };

class Game {
private:
    Map gameMap;
    static const int START_Y = 18;
    static const int MAP_START_Y = 14;

    // ���� ���� �Լ�
    KeyValue keyControl() const;
    void moveCursor(int& x, int& y, KeyValue key, int minY, int maxY) const;

public:
    // ������ �� �ʱ�ȭ
    Game();
    void init() const;

    // �ֿ� ���� ����
    void showTitle() const;
    int showMenu() const;
    void showInfo() const;
    void loading(int q, int p);

    // ���� ���� �Լ�
    void run();
};

#endif // GAME_H

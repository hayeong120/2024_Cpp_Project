#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <Windows.h>
#include <conio.h>

// Ű���� ��
enum class KeyValue { UP, DOWN, LEFT, RIGHT, SUBMIT, NONE };

class Game {
private:
    static const int START_Y = 17;

    // ���� ��ƿ��Ƽ �Լ�
    void gotoxy(int x, int y) const;

    // ���� ���� �Լ�
    KeyValue keyControl() const;

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

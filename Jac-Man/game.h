#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "util.h"

// 키보드 값
enum class KeyValue { UP, DOWN, LEFT, RIGHT, SUBMIT, NONE };

class Game {
private:
    static const int START_Y = 17;
    static const int MAP_START_Y = 14;

    // 내부 로직 함수
    KeyValue keyControl() const;
    void moveCursor(int& x, int& y, KeyValue key, int minY, int maxY) const;

public:
    // 생성자 및 초기화
    Game();
    void init() const;

    // 주요 게임 로직
    void titleDraw() const;
    void infoDraw() const;
    int menuDraw() const;
    int maplistDraw() const;

    // 메인 실행 함수
    void run();
};

#endif // GAME_H

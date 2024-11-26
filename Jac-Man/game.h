#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "util.h"
#include "map.h"

// 키보드 값
enum class KeyValue { UP, DOWN, LEFT, RIGHT, SUBMIT, NONE };

class Game {
private:
    Map gameMap;
    static const int START_Y = 18;
    static const int MAP_START_Y = 14;

    // 내부 로직 함수
    KeyValue keyControl() const;
    void moveCursor(int& x, int& y, KeyValue key, int minY, int maxY) const;

public:
    // 생성자 및 초기화
    Game();
    void init() const;

    // 주요 게임 로직
    void showTitle() const;
    int showMenu() const;
    void showInfo() const;
    void loading(int q, int p);

    // 메인 실행 함수
    void run();
};

#endif // GAME_H

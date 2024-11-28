#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "util.h"
#include "map.h"

// 키보드 값
enum class KeyValue { UP, DOWN, LEFT, RIGHT, SUBMIT, NONE };

struct player {
    int coin;
    bool power;
    bool death;
};

class Game {
private:
    Map gameMap;
    static const int START_Y = 18;
    static const int MAP_START_Y = 14;

    // 내부 로직 함수
    KeyValue keyControl() const;
    void moveCursor(int& x, int& y, KeyValue key, int minY, int maxY) const;

    // 플레이어
    int playerX, playerY; // 플레이어 위치
    int score;            // 플레이어 점수
    player playerState;   // 플레이어 상태 구조체
    Map map;              // 맵 객체

    void drawPlayer() const;                    // 플레이어 그리기
    void updatePlayerPosition(KeyValue key);    // 플레이어 위치 업데이트
    void handleItem(int x, int y);              // 아이템 처리
    void teleport();                            // 포탈 처리
    void drawScore() const;

    void clearItem(int x, int y);   // 특정 위치의 아이템을 제거
    int getItem(int x, int y);      // 특정 위치의 아이템 타입을 반환  

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

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include "util.h"
#include "map.h"

// 키보드 값
enum class KeyValue { UP, DOWN, LEFT, RIGHT, SUBMIT, NONE };

// 플레이어 방향 열거형
enum Direction { UP, DOWN, LEFT, RIGHT };

// 유령 클래스
class Ghost;

// 플레이어 클래스
class Player {
public:
    int x, y;               // 좌표
    int coin;               // 코인
    bool power;             // 파워 상태
    int lives;              // 목숨 수
    Direction direction;    // 방향

    Player(int startX, int startY, Direction startDirection)
        : x(startX), y(startY), coin(0), power(false), lives(3), direction(startDirection) {}
};

class Game {
private:
    static const int START_Y = 18;
    static const int MAP_START_Y = 14;

    // 내부 로직 함수
    KeyValue keyControl() const;
    void moveCursor(int& x, int& y, KeyValue key, int minY, int maxY) const;

    Map gameMap;
    Player player;
    std::vector<Ghost*> ghosts;

    int timer;           // 타이머 (초 단위)
    int powerTimer;      // 파워 아이템 지속 시간
    int level;           // 현재 레벨

    // 유령
    void drawGhosts() const;       // 유령 그리기
    void updateGhosts();           // 유령 위치 업데이트
    void handleGhostCollision();   // 유령 충돌 처리
    void updateGhostModes();    // 유령 모드 업데이트

    // 플레이어
    void drawPlayer() const;                    // 플레이어 그리기
    void updatePlayerPosition(KeyValue key);    // 플레이어 위치 업데이트

    void resetLevel();              // 레벨 초기화
    void updateTimers();            // 타이머 업데이트

    void drawScore() const;         // 점수 처리
    void handleItem(int x, int y);  // 아이템 처리
    void teleport();                // 포탈 처리

    void clearItem(int x, int y);   // 특정 위치의 아이템을 제거
    int getItem(int x, int y);      // 특정 위치의 아이템 타입을 반환  

public:
    // 생성자 및 초기화
    Game();
    ~Game();

    void init() const;

    // 게임 인트로 로직
    void showTitle() const;
    int showMenu() const;
    void showInfo() const;
    void loading(int q, int p);

    // 메인 실행 함수
    void run();
};

#endif // GAME_H

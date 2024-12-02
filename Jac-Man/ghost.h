#ifndef GHOST_H
#define GHOST_H

#include "util.h"
#include <cmath>

class Player;

// 유령 모드
enum GhostMode { Chase, Scatter, Frightened, Eaten };
// 추격 모드, 해산 모드, 공포 모드, 포획 모드

// 유령 클래스
class Ghost {
public:
    int x, y;               // 유령의 좌표
    int startX, startY;     // 초기 위치
    int speed;              // 이동 속도
    GhostMode mode;         // 현재 모드
    int frightenedTimer;    // 공포 모드 타이머

    Ghost(int startX, int startY, int startSpeed = 10000)
        : x(startX), y(startY), startX(startX), startY(startY),
        speed(startSpeed), mode(Scatter), frightenedTimer(0) {}

    // 유령 이동 함수
    virtual void move(Player& player) = 0; // 순수 가상 함수

    void reset();         // 초기 위치로 복귀
    void enterFrightenedMode(); // 공포 모드로 전환
    void updateMode(int elapsedTime); // 모드 업데이트

};

// Blinky: 플레이어를 쫓아감
class Blinky : public Ghost {
public:
    Blinky(int startX, int startY, int startSpeed = 10000)
        : Ghost(startX, startY, startSpeed) {}

    void move(Player& player) override;
};

// Pinky: 플레이어가 보는 방향의 4칸을 쫓아감
class Pinky : public Ghost {
public:
    Pinky(int startX, int startY, int startSpeed = 1)
        : Ghost(startX, startY, startSpeed) {}

    void move(Player& player) override;
};

// Inky: 플레이어와의 거리를 계산하여 쫓아감
class Inky : public Ghost {
public:
    Inky(int startX, int startY, int startSpeed = 1)
        : Ghost(startX, startY, startSpeed) {}

    void move(Player& player) override;
};

// Clyde: 멀면 쫓고, 가까우면 구석으로 감
class Clyde : public Ghost {
public:
    Clyde(int startX, int startY, int startSpeed = 1)
        : Ghost(startX, startY, startSpeed) {}

    void move(Player& player) override;
};

#endif // GHOST_H
#include "ghost.h"
#include "game.h"
#include "util.h" 
#include "map.h"

Map gameMap;

// 초기 위치로 복귀
void Ghost::reset() {
    x = startX;
    y = startY;
    mode = Scatter; // 초기화 시 해산 모드로 시작
}

// 공포 모드로 전환
void Ghost::enterFrightenedMode() {
    mode = Frightened;
    frightenedTimer = 2000; // 공포 모드 20초 유지
}

// 모드 업데이트
void Ghost::updateMode(int elapsedTime) {
    static const int scatterDurations[] = { 7000, 7000, 5000, 5000 };
    static const int chaseDurations[] = { 20000, 200000, 200000, -1 }; // -1은 무한

    int totalDuration = 0;
    for (int i = 0; i < 4; i++) {
        totalDuration += scatterDurations[i];
        if (elapsedTime < totalDuration) {
            mode = Scatter;
            return;
        }
        totalDuration += chaseDurations[i];
        if (elapsedTime < totalDuration) {
            mode = Chase;
            return;
        }
    }
    mode = Chase; // 기본적으로 추격 모드
}

// Blinky: 플레이어를 쫓아감
void Blinky::move(Player& player) {
    setTextColor(Red);
    if (mode == Frightened) return;
    int dx = player.x - x;
    int dy = player.y - y;

    // 이동 전 이전 위치 지우기
    gotoxy(x * 2 + 4, y + 3);
    std::cout << "  ";

    if (abs(dx) > abs(dy)) {
        int nextX = x + ((dx > 0) ? speed : -speed);
        if (!gameMap.isWall(nextX, y)) {
            x = nextX;
        }
    }
    else {
        int nextY = y + ((dy > 0) ? speed : -speed);
        if (!gameMap.isWall(x, nextY)) {
            y = nextY;
        }
    }

    // 이동 후 새로운 위치 그리기
    gotoxy(x * 2 + 4, y + 3);
    std::cout << "▼";
}

// Pinky: 플레이어가 보는 방향의 사각형 4칸을 쫓아감
void Pinky::move(Player& player) {
    setTextColor(Magenta);
    int targetX = player.x;
    int targetY = player.y;
    switch (player.direction) {
    case UP: targetY -= 4; break;
    case DOWN: targetY += 4; break;
    case LEFT: targetX -= 4; break;
    case RIGHT: targetX += 4; break;
    }

    int dx = targetX - x;
    int dy = targetY - y;
    if (abs(dx) > abs(dy)) {
        x += (dx > 0) ? speed : -speed;
    }
    else {
        y += (dy > 0) ? speed : -speed;
    }
}

// Inky: 플레이어와의 거리를 계산하여 쫓아감
void Inky::move(Player& player) {
    setTextColor(Cyan);
    int dx = player.x - x;
    int dy = player.y - y;
    int distance = static_cast<int>(sqrt(dx * dx + dy * dy));

    if (distance > 5) {
        x += (dx > 0) ? speed : -speed;
        y += (dy > 0) ? speed : -speed;
    }
}

// Clyde: 플레이어가 멀면 쫓고, 가까우면 구석으로 감
void Clyde::move(Player& player) {
    setTextColor(Yellow);
    int dx = player.x - x;
    int dy = player.y - y;
    int distance = static_cast<int>(sqrt(dx * dx + dy * dy));

    if (distance > 8) {
        x += (dx > 0) ? speed : -speed;
        y += (dy > 0) ? speed : -speed;
    }
    else {
        x = 0; // 구석으로 이동 (맵의 구석 좌표로 수정 가능)
        y = 0;
    }
}

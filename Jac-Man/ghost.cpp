#include "ghost.h"
#include "game.h"
#include "util.h" 
#include "map.h"

Map gameMap;

// �ʱ� ��ġ�� ����
void Ghost::reset() {
    x = startX;
    y = startY;
    mode = Scatter; // �ʱ�ȭ �� �ػ� ���� ����
}

// ���� ���� ��ȯ
void Ghost::enterFrightenedMode() {
    mode = Frightened;
    frightenedTimer = 2000; // ���� ��� 20�� ����
}

// ��� ������Ʈ
void Ghost::updateMode(int elapsedTime) {
    static const int scatterDurations[] = { 7000, 7000, 5000, 5000 };
    static const int chaseDurations[] = { 20000, 200000, 200000, -1 }; // -1�� ����

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
    mode = Chase; // �⺻������ �߰� ���
}

// Blinky: �÷��̾ �Ѿư�
void Blinky::move(Player& player) {
    setTextColor(Red);
    if (mode == Frightened) return;
    int dx = player.x - x;
    int dy = player.y - y;

    // �̵� �� ���� ��ġ �����
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

    // �̵� �� ���ο� ��ġ �׸���
    gotoxy(x * 2 + 4, y + 3);
    std::cout << "��";
}

// Pinky: �÷��̾ ���� ������ �簢�� 4ĭ�� �Ѿư�
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

// Inky: �÷��̾���� �Ÿ��� ����Ͽ� �Ѿư�
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

// Clyde: �÷��̾ �ָ� �Ѱ�, ������ �������� ��
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
        x = 0; // �������� �̵� (���� ���� ��ǥ�� ���� ����)
        y = 0;
    }
}

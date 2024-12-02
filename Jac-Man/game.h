#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include "util.h"
#include "map.h"

// Ű���� ��
enum class KeyValue { UP, DOWN, LEFT, RIGHT, SUBMIT, NONE };

// �÷��̾� ���� ������
enum Direction { UP, DOWN, LEFT, RIGHT };

// ���� Ŭ����
class Ghost;

// �÷��̾� Ŭ����
class Player {
public:
    int x, y;               // ��ǥ
    int coin;               // ����
    bool power;             // �Ŀ� ����
    int lives;              // ��� ��
    Direction direction;    // ����

    Player(int startX, int startY, Direction startDirection)
        : x(startX), y(startY), coin(0), power(false), lives(3), direction(startDirection) {}
};

class Game {
private:
    static const int START_Y = 18;
    static const int MAP_START_Y = 14;

    // ���� ���� �Լ�
    KeyValue keyControl() const;
    void moveCursor(int& x, int& y, KeyValue key, int minY, int maxY) const;

    Map gameMap;
    Player player;
    std::vector<Ghost*> ghosts;

    int timer;           // Ÿ�̸� (�� ����)
    int powerTimer;      // �Ŀ� ������ ���� �ð�
    int level;           // ���� ����

    // ����
    void drawGhosts() const;       // ���� �׸���
    void updateGhosts();           // ���� ��ġ ������Ʈ
    void handleGhostCollision();   // ���� �浹 ó��
    void updateGhostModes();    // ���� ��� ������Ʈ

    // �÷��̾�
    void drawPlayer() const;                    // �÷��̾� �׸���
    void updatePlayerPosition(KeyValue key);    // �÷��̾� ��ġ ������Ʈ

    void resetLevel();              // ���� �ʱ�ȭ
    void updateTimers();            // Ÿ�̸� ������Ʈ

    void drawScore() const;         // ���� ó��
    void handleItem(int x, int y);  // ������ ó��
    void teleport();                // ��Ż ó��

    void clearItem(int x, int y);   // Ư�� ��ġ�� �������� ����
    int getItem(int x, int y);      // Ư�� ��ġ�� ������ Ÿ���� ��ȯ  

public:
    // ������ �� �ʱ�ȭ
    Game();
    ~Game();

    void init() const;

    // ���� ��Ʈ�� ����
    void showTitle() const;
    int showMenu() const;
    void showInfo() const;
    void loading(int q, int p);

    // ���� ���� �Լ�
    void run();
};

#endif // GAME_H

#include "game.h"
#include "ghost.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;

// ������
Game::Game() : player(20, 21, UP), timer(0), powerTimer(0), level(1) {
    ghosts.push_back(new Blinky(22, 7));
    //ghosts.push_back(new Pinky(22, 6));
    //ghosts.push_back(new Inky(21, 6));
    //ghosts.push_back(new Clyde(23, 6));
}

// �Ҹ���
Game::~Game() {
    for (Ghost* ghost : ghosts) {
        delete ghost; // ���� ���� �޸� ����
    }
}

// Ű �Է� ó��
KeyValue Game::keyControl() const {
    int key = _getch();

    if (key == 0 || key == 224) { // Ư�� Ű Ȯ��
        key = _getch();
        switch (key) {
            case 72: return KeyValue::UP;
            case 75: return KeyValue::LEFT;
            case 77: return KeyValue::RIGHT;
            case 80: return KeyValue::DOWN;
        }
    }
    else { // �Ϲ� Ű
        switch (key) {  // �����̽��� �Ǵ� ���͹�
            case 32: case 13: return KeyValue::SUBMIT; 
        }
    }
    return KeyValue::NONE;
}

// Ŀ�� �̵� ó��
void Game::moveCursor(int& x, int& y, KeyValue key, int minY, int maxY) const {
    if (key == KeyValue::UP && y > minY) {
        gotoxy(x - 2, y--);
        std::cout << " ";
        gotoxy(x - 2, y);
        std::cout << ">";
    }
    if (key == KeyValue::DOWN && y < maxY) {
        gotoxy(x - 2, y++);
        std::cout << " ";
        gotoxy(x - 2, y);
        std::cout << ">";
    }
}

// �ʱ�ȭ
void Game::resetLevel() {
    timer = 0;
    powerTimer = 0;
    player.x = 20;
    player.y = 21;
    player.power = false;
    for (Ghost* ghost : ghosts) {
        ghost->reset();
    }
}

// Ÿ�̸� ����
void Game::updateTimers() {
    timer++;
    if (powerTimer > 0) powerTimer--;

    if (powerTimer == 0 && player.power) {
        player.power = false; // �Ŀ� ��� ����
        for (Ghost* ghost : ghosts) {
            if (ghost->mode == Frightened) {
                ghost->mode = Scatter;
            }
        }
    }
}

// ��� ��ȯ
void Game::updateGhostModes() {
    for (Ghost* ghost : ghosts) {
        ghost->updateMode(timer);
    }
}

// �÷��̾� �׸���
void Game::drawPlayer() const {
    gotoxy(player.x * 2 + 4, player.y + 3); // ���� ��ǥ�� ���� ��ġ ��ȯ
    std::cout << "��"; // �÷��̾� ĳ����
}

// �÷��̾� �̵� ������Ʈ
void Game::updatePlayerPosition(KeyValue key) {
    int nextX = player.x;
    int nextY = player.y;

    switch (key) {
    case KeyValue::UP:    nextY--; break;
    case KeyValue::DOWN:  nextY++; break;
    case KeyValue::LEFT:  nextX--; break;
    case KeyValue::RIGHT: nextX++; break;
    default: return;
    }

    // �̵� ���� ���� Ȯ��
    if (!gameMap.isWall(nextX, nextY)) {
        // ���� ��ġ �����
        gotoxy(player.x * 2 + 4, player.y + 3);
        std::cout << "  ";

        // ��ġ ������Ʈ
        player.x = nextX;
        player.y = nextY;

        // ������ ó��
        handleItem(player.x, player.y);

        // ���ο� ��ġ�� �÷��̾� �׸���
        drawPlayer();

        // ���� ���
        drawScore();
    }
}

// ������ ó��
void Game::handleItem(int x, int y) {
    if (x < 0 || y < 0 || x >= gameMap.getCols() || y >= gameMap.getRows()) return;

    int itemType = gameMap.getTile(x, y);
    switch (itemType) {
    case 2: // ���� ������
        player.coin+=10;
        gameMap.setTile(x, y, 0);
        break;

    case 3: // �Ŀ� ������
        player.power = true;
        gameMap.setTile(x, y, 0);
        break;

    case 4: // ��Ż
        teleport(); // ��Ż ó��
        break;

    default:
        break;
    }
}

// ��Ż ó��
void Game::teleport() {
    for (int row = 0; row < gameMap.getRows(); ++row) {
        for (int col = 0; col < gameMap.getCols(); ++col) {
            if (gameMap.getTile(col, row) == 4) {  // ��Ż�� ã����
                // ��Ż ��ġ�� ���� ��ġ�� �ٸ��� �ݴ��� ��Ż�� �̵�
                if (row != player.y || col != player.x) {
                    player.x = col;  
                    player.y = row;  
                    drawPlayer();
                    return;          
                }
            }
        }
    }
}

// ����
// ���� �׸���
void Game::drawGhosts() const {
    for (const Ghost* ghost : ghosts) {
        gotoxy(ghost->x * 2 + 4, ghost->y + 3);
        std::cout << "��"; // ���� ĳ����
    }
}

// ���� �̵� ������Ʈ
void Game::updateGhosts() {
    for (Ghost* ghost : ghosts) {
        ghost->move(player);
    }
    drawGhosts();
}

// ���� �浹 ó��
void Game::handleGhostCollision() {
    for (Ghost* ghost : ghosts) {
        if (ghost->x == player.x && ghost->y == player.y) {
            if (player.power) {
                // ���� ����
                ghost->x = -1;
                ghost->y = -1;
            }
            else {
                player.lives--;
                if (player.lives <= 0) {
                    std::cout << "Game Over!\n";
                    Sleep(2000);
                    exit(0); // ���� ����
                }

            }
        }
    }
}

// ���� ó��
void Game::drawScore() const {
    gotoxy(2, 1); // ���ھ� ��ġ
    std::cout << "Score: " << player.coin << "\t" << "Lives: ";
    for (int i = 0; i < player.lives; i++)
        std::cout << "�� ";
}

// �ܼ� �ʱ�ȭ
void Game::init() const {
    system("mode con cols = 100 lines = 30 | title Jac-Man");
}

// Ÿ��Ʋ ���
void Game::showTitle() const {
    std::cout << "\n\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t       #####   #    ####       #   #   #   #   # \n";
    std::cout << "\t\t\t         #    # #  #           ## ##  # #  ##  # \n";
    std::cout << "\t\t\t         #   ##### #     ##### # # # ##### # # # \n";
    std::cout << "\t\t\t       # #   #   # #           #   # #   # #  ## \n";
    std::cout << "\t\t\t        #    #   #  ####       #   # #   # #   # \n";
}

// ���� ���� ���
void Game::showInfo() const {
    system("cls");
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t       [���۹�]\n\n";
    std::cout << "\t\t\t\t         �̵� : ����Ű �̿�\n";
    std::cout << "\t\t\t\t     ���� : �����̽��� �Ǵ� ����";
    while (true) {
        if (keyControl() == KeyValue::SUBMIT) {
            break;
        }
    }
}

// �޴� ��� �� �Է�
int Game::showMenu() const {
    int x = 45, y = START_Y;

    // �޴� ǥ��
    gotoxy(x - 2, y);
    std::cout << ">";
    gotoxy(x, START_Y);
    std::cout << " �� �� �� ��";
    gotoxy(x, START_Y + 1);
    std::cout << " �� �� �� ��";
    gotoxy(x, START_Y + 2);
    std::cout << " ��       ��";

    while (true) {
        KeyValue key = keyControl();
        moveCursor(x, y, key, START_Y, START_Y + 2);
        if (key == KeyValue::SUBMIT) {
            return y - START_Y;
        }
    }

}

// �ε� ȭ��
void Game::loading(int q, int p) {
    int x = 39, y = 13;
    system("cls");
    gotoxy(x, y);
    for (int i = 0; i <= q; i++)
        std::cout << "��";
    for (int i = 0; i <= p; i++)
        std::cout << "��";
    gotoxy(x, y + 2);
    std::cout << "\t       loading...";
    Sleep(100);
    system("cls");
}

// ���� ����
void Game::run() {
    while (true) {
        showTitle();
        int menuCode = showMenu();
        if (menuCode == 0) {    // ���� ����
            for (int i = 0; i < 10; i++)
                loading(i, 10 - i);

            resetLevel();
            while (player.lives > 0) {
                gameMap.drawMap(4, 3);
                drawScore();
                drawPlayer();
                drawGhosts();
                updateGhosts();
                handleGhostCollision();
            }
        }
        else if (menuCode == 1) {   // ���� ����
            showInfo(); 
        }
        else if (menuCode == 2) {   // ����
            return; 
        }
        system("cls");
    }
}

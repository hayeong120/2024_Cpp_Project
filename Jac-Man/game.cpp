#include "game.h"

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

// ������
Game::Game() : playerX(20), playerY(21), score(0), playerState({ 0, false, false }) {
    init();
}

// �÷��̾� �׸���
void Game::drawPlayer() const {
    gotoxy(playerX * 2 + 4, playerY + 3); // ���� ��ǥ�� ���� ��ġ ��ȯ
    std::cout << "��"; // �÷��̾� ĳ����
}

// Ư�� ��ġ�� ������ ����
void Game::clearItem(int x, int y) {
    // �� �����Ϳ��� ������ ����
    map.setTile(x, y, 0);

    // �ܼ� ȭ�鿡���� �ش� ��ġ�� �� �������� ������Ʈ
    gotoxy(x * 2 + 4, y + 3);
    std::cout << "  ";
}

// Ư�� ��ġ�� ������ Ÿ�� ��ȯ
int Game::getItem(int x, int y) {
    return map.getTile(x, y);
}

// ������ ó��
void Game::handleItem(int x, int y) {
    int itemType = getItem(x, y);
    switch (itemType) {
    case 2: // ���� ������
        playerState.coin++;       // coin ����
        score = playerState.coin; // score ����
        clearItem(x, y);
        drawScore();
        break;

    case 3: // �Ŀ� ������
        playerState.power = true;
        clearItem(x, y);
        drawScore();
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
    // ��Ż�� �ִ� ��ġ�� ã�Ƽ� �ݴ��� ��Ż�� �̵�
    for (int row = 0; row < map.getRows(); ++row) {
        for (int col = 0; col < map.getCols(); ++col) {
            if (map.getTile(col, row) == 4) {  // ��Ż�� ã����
                // ��Ż ��ġ�� ���� ��ġ�� �ٸ��� �ݴ��� ��Ż�� �̵�
                if (row != playerY || col != playerX) {
                    playerX = col;  // �ݴ��� ��Ż�� X ��ǥ
                    playerY = row;  // �ݴ��� ��Ż�� Y ��ǥ
                    drawPlayer();    // ���ο� ��ġ�� �÷��̾� ǥ��
                    return;          // ��Ż�� �̵������� �Լ� ����
                }
            }
        }
    }
}

// �÷��̾� �̵� ������Ʈ
void Game::updatePlayerPosition(KeyValue key) {
    int nextX = playerX;
    int nextY = playerY;

    switch (key) {
    case KeyValue::UP:    nextY--; break;
    case KeyValue::DOWN:  nextY++; break;
    case KeyValue::LEFT:  nextX--; break;
    case KeyValue::RIGHT: nextX++; break;
    default: return;
    }

    // �̵� ���� ���� Ȯ��
    if (!map.isWall(nextX, nextY)) {
        // ���� ��ġ �����
        gotoxy(playerX * 2 + 4, playerY + 3);
        std::cout << "  ";

        // ��ġ ������Ʈ
        playerX = nextX;
        playerY = nextY;

        // ������ ó��
        handleItem(playerX, playerY);

        // ���ο� ��ġ�� �÷��̾� �׸���
        drawPlayer();

        // ���� ���
        drawScore();
    }
}

void Game::drawScore() const {
    gotoxy(2, 1); // ���ھ� ��ġ
    std::cout << "Score: " << playerState.coin;
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
                loading(i, 10-i);
            gameMap.drawMap();
            drawScore();
            drawPlayer();

            while (true) {
                KeyValue key = keyControl();
                if (key == KeyValue::SUBMIT) break; // ���� ���� �߰�
                updatePlayerPosition(key);
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

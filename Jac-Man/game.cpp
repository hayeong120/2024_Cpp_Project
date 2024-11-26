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
Game::Game() {
    init();
}

// �ܼ� �ʱ�ȭ
void Game::init() const {
    system("mode con cols = 100 lines = 30 | title Jac-Man");
}

// Ÿ��Ʋ ���
void Game::titleDraw() const {
    std::cout << "\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t#####   #    ####       #   #   #   #   # \n";
    std::cout << "\t\t\t\t  #    # #  #           ## ##  # #  ##  # \n";
    std::cout << "\t\t\t\t  #   ##### #     ##### # # # ##### # # # \n";
    std::cout << "\t\t\t\t# #   #   # #           #   # #   # #  ## \n";
    std::cout << "\t\t\t\t #    #   #  ####       #   # #   # #   # \n";
}

// ���� ���� ���
void Game::infoDraw() const {
    system("cls");
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t\t[���۹�]\n\n";
    std::cout << "\t\t\t\t\t�̵� : ����Ű �̿�\n";
    std::cout << "\t\t\t\t\t���� : �����̽��� �Ǵ� ����\n\n";
    while (true) {
        if (keyControl() == KeyValue::SUBMIT) {
            break;
        }
    }
}

// �޴� ��� �� �Է�
int Game::menuDraw() const {
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

// �� ���̵� ����
int  Game::maplistDraw() const {
    int x = 48, y = MAP_START_Y;

    system("cls");
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t      [�� ����]\n\n";

    gotoxy(x - 2, y);
    std::cout << "> ";
    gotoxy(x, MAP_START_Y);
    std::cout << "��  ��";
    gotoxy(x, MAP_START_Y + 1);
    std::cout << "�����";
    gotoxy(x, MAP_START_Y + 2);
    std::cout << "��  ��";

    while (true) {
        KeyValue key = keyControl();
        moveCursor(x, y, key, MAP_START_Y, MAP_START_Y + 2);
        if (key == KeyValue::SUBMIT) {
            return y - MAP_START_Y;
        }
    }

}

// ���� ����
void Game::run() {
    while (true) {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {    // ���� ����
            int n = maplistDraw();

            if (n == 0) {   // ����
                std::cout << "���̵� ������ �����ϼ̽��ϴ�.";
                Sleep(1000);
            } else if (n == 1) {  // �����
                std::cout << "���̵� ������� �����ϼ̽��ϴ�.";
                Sleep(1000);
            }
        }
        else if (menuCode == 1) {   // ���� ����
            infoDraw(); 
        }
        else if (menuCode == 2) {   // ����
            return; 
        }
        system("cls");
    }
}

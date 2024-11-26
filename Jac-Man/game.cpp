#include "game.h"

// �ܼ� Ŀ�� ��ġ �̵�
void Game::gotoxy(int x, int y) const {

    // Ŀ�� ����ó��
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

    // Ŀ�� ��ġ ����
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
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
        switch (key) {
            case 32: case 13: return KeyValue::SUBMIT; // �����̽��� �Ǵ� ����
        }
    }
    return KeyValue::NONE;
}

// ������
Game::Game() {
    init();
}

// �ܼ� �ʱ�ȭ
void Game::init() const {
    system("title Jac-Man");
}

// Ÿ��Ʋ ���
void Game::titleDraw() const {
    std::cout << "\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t#####   #    ####       #   #   #   #   # \n";
    std::cout << "\t\t\t\t\t  #    # #  #           ## ##  # #  ##  # \n";
    std::cout << "\t\t\t\t\t  #   ##### #     ##### # # # ##### # # # \n";
    std::cout << "\t\t\t\t\t# #   #   # #           #   # #   # #  ## \n";
    std::cout << "\t\t\t\t\t #    #   #  ####       #   # #   # #   # \n";
}

// ���� ���� ���
void Game::infoDraw() const {
    system("cls");
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t\t\t[���۹�]\n\n";
    std::cout << "\t\t\t\t\t\t�̵� : ����Ű �̿�\n";
    std::cout << "\t\t\t\t\t\t���� : �����̽��� �Ǵ� ����\n\n";
    while (true) {
        if (keyControl() == KeyValue::SUBMIT) {
            break;
        }
    }
}

// �޴� ��� �� �Է�
int Game::menuDraw() const {
    int x = 55, y = START_Y;

    // �޴� ǥ��
    gotoxy(x - 2, y);
    std::cout << "> ";
    gotoxy(x, START_Y);
    std::cout << "�� �� �� ��";
    gotoxy(x, START_Y + 1);
    std::cout << "�� �� �� ��";
    gotoxy(x, START_Y + 2);
    std::cout << "��       ��";

    while (true) {
        KeyValue key = keyControl();
        switch (key) {
        case KeyValue::UP:
            if (y > START_Y) {
                gotoxy(x - 2, y);
                std::cout << " ";
                gotoxy(x - 2, --y);
                std::cout << ">";
            }
            break;
        case KeyValue::DOWN:
            if (y < START_Y+2) {
                gotoxy(x - 2, y);
                std::cout << " ";
                gotoxy(x - 2, ++y);
                std::cout << ">";
            }
            break;
        case KeyValue::SUBMIT:
            return y - START_Y;
        default:
            break;
        }
    }
}

// ���� ����
void Game::run() {
    while (true) {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {
            // ���� ����
        }
        else if (menuCode == 1) {
            infoDraw(); // ���� ����
        }
        else if (menuCode == 2) {
            return; // ����
        }
        system("cls");
    }
}

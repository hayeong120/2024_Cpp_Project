#include "game.h"

// 콘솔 커서 위치 이동
void Game::gotoxy(int x, int y) const {

    // 커서 숨김처리
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

    // 커서 위치 설정
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

// 키 입력 처리
KeyValue Game::keyControl() const {
    int key = _getch();

    if (key == 0 || key == 224) { // 특수 키 확인
        key = _getch();
        switch (key) {
            case 72: return KeyValue::UP;
            case 75: return KeyValue::LEFT;
            case 77: return KeyValue::RIGHT;
            case 80: return KeyValue::DOWN;
        }
    }
    else { // 일반 키
        switch (key) {
            case 32: case 13: return KeyValue::SUBMIT; // 스페이스바 또는 엔터
        }
    }
    return KeyValue::NONE;
}

// 생성자
Game::Game() {
    init();
}

// 콘솔 초기화
void Game::init() const {
    system("title Jac-Man");
}

// 타이틀 출력
void Game::titleDraw() const {
    std::cout << "\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t#####   #    ####       #   #   #   #   # \n";
    std::cout << "\t\t\t\t\t  #    # #  #           ## ##  # #  ##  # \n";
    std::cout << "\t\t\t\t\t  #   ##### #     ##### # # # ##### # # # \n";
    std::cout << "\t\t\t\t\t# #   #   # #           #   # #   # #  ## \n";
    std::cout << "\t\t\t\t\t #    #   #  ####       #   # #   # #   # \n";
}

// 게임 정보 출력
void Game::infoDraw() const {
    system("cls");
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t\t\t[조작법]\n\n";
    std::cout << "\t\t\t\t\t\t이동 : 방향키 이용\n";
    std::cout << "\t\t\t\t\t\t선택 : 스페이스바 또는 엔터\n\n";
    while (true) {
        if (keyControl() == KeyValue::SUBMIT) {
            break;
        }
    }
}

// 메뉴 출력 및 입력
int Game::menuDraw() const {
    int x = 55, y = START_Y;

    // 메뉴 표시
    gotoxy(x - 2, y);
    std::cout << "> ";
    gotoxy(x, START_Y);
    std::cout << "게 임 시 작";
    gotoxy(x, START_Y + 1);
    std::cout << "게 임 정 보";
    gotoxy(x, START_Y + 2);
    std::cout << "종       료";

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

// 게임 실행
void Game::run() {
    while (true) {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {
            // 게임 시작
        }
        else if (menuCode == 1) {
            infoDraw(); // 게임 정보
        }
        else if (menuCode == 2) {
            return; // 종료
        }
        system("cls");
    }
}

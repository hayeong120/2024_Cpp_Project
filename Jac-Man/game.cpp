#include "game.h"

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
        switch (key) {  // 스페이스바 또는 엔터바
            case 32: case 13: return KeyValue::SUBMIT; 
        }
    }
    return KeyValue::NONE;
}

// 커서 이동 처리
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

// 생성자
Game::Game() {
    init();
}

// 콘솔 초기화
void Game::init() const {
    system("mode con cols = 100 lines = 30 | title Jac-Man");
}

// 타이틀 출력
void Game::titleDraw() const {
    std::cout << "\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t#####   #    ####       #   #   #   #   # \n";
    std::cout << "\t\t\t\t  #    # #  #           ## ##  # #  ##  # \n";
    std::cout << "\t\t\t\t  #   ##### #     ##### # # # ##### # # # \n";
    std::cout << "\t\t\t\t# #   #   # #           #   # #   # #  ## \n";
    std::cout << "\t\t\t\t #    #   #  ####       #   # #   # #   # \n";
}

// 게임 정보 출력
void Game::infoDraw() const {
    system("cls");
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t\t[조작법]\n\n";
    std::cout << "\t\t\t\t\t이동 : 방향키 이용\n";
    std::cout << "\t\t\t\t\t선택 : 스페이스바 또는 엔터\n\n";
    while (true) {
        if (keyControl() == KeyValue::SUBMIT) {
            break;
        }
    }
}

// 메뉴 출력 및 입력
int Game::menuDraw() const {
    int x = 45, y = START_Y;

    // 메뉴 표시
    gotoxy(x - 2, y);
    std::cout << ">";
    gotoxy(x, START_Y);
    std::cout << " 게 임 시 작";
    gotoxy(x, START_Y + 1);
    std::cout << " 게 임 정 보";
    gotoxy(x, START_Y + 2);
    std::cout << " 종       료";

    while (true) {
        KeyValue key = keyControl();
        moveCursor(x, y, key, START_Y, START_Y + 2);
        if (key == KeyValue::SUBMIT) {
            return y - START_Y;
        }
    }

}

// 맵 난이도 선택
int  Game::maplistDraw() const {
    int x = 48, y = MAP_START_Y;

    system("cls");
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t      [맵 선택]\n\n";

    gotoxy(x - 2, y);
    std::cout << "> ";
    gotoxy(x, MAP_START_Y);
    std::cout << "쉬  움";
    gotoxy(x, MAP_START_Y + 1);
    std::cout << "어려움";
    gotoxy(x, MAP_START_Y + 2);
    std::cout << "뒤  로";

    while (true) {
        KeyValue key = keyControl();
        moveCursor(x, y, key, MAP_START_Y, MAP_START_Y + 2);
        if (key == KeyValue::SUBMIT) {
            return y - MAP_START_Y;
        }
    }

}

// 게임 실행
void Game::run() {
    while (true) {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {    // 게임 시작
            int n = maplistDraw();

            if (n == 0) {   // 쉬움
                std::cout << "난이도 쉬움을 선택하셨습니다.";
                Sleep(1000);
            } else if (n == 1) {  // 어려움
                std::cout << "난이도 어려움을 선택하셨습니다.";
                Sleep(1000);
            }
        }
        else if (menuCode == 1) {   // 게임 정보
            infoDraw(); 
        }
        else if (menuCode == 2) {   // 종료
            return; 
        }
        system("cls");
    }
}

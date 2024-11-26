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
void Game::showTitle() const {
    std::cout << "\n\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t       #####   #    ####       #   #   #   #   # \n";
    std::cout << "\t\t\t         #    # #  #           ## ##  # #  ##  # \n";
    std::cout << "\t\t\t         #   ##### #     ##### # # # ##### # # # \n";
    std::cout << "\t\t\t       # #   #   # #           #   # #   # #  ## \n";
    std::cout << "\t\t\t        #    #   #  ####       #   # #   # #   # \n";
}

// 게임 정보 출력
void Game::showInfo() const {
    system("cls");
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "\t\t\t\t\t       [조작법]\n\n";
    std::cout << "\t\t\t\t         이동 : 방향키 이용\n";
    std::cout << "\t\t\t\t     선택 : 스페이스바 또는 엔터";
    while (true) {
        if (keyControl() == KeyValue::SUBMIT) {
            break;
        }
    }
}

// 메뉴 출력 및 입력
int Game::showMenu() const {
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

// 로딩 화면
void Game::loading(int q, int p) {
    int x = 39, y = 13;
    system("cls");
    gotoxy(x, y);
    for (int i = 0; i <= q; i++)
        std::cout << "■";
    for (int i = 0; i <= p; i++)
        std::cout << "□";
    gotoxy(x, y + 2);
    std::cout << "\t       loading...";
    Sleep(100);
    system("cls");
}

// 게임 실행
void Game::run() {
    while (true) {
        showTitle();
        int menuCode = showMenu();
        if (menuCode == 0) {    // 게임 시작
            for (int i = 0; i < 10; i++)
                loading(i, 10-i);
            gameMap.drawMap();
            Sleep(5000);
        }
        else if (menuCode == 1) {   // 게임 정보
            showInfo(); 
        }
        else if (menuCode == 2) {   // 종료
            return; 
        }
        system("cls");
    }
}

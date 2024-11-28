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
Game::Game() : playerX(20), playerY(21), score(0), playerState({ 0, false, false }) {
    init();
}

// 플레이어 그리기
void Game::drawPlayer() const {
    gotoxy(playerX * 2 + 4, playerY + 3); // 맵의 좌표에 맞춰 위치 변환
    std::cout << "▲"; // 플레이어 캐릭터
}

// 특정 위치의 아이템 제거
void Game::clearItem(int x, int y) {
    // 맵 데이터에서 아이템 제거
    map.setTile(x, y, 0);

    // 콘솔 화면에서도 해당 위치를 빈 공간으로 업데이트
    gotoxy(x * 2 + 4, y + 3);
    std::cout << "  ";
}

// 특정 위치의 아이템 타입 반환
int Game::getItem(int x, int y) {
    return map.getTile(x, y);
}

// 아이템 처리
void Game::handleItem(int x, int y) {
    int itemType = getItem(x, y);
    switch (itemType) {
    case 2: // 점수 아이템
        playerState.coin++;       // coin 증가
        score = playerState.coin; // score 갱신
        clearItem(x, y);
        drawScore();
        break;

    case 3: // 파워 아이템
        playerState.power = true;
        clearItem(x, y);
        drawScore();
        break;

    case 4: // 포탈
        teleport(); // 포탈 처리
        break;

    default:
        break;
    }
}

// 포탈 처리
void Game::teleport() {
    // 포탈이 있는 위치를 찾아서 반대편 포탈로 이동
    for (int row = 0; row < map.getRows(); ++row) {
        for (int col = 0; col < map.getCols(); ++col) {
            if (map.getTile(col, row) == 4) {  // 포탈을 찾으면
                // 포탈 위치가 현재 위치와 다르면 반대편 포탈로 이동
                if (row != playerY || col != playerX) {
                    playerX = col;  // 반대편 포탈의 X 좌표
                    playerY = row;  // 반대편 포탈의 Y 좌표
                    drawPlayer();    // 새로운 위치에 플레이어 표시
                    return;          // 포탈로 이동했으면 함수 종료
                }
            }
        }
    }
}

// 플레이어 이동 업데이트
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

    // 이동 가능 여부 확인
    if (!map.isWall(nextX, nextY)) {
        // 이전 위치 지우기
        gotoxy(playerX * 2 + 4, playerY + 3);
        std::cout << "  ";

        // 위치 업데이트
        playerX = nextX;
        playerY = nextY;

        // 아이템 처리
        handleItem(playerX, playerY);

        // 새로운 위치에 플레이어 그리기
        drawPlayer();

        // 점수 출력
        drawScore();
    }
}

void Game::drawScore() const {
    gotoxy(2, 1); // 스코어 위치
    std::cout << "Score: " << playerState.coin;
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
            drawScore();
            drawPlayer();

            while (true) {
                KeyValue key = keyControl();
                if (key == KeyValue::SUBMIT) break; // 종료 조건 추가
                updatePlayerPosition(key);
            }
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

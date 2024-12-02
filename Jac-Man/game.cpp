#include "game.h"
#include "ghost.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;

// 생성자
Game::Game() : player(20, 21, UP), timer(0), powerTimer(0), level(1) {
    ghosts.push_back(new Blinky(22, 7));
    //ghosts.push_back(new Pinky(22, 6));
    //ghosts.push_back(new Inky(21, 6));
    //ghosts.push_back(new Clyde(23, 6));
}

// 소멸자
Game::~Game() {
    for (Ghost* ghost : ghosts) {
        delete ghost; // 유령 동적 메모리 해제
    }
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

// 초기화
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

// 타이머 측정
void Game::updateTimers() {
    timer++;
    if (powerTimer > 0) powerTimer--;

    if (powerTimer == 0 && player.power) {
        player.power = false; // 파워 모드 종료
        for (Ghost* ghost : ghosts) {
            if (ghost->mode == Frightened) {
                ghost->mode = Scatter;
            }
        }
    }
}

// 모드 전환
void Game::updateGhostModes() {
    for (Ghost* ghost : ghosts) {
        ghost->updateMode(timer);
    }
}

// 플레이어 그리기
void Game::drawPlayer() const {
    gotoxy(player.x * 2 + 4, player.y + 3); // 맵의 좌표에 맞춰 위치 변환
    std::cout << "▲"; // 플레이어 캐릭터
}

// 플레이어 이동 업데이트
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

    // 이동 가능 여부 확인
    if (!gameMap.isWall(nextX, nextY)) {
        // 이전 위치 지우기
        gotoxy(player.x * 2 + 4, player.y + 3);
        std::cout << "  ";

        // 위치 업데이트
        player.x = nextX;
        player.y = nextY;

        // 아이템 처리
        handleItem(player.x, player.y);

        // 새로운 위치에 플레이어 그리기
        drawPlayer();

        // 점수 출력
        drawScore();
    }
}

// 아이템 처리
void Game::handleItem(int x, int y) {
    if (x < 0 || y < 0 || x >= gameMap.getCols() || y >= gameMap.getRows()) return;

    int itemType = gameMap.getTile(x, y);
    switch (itemType) {
    case 2: // 점수 아이템
        player.coin+=10;
        gameMap.setTile(x, y, 0);
        break;

    case 3: // 파워 아이템
        player.power = true;
        gameMap.setTile(x, y, 0);
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
    for (int row = 0; row < gameMap.getRows(); ++row) {
        for (int col = 0; col < gameMap.getCols(); ++col) {
            if (gameMap.getTile(col, row) == 4) {  // 포탈을 찾으면
                // 포탈 위치가 현재 위치와 다르면 반대편 포탈로 이동
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

// 유령
// 유령 그리기
void Game::drawGhosts() const {
    for (const Ghost* ghost : ghosts) {
        gotoxy(ghost->x * 2 + 4, ghost->y + 3);
        std::cout << "▼"; // 유령 캐릭터
    }
}

// 유령 이동 업데이트
void Game::updateGhosts() {
    for (Ghost* ghost : ghosts) {
        ghost->move(player);
    }
    drawGhosts();
}

// 유령 충돌 처리
void Game::handleGhostCollision() {
    for (Ghost* ghost : ghosts) {
        if (ghost->x == player.x && ghost->y == player.y) {
            if (player.power) {
                // 유령 제거
                ghost->x = -1;
                ghost->y = -1;
            }
            else {
                player.lives--;
                if (player.lives <= 0) {
                    std::cout << "Game Over!\n";
                    Sleep(2000);
                    exit(0); // 게임 종료
                }

            }
        }
    }
}

// 점수 처리
void Game::drawScore() const {
    gotoxy(2, 1); // 스코어 위치
    std::cout << "Score: " << player.coin << "\t" << "Lives: ";
    for (int i = 0; i < player.lives; i++)
        std::cout << "♥ ";
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
        else if (menuCode == 1) {   // 게임 정보
            showInfo(); 
        }
        else if (menuCode == 2) {   // 종료
            return; 
        }
        system("cls");
    }
}

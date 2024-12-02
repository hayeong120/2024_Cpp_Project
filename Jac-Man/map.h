#pragma once

#include <vector>
#include <iostream>
#include "util.h"

class Map {
private:
    static constexpr int ROWS = 24; // 맵의 세로 크기
    static constexpr int COLS = 46; // 맵의 가로 크기
    int map[ROWS][COLS];            // 2차원 배열로 맵 저장

public:
    Map();
    void drawMap(int x, int y) const;   // 맵 출력 함수
    bool isWall(int x, int y) const;    // 특정 좌표가 벽인지 확인

    void setTile(int x, int y, int value); // 특정 위치의 타일 값을 설정
    int getTile(int x, int y) const;       // 특정 위치의 타일 값을 가져옴

    int getCols() const { return COLS; }
    int getRows() const { return ROWS; }

    bool isWithinBounds(int x, int y) const;    // 경계 검사 함수
};

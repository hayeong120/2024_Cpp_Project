#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include "util.h"

class Map {
private:
    static const int ROWS = 24; // 맵의 세로 크기
    static const int COLS = 46; // 맵의 가로 크기
    int map[ROWS][COLS];        // 2차원 배열로 맵 저장

public:
    Map();
    void drawMap() const;       // 맵 출력 함수
    bool isWall(int x, int y) const; // 특정 좌표가 벽인지 확인
};

#endif // MAP_H
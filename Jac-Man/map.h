#pragma once

#include <vector>
#include <iostream>
#include "util.h"

class Map {
private:
    static constexpr int ROWS = 24; // ���� ���� ũ��
    static constexpr int COLS = 46; // ���� ���� ũ��
    int map[ROWS][COLS];            // 2���� �迭�� �� ����

public:
    Map();
    void drawMap(int x, int y) const;   // �� ��� �Լ�
    bool isWall(int x, int y) const;    // Ư�� ��ǥ�� ������ Ȯ��

    void setTile(int x, int y, int value); // Ư�� ��ġ�� Ÿ�� ���� ����
    int getTile(int x, int y) const;       // Ư�� ��ġ�� Ÿ�� ���� ������

    int getCols() const { return COLS; }
    int getRows() const { return ROWS; }

    bool isWithinBounds(int x, int y) const;    // ��� �˻� �Լ�
};

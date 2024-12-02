#ifndef UTIL_H
#define UTIL_H

enum ConsoleColor {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Yellow = 6,
    White = 7,
    Gray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    LightYellow = 14,
    BrightWhite = 15
};

void hideCursor();				// �ܼ� Ŀ���� ����
void gotoxy(int x, int y);		// �ܼ� Ŀ���� Ư�� ��ġ�� �̵�
void setTextColor(ConsoleColor color);	// �ܼ� �ؽ�Ʈ ���� ����

#endif // UTIL_H

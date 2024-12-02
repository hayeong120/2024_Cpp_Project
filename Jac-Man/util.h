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

void hideCursor();				// 콘솔 커서를 숨김
void gotoxy(int x, int y);		// 콘솔 커서를 특정 위치로 이동
void setTextColor(ConsoleColor color);	// 콘솔 텍스트 색상 설정

#endif // UTIL_H

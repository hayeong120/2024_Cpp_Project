#include <stdio.h>
#include <Windows.h>

// 함수 선언
void init();
void titleDraw();
void menuDraw();
void gotoxy(int, int);

int main() {
	//init();
	titleDraw();
	menuDraw();

	return 0;
}

// 함수 구현
void init() {
	system("mode con cols=56 lines=20 | title Jac-Man");
}

void titleDraw() {
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t#####   #    ####       #   #   #   #   # \n");
	printf("\t\t\t\t\t  #    # #  #           ## ##  # #  ##  # \n");
	printf("\t\t\t\t\t  #   ##### #     ##### # # # ##### # # # \n");
	printf("\t\t\t\t\t# #   #   # #           #   # #   # #  ## \n");
	printf("\t\t\t\t\t #    #   #  ####       #   # #   # #   # \n");
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

void menuDraw() {
	gotoxy(55 - 2, 12);	// -2는 >를 출력하기 위해
	printf("> 게 임 시 작");
	gotoxy(55, 13);
	printf("게 임 정 보");
	gotoxy(55, 14);
	printf("종       료");
}
#include <stdio.h>
#include <Windows.h>

// �Լ� ����
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

// �Լ� ����
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
	gotoxy(55 - 2, 12);	// -2�� >�� ����ϱ� ����
	printf("> �� �� �� ��");
	gotoxy(55, 13);
	printf("�� �� �� ��");
	gotoxy(55, 14);
	printf("��       ��");
}
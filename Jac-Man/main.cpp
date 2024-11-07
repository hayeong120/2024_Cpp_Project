#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

// Ű���� ��
enum keyValue { UP, DOWN, LEFT, RIGHT, SUBMIT };

const int START_Y = 16;

// �Լ� ����
void init();
void titleDraw();
int menuDraw();
void gotoxy(int, int);
keyValue keyControl();
void infoDraw();

int main() {
	//init();
	while (true) {
		titleDraw();
		int menuCode = menuDraw();
		if (menuCode == 0) {
			// ���ӽ���
		} else if (menuCode == 1) {
			infoDraw();		// ��������
		} else if (menuCode == 2) {
			return 0;	// ����
		}
		system("cls");
	}

	return 0;
}

// �Լ� ����
void infoDraw() {
	system("cls");
	cout << "\n\n";
	cout << "\t[���۹�]\n\n";
	cout << "�̵� : ����� �̿�\n";
	cout << "���� : �����̽��� �Ǵ� ����\n\n";

	while (true) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

keyValue keyControl() {
	int key = _getch();

	// ����Ű�� ���� Ư�� Ű�� �� �ܰ��� �Է����� ó����
	if (key == 0 || key == 224) {	// Ư��Ű Ȯ��
		key = _getch();		// ���� Ű ��(����Ű ��) �б�
		switch (key) {
			case 72:
				return UP;    // ���� ȭ��ǥ
			case 75:
				return LEFT;  // ���� ȭ��ǥ
			case 77:
				return RIGHT; // ������ ȭ��ǥ
			case 80:
				return DOWN;  // �Ʒ��� ȭ��ǥ
		}
	} else {	// �Ϲ� Ű��� 
		switch (key) {
			case 32: case 13:
				return SUBMIT;  // �����̽��� �Ǵ� ���͸� ������ ����
		}
	}
	//return NONE; // ����Ű�� �ƴ� ���

}

void init() {
	system("mode con cols=56 lines=20 | title Jac-Man");
}

void titleDraw() {
	cout << "\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t#####   #    ####       #   #   #   #   # \n";
	cout << "\t\t\t\t\t  #    # #  #           ## ##  # #  ##  # \n";
	cout << "\t\t\t\t\t  #   ##### #     ##### # # # ##### # # # \n";
	cout << "\t\t\t\t\t# #   #   # #           #   # #   # #  ## \n";
	cout << "\t\t\t\t\t #    #   #  ####       #   # #   # #   # \n";
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int menuDraw() {
	int x = 55, y = START_Y;

	// �ʱ� �޴� ǥ��
	gotoxy(x - 2, y);		// -2�� >�� ����ϱ� ����
	std::cout << "> ";
	gotoxy(x, START_Y);
	std::cout << "�� �� �� ��";
	gotoxy(x, START_Y + 1);
	std::cout << "�� �� �� ��";
	gotoxy(x, START_Y + 2);
	std::cout << "��       ��";

	while (true) {	// ���ѹݺ�
		keyValue key = keyControl();
		switch (key) {
			case UP: {
				if (y > START_Y) {
					gotoxy(x - 2, y);
					cout << " ";
					gotoxy(x - 2, --y);
					cout << ">";
				}
				break;
			}
			case DOWN: {
				if (y < 18) {
					gotoxy(x - 2, y);
					cout << " ";
					gotoxy(x - 2, ++y);
					cout << ">";
				}
				break;
			}
				 
			case SUBMIT: {
				return y - START_Y;
				// y���� ������ġ ����ŭ ���� ���� ��ġ�� �ɼ��� �� �� �ִ�. 
			}
		}
	}
}
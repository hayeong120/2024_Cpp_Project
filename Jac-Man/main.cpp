#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

// 키보드 값
enum keyValue { UP, DOWN, LEFT, RIGHT, SUBMIT };

const int START_Y = 16;

// 함수 선언
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
			// 게임시작
		} else if (menuCode == 1) {
			infoDraw();		// 게임정보
		} else if (menuCode == 2) {
			return 0;	// 종료
		}
		system("cls");
	}

	return 0;
}

// 함수 구현
void infoDraw() {
	system("cls");
	cout << "\n\n";
	cout << "\t[조작법]\n\n";
	cout << "이동 : 방향기 이용\n";
	cout << "선택 : 스페이스바 또는 엔터\n\n";

	while (true) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

keyValue keyControl() {
	int key = _getch();

	// 방향키와 같은 특수 키는 두 단계의 입력으로 처리됨
	if (key == 0 || key == 224) {	// 특수키 확인
		key = _getch();		// 실제 키 값(방향키 값) 읽기
		switch (key) {
			case 72:
				return UP;    // 위쪽 화살표
			case 75:
				return LEFT;  // 왼쪽 화살표
			case 77:
				return RIGHT; // 오른쪽 화살표
			case 80:
				return DOWN;  // 아래쪽 화살표
		}
	} else {	// 일반 키라면 
		switch (key) {
			case 32: case 13:
				return SUBMIT;  // 스페이스바 또는 엔터를 누르면 선택
		}
	}
	//return NONE; // 방향키가 아닌 경우

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

	// 초기 메뉴 표시
	gotoxy(x - 2, y);		// -2는 >를 출력하기 위해
	std::cout << "> ";
	gotoxy(x, START_Y);
	std::cout << "게 임 시 작";
	gotoxy(x, START_Y + 1);
	std::cout << "게 임 정 보";
	gotoxy(x, START_Y + 2);
	std::cout << "종       료";

	while (true) {	// 무한반복
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
				// y에서 시작위치 값만큼 빼면 지금 위치한 옵션을 알 수 있다. 
			}
		}
	}
}
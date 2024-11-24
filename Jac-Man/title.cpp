#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

const int ALPHA_CNT = 26;
const int ALPHA_SIZE = 5;
const int BUFFER_SIZE = 1 << 10;

bool alphaBoard[ALPHA_CNT][ALPHA_SIZE][ALPHA_SIZE] = {
	// A
	{
		{false, false, true, false, false},
		{false, true, false, true, false},
		{true, true, true, true, true},
		{true, false, false, false, true},
		{true, false, false, false, true}
	},
	// B
	{
		{true, true, true, true, false},
		{true, false, false, false, true},
		{true, true, true, true, false},
		{true, false, false, false, true},
		{true, true, true, true, false}
	},
	// C
	{
		{false, true, true, true, true},
		{true, false, false, false, false},
		{true, false, false, false, false},
		{true, false, false, false, false},
		{false, true, true, true, true}
	},
	// D
	{
		{true, true, true, true, false},
		{true, false, false, false, true},
		{true, false, false, false, true},
		{true, false, false, false, true},
		{true, true, true, true, false}
	},
	// E
	{
		{true, true, true, true, true},
		{true, false, false, false, false},
		{true, true, true, true, false},
		{true, false, false, false, false},
		{true, true, true, true, true}
	},
	// F
	{
		{true, true, true, true, true},
		{true, false, false, false, false},
		{true, true, true, true, false},
		{true, false, false, false, false},
		{true, false, false, false, false}
	},
	// G
	{
		{false, true, true, true, false},
		{true, false, false, false, false},
		{true, false, true, true, true},
		{true, false, false, true, false},
		{false, true, true, true, false}
	},
	// H
	{
		{true, false, false, false, true},
		{true, false, false, false, true},
		{true, true, true, true, true},
		{true, false, false, false, true},
		{true, false, false, false, true}
	},
	// I
	{
		{true, true, true, true, true},
		{false, false, true, false, false},
		{false, false, true, false, false},
		{false, false, true, false, false},
		{true, true, true, true, true}
	},
	// J
	{
		{true, true, true, true, true},
		{false, false, true, false, false},
		{false, false, true, false, false},
		{true, false, true, false, false},
		{false, true, false, false, false}
	},
	// K
	{
		{true, false, false, false, true},
		{true, false, false, true, false},
		{true, true, true, false, false},
		{true, false, false, true, false},
		{true, false, false, false, true}
	},
	// L
	{
		{true, false, false, false, false},
		{true, false, false, false, false},
		{true, false, false, false, false},
		{true, false, false, false, false},
		{true, true, true, true, true}
	},
	// M
	{
		{true, false, false, false, true},
		{true, true, false, true, true},
		{true, false, true, false, true},
		{true, false, true, false, true},
		{true, false, false, false, true}
	},
	// N
	{
		{true, false, false, false, true},
		{true, true, false, false, true},
		{true, false, true, false, true},
		{true, false, false, true, true},
		{true, false, false, false, true}
	},
	// O
	{
		{false, true, true, true, false},
		{true, false, false, false, true},
		{true, false, false, false, true},
		{true, false, false, false, true},
		{false, true, true, true, false}
	},
	// P
	{
		{true, true, true, true, false},
		{true, false, false, false, true},
		{true, true, true, true, false},
		{true, false, false, false, false},
		{true, false, false, false, false}
	},
	// Q
	{
		{false, true, true, false, false},
		{true, false, false, true, false},
		{true, false, true, true, false},
		{true, false, false, true, false},
		{false, true, true, false, true}
	},
	// R
	{
		{true, true, true, true, false},
		{true, false, false, false, true},
		{true, true, true, true, false},
		{true, false, false, true, false},
		{true, false, false, false, true}
	},
	// S
	{
		{false, true, true, true, false},
		{true, false, false, false, false},
		{false, true, true, true, false},
		{false, false, false, false, true},
		{false, true, true, true, false}
	},
	// T
	{
		{true, true, true, true, true},
		{false, false, true, false, false},
		{false, false, true, false, false},
		{false, false, true, false, false},
		{false, false, true, false, false}
	},
	// U
	{
		{true, false, false, false, true},
		{true, false, false, false, true},
		{true, false, false, false, true},
		{true, false, false, false, true},
		{false, true, true, true, false}
	},
	// V
	{
		{true, false, false, false, true},
		{true, false, false, false, true},
		{true, false, false, false, true},
		{false, true, false, true, false},
		{false, false, true, false, false}
	},
	// W
	{
		{true, false, true, false, true},
		{true, false, true, false, true},
		{true, false, true, false, true},
		{false, true, false, true, false},
		{false, true, false, true, false}
	},
	// X
	{
		{true, false, false, false, true},
		{false, true, false, true, false},
		{false, false, true, false, false},
		{false, true, false, true, false},
		{true, false, false, false, true}
	},
	// Y
	{
		{true, false, false, false, true},
		{false, true, false, true, false},
		{false, false, true, false, false},
		{false, false, true, false, false},
		{false, false, true, false, false}
	},
	// Z
	{
		{true, true, true, true, true},
		{false, false, false, true, false},
		{false, false, true, false, false},
		{false, true, false, false, false},
		{true, true, true, true, true}
	}
};
bool alphaOutput[ALPHA_SIZE][BUFFER_SIZE];

// 문자열을 5X5 bool 배열로 분리하는 함수
void split(string& s, bool output[][BUFFER_SIZE])
{
	int len = s.length();
	for (int y = 0; y < ALPHA_SIZE; ++y) {
		for (int idx = 0; idx < len; ++idx) {
			int alphaOffset = s[idx] - 'A';              // [A...Z] -> [0...25]
			for (int x = 0; x < ALPHA_SIZE; ++x) {
				int xOffset = idx * ALPHA_SIZE + x;      // xOffset -> [ALPHA_SIZE*idx ... ALPHA_SIZE*idx + ALPHA_SIZE)

				output[y][xOffset] = alphaBoard[alphaOffset][y][x];
			}
		}
	}
}

// (분리결과, 문자열의 길이, 문자 간격, 표시할 문자)를 함수에 입력하면 출력
void print(bool output[][BUFFER_SIZE], int len, int spaceSize, char mark)
{
	for (int y = 0; y < ALPHA_SIZE; ++y) {
		for (int idx = 0; idx < len; ++idx) {
			for (int x = 0; x < ALPHA_SIZE; ++x) {
				int xOffset = idx * ALPHA_SIZE + x;      // xOffset -> [ALPHA_SIZE*idx ... ALPHA_SIZE*idx + ALPHA_SIZE)

				cout << (output[y][xOffset] ? mark : ' ');
			}

			for (int iter = 0; iter < spaceSize; ++iter) {
				cout << ' ';
			}
		}
		cout << '\n';
	}
}

// 커서 위치 이동 함수
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

void munuDraw() {
	gotoxy(1 -2, 12);
	printf("> 게 임 시 작 ");
	gotoxy(1, 13);
	printf("게 임 정 보 ");
	gotoxy(1, 14);
	printf("종 료");
}

int main()
{
	//system("mode con cols=56 lines=10 | title Jac-Man");

	printf("\n\n\n\n");
	string input = "JAC-MAN";
	split(input, alphaOutput);
	print(alphaOutput, input.length(), 1, '#');

	void menuDraw();

	return 0;
}
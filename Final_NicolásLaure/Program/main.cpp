#include "Game.h"

void main()
{
	Play();
}

void Initialize(GameData& gd)
{
	SetConsoleFontSize(gd.ConsoleFontSize);


	HWND console = GetConsoleWindow();
	ShowWindow(console, SW_SHOWMAXIMIZED);
	ShowScrollBar(GetConsoleWindow(), SB_BOTH, FALSE);

	CONSOLE_CURSOR_INFO CCI;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
	CCI.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
}
void SetConsoleFontSize(int size)
{
	static CONSOLE_FONT_INFOEX  cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(handle, 0, &cfi);
	cfi.FontWeight = 500;
	cfi.dwFontSize.X = size / 1.5f;
	cfi.dwFontSize.Y = size;
	cfi.FontFamily = FF_ROMAN;
	SetCurrentConsoleFontEx(handle, 0, &cfi);
}
void PrintUpperBar(GameData& gd)
{
	SetConsoleTextAttribute(gd.handle, 7);
	SetConsoleCursorPosition(gd.handle, { 0,0 });
	cout << " -HEALTH-" << endl << " ";
	SetConsoleTextAttribute(gd.handle, 4);
	for (int i = 0; i < gd.player.maxHealthPoints; i++)
	{
		if (gd.player.healthPoints == 2 && i == 2)
			SetConsoleTextAttribute(gd.handle, 8);
		else if (gd.player.healthPoints == 1 && i == 1)
			SetConsoleTextAttribute(gd.handle, 8);

		cout << "<3 ";
	}
}
void CleanUpperBar(GameData& gd)
{
	SetConsoleTextAttribute(gd.handle, 7);
	SetConsoleCursorPosition(gd.handle, { 0,0 });
	cout << "   -LIFE-" << endl << "                             ";
}
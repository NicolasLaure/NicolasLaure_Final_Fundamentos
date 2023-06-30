#include "Game.h"
void main()
{
	Play();
}

void Play()
{
	srand(0);
	ShowCursor(false);

	HWND console = GetConsoleWindow();

	/*RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);

	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1280, 720, TRUE);*/
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	ShowScrollBar(GetConsoleWindow(), SB_BOTH, FALSE);
	GameLoop();
}

void GameLoop()
{
	GameData gd{};

	do
	{
		gd.enteredNewScene = gd.scene != gd.prevScene;
		gd.prevScene = gd.scene;

		switch (gd.scene)
		{
		case Scenes::End:
			break;
		case Scenes::Menu:
			Menu(gd);
			break;
		case Scenes::Game:

			break;
		case Scenes::Credits:
			break;
		default:
			break;
		}

	} while (gd.scene != Scenes::End);
}

void Menu(GameData& gd)
{
	if (gd.enteredNewScene)
		MenuStart();

	MenuUpdate(gd);
	MenuDraw(gd);
}

void MenuStart()
{

}
void MenuUpdate(GameData& gd)
{
	if (_kbhit() && gd.isMenuFirstPhase)
		gd.isMenuFirstPhase = false;

}
void MenuDraw(GameData gd)
{
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	int width = csbi.srWindow.Right - csbi.srWindow.Left;
	int height = csbi.srWindow.Bottom - csbi.srWindow.Top;

	if (gd.isMenuFirstPhase)
	{
		int logoWidth = 74;
		int logoHeight = 30;
		COORD coordinates;
		coordinates.X = width / 2 - (logoWidth / 2);
		coordinates.Y = height / 2 - (logoHeight / 2);
		SetConsoleCursorPosition(handle, coordinates);
		cout << R"(
									 /@
                     __        __   /\/
                    /==\      /  \_/\/   
                  /======\    \/\__ \__
                /==/\  /\==\    /\_|__ \
             /==/    ||    \=\ / / / /_/
           /=/    /\ || /\   \=\/ /     
        /===/   /   \||/   \   \===\
      /===/   /_________________ \===\
   /====/   / |                /  \====\
 /====/   /   |  _________    /  \   \===\    THE LEGEND OF 
 /==/   /     | /   /  \ / / /  __________\_____      ______       ___
|===| /       |/   /____/ / /   \   _____ |\   /      \   _ \      \  \
 \==\             /\   / / /     | |  /= \| | |        | | \ \     / _ \
 \===\__    \    /  \ / / /   /  | | /===/  | |        | |  \ \   / / \ \
   \==\ \    \\ /____/   /_\ //  | |_____/| | |        | |   | | / /___\ \
   \===\ \   \\\\\\\/   /////// /|  _____ | | |        | |   | | |  ___  |
     \==\/     \\\\/ / //////   \| |/==/ \| | |        | |   | | | /   \ |
     \==\     _ \\/ / /////    _ | |==/     | |        | |  / /  | |   | |
       \==\  / \ / / ///      /|\| |_____/| | |_____/| | |_/ /   | |   | |
       \==\ /   / / /________/ |/_________|/_________|/_____/   /___\ /___\
         \==\  /               | /==/
         \=\  /________________|/=/    
           \==\     _____     /==/ 
          / \===\   \   /   /===/
         / / /\===\  \_/  /===/               Press Any Key
        / / /   \====\ /====/
       / / /      \===|===/
       |/_/         \===/
                      =
)";
	}
	else
	{
		int textWidth = 8;
		int textHeight = 3;
		COORD coordinates;
		coordinates.X = width / 2 - (textWidth / 2);
		coordinates.Y = height / 2 - (textHeight / 2);
		SetConsoleCursorPosition(handle, coordinates);
		cout << "1.Play";
		coordinates.Y++;
		SetConsoleCursorPosition(handle, { coordinates.X , coordinates.Y });
		cout << "2.Credits";
		coordinates.Y++;
		SetConsoleCursorPosition(handle, { coordinates.X , coordinates.Y });
		cout << "3.Quit";
	}
}


void Game(GameData& gd)
{
	if (gd.enteredNewScene)
		GameStart();

	GameUpdate();
	GameDraw();
}

void GameStart()
{

}
void GameUpdate()
{

}
void GameDraw()
{

}
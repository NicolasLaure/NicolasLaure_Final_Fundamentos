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
	ShowWindow(console, SW_SHOWMAXIMIZED);
	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
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
			Game(gd);
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

	if (!gd.isMenuFirstPhase && _getch() == '1')
		gd.scene = Scenes::Game;

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
		const int LOGO_HEIGHT = 30;
		COORD coordinates;
		coordinates.X = width / 2 - (logoWidth / 2);
		coordinates.Y = height / 2 - (LOGO_HEIGHT / 2);
		string logo[LOGO_HEIGHT] = {
		R"(                                     /@)",
		R"(                     __        __   /\/)",
		R"(                    /==\      /  \_/\/)",
		R"(                  /======\    \/\__ \__)",
		R"(                /==/\  /\==\    /\_|__ \)",
		R"(             /==/    ||    \=\ / / / /_/)",
		R"(           /=/    /\ || /\   \=\/ /)",
		R"(        /===/   /   \||/   \   \===\)",
		R"(      /===/   /_________________ \===\)",
		R"(   /====/   / |                /  \====\)",
		R"( /====/   /   |  _________    /  \   \===\    THE LEGEND OF)",
		R"( /==/   /     | /   /  \ / / /  __________\_____      ______       ___)",
		R"(|===| /       |/   /____/ / /   \   _____ |\   /      \   _ \      \  \)",
		R"( \==\             /\   / / /     | |  /= \| | |        | | \ \     / _ \)",
		R"( \===\__    \    /  \ / / /   /  | | /===/  | |        | |  \ \   / / \ \)",
		R"(   \==\ \    \\ /____/   /_\ //  | |_____/| | |        | |   | | / /___\ \)",
		R"(   \===\ \   \\\\\\\/   /////// /|  _____ | | |        | |   | | |  ___  |)",
		R"(     \==\/     \\\\/ / //////   \| |/==/ \| | |        | |   | | | /   \ |)",
		R"(     \==\     _ \\/ / /////    _ | |==/     | |        | |  / /  | |   | |)",
		R"(       \==\  / \ / / ///      /|\| |_____/| | |_____/| | |_/ /   | |   | |)",
		R"(       \==\ /   / / /________/ |/_________|/_________|/_____/   /___\ /___\)",
		R"(         \==\  /               | /==/)",
		R"(         \=\  /________________|/=/    )",
		R"(           \==\     _____     /==/ )",
		R"(          / \===\   \   /   /===/)",
		R"(         / / /\===\  \_/  /===/               Press Any Key)",
		R"(        / / /   \====\ /====/)",
		R"(       / / /      \===|===/)",
		R"(       |/_/         \===/)",
		R"(                      =)",
		};

		for (size_t i = 0; i < LOGO_HEIGHT; i++)
		{
			SetConsoleCursorPosition(handle, coordinates);
			cout << logo[i];
			coordinates.Y++;
		}
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
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	int width = csbi.srWindow.Right - csbi.srWindow.Left;
	int height = csbi.srWindow.Bottom - csbi.srWindow.Top;

	int mapWidth = 81;
	const int MAP_HEIGHT = 25;
	COORD coordinates;
	coordinates.X = width / 2 - (mapWidth / 2);
	coordinates.Y = height / 2 - (MAP_HEIGHT / 2);
	string map[MAP_HEIGHT] = {
	R"(#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#@#                #@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%)",
	R"(#@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#                #@##@#*##@#*##@#*##@#*##@#*##@#*##@#*#)",
	R"(#&#&&#&#&&#&#&&#&#&&[   ]#&#&&.#%(@#@#                #@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%)",
	R"(#@#*##@#*##@#*##@#*#[   ]#@#*#.%%                     #@##@#*##@#*##@#*##@#*##@#*##@#*##@#*#)",
	R"(#&#&&#&#&&#&#&&.#%(@                                  #@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%)",
	R"(#@#*##@#*##@#*#.%%                                    #@##@#*##@#*##@#*##@#*##@#*##@#*##@#*#)",
	R"(#&#&&#&#&&.#%/@                                       #@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%)",
	R"(#@#*##@#*#.%%                                         #@##@#*##@#*##@#*##@#*##@#*##@#*##@#*#)",
	R"(#&#&&.#%/@                                            #@##(#@##&#&%#&#&%#&%&%#&%&%#&%&%#&%&%)",
	R"(#@#*#.%%                                               #@#@#&*#@#*##@#*##@#*##@#*##@#*##@#*#)",
	R"(                                                                                            )",
	R"(                                                                                            )",
	R"(                                                                                            )",
	R"(                                                                                            )",
	R"( %                                                                                 %    %   )",
	R"(##/#####%@                                                                        ##/####/##)",
	R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
	R"(#@#*##@#*#                                                                        #@#*##@#*#)",
	R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
	R"(#@#*##@#*#                                                                        #@#*##@#*#)",
	R"(#&#&&#&#&&.%     %     %     %     %     %     %     %     %     %     %     %    #&%&%#&%&%)",
	R"(#@#*##@#*###/####/####/####/####/####/####/####/####/####/####/####/###@#*##@#*#@#/####/####)",
	R"(#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%@##&#&&#&#&&)",
	R"(#@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*#@#*##@#*##@#)",
	};

	for (size_t i = 0; i < MAP_HEIGHT; i++)
	{
		SetConsoleCursorPosition(handle, coordinates);
		cout << map[i];
		coordinates.Y++;
	}
}
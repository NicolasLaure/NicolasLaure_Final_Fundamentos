#include "Game.h"
void main()
{
	Play();
}

void Play()
{
	srand(0);
	GameData gd{};
	SetConsoleFontSize(gd.ConsoleFontSize);

	HWND console = GetConsoleWindow();
	ShowWindow(console, SW_SHOWMAXIMIZED);
	ShowScrollBar(GetConsoleWindow(), SB_BOTH, FALSE);

	CONSOLE_CURSOR_INFO CCI;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
	CCI.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
	//ShowCursor(false);
	GameLoop(gd);
}

void GameLoop(GameData& gd)
{
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
	{
		gd.isMenuFirstPhase = false;
		gd.isArtPrinted = false;
		system("cls");
	}

	if (!gd.isMenuFirstPhase && _getch() == '1')
	{
		gd.scene = Scenes::Game;
	}

}
void MenuDraw(GameData& gd)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	int width = csbi.srWindow.Right - csbi.srWindow.Left;
	int height = csbi.srWindow.Bottom - csbi.srWindow.Top;
	if (!gd.isArtPrinted)
	{
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
		gd.isArtPrinted = true;
	}

}


void Game(GameData& gd)
{
	if (gd.enteredNewScene)
		GameStart(gd);

	GameUpdate(gd);
	GameDraw(gd);
}

void GameStart(GameData& gd)
{
	gd.isArtPrinted = false;
}
void GameUpdate(GameData& gd)
{
	int mapToPrintPrevFrame = gd.mapToPrint;
	if (_kbhit())
	{
		char dir = _getch();

		if (gd.mapToPrint == 0)
			SetConsoleTextAttribute(gd.handle, 233);
		else
			SetConsoleTextAttribute(gd.handle, 7);
		SetConsoleCursorPosition(gd.handle, { (short)gd.player.position.x, (short)gd.player.position.y });
		cout << ' ';
		SetConsoleTextAttribute(gd.handle, 7);

		int x = gd.player.position.x;
		int y = gd.player.position.y;
		if (dir == 'w')
		{
			if (!gd.mapOfTiles[y - 1][x].hasCollision)
				gd.player.position.y--;
			else if (gd.mapOfTiles[y - 1][x].isCaveEntrance)
			{
				gd.mapToPrint = 1;
				gd.storedPosition = gd.player.position;
			}
			/*else if(gd.mapOfTiles[y - 1][x].isEndOfMap)
				gd.mapToPrint = 2;*/
		}
		else if (dir == 's')
		{
			if (!gd.mapOfTiles[y + 1][x].hasCollision)
				gd.player.position.y++;
			else if (gd.mapOfTiles[y + 1][x].isEndOfMap && gd.mapToPrint == 1)
				gd.mapToPrint = 0;
			/*else if(gd.mapOfTiles[y + 1][x].isEndOfMap)*/
		}
		else if (dir == 'a')
		{
			if (!gd.mapOfTiles[y][x - 1].hasCollision)
				gd.player.position.x--;
		}
		else if (dir == 'd')
		{
			if (!gd.mapOfTiles[y][x + 1].hasCollision)
				gd.player.position.x++;

		}
		if (mapToPrintPrevFrame != gd.mapToPrint)
			gd.isArtPrinted = false;
	}
}
void GameDraw(GameData& gd)
{
	/*string FirstScreen[] = {
	R"(#&#&&#&#&&#&#&&#&&#&&#&#&&#&#&&#&#&&#@#               #@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%)",
	R"(#@#*##@#*##@#*##@#*##@#*#@#@#*##@#*##@#               #@##@#*##@#*##@#*##@#*##@#*##@#*##@#*#)",
	R"(#&#&&#&#&&#&#&&#&#&&[    ]#&#&&.#%(@#@#               #@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%)",
	R"(#@#*##@#*##@#*##@#*#[    ]#@#*#.%%                    #@##@#*##@#*##@#*##@#*##@#*##@#*##@#*#)",
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
	R"(                                                                                            )",
	R"( %                                                                                 %    %   )",
	R"(##/#####%@                                                                        ##/####/##)",
	R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
	R"(#@#*##@#*#                                                                        #@#*##@#*#)",
	R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
	R"(#@#*##@#*#                                                                        #@#*##@#*#)",
	R"(#&#&&#&#&&.%     %     %     %     %     %     %     %     %     %     %     %    #&%&%#&%&%)",
	R"(#@#*##@#*###/####/####/####/####/####/####/####/####/####/####/####/###@#*##@#*#@#/####/####)",
	R"(#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&%#&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%@##&#&&#&#&&)",
	R"(#@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*#@#*##@#*##@#)"
	};
	string Cave[] = {
	R"(%&@%@@%@@%@%%@@%@%%@@&@%%@@@@%%@%@@%@@%@%%@%@%%@@%@%%@@@@%%@&@@%@@%@&%@@%@%%@@%@%%@@@@%%@@@@)",
	R"(%%@%&&%%%%&@%&%%&@%@%&&@%@%&&&%@%&&%%&%&@%%%&@%@%%&@%@%&&@%@%&&%%@%&@%%%%&@%@%%&@%@%&&@%@%&&)",
	R"(%&%@%&%%%@%@@%%@%@@%@@%@@%@@&&@%@&&%%%@%@&%@%@@%&@%@@%@@&@@%@@&%&%@%@%%%@%@@%&@%@@%@@%@@%@@&)",
	R"(@%@%%@@%%%%%%&%%%&%@%%%@%@%%@@%@%%@@%&%%%&%%%%%@%%%@%@%%@@%@%%@@%@%%&@%%%%%%@%%%@%@%%&@%@%%@)",
	R"(@@@%%&@@@&%@%@@@%@%@@@%@@@@@%@@@%&%@@@%%@&@@%@%@@@%@&@@@%@@@&@%@@@%%@@@@@%@%@@@%@&@@@%@@@@@%)",
	R"(%%@%%@%%@%%%                                                                     %@%%@@%@%%@)",
	R"(%&@%%%%@%%%%       IT'S    DANGEROUS    TO   GO   ALONE!!    TAKE    THIS.       %@%@%@%@%@%)",
	R"(%&@%@@%@@%@%                                                                     %@@@@%%@@@@)",
	R"(%%@%&&%%%%&@                                 A                                   %@%&&@%@%&&)",
	R"(%&%@%&%%%@%@            /\                  MMM                      /\          @%@@%@@%@@&)",
	R"(@%@%%@@%%%%%           /\\\                 / \                     /\\\         %@%%&@%@%%@)",
	R"(@@@%%&@@@&%@            \/                                           \/          &@@@%@@@@@%)",
	R"(%%@%%@%%@%%%                                                                     %@%%@@%@%%@)",
	R"(%&@%%%%@%%%%                               ->---                                 %@%@%@%@%@%)",
	R"(%&@%@@%@@%@%                                                                     %@@@@%%@@@@)",
	R"(%%@%&&%%%%&@                                                                     %@%&&@%@%&&)",
	R"(%&%@%&%%%@%@                                                                     @%@@%@@%@@&)",
	R"(@%@%%@@%%%%%                                                                     %@%%&@%@%%@)",
	R"(@@@%%&@@@&%@                                                                     &@@@%@@@@@%)",
	R"(%%@%%@%%@%%%                                                                     %@%%@@%@%%@)",
	R"(%&@%%%%@%%%%                                                                     %@%@%@%@%@%)",
	R"(%&@%@@%@@%@%                                                                     %@@@@%%@@@@)",
	R"(%%@%&&%%%%&@%%@%%@%%@%%@%%@%%@%%@%%@%&@%&            %@%%@%%@%%@%%@%&@%@&%&%%@%%@%@%&&@%@%&&)",
	R"(%&%@%&%%%@%@%%@@&&%%@@&@%%@@%&%&@@%&%&@@&            %@@%@%&@@%&%&@@&&%@@@&%%@@&@@%@@%@@%@@&)",
	R"(@%@%%@@%%%%%%&%%%&%@%%%@%@%%@@%@%%@@%&%%%            %%%@@%@%%@@%@%%&@%%%%%%@%%%@%@%%&@%@%%@)"
	};*/

	if (!gd.isArtPrinted)
	{
		PrintUpperBar(gd);
		PrintMap(gd, gd.maps[gd.mapToPrint], 25);
		if (gd.mapToPrint == 0)
		{
			//PrintMap(gd, FirstScreen, 25);
			if (gd.firstScreen)
			{
				gd.player.position = { 45, 16 };
				gd.firstScreen = false;
			}
			else
				gd.player.position = gd.storedPosition;
		}
		else if (gd.mapToPrint == 1)
		{
			//PrintMap(gd, Cave, 25);
			gd.player.position = { 48, 28 };
		}

		gd.isArtPrinted = true;
	}

	PrintPlayer(gd);
}

//Utilities
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
void PrintUpperBar(GameData gd)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	cout << "   -LIFE-" << endl;
	for (int i = 0; i < gd.player.HealthPoints; i++)
	{
		cout << "<3 ";
	}
}
void PrintMap(GameData& gd, string map[], int MAP_HEIGHT)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	int width = csbi.srWindow.Right - csbi.srWindow.Left;
	int height = csbi.srWindow.Bottom - csbi.srWindow.Top;

	int mapWidth = 93;
	COORD coordinates;
	coordinates.X = width / 2 - (mapWidth / 2) + 1;
	coordinates.Y = height / 2 - (MAP_HEIGHT / 2);

	int leftBorder = 2;
	int upperBorder = 4;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i < upperBorder || j < leftBorder || j > mapWidth + leftBorder || i >= MAP_HEIGHT + upperBorder)
			{
				gd.mapOfTiles[i][j].hasCollision = true;
				gd.mapOfTiles[i][j].isEndOfMap = true;
			}
		}
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		SetConsoleCursorPosition(handle, coordinates);
		bool isBetweenBraces = false;
		for (int j = 0; j < mapWidth; j++)
		{
			if (map[i][j] == 91)
				isBetweenBraces = true;
			if (map[i][j] == 93)
				isBetweenBraces = false;

			if (map[i][j] != ' ')
				gd.mapOfTiles[i + 4][j + 2].hasCollision = true;
			else if (map[i][j] == ' ' && isBetweenBraces)
			{
				gd.mapOfTiles[i + 4][j + 2].hasCollision = true;
				gd.mapOfTiles[i + 4][j + 2].isCaveEntrance = true;
			}
			else
				gd.mapOfTiles[i + 4][j + 2].hasCollision = false;

			if (gd.mapOfTiles[i + 4][j + 2].hasCollision)
			{
				if (gd.mapOfTiles[i + 4][j + 2].isCaveEntrance)
					SetConsoleTextAttribute(gd.handle, 7);
				else
				{
					if (gd.mapToPrint == 0)
						SetConsoleTextAttribute(gd.handle, 32);
					else
						SetConsoleTextAttribute(gd.handle, 64);

				}
			}
			else
			{
				if (gd.mapToPrint == 0)
					SetConsoleTextAttribute(gd.handle, 238);
				else
					SetConsoleTextAttribute(gd.handle, 7);
			}

			cout << map[i][j];
			SetConsoleTextAttribute(gd.handle, 7);
		}
		//cout << map[i];
		coordinates.Y++;
	}
}
void PrintPlayer(GameData& gd)
{
	if (gd.mapToPrint == 0)
		SetConsoleTextAttribute(gd.handle, 233);
	else
		SetConsoleTextAttribute(gd.handle, 9);

	SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y) });
	cout << gd.player.graphic;
	SetConsoleTextAttribute(gd.handle, 7);
}
#include "Game.h"
void main()
{
	Play();
}

void Play()
{
	srand(0);
	GameData gd{};
	Initialize(gd);
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
		case Scenes::GameOver:
			GameOver(gd);
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
		MenuStart(gd);

	MenuUpdate(gd);
	MenuDraw(gd);
}

void MenuStart(GameData& gd)
{
	gd.isMenuFirstPhase = true;
	gd.isArtPrinted = false;
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

			for (int i = 0; i < LOGO_HEIGHT; i++)
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
	MapsSetup(gd, gd.maps, gd.MAPS_QUANTITY, gd.MAP_SIZE);
	gd.actualMap = gd.maps[0];

	Player player;
	gd.player = player;
	gd.player.position = { 45, 16 };
	gd.playerLastDirection = Directions::East;

	for (int i = 0; i < gd.MAX_ENEMIES; i++)
	{
		gd.enemies[i] = gd.deadEnemy;
	}
}

void GameUpdate(GameData& gd)
{
	if (!gd.player.isAlive)
	{
		gd.scene = Scenes::GameOver;
		return;
	}
	gd.playerLivesPrevFrame = gd.player.healthPoints;

	if (clock() >= gd.player.timer)
		gd.player.canTakeDamage = true;

	Map mapPrevFrame = gd.actualMap;
	if (_kbhit())
	{
		ClearPreviousPlayerPos(gd);

		char pressedKey = _getch();

		int x = gd.player.position.x;
		int y = gd.player.position.y;

		if (pressedKey == 'w')
		{
			gd.playerLastDirection = Directions::North;
			if (!gd.mapOfTiles[y - 1][x].hasCollision)
				gd.player.position.y--;
			else if (gd.mapOfTiles[y - 1][x].isCaveEntrance)
			{
				MapChange(gd, true);
			}
			else if (gd.mapOfTiles[y - 1][x].isEndOfMap)
			{
				MapChange(gd, Directions::North);
			}
			else if (gd.mapOfTiles[y - 1][x].isItem)
			{
				TakeItem(gd);
			}
		}
		else if (pressedKey == 's')
		{
			gd.playerLastDirection = Directions::South;
			if (!gd.mapOfTiles[y + 1][x].hasCollision)
				gd.player.position.y++;
			else if (gd.mapOfTiles[y + 1][x].isEndOfMap)
			{
				MapChange(gd, Directions::South);
			}
			else if (gd.mapOfTiles[y + 1][x].isItem)
			{
				TakeItem(gd);
			}
		}
		else if (pressedKey == 'a')
		{
			gd.playerLastDirection = Directions::West;
			if (!gd.mapOfTiles[y][x - 1].hasCollision)
				gd.player.position.x--;
			else if (gd.mapOfTiles[y][x - 1].isEndOfMap)
			{
				MapChange(gd, Directions::West);
			}
			else if (gd.mapOfTiles[y][x - 1].isItem)
			{
				TakeItem(gd);
			}
		}
		else if (pressedKey == 'd')
		{
			gd.playerLastDirection = Directions::East;
			if (!gd.mapOfTiles[y][x + 1].hasCollision)
				gd.player.position.x++;
			else if (gd.mapOfTiles[y][x + 1].isEndOfMap)
			{
				MapChange(gd, Directions::East);
			}
			else if (gd.mapOfTiles[y][x + 1].isItem)
			{
				TakeItem(gd);
			}
		}
		else if (pressedKey == 'x' && gd.player.hasSword)
		{
			PlayerAttack(gd);
		}
		else if (pressedKey == 'c' && gd.player.hasShield)
		{
			PlayerParry(gd);
		}
		if (mapPrevFrame.name != gd.actualMap.name)
			gd.isArtPrinted = false;
	}
	gd.player.direction = gd.playerLastDirection;

	for (int i = 0; i < gd.MAX_ENEMIES; i++)
	{
		if (gd.enemies[i].position.x == gd.player.position.x && gd.enemies[i].position.y == gd.player.position.y && gd.player.canTakeDamage)
			gd.player.TakeDamage();
	}
}
void GameDraw(GameData& gd)
{
	if (!gd.isArtPrinted)
	{
		PrintUpperBar(gd);
		PrintMap(gd, gd.actualMap, 25);
		gd.isArtPrinted = true;
	}
	if (gd.playerLivesPrevFrame != gd.player.healthPoints)
	{
		//CleanUpperBar(gd);
		PrintUpperBar(gd);
	}

	PrintPlayer(gd);
	if (gd.actualMap.name == MapNames::Mountain1)
		PrintEnemies(gd);
}

void GameOver(GameData& gd)
{
	if (gd.enteredNewScene)
		GameOverStart(gd);

	GameOverUpdate(gd);
	GameOverDraw(gd);
}

void GameOverStart(GameData& gd)
{
	gd.isArtPrinted = false;
}
void GameOverUpdate(GameData& gd)
{
	if (_kbhit())
		gd.scene = Scenes::Menu;
}
void GameOverDraw(GameData& gd)
{
	if (!gd.isArtPrinted)
	{
		SetConsoleTextAttribute(gd.handle, 7);
		system("cls");
		string gameOverText[7] = {
			R"( ######      ###    ##     ## ########  #######  ##     ## ######## ######## )",
			R"(##    ##    ## ##   ###   ### ##       ##     ## ##     ## ##       ##     ## )",
			R"(##         ##   ##  #### #### ##       ##     ## ##     ## ##       ##     ## )",
			R"(##   #### ##     ## ## ### ## ######   ##     ## ##     ## ######   ########  )",
			R"(##    ##  ######### ##     ## ##       ##     ##  ##   ##  ##       ##   ##   )",
			R"(##    ##  ##     ## ##     ## ##       ##     ##   ## ##   ##       ##    ##  )",
			R"( ######   ##     ## ##     ## ########  #######     ###    ######## ##     ## )"
		};
		COORD coordinates;
		coordinates.X = gd.width / 2 - (78 / 2);
		coordinates.Y = gd.height / 4;
		for (int i = 0; i < 7; i++)
		{
			SetConsoleTextAttribute(gd.handle, 4);
			SetConsoleCursorPosition(gd.handle, coordinates);
			cout << gameOverText[i];
			coordinates.Y++;
		}
		SetConsoleTextAttribute(gd.handle, 7);
		coordinates.X = gd.width / 2 - (37 / 2);
		coordinates.Y += 5;
		SetConsoleCursorPosition(gd.handle, coordinates);
		cout << "Press Any Key To Return To Main Menu";
		gd.isArtPrinted = true;
	}
}

//Utilities
void Initialize(GameData gd)
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
void PrintUpperBar(GameData gd)
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
void CleanUpperBar(GameData gd)
{
	SetConsoleTextAttribute(gd.handle, 7);
	SetConsoleCursorPosition(gd.handle, { 0,0 });
	cout << "   -LIFE-" << endl << "                             ";
}
void PrintMap(GameData& gd, Map map, int MAP_HEIGHT)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	gd.width = csbi.dwSize.X;
	gd.height = csbi.srWindow.Bottom - csbi.srWindow.Top;

	int mapWidth = 93;
	COORD coordinates;
	coordinates.X = gd.width / 2 - (mapWidth / 2) + 1;
	coordinates.Y = gd.height / 2 - (MAP_HEIGHT / 2);

	int leftBorder = 2;
	int upperBorder = 4;
	for (int i = 0; i < gd.height; i++)
	{
		for (int j = 0; j < gd.width; j++)
		{
			if (i < upperBorder || j < leftBorder || j >= mapWidth + 1 || i >= MAP_HEIGHT + upperBorder)
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
			if (map.mapGraphic[i][j] == 91)
				isBetweenBraces = true;
			if (map.mapGraphic[i][j] == 93)
				isBetweenBraces = false;

			if (map.mapGraphic[i][j] != ' ')
			{
				gd.mapOfTiles[i + 4][j + 2].isCaveEntrance = false;
				gd.mapOfTiles[i + 4][j + 2].hasCollision = true;
				if (gd.actualMap.name == MapNames::Cave1)
				{
					if (map.mapGraphic[i][j] == '>' || map.mapGraphic[i][j] == '-')
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
				}
				else if (gd.actualMap.name == MapNames::Cave2)
				{
					if (map.mapGraphic[i][j] == '_' || map.mapGraphic[i][j] == '/' || map.mapGraphic[i][j] == 92)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
				}
			}
			else if (map.mapGraphic[i][j] == ' ' && isBetweenBraces)
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
					if (map.mapType == MapType::OverWorld)
					{
						if (gd.actualMap.name == MapNames::WesternRiver && map.mapGraphic[i][j] == '.')
							SetConsoleTextAttribute(gd.handle, 23);
						else
							SetConsoleTextAttribute(gd.handle, 32);
					}
					else if (map.mapType == MapType::Cave)
						SetConsoleTextAttribute(gd.handle, 4);
					else
						SetConsoleTextAttribute(gd.handle, 6);
				}
			}
			else
			{
				if (map.mapType == MapType::OverWorld || map.mapType == MapType::Mountain)
					SetConsoleTextAttribute(gd.handle, 238);
				else if (map.mapType == MapType::Cave)
					SetConsoleTextAttribute(gd.handle, 7);
			}


			cout << map.mapGraphic[i][j];
			SetConsoleTextAttribute(gd.handle, 7);
		}
		//cout << map[i];
		coordinates.Y++;
	}
}
void PrintPlayer(GameData& gd)
{
	if (gd.actualMap.mapType == MapType::OverWorld || gd.actualMap.mapType == MapType::Mountain)
		SetConsoleTextAttribute(gd.handle, 233);
	else
		SetConsoleTextAttribute(gd.handle, 9);

	SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y) });
	cout << gd.player.graphic;
	switch (gd.player.direction)
	{
	case Directions::North:
		if (!gd.mapOfTiles[gd.player.position.y - 1][gd.player.position.x].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y - 1) });
			cout << '.';
		}
		break;
	case Directions::South:
		if (!gd.mapOfTiles[gd.player.position.y + 1][gd.player.position.x].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y + 1) });
			cout << '.';
		}
		break;
	case Directions::East:
		if (!gd.mapOfTiles[gd.player.position.y][gd.player.position.x + 1].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x + 1), static_cast<short>(gd.player.position.y) });
			cout << '.';
		}
		break;
	case Directions::West:
		if (!gd.mapOfTiles[gd.player.position.y][gd.player.position.x - 1].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x - 1), static_cast<short>(gd.player.position.y) });
			cout << '.';
		}
		break;
	default:
		break;
	}
	SetConsoleTextAttribute(gd.handle, 7);
}
void PrintEnemies(GameData& gd)
{
	if (gd.actualMap.mapType == MapType::OverWorld || gd.actualMap.mapType == MapType::Mountain)
		SetConsoleTextAttribute(gd.handle, 236);

	for (int i = 0; i < gd.MAX_ENEMIES; i++)
	{
		SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.enemies[i].position.x),static_cast<short>(gd.enemies[i].position.y) });
		if (gd.enemies[i].isAlive)
			cout << gd.enemies[i].graphic;
		else if (gd.enemies[i].isActiveEnemy)
			cout << ' ';
	}
}

void ClearPreviousPlayerPos(GameData& gd)
{
	if (gd.actualMap.mapType == MapType::OverWorld || gd.actualMap.mapType == MapType::Mountain)
		SetConsoleTextAttribute(gd.handle, 233);
	else
		SetConsoleTextAttribute(gd.handle, 7);
	SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y) });
	cout << ' ';
	switch (gd.player.direction)
	{
	case Directions::North:
		if (!gd.mapOfTiles[gd.player.position.y - 1][gd.player.position.x].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y - 1) });
			cout << ' ';
		}
		break;
	case Directions::South:
		if (!gd.mapOfTiles[gd.player.position.y + 1][gd.player.position.x].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y + 1) });
			cout << ' ';
		}
		break;
	case Directions::East:
		if (!gd.mapOfTiles[gd.player.position.y][gd.player.position.x + 1].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x + 1), static_cast<short>(gd.player.position.y) });
			cout << ' ';
		}
		break;
	case Directions::West:
		if (!gd.mapOfTiles[gd.player.position.y][gd.player.position.x - 1].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x - 1), static_cast<short>(gd.player.position.y) });
			cout << ' ';
		}
		break;
	default:
		break;
	}
	SetConsoleTextAttribute(gd.handle, 7);
}
void MapsSetup(GameData& gd, Map maps[], int mapQty, int mapSize)
{
	for (int i = 0; i < mapQty; i++)
	{
		switch (static_cast<MapNames>(i))
		{
		case MapNames::StartValley:
		{
			maps[i].name = MapNames::StartValley;
			maps[i].mapGraphic = new string[25]{
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
			maps[i].mapType = MapType::OverWorld;
		}
		break;
		case MapNames::WesternRiver:
			maps[i].name = MapNames::WesternRiver;
			maps[i].mapGraphic = new string[25]{
			R"(......{/(,@(&((,((@(/*@(((*%*(%%*@((*(,@(#((,%(@(/,,(%(/#,(,(*&((,(,@@           (@(//,(/(*%)",
			R"(......{/(,@(&((,((@(/*@(((*%*(%(*@((*(,@(#((,%(@(/,,(%(/#,(,(*&((,(,@@           (@(//,(/(*%)",
			R"(......}((@(@&(#@((%(&((,@(@,(/,(@*#(/(@(@%((@(%&(%%(**(@,(*&(@*#(*(@/&           ((@*(,&(@,()",
			R"(......{(/(((/&(((%(@((#@((((&/(%((#(/(@(@%#(((#(@(((@(%((%#(,((&%((@/&           (@((#&(/((&)",
			R"(......}%@%(@/@@@((#@@/(@@@&@(@%@#(@(((@(%(%@@(%(%@#(,&&@&(&@&#,(@((@             %&@*(&@&%&()",
			R"(......{                                                                          (@/(@&(@((@)",
			R"(......}                              ,,                                          (@(,(@(/(&()",
			R"(......{                             /(/*         %                               /,#@(%(#*@@)",
			R"(......}                              /,(       (@((&,                            @&(@(((/(,#)",
			R"(......{                                        ((#&%(                                /(*(&(%)",
			R"(......}                                                                                (/(@()",
			R"(......}                                         ,         ,(#((&                            )",
			R"(......{                                       ,*(,*       ,(((#&                            )",
			R"(......}     /(%(*             ,@(@            /(#(,                                         )",
			R"(......{    /&(@((             (%@%@           (@(&(,                                        )",
			R"(......{                                                   ,(,&#@                        /@(()",
			R"(......}                                                    (((@@                       ((@(&)",
			R"(......{                   /**/         /***        &/(#                            @(#@(/((#)",
			R"(......}                  */,,//       ,(,,**      (@(#@,                          @@((&/*%@()",
			R"(......{                                                                          (@/(&&(@((@)",
			R"(......}                                                                          #@(,(&%/(&()",
			R"(......{(*,*,,%,,*,,@,,*,(@,*,,(@,,,,((,,*,#,*,,,@,,*,/@,,,,(@,,*,(%,,*,(*,,*,&,*,(*,&(/(%*@@)",
			R"(......{(@(#@#(&(@@((*(@@(%,(#@(@((#@(@((@%(@(&@((/(@@(##(%@(@/((@(@((&&(@(%@((#@@*((@#&((%@@)",
			R"(......}(&*(@#(%((@((,((&((@((&((@(#&(%,(@#(&/(@((/((&((@((&((#((@(#,(&%(@/(@((#(&(@(,(*(/(@()",
			R"(......{(@(#@#(&(@@((*(@@(%,(#@(@((#@(@((@%(@(&@((/(@@(##(%@(@/((@(@((&&(@(%@((#@@*((@#&((%@@)"
			};
			maps[i].mapType = MapType::OverWorld;
			break;
		case MapNames::HyruleField:
			maps[i].name = MapNames::HyruleField;
			maps[i].mapGraphic = new string[25]{
			R"(#&##@&#&           &##@&#&##@&#&##@&#&##@&#&##@&#&##@&#&##@&#&##@&#&##@&###@&#&##@&#&##@&#&#)",
			R"(#&##@&#&           &####@#&##@&#&##@&####@#&##@&#&##@&####@#&##@&#&##@&###@#&##@&#&##@&####@)",
			R"(.,#@,,#&           &.##@,.,#@,,#&##@&.##@,.,#@,,#&##@&.##@,.,#@,,#&##@&.#@,.,#@,,#&##@&.##@,)",
			R"(.###@%#&           &####@.###@%#&##@&####@.###@%#&##@&####@.###@%#&##@&###@.###@%#&##@&####@)",
			R"(#@###%#&           &####@#@###%#&##@&####@#@###%#&##@&####@#@###%#&##@&###@#@###%#&##@&####@)",
			R"(#%##@&                                                                           ,##@&.###@.)",
			R"(.,#@,,                                                                           #@##@.####@)",
			R"(#%##@&                                                                           #@##@.####@)",
			R"(.,#@,,                                                     &##&@                %&#/&&.&##&@)",
			R"(.###@%                                                      #&#,                    ,#&##%#,)",
			R"(#%##@&      ####@                   ###@       ####@                                   @@@@#)",
			R"(.,#@,,      ####@                  #####       ####@                                   @#@#.)",
			R"(.###@%                                                     ###@                        @@@@#)",
			R"(#%##@&                                                     ####@       ***             ####@)",
			R"(.,#@,,                                                                 ###*            ####@)",
			R"(.###@%      ####@/                 ####@#      ####@                                   &##&@)",
			R"(#%##@&       ##@,,                  (#@,,       ##@,,                                  ##%#,)",
			R"(.,#@,,                                                     ####@                       ####@)",
			R"(.###@%                                                     @##@@                       @##@@)",
			R"(#%##@&                     #*#*###*      /.#&                                    ,##@&.###@.)",
			R"(.,#@,,                      #,,###*      /.#&                                    #@##@.####@)",
			R"(.###@%                                                                           #@##@.####@)",
			R"(#%##@&####@#####@/###%@.&##&@*&##@@####@#####@#####@.%##&@.&##&@                 ###%@.&##&@)",
			R"(.,#@,,.(#@,,.##@,,.##&,,.###,..#@/,.(#@,,.(#@,,.##@,,.###,,.#&#,                 .##%,,.#%#,)",
			R"(.###@%.###@.####@.####@.####@.###&@.###@./###@.####@.####@.####@                 ####@.####@)"
			};
			maps[i].mapType = MapType::OverWorld;
			break;
		case MapNames::KokiriForest:
			maps[i].name = MapNames::KokiriForest;
			maps[i].mapGraphic = new string[25]{
			R"(#%.#&%#@/(@/#@((@*#@(#@*#@##@/#@##@(#@#(@##&#(&##*((&##.(%&#%.(&%#@,#@/(@((@*#@##@*#@##@/#@##)",
			R"(#@##(##@###&#@#/(@#&#.#@(/#.#&(.#,###.#*((&,#(##@(##(#@###(#@#####@#(#&#@#/#@#@#.#@(/#.#&(.(.)",
			R"(./,@.%&#(@.*,#&@..*#@@(.##%@&*##*&@&/(.(@@,(..@&.,*.@#..%.@.*.@.&.#*@.*.#%@../#@@/.##&@&/##(@)",
			R"(#%##.%#@##.*#@##..#&##(.#/#(&,#.#(@(#.#*@[     ]#/#.@####.@#%##.&#@##.*#@##..#@#((.#/##&*#.##)",
			R"(@##@#%@#%@#*&#%##.(#%.#..#&.#,.(@,((,(@/#[     ]#(@#@%#(@#@@##@#&@##&#*&#%%#.*#%,#..#&.#*.#@.)",
			R"(#&,###.@#@#,                                         #@##,#.%#@#&                  (/#@#/#&##)",
			R"(#@@@#@&@&                                              @@@#.%#                      (@@,/@.#.)",
			R"(###@#@             ##          (@                                       ##              *###@)",
			R"(#%#,              #&((&       #,&#@                                    #@(##             ,##@)",
			R"(%#                %%%@&#     ,%%#@@,                                   #%%%@%              @#)",
			R"(#%                                                                                         #@)",
			R"(%#                                                                                         #@)",
			R"(#%                *###(      ,(@##                                     ,((#&               @#)",
			R"(%#                #&##%       #,&#@                                    #@#&(               #@)",
			R"(#%                                                                                         #@)",
			R"(%#                                                                                         @#)",
			R"(#%                                                                                         #@)",
			R"(###               *%#(&      ,#,##@                                     &(##               (#)",
			R"(##&##%            #&##@      ,#(##&                                    #@(%@             #(##)",
			R"((&.#%#.(                                                ##@,(                         (#*#@##)",
			R"((@######(##                                           #(#####@(#                   #%@##*(.#.)",
			R"((/&#*##.(#.#,@    *@    #@    #@    #&               #@@#%###@#*(&      @    /@    ##,@&#(@*@)",
			R"(#&##/%#@##/*(#(##@#(/##@##*##&#(,##%#(.##            ####/@#%##/&##&##@##(##@##/##@#/#*%*#.#*)",
			R"(%%,.(&%#%@(/#(%(%@##%&#@###&#&##*&#%(%,&#            ###@(@%##@#&(#@*%@##%/%@(#%%#@,#&*%/,#@*)",
			R"(#&#####@###&#@###@#%##%@#/##&%#.##@,#.##&            *####((%#####@###&#@###@#@##%@#/##@&,,#%)"
			};
			maps[i].mapType = MapType::OverWorld;
			break;
		case MapNames::Cave1:
		{
			maps[i].name = MapNames::Cave1;
			maps[i].mapGraphic = new string[25]{
			R"(%&@%@@%@@%@%%@@%@%%@@&@%%@@@@%%@%@@%@@%@%%@%@%%@@%@%%@@@@%%@&@@%@@%@&%@@%@%%@@%@%%@@@@%%@@@@)",
			R"(%%@%&&%%%%&@%&%%&@%@%&&@%@%&&&%@%&&%%&%&@%%%&@%@%%&@%@%&&@%@%&&%%@%&@%%%%&@%@%%&@%@%&&@%@%&&)",
			R"(%&%@%&%%%@%@@%%@%@@%@@%@@%@@&&@%@&&%%%@%@&%@%@@%&@%@@%@@&@@%@@&%&%@%@%%%@%@@%&@%@@%@@%@@%@@&)",
			R"(@%@%%@@%%%%%%&%%%&%@%%%@%@%%@@%@%%@@%&%%%&%%%%%@%%%@%@%%@@%@%%@@%@%%&@%%%%%%@%%%@%@%%&@%@%%@)",
			R"(@@@%%&@@@&%@%@@@%@%@@@%@@@@@%@@@%&%@@@%%@&@@%@%@@@%@&@@@%@@@&@%@@@%%@@@@@%@%@@@%@&@@@%@@@@@%)",
			R"(%%@%%@%%@%%%                                                                     %@%%@@%@%%@)",
			R"(%&@%%%%@%%%%       IT'S    DANGEROUS    TO    GO    ALONE!    TAKE    THIS.      %@%@%@%@%@%)",
			R"(%&@%@@%@@%@%                                                                     %@@@@%%@@@@)",
			R"(%%@%&&%%%%&@                                  A                                  %@%&&@%@%&&)",
			R"(%&%@%&%%%@%@            /\                   MMM                     /\          @%@@%@@%@@&)",
			R"(@%@%%@@%%%%%           /\\\                  / \                    /\\\         %@%%&@%@%%@)",
			R"(@@@%%&@@@&%@            \/                                           \/          &@@@%@@@@@%)",
			R"(%%@%%@%%@%%%                                                                     %@%%@@%@%%@)",
			R"(%&@%%%%@%%%%                                ->---                                %@%@%@%@%@%)",
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
			};
			maps[i].mapType = MapType::Cave;
		}
		break;
		case  MapNames::Cave2:
			maps[i].name = MapNames::Cave2;
			maps[i].mapGraphic = new string[25]{
			R"(%&@%@@%@@%@%%@@%@%%@@&@%%@@@@%%@%@@%@@%@%%@%@%%@@%@%%@@@@%%@&@@%@@%@&%@@%@%%@@%@%%@@@@%%@@@@)",
			R"(%%@%&&%%%%&@%&%%&@%@%&&@%@%&&&%@%&&%%&%&@%%%&@%@%%&@%@%&&@%@%&&%%@%&@%%%%&@%@%%&@%@%&&@%@%&&)",
			R"(%&%@%&%%%@%@@%%@%@@%@@%@@%@@&&@%@&&%%%@%@&%@%@@%&@%@@%@@&@@%@@&%&%@%@%%%@%@@%&@%@@%@@%@@%@@&)",
			R"(@%@%%@@%%%%%%&%%%&%@%%%@%@%%@@%@%%@@%&%%%&%%%%%@%%%@%@%%@@%@%%@@%@%%&@%%%%%%@%%%@%@%%&@%@%%@)",
			R"(@@@%%&@@@&%@%@@@%@%@@@%@@@@@%@@@%&%@@@%%@&@@%@%@@@%@&@@@%@@@&@%@@@%%@@@@@%@%@@@%@&@@@%@@@@@%)",
			R"(%%@%%@%%@%%%                                                                     %@%%@@%@%%@)",
			R"(%&@%%%%@%%%%                    Take         This        Shield,                 %@%@%@%@%@%)",
			R"(%&@%@@%@@%@%         It'll    allow   you   to   parry   enemy   proyectiles     %@@@@%%@@@@)",
			R"(%%@%&&%%%%&@                                  A                                  %@%&&@%@%&&)",
			R"(%&%@%&%%%@%@            #$                   MMM                     #$          @%@@%@@%@@&)",
			R"(@%@%%@@%%%%%           &%&%                  / \                    &%&%         %@%%&@%@%%@)",
			R"(@@@%%&@@@&%@            #$                   ___                     #$          &@@@%@@@@@%)",
			R"(%%@%%@%%@%%%                                / ^ \                                %@%%@@%@%%@)",
			R"(%&@%%%%@%%%%                                \^ ^/                                %@%@%@%@%@%)",
			R"(%&@%@@%@@%@%                                 \_/                                 %@@@@%%@@@@)",
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
			};
			maps[i].mapType = MapType::Cave;
			break;
		case MapNames::Mountain1:
		{
			maps[i].name = MapNames::Mountain1;
			maps[i].mapGraphic = new string[25]{
			R"((#@(@&(@@(@((#@(.((..%.(((.@@((@(@@(@@(@((@@(/(./(.((..@%((@/@@(&@(@#(@@(@((,@(.((..@,((@,@@)",
			R"(((.(/%((((/@(#((/#(@(//.(#(,#*(.(*#((*(/@((((/(@((/.(@(,(.(.(,#((.(/@((((/@(@((/,(@(,/.(.(,#)",
			R"((*(@(%(((@(@#((@(&#(&%(/,(&/%(,(@(%(((@(@(((@(#(%@(//(&/#/,(@/%(/(@(@(((@(@#((@((#(&((/,(&/%)",
			R"(.(.((&.((((((#(((%(@(((@(#((@#(.((@.(*(((*(((((@(((@(@((&@(.((@.(.((#.((((((@(((@(@(((@(.((@)",
			R"(.%.((#..@#(@(.@@(#(.@#(.@.@.(.@.(*(..#((@*.@@((.@@(.&.@.(.@.#.(.*.((@..@@(@(.@@(,(.@,(.@.@.()",
			R"(.@(@(#(@((.((&(@(@                                                               (.(@(@(@((@)",
			R"(.((@....@#@((#(                                                                   @(@&((.(.()",
			R"(                            (@                                (@                       (@,@@)",
			R"(                         *@((.(((@                         (@((.(((@                   (.(.()",
			R"(                        ((@(@*((.%@                       ((@(@(((.(@                  ((#@@)",
			R"(                    @((@(#(((%(.(((.((                @(&@(.(((((.(((.((               (((@()",
			R"(                  (@@((@*/#.(,*/&*(%((.(@           (@@((@*/&.(///&(@%(#/(@                 )",
			R"(                  (@((%@(@((@#(@((@*(((((           (@((@@(@((@*(@((#*(.(((                 )",
			R"(                  (@(/(@(#(.(%(.(*(/@*(((           (@(.(@(.(.(/@.(((/@((((                 )",
			R"(                  (.(@(@((.@@%@@@@@.((@(@           (.(@(@(@/@@(&@(@#.((@(@               (@)",
			R"(                  @.(%@((#(.((@@@@@.((@             @.(@/((.(.(((.((@.((@               (@(()",
			R"(                       ((((@@@@@@@@@                    %(((&@@(((@(@@                 ((@(@)",
			R"(                                                                                       (.((()",
			R"(                                                                                        (#.()",
			R"( ((      ,(@((@                                                                     ((@(@((@)",
			R"(((@((#.((((@((@((#                                                               ((@((.@.(.()",
			R"(((@(#@(#*(#&(#*(&#/#..&.(%....(@.,..(&./.*(&.#/#*.&./#..*.(@....(@./..(&././#%.&.(&/#&,(@/#@)",
			R"(((.((((%(((%(&(((#((.(((((.((#((*((%(#*(@#(%((((*(((((.(((((,((%((*(@%(%/(@((%((#(@(.(((.(.()",
			R"(#((&/@#//@/@.//@/@((.(@@#%.((@#@(((@#@(#@%#@(&((/(@@((.(#@#@/((@#@(#&@#@(#@((@(@@.(#@(&((#@@)",
			R"(((.((((((((((#(((%(@(((@(#(((%(.(((((*(((((((((@(((@(@(((@(.(((((.((((((((((@(((@(@(((@(.((()"
			};
			maps[i].mapType = MapType::Mountain;
		}
		break;
		default:
			break;
		}

	}
}
void MapChange(GameData& gd, Directions dir)
{
	switch (gd.actualMap.name)
	{
	case MapNames::StartValley:
		if (dir == Directions::East)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::Mountain1)];
			gd.storedPosition = gd.player.position;
			Enemy spider{ 'M',0, true , {2, 20}, true };
			gd.enemies[0] = spider;
			gd.player.position = { 2, 17 };
		}
		else if (dir == Directions::North)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::HyruleField)];
			gd.storedPosition = gd.player.position;
			gd.player.position = { 74, 28 };
		}
		else if (dir == Directions::West)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::WesternRiver)];
			gd.storedPosition = gd.player.position;
			gd.player.position = { 93, 17 };
		}
		break;
	case MapNames::Cave1:
	case MapNames::Cave2:
		if (dir == Directions::South)
		{
			gd.actualMap = gd.previousMap;
			gd.player.position = gd.storedPosition;
		}
		break;
	case MapNames::Mountain1:
		if (dir == Directions::West)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::StartValley)];
			gd.player.position = gd.storedPosition;
		}
		break;
	case MapNames::WesternRiver:
		gd.actualMap = gd.maps[static_cast<int>(MapNames::StartValley)];
		gd.player.position = gd.storedPosition;
		break;
	case MapNames::HyruleField:
		if (dir == Directions::North)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::KokiriForest)];
			gd.storedPosition = gd.player.position;
			gd.player.position = { 45, 28 };
		}
		else if (dir == Directions::South)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::StartValley)];
			gd.player.position = { 48, 4 };
		}
		break;
	case MapNames::KokiriForest:
		gd.actualMap = gd.maps[static_cast<int>(MapNames::HyruleField)];
		gd.player.position = { 15, 4 };
	default:
		break;
	}
}
void MapChange(GameData& gd, bool isCave)
{
	switch (gd.actualMap.name)
	{
	case MapNames::StartValley:
		gd.previousMap = gd.actualMap;
		gd.actualMap = gd.maps[static_cast<int>(MapNames::Cave1)];
		gd.storedPosition = gd.player.position;
		gd.player.position = { 48, 28 };
		break;
	case MapNames::KokiriForest:
		gd.previousMap = gd.actualMap;
		gd.actualMap = gd.maps[static_cast<int>(MapNames::Cave2)];
		gd.storedPosition = gd.player.position;
		gd.player.position = { 48, 28 };
		break;
	}
}

void PlayerAttack(GameData& gd)
{
	if (gd.actualMap.mapType == MapType::OverWorld || gd.actualMap.mapType == MapType::Mountain)
		SetConsoleTextAttribute(gd.handle, 233);
	else
		SetConsoleTextAttribute(gd.handle, 9);

	Vector2 attackedPosition = { 0,0 };
	switch (gd.player.direction)
	{
	case Directions::North:
		attackedPosition = { gd.player.position.x , gd.player.position.y - 1 };
		break;
	case Directions::South:
		attackedPosition = { gd.player.position.x , gd.player.position.y + 1 };
		break;
	case Directions::East:
		attackedPosition = { gd.player.position.x + 1 , gd.player.position.y };
		break;
	case Directions::West:
		attackedPosition = { gd.player.position.x - 1 , gd.player.position.y };
		break;
	}
	SetConsoleCursorPosition(gd.handle, { static_cast<short>(attackedPosition.x),  static_cast<short>(attackedPosition.y) });
	if (attackedPosition.x != gd.player.position.x && !gd.mapOfTiles[attackedPosition.y][attackedPosition.x].hasCollision)
		cout << static_cast<char>(45);
	else if (!gd.mapOfTiles[attackedPosition.y][attackedPosition.x].hasCollision)
		cout << static_cast<char>(124);
	Sleep(40);

	SetConsoleTextAttribute(gd.handle, 7);

	for (int i = 0; i < gd.MAX_ENEMIES; i++)
	{
		if (gd.enemies[i].position.x == attackedPosition.x && gd.enemies[i].position.y == attackedPosition.y)
			gd.enemies[i].TakeDamage(gd.player.attackDamage);
	}
}
void PlayerParry(GameData& gd)
{
	if (gd.actualMap.mapType == MapType::OverWorld || gd.actualMap.mapType == MapType::Mountain)
		SetConsoleTextAttribute(gd.handle, 233);
	else
		SetConsoleTextAttribute(gd.handle, 9);


	Vector2 parryPosition = { 0,0 };
	switch (gd.player.direction)
	{
	case Directions::North:
		parryPosition = { gd.player.position.x , gd.player.position.y - 1 };
		break;
	case Directions::South:
		parryPosition = { gd.player.position.x , gd.player.position.y + 1 };
		break;
	case Directions::East:
		parryPosition = { gd.player.position.x + 1 , gd.player.position.y };
		break;
	case Directions::West:
		parryPosition = { gd.player.position.x - 1 , gd.player.position.y };
		break;
	}
	SetConsoleCursorPosition(gd.handle, { static_cast<short>(parryPosition.x),  static_cast<short>(parryPosition.y) });
	if (parryPosition.x != gd.player.position.x && !gd.mapOfTiles[parryPosition.y][parryPosition.x].hasCollision)
		cout << static_cast<char>(124);
	else if (!gd.mapOfTiles[parryPosition.y][parryPosition.x].hasCollision)
		cout << static_cast<char>(45);
	Sleep(40);

	SetConsoleTextAttribute(gd.handle, 7);
}
void TakeItem(GameData& gd)
{
	if (gd.actualMap.name == MapNames::Cave1)
	{
		gd.maps[static_cast<int>(MapNames::Cave1)].isCaveItemTaken = true;
		gd.maps[static_cast<int>(MapNames::Cave1)].mapGraphic[13] = R"(%&@%%%%@%%%%                                                                     %@%@%@%@%@%)";

		gd.player.hasSword = true;
		SetConsoleCursorPosition(gd.handle, { 46,17 });
		for (int i = 0; i < 5; i++)
		{
			gd.mapOfTiles[17][46 + i].hasCollision = false;
		}
		cout << "     ";
	}
	else if (gd.actualMap.name == MapNames::Cave2)
	{
		gd.maps[static_cast<int>(MapNames::Cave2)].isCaveItemTaken = true;

		for (int i = 11; i < 15; i++)
		{
			if (i == 11)
				gd.maps[static_cast<int>(MapNames::Cave2)].mapGraphic[i] = R"(@@@%%&@@@&%@            #$                                           #$          &@@@%@@@@@%)";
			else
				gd.maps[static_cast<int>(MapNames::Cave2)].mapGraphic[i] = R"(%&@%%%%@%%%%                                                                     %@%@%@%@%@%)";
		}

		gd.player.hasShield = true;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 15; j < 19; j++)
			{
				gd.mapOfTiles[j][46 + i].hasCollision = false;
				SetConsoleCursorPosition(gd.handle, { 46,static_cast<short>(j) });
				cout << "     ";
			}
		}
	}
}
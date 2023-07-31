#include "Game.h"
void main()
{
	Play();
}

void Play()
{
	srand(time(0));
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
		case Scenes::GameQuit:
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
		default:
			break;
		}

	} while (gd.scene != Scenes::GameQuit);
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

	if (!gd.isMenuFirstPhase)
	{
		char response = _getch();

		if (response == '1')
			gd.scene = Scenes::Game;
		else if (response == '2')
			Rules(gd);
		else if (response == '3')
			gd.scene = Scenes::GameQuit;
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
		system("cls");
		if (gd.isMenuFirstPhase)
		{
			int logoWidth = 74;
			const int LOGO_HEIGHT = 30;
			COORD coordinates;
			coordinates.X = width / 2 - (logoWidth / 2);
			coordinates.Y = height / 2 - (LOGO_HEIGHT / 2);
			string logo[LOGO_HEIGHT] = {
			R"(                                     /@           Nicolas Laure TSDV_ImageCampus 2023)",
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
			cout << "2.Rules";
			coordinates.Y++;
			SetConsoleCursorPosition(handle, { coordinates.X , coordinates.Y });
			cout << "3.Quit";
		}
		gd.isArtPrinted = true;
	}
}

void Rules(GameData& gd)
{
	system("cls");
	gd.isArtPrinted = false;
	SetConsoleCursorPosition(gd.handle, { 5,7 });
	cout << "Princess Zelda was kidnapped at Hyrule Castle, you have to rescue her!!";
	SetConsoleCursorPosition(gd.handle, { 5,13 });
	cout << "Use WASD keys to move, once you got a sword you can attack with 'X' key";
	SetConsoleCursorPosition(gd.handle, { 5,19 });
	cout << "You are Hyrule's only hope Link";

	SetConsoleCursorPosition(gd.handle, { 5,25 });
	system("pause");
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

	if (gd.actualMap.name == MapNames::HyruleCastle && gd.player.position.y <= 19)
	{
		gd.playerHasWon = true;
		gd.scene = Scenes::GameOver;
		return;
	}

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
			else if (gd.mapOfTiles[y - 1][x].isCastleEntrance && gd.player.hasTriforce)
			{
				MapChange(gd, Directions::North);
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
		if (mapPrevFrame.name != gd.actualMap.name)
			gd.isArtPrinted = false;
	}
	gd.player.direction = gd.playerLastDirection;

	if (gd.masterSword.isFlying)
	{
		SwordUpdate(gd);
	}

	for (int i = 0; i < gd.MAX_ENEMIES; i++)
	{
		if (gd.enemies[i].position.x == gd.player.position.x && gd.enemies[i].position.y == gd.player.position.y && gd.player.canTakeDamage)
			gd.player.TakeDamage();
	}

	EnemyUpdate(gd);
	EnemyDraw(gd);
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
		PrintUpperBar(gd);
	}

	PrintPlayer(gd);
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
		system("cls");
		COORD coordinates;

		if (!gd.playerHasWon)
		{
			SetConsoleTextAttribute(gd.handle, 7);
			string gameOverText[7] = {
				R"( ######      ###    ##     ## ########  #######  ##     ## ######## ######## )",
				R"(##    ##    ## ##   ###   ### ##       ##     ## ##     ## ##       ##     ## )",
				R"(##         ##   ##  #### #### ##       ##     ## ##     ## ##       ##     ## )",
				R"(##   #### ##     ## ## ### ## ######   ##     ## ##     ## ######   ########  )",
				R"(##    ##  ######### ##     ## ##       ##     ##  ##   ##  ##       ##   ##   )",
				R"(##    ##  ##     ## ##     ## ##       ##     ##   ## ##   ##       ##    ##  )",
				R"( ######   ##     ## ##     ## ########  #######     ###    ######## ##     ## )"
			};
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
		else
		{
			string gameOverText[7] = {
				R"(######## ##     ## ########        ######## ##    ## ########  )",
				R"(	  ##    ##     ## ##              ##       ###   ## ##     ## )",
				R"(	  ##    ##     ## ##              ##       ####  ## ##     ## )",
				R"(   ##    ######### ######          ######   ## ## ## ##     ## )",
				R"(	  ##    ##     ## ##              ##       ##  #### ##     ## )",
				R"(	  ##    ##     ## ##              ##       ##   ### ##     ## )",
				R"(	  ##    ##     ## ########        ######## ##    ## ########  )"
			};

			coordinates.X = gd.width / 2 - (64 / 2);
			coordinates.Y = gd.height / 4;
			for (int i = 0; i < 7; i++)
			{
				SetConsoleTextAttribute(gd.handle, 4);
				SetConsoleCursorPosition(gd.handle, coordinates);
				cout << gameOverText[i];
				coordinates.Y++;
			}

			SetConsoleTextAttribute(gd.handle, 7);
			coordinates.X = gd.width / 2 - (19 / 2);
			coordinates.Y += 5;
			SetConsoleCursorPosition(gd.handle, coordinates);
			cout << "YOU   ARE   GREAT!";
			coordinates.Y += 5;
			coordinates.X = gd.width / 2 - (37 / 2);
			SetConsoleCursorPosition(gd.handle, coordinates);
			cout << "Press Any Key To Return To Main Menu";
			gd.isArtPrinted = true;
		}
	}
}

void EnemyUpdate(GameData& gd)
{
	int randomNum = 0;
	for (int i = 0; i < gd.actualEnemies; i++)
	{
		if (!gd.enemies[i].isAlive)
			gd.enemies[i] = gd.deadEnemy;

		if (gd.enemies[i].isActiveEnemy && gd.enemies[i].isAlive)
		{
			gd.enemies[i].hasChangedOnLastFrame = false;
			if (gd.enemies[i].stateChangeTime == 0)
			{
				gd.enemies[i].stateChangeTime = clock() + (rand() % 400 + 50);
			}

			if (clock() >= gd.enemies[i].stateChangeTime)
			{
				gd.enemies[i].stateChangeTime = 0;

				if (gd.enemies[i].enemyType == EnemyType::Spider)
				{
					randomNum = rand() % 2;
					gd.enemies[i].state = static_cast<EnemyStates>(randomNum);

					if (gd.enemies[i].state == EnemyStates::Move)
						static_cast<Spider&>(gd.enemies[i]).Move(gd.mapOfTiles);
				}
				else if (gd.enemies[i].enemyType == EnemyType::Octorok)
				{
					randomNum = rand() % 3;
					gd.enemies[i].state = static_cast<EnemyStates>(randomNum);
					switch (gd.enemies[i].state)
					{
					case EnemyStates::Move:
						static_cast<Octorok&>(gd.enemies[i]).qtyOfMoves = rand() % 3 + 1;
						gd.enemies[i].isMoving = true;
						gd.enemies[i].moveTimer = clock() + gd.enemies[i].moveCoolDown;
						break;
					case EnemyStates::Attack:
						if (!static_cast<Octorok&>(gd.enemies[i]).hasShooted)
						{
							static_cast<Octorok&>(gd.enemies[i]).Shoot(gd.mapOfTiles);
						}
						break;
					case EnemyStates::Rotate:
						if (clock() >= static_cast<Octorok&>(gd.enemies[i]).rotationTimer)
						{
							static_cast<Octorok&>(gd.enemies[i]).Rotate();
							static_cast<Octorok&>(gd.enemies[i]).rotationTimer = clock() + 150;
						}
						break;
					default:
						break;
					}
				}
			}
			if (gd.enemies[i].isMoving && clock() >= gd.enemies[i].moveTimer)
			{
				if (gd.enemies[i].enemyType == EnemyType::Octorok)
				{
					static_cast<Octorok&>(gd.enemies[i]).Move(gd.mapOfTiles);
					if (static_cast<Octorok&>(gd.enemies[i]).qtyOfMoves <= 0)
					{
						gd.enemies[i].isMoving = false;
						static_cast<Octorok&>(gd.enemies[i]).qtyOfMoves = 0;
					}
				}
				gd.enemies[i].moveTimer = clock() + gd.enemies[i].moveCoolDown;
			}
		}
		if (gd.enemies[i].enemyType == EnemyType::Octorok && static_cast<Octorok&>(gd.enemies[i]).hasShooted)
		{
			if (clock() >= gd.enemies[i].rock.moveTimer)
			{
				RockUpdate(gd.enemies[i].rock, gd.mapOfTiles, static_cast<Octorok&>(gd.enemies[i]).hasShooted);
				if (gd.player.position.x == gd.enemies[i].rock.position.x && gd.player.position.y == gd.enemies[i].rock.position.y)
					gd.player.TakeDamage();
				RockDraw(gd.enemies[i].rock, gd.actualMap.mapType, gd.handle);
				CleanTrail(gd.handle, gd.enemies[i].rock.previousPosition, gd.enemies[i].rock.moveCoolDown);
				gd.enemies[i].rock.moveTimer = clock() + gd.enemies[i].rock.moveCoolDown;
			}
		}
	}
}

void EnemyDraw(GameData& gd)
{
	if (gd.actualMap.mapType == MapType::OverWorld || gd.actualMap.mapType == MapType::Mountain)
		SetConsoleTextAttribute(gd.handle, 236);

	for (int i = 0; i < gd.actualEnemies; i++)
	{
		if (gd.enemies[i].isActiveEnemy && gd.enemies[i].isAlive && gd.enemies[i].hasChangedOnLastFrame)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.enemies[i].previousPosition.x),  static_cast<short>(gd.enemies[i].previousPosition.y) });
			cout << " ";
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.enemies[i].position.x),  static_cast<short>(gd.enemies[i].position.y) });
			if (gd.enemies[i].enemyType == EnemyType::Spider)
				cout << "M";
			else if (gd.enemies[i].enemyType == EnemyType::Octorok)
			{
				switch (static_cast<Octorok&>(gd.enemies[i]).dir)
				{
				case Directions::North:
					cout << "V";
					break;
				case Directions::East:
					cout << '<';
					break;
				case Directions::West:
					cout << ">";
					break;
				case Directions::South:
					cout << "A";
					break;
				}
			}
		}
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
		bool isBetweenBrackets = false;
		bool isBetweenBraces = false;
		for (int j = 0; j < mapWidth; j++)
		{
			gd.mapOfTiles[i + 4][j + 2].isItem = false;
			gd.mapOfTiles[i + 4][j + 2].isTriforceLogo = false;

			if (map.mapGraphic[i][j] == 91)
				isBetweenBrackets = true;
			if (map.mapGraphic[i][j] == 93)
				isBetweenBrackets = false;

			if (gd.actualMap.name == MapNames::CastleEntrance && map.mapGraphic[i][j] == 123)
				isBetweenBraces = true;
			if (gd.actualMap.name == MapNames::CastleEntrance && map.mapGraphic[i][j] == 125)
				isBetweenBraces = false;

			if (map.mapGraphic[i][j] != ' ')
			{
				gd.mapOfTiles[i + 4][j + 2].isCaveEntrance = false;
				gd.mapOfTiles[i + 4][j + 2].hasCollision = true;
			}
			else if (map.mapGraphic[i][j] == ' ' && isBetweenBrackets)
			{
				gd.mapOfTiles[i + 4][j + 2].hasCollision = true;
				gd.mapOfTiles[i + 4][j + 2].isCaveEntrance = true;
			}
			else if (map.mapGraphic[i][j] == ' ' && isBetweenBraces)
			{
				gd.mapOfTiles[i + 4][j + 2].hasCollision = true;
				gd.mapOfTiles[i + 4][j + 2].isCastleEntrance = true;
			}
			else
				gd.mapOfTiles[i + 4][j + 2].hasCollision = false;

			if (gd.actualMap.name == MapNames::Cave1)
			{
				if (map.mapGraphic[i][j] == '>' || map.mapGraphic[i][j] == '-')
					gd.mapOfTiles[i + 4][j + 2].isItem = true;
			}
			else if (gd.actualMap.name == MapNames::Cave2)
			{
				if (map.mapGraphic[i][j] == '_' || (map.mapGraphic[i][j] == 92 || map.mapGraphic[i][j] == '/') && i >= 12)
					gd.mapOfTiles[i + 4][j + 2].isItem = true;
			}
			else if (gd.actualMap.name == MapNames::FairysFountain)
			{
				if (i == 11 || i == 12)
				{
					if (j >= 15 && j <= 18)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
					else if (j >= 74 && j <= 77)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
				}
				else if (i == 13)
				{
					if (j == 16 || j == 17)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
					else if (j == 75 || j == 76)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
				}
				else if (i == 17 || i == 18)
				{
					if (j >= 45 && j <= 48)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
				}
				else if (i == 19)
				{
					if (j == 46 || j == 47)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
				}
			}
			else if (gd.actualMap.name == MapNames::CastleEntrance)
			{
				if (map.mapGraphic[i][j] == '_' || map.mapGraphic[i][j] == 92 || map.mapGraphic[i][j] == '/')
					gd.mapOfTiles[i + 4][j + 2].isTriforceLogo = true;
			}

			if (gd.mapOfTiles[i + 4][j + 2].hasCollision)
			{
				if (gd.mapOfTiles[i + 4][j + 2].isCaveEntrance)
					SetConsoleTextAttribute(gd.handle, 7);
				else if (gd.actualMap.name == MapNames::CastleEntrance && gd.mapOfTiles[i + 4][j + 2].isCastleEntrance)
				{
					if (gd.player.hasTriforce)
						SetConsoleTextAttribute(gd.handle, 7);
					else
						SetConsoleTextAttribute(gd.handle, 135);
				}
				else
				{
					if (map.mapType == MapType::OverWorld)
					{
						if (gd.actualMap.name == MapNames::WesternRiver && map.mapGraphic[i][j] == '.')
							SetConsoleTextAttribute(gd.handle, 27);
						else
							SetConsoleTextAttribute(gd.handle, 32);
					}
					else if (map.mapType == MapType::Cave)
						SetConsoleTextAttribute(gd.handle, 4);
					else if (map.mapType == MapType::Mountain)
					{
						if (gd.actualMap.name == MapNames::FairysFountain)
						{
							if (map.mapGraphic[i][j] == '.')
								SetConsoleTextAttribute(gd.handle, 27);
							else if (i == 10 && j == 46)
								SetConsoleTextAttribute(gd.handle, 22);
							else if (i == 11 && j >= 44 && j <= 48)
								SetConsoleTextAttribute(gd.handle, 22);
							else if (i == 12 && (j == 45 || j == 47))
								SetConsoleTextAttribute(gd.handle, 22);
							else
								SetConsoleTextAttribute(gd.handle, 6);
						}
						else
							SetConsoleTextAttribute(gd.handle, 6);
					}
					else if (map.mapType == MapType::CastleEntrance)
					{
						if (i < 10)
							SetConsoleTextAttribute(gd.handle, 135);
						else
							SetConsoleTextAttribute(gd.handle, 6);
					}
					else if (map.mapType == MapType::CastleEntrance)
						SetConsoleTextAttribute(gd.handle, 128);
				}
			}
			else
			{
				if (map.mapType == MapType::OverWorld || map.mapType == MapType::Mountain || map.mapType == MapType::CastleEntrance)
					SetConsoleTextAttribute(gd.handle, 238);
				else if (map.mapType == MapType::Cave)
					SetConsoleTextAttribute(gd.handle, 7);
				else if (map.mapType == MapType::CastleEntrance)
					SetConsoleTextAttribute(gd.handle, 128);
			}

			if (gd.mapOfTiles[i + 4][j + 2].isItem)
			{
				if (gd.actualMap.name == MapNames::Cave1)
					SetConsoleTextAttribute(gd.handle, 9);
				if (gd.actualMap.name == MapNames::Cave2)
					SetConsoleTextAttribute(gd.handle, 14);
				else if (gd.actualMap.name == MapNames::FairysFountain)
					SetConsoleTextAttribute(gd.handle, 192);
			}

			if (gd.mapOfTiles[i + 4][j + 2].isTriforceLogo)
			{
				if (gd.player.hasTriforce)
					SetConsoleTextAttribute(gd.handle, 142);
				else
					SetConsoleTextAttribute(gd.handle, 135);
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
	if (gd.actualMap.mapType == MapType::OverWorld || gd.actualMap.mapType == MapType::Mountain || gd.actualMap.mapType == MapType::CastleEntrance)
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

void ClearPreviousPlayerPos(GameData& gd)
{
	if (gd.actualMap.mapType == MapType::OverWorld || gd.actualMap.mapType == MapType::Mountain || gd.actualMap.mapType == MapType::CastleEntrance)
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
			R"(#%##@&                                                                            ##@&.###@.)",
			R"(.,#@,,                                                                             ##@.####@)",
			R"(#%##@&                                                                              #@.####@)",
			R"(.,#@,,                                                     &##&@                     &.&##&@)",
			R"(.###@%                                                      #&#,                     #&##%#,)",
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
			R"(#%.#&%#@/(@/#@((@*#@(#@*#@##@/#@##@(#@#(@##&#(&##*((&##.(%&#%.(&%#@,#@/(@((@*#@##@*#@##@/#@#)",
			R"(#@##(##@###&#@#/(@#&#.#@(/#.#&(.#,###.#*((&,#(##@(##(#@###(#@#####@#(#&#@#/#@#@#.#@(/#.#&(.()",
			R"(./,@.%&#(@.*,#&@..*#@@(.##%@&*##*&@&/(.(@@,(..@&.,*.@#..%.@.*.@.&.#*@.*.#%@../#@@/.##&@&/##()",
			R"(#%##.%#@##.*#@##..#&##(.#/#(&,#.#(@(#.#*@[     ]#/#.@####.@#%##.&#@##.*#@##..#@#((.#/##&*#.#)",
			R"(@##@#%@#%@#*&#%##.(#%.#..#&.#,.(@,((,(@/#[     ]#(@#@%#(@#@@##@#&@##&#*&#%%#.*#%,#..#&.#*.#@)",
			R"(#&,###.@#@#,                                         #@##,#.%#@#&                  (/#@#/#&#)",
			R"(#@@@#@&@&                                              @@@#.%#                      (@@,/@.#)",
			R"(###@#@             ##          (@                                       ##              *###)",
			R"(#%#,              #&((&       #,&#@                                    #@(##             ,##)",
			R"(%#                %%%@&#     ,%%#@@,                                   #%%%@%              @)",
			R"(#%                                                                                         #)",
			R"(%#                                                                                         #)",
			R"(#%                *###(      ,(@##                                     ,((#&               @)",
			R"(%#                #&##%       #,&#@                                    #@#&(               #)",
			R"(#%                                                                                         #)",
			R"(%#                                                                                         @)",
			R"(#%                                                                                         #)",
			R"(###               *%#(&      ,#,##@                                     &(##               ()",
			R"(##&##%            #&##@      ,#(##&                                    #@(%@             #(#)",
			R"((&.#%#.(                                                ##@,(                         (#*#@#)",
			R"((@######(##                                           #(#####@(#                   #%@##*(.#)",
			R"((/&#*##.(#.#,@    *@    #@    #@    #&               #@@#%###@#*(&      @    /@    ##,@&#(@*)",
			R"(#&##/%#@##/*(#(##@#(/##@##*##&#(,##%#(.##            ####/@#%##/&##&##@##(##@##/##@#/#*%*#.#)",
			R"(%%,.(&%#%@(/#(%(%@##%&#@###&#&##*&#%(%,&#            ###@(@%##@#&(#@*%@##%/%@(#%%#@,#&*%/,#@)",
			R"(#&#####@###&#@###@#%##%@#/##&%#.##@,#.##&            *####((%#####@###&#@###@#@##%@#/##@&,,#)"
			};
			maps[i].mapType = MapType::OverWorld;
			break;
		case MapNames::Cave1:
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
			R"(%&@%%%%@%%%%                  Take           The         Triforce,               %@%@%@%@%@%)",
			R"(%&@%@@%@@%@%    It'll   allow   you   to   save   Zelda   at   Hyrule  Castle    %@@@@%%@@@@)",
			R"(%%@%&&%%%%&@                                  A                                  %@%&&@%@%&&)",
			R"(%&%@%&%%%@%@            #$                   MMM                     #$          @%@@%@@%@@&)",
			R"(@%@%%@@%%%%%           &%&%                  / \                    &%&%         %@%%&@%@%%@)",
			R"(@@@%%&@@@&%@            #$                                           #$          &@@@%@@@@@%)",
			R"(%%@%%@%%@%%%                                 /\                                  %@%%@@%@%%@)",
			R"(%&@%%%%@%%%%                                /__\                                 %@%@%@%@%@%)",
			R"(%&@%@@%@@%@%                               /\  /\                                %@@@@%%@@@@)",
			R"(%%@%&&%%%%&@                              /__\/__\                               %@%&&@%@%&&)",
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
			break;
		case MapNames::FairysFountain:
			maps[i].name = MapNames::FairysFountain;
			maps[i].mapGraphic = new string[25]
			{
				R"((/(#@(#,(#@(#%(%@(%%(%&(%,(&%(&,(&#(&*(@((@*(@/(@/(@*(@((@,(@((@%(@((@%(@((@,(@((@*(@((@*(@()",
				R"(@/((#(@(((#(@(((#(@(((#(@(((%(@(((%(@(((%(@(/(%(@(/(%(&(*(%(%(*(&(#(,(%(((@(%(/(@(%#*(@(##,()",
				R"(*/%*@(**%*@//*&*@*/*&*@,//@*&*(/@*&@((@*%,(#@*%,(#@*#*(%@/(*(%@((/(&@#(((%@%(((%@%#((#@&#((#)",
				R"((/(/%(#((/%(#((/%(%((/%(%((/%(&((/%(@((/%(@((/%(@((/%(&((/%(%(((%(#(((%((((##(/((##(*((##(,()",
				R"(((@(&%((@(@&((@(@&((@(&@((@(%@(#@(#@(#&((&(#%(/%(##(*#(#((,((#/(@/(#*(@*(%,(,@(%@(*@(%@(*,(&)",
				R"((/((#@#(@(@                                                                       *#/(&(/(@()",
				R"(@##(%(#((                                                                           %&@*/&,()",
				R"(&%(&&                           ...............................                         *#@/)",
				R"(#/((&                         ..................................                        *#,()",
				R"(((@(@                        ...................................                        *((&)",
				R"((/((#                        .................O.................                        *(,()",
				R"(*#&(@          /\/\          ...............\\W//...............          /\/\          ,(*%)",
				R"((/(##          \  /          ................/.\................          \  /          ,(@()",
				R"(@/((#           \/           ...................................           \/           *#,()",
				R"(&&(&%                        ...................................                        *#&/)",
				R"((/(/@                        ...................................                        *(,()",
				R"(((@(@                         ..................................                        **(@)",
				R"((/((#                                        /\/\                                       *(,()",
				R"(,%%(&                                        \  /                                       *&&%)",
				R"((/(#%@#,                                      \/                                     ,(#*(@()",
				R"(@/(((((@%(,                                                                        *#&((*#,()",
				R"(*//*@(@#(@*                                                                        (#&@#((#/)",
				R"((/(@@(#((@@*(@/((/(@/(#((@((#((@((%((@((%            ((@((@((@((@((@((&((&((%((%((&(*((&*(,()",
				R"(((@(@%((@(@#(@,&(#(@,%##(@,%#((@,#%((@*#%            ((@((@((@#(@((@%(@((&&(@((%@(&@(@@(*,(@)",
				R"((/((#*#/((#*#*(((/%/((#(%/((#(&/((%(&/((%            (@((#@(&((%@(&((%&(%((&%(#((&#(#((@(((()"
			};
			maps[i].mapType = MapType::Mountain;
			break;
		case MapNames::CastleEntrance:
			maps[i].name = MapNames::CastleEntrance;
			maps[i].mapGraphic = new string[25]{
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@##@####/\@#*@#*##@#*##@#*##@#*##@#*##@##@#*##@#*##*#)",
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&#/__\&#&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@##@##/\--/\#@#*##@#*##@#*##@#*##@#*##@##@#*##@#*##*#)",
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&#/__\/__\&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@##@#*##@#*##*#)",
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@#{            }%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#{            }##@#*##@#*##@#*##@#*##@##@#*##@#*##*#)",
			R"(#@##(#@##&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@#{            }%#&%&%#&%&%#&%&%#&%&%#@##(#@##&#&%%&%)",
			R"(##@#@#&*#@#*##@#*##@#*##@#*##@#*##@#*###@{            }##@#*##@#*##@#*##@#*###@#@#&*#@#*##*#)",
			R"(                                                                                  ##@####@##)",
			R"(                                                                                  #&%&%#&%&%)",
			R"(                                                                                  #@#*##@#*#)",
			R"(                                                                                  #&%&%#&%&%)",
			R"(                                                                                  #@#*##@#*#)",
			R"(                                                                                  #&%&%#&%&%)",
			R"(##@#####%@                                                                        ##@####@##)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&.%     %     %     %     %     %     %     %     %     %     %     %    #&%&%#&%&%)",
			R"(#@#*##@#*###@####@####@####@####@####@####@####@####@####@####@####@###@#*##@#*#@#@####@####)",
			R"(#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&%#&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%@##&#&&#&#&&)",
			R"(#@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*#@#*##@#*##@#)"
			};
			maps[i].mapType = MapType::CastleEntrance;
			break;
		case MapNames::HyruleCastle:
			maps[i].name = MapNames::HyruleCastle;
			maps[i].mapGraphic = new string[25]{
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&&%#&#&%#&&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@##@###/\@#*@@#*##@#*##@#*##@#*##@#*##@##@#*##@#*##*#)",
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&&#/__\&#&&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@##@#/\--/\#@@#*##@#*##@#*##@#*##@#*##@##@#*##@#*##*#)",
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&/__\/__\&&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@                                                                        *##@#*##*#)",
			R"(#@##&#&%#&         Thanks  for  opening  the  gate  Link  You  saved  me!         &%#&#&%%&%)",
			R"(#@##@#*##@                                                                        *##@#*##*#)",
			R"(##@#####%@                                                                        @##&#&%%&%)",
			R"(#&#&&#&#&&                                    A                                   &*#@#*##*#)",
			R"(#@#*##@#*#                                   ZZZ                                  ##@####@##)",
			R"(#&#&&#&#&&                                   / \                                  #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        ##@####@##)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*###@####@####@####@####@####@####          #####@####@####@###@#*##@#*#@#@####@####)",
			R"(#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&##          &&%#&#&%#&%&%#&%&%#&%&%#&%&%@##&#&&#&#&&)",
			R"(#@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*###          @@##@#*##@#*##@#*##@#*##@#*#@#*##@#*##@#)"
			};
			maps[i].mapType = MapType::Castle;
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
	case MapNames::FairysFountain:
		if (dir == Directions::South)
		{
			gd.actualMap = gd.previousMap;
			gd.player.position = gd.storedPosition;
		}
		break;
	case MapNames::Mountain1:
		for (int i = 0; i < gd.MAX_ENEMIES; i++)
		{
			gd.enemies[i].isActiveEnemy = false;
			gd.enemies[i].isAlive = false;
		}

		if (dir == Directions::West)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::StartValley)];
			gd.player.position = { 93, 17 };
		}
		else if (dir == Directions::East)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::CastleEntrance)];
			gd.player.position = { 2, 17 };
		}
		break;
	case MapNames::WesternRiver:
		if (dir == Directions::East)
		{
			gd.player.position = { 2, 17 };
			gd.actualMap = gd.maps[static_cast<int>(MapNames::StartValley)];
		}
		else if (dir == Directions::North)
		{
			gd.previousMap = gd.actualMap;
			gd.storedPosition = gd.player.position;
			gd.actualMap = gd.maps[static_cast<int>(MapNames::FairysFountain)];
			gd.player.position = { 45, 28 };
		}
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
		break;
	case MapNames::CastleEntrance:
		if (dir == Directions::West)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::Mountain1)];
			gd.player.position = { 93, 17 };
		}
		else if (dir == Directions::North)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::HyruleCastle)];
			gd.player.position = { 48, 28 };
		}
		break;
	default:
		break;
	}

	for (int i = 0; i < gd.actualEnemies; i++)
	{
		gd.enemies[i] = gd.deadEnemy;
	}

	switch (gd.actualMap.name)
	{
	case MapNames::Mountain1:
	case MapNames::HyruleField:
	case MapNames::WesternRiver:
	case MapNames::KokiriForest:
	{
		int counter = 0;

		const int spidersQty = 5;
		Enemy spider[spidersQty];
		for (int i = 0; i < spidersQty; i++)
		{
			spider[i].HealthPoints = 1;
			spider[i].isActiveEnemy = true;
			spider[i].enemyType = EnemyType::Spider;
			spider[i].isAlive = true;

			switch (i)
			{
			case 0:
				spider[i].position = { 14, 20 };
				break;
			case 1:
				if (gd.actualMap.name == MapNames::Mountain1)
					spider[i].position = { 45, 12 };
				else
					spider[i].position = { 15, 12 };
				break;
			case 2:
				spider[i].position = { 76, 14 };
				break;
			case 3:
				spider[i].position = { 65, 23 };
				break;
			case 4:
				spider[i].position = { 80, 22 };
				break;
			default:
				break;
			}
			spider[i].previousPosition = spider[i].position;
			gd.enemies[counter] = spider[i];
			counter++;
		}

		Octorok octorok;
		octorok.HealthPoints = 1;
		octorok.isActiveEnemy = true;
		octorok.enemyType = EnemyType::Octorok;
		octorok.isAlive = true;

		if (gd.actualMap.name == MapNames::Mountain1)
			octorok.position = { 5, 20 };
		else if (gd.actualMap.name == MapNames::HyruleField)
			octorok.position = { 60, 20 };
		else
			octorok.position = { 80, 12 };


		octorok.previousPosition = octorok.position;
		gd.enemies[counter] = octorok;

		gd.actualEnemies = spidersQty + 1;
	}
	break;
	default:
		break;
	}

}
void MapChange(GameData& gd, bool isCave)
{
	for (int i = 0; i < gd.actualEnemies; i++)
	{
		gd.enemies[i] = gd.deadEnemy;
	}

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
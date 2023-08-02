#include "Game.h"

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
	SetConsoleCursorPosition(gd.handle, { 5,3 });
	cout << "Princess Zelda was kidnapped at Hyrule Castle, you have to rescue her!!";
	SetConsoleCursorPosition(gd.handle, { 5,8 });
	cout << "Your character is the blue letter C, the little point shows you where you are looking at";
	SetConsoleCursorPosition(gd.handle, { 5,14 });
	cout << "Use WASD keys to move, once you got a sword you can attack with 'X' key";
	SetConsoleCursorPosition(gd.handle, { 5,19 });
	cout << "You are Hyrule's only hope Link";

	SetConsoleCursorPosition(gd.handle, { 5,24 });
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
		gd.playerHasWon = false;
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
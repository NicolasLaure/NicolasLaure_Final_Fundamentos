#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Player.h"
using namespace std;

enum class Scenes
{
	Menu,
	Game,
	GameOver,
	Credits,
	End
};

enum class MapType
{
	OverWorld,
	Mountain,
	Cave,
	Counter
};
struct TileMap
{
	bool hasCollision;
	bool isCaveEntrance;
	bool isEndOfMap;
	bool isItem;
};

enum class MapNames
{
	StartValley,
	WesternRiver,
	HyruleField,
	KokiriForest,
	Cave1,
	Cave2,
	Mountain1,
	Count
};
struct Map
{
	MapNames name;
	string* mapGraphic;
	bool isCaveItemTaken = false;
	MapType mapType;
};
struct GameData
{
	// Global Variables
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	Scenes scene = Scenes::Menu;
	Scenes prevScene;
	const int ConsoleFontSize = 30;

	bool enteredNewScene = false;
	bool isArtPrinted = false;

	//int mapToPrint = 0;
	Player player;
	const static int MAPS_QUANTITY = static_cast<int>(MapNames::Count);
	const int MAP_SIZE = 25;
	//Map Size = [25][93] added 4 and 2 to make the offset
	TileMap mapOfTiles[32][97];

	Map maps[MAPS_QUANTITY];
	Map actualMap;
	Map previousMap;

	int width;
	int height;

	// Game
	bool isMenuFirstPhase = true;
	bool firstScreen = true;

	int playerLivesPrevFrame;

	const static int MAX_ENEMIES = 10;
	Enemy deadEnemy = {};
	Enemy enemies[MAX_ENEMIES];
	
	Directions playerLastDirection;
	Vector2 storedPosition;
};

void Play();
void GameLoop(GameData& gd);

void Menu(GameData& gd);
void MenuStart(GameData& gd);
void MenuUpdate(GameData& gd);
void MenuDraw(GameData& gd);

void Game(GameData& gd);
void GameStart(GameData& gd);
void GameUpdate(GameData& gd);
void GameDraw(GameData& gd);
void GameOver(GameData& gd);
void GameOverStart(GameData& gd);
void GameOverUpdate(GameData& gd);
void GameOverDraw(GameData& gd);

//utilities
void Initialize(GameData gd);
void SetConsoleFontSize(int size);
void PrintMap(GameData& gd, Map map, int MAP_HEIGHT);
void PrintUpperBar(GameData gd);
void CleanUpperBar(GameData gd);
void PrintPlayer(GameData& gd);
void PrintEnemies(GameData& gd);

void ClearPreviousPlayerPos(GameData& gd);
void MapsSetup(GameData& gd, Map maps[], int mapQty, int mapSize);
void MapChange(GameData& gd, Directions dir);
void MapChange(GameData& gd, bool isCave);

//PlayerFunctions
void PlayerAttack(GameData& gd);
void PlayerParry(GameData& gd);
void TakeItem(GameData& gd);
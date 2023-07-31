#pragma once
#include "Enemies.h"
#include "Player.h"

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
	Sword masterSword;
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
	bool playerHasWon = false;
	bool isMenuFirstPhase = true;
	bool firstScreen = true;

	int playerLivesPrevFrame;

	const static int MAX_ENEMIES = 10;
	Enemy deadEnemy;
	Enemy enemies[MAX_ENEMIES];
	int actualEnemies;
	Directions playerLastDirection;
	Vector2 storedPosition;
};
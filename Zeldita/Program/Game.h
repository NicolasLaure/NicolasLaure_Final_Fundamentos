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
};

enum class MapNames
{
	OverWorld1,
	Cave1,
	Mountain1
};
struct Map
{
	MapNames name;
	string* mapGraphic;
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
	const static int MAPS_QUANTITY = 4;
	const int MAP_SIZE = 25;
	//Map Size = [25][93] added 4 and 2 to make the offset
	TileMap mapOfTiles[32][97];

	Map maps[MAPS_QUANTITY];
	Map actualMap;
	
	// Game
	bool isMenuFirstPhase = true;
	bool firstScreen = true;

	Vector2 storedPosition;
};



void Play();
void GameLoop(GameData& gd);


void Menu(GameData& gd);
void MenuStart();
void MenuUpdate(GameData& gd);
void MenuDraw(GameData& gd);

void Game(GameData& gd);
void GameStart(GameData& gd);
void GameUpdate(GameData& gd);
void GameDraw(GameData& gd);


//utilities
void Initialize(GameData gd);
void SetConsoleFontSize(int size);
void PrintMap(GameData& gd, Map map, int MAP_HEIGHT);
void PrintUpperBar(GameData gd);
void PrintPlayer(GameData& gd);
void ClearPreviousPlayerPos(GameData& gd);
void MapsSetup(Map maps[], int mapQty, int mapSize);
void MapChange(GameData& gd, Directions dir);
void MapChange(GameData& gd, bool isCave);

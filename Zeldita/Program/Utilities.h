#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

enum class Directions
{
	North,
	East,
	West,
	South,
};

enum class MapType
{
	OverWorld,
	Mountain,
	Cave,
	Counter
};
struct Vector2
{
	int x;
	int y;
};

enum class Scenes
{
	Menu,
	Game,
	GameOver,
	Credits,
	End
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
	MapNames name{};
	string* mapGraphic{};
	bool isCaveItemTaken = false;
	MapType mapType{};
};
void CleanTrail(HANDLE handle, Vector2 attackedPosition, float timeToMove);

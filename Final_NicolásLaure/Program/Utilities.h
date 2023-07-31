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
	Castle,
	CastleEntrance,
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
	GameQuit
};

struct TileMap
{
	bool hasCollision;
	bool isCaveEntrance;
	bool isCastleEntrance;
	bool isEndOfMap;
	bool isItem;
	bool isTriforceLogo;
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
	FairysFountain,
	CastleEntrance,
	HyruleCastle,
	Count
};

struct Map
{
	MapNames name{};
	string* mapGraphic{};
	bool isCaveItemTaken = false;
	MapType mapType{};
};

struct Item
{
	Vector2 position{};
};

void CleanTrail(HANDLE handle, Vector2 attackedPosition, float timeToMove);

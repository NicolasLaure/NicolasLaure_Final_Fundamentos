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

void CleanTrail(HANDLE handle, Vector2 attackedPosition);

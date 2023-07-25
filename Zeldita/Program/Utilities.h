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

struct Vector2
{
	int x;
	int y;
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
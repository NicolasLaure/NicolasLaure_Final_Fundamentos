#pragma once
#include "GameData.h"

void PrintMap(GameData& gd, Map map, int MAP_HEIGHT);
void MapsSetup(GameData& gd, Map maps[], int mapQty, int mapSize);
void MapChange(GameData& gd, Directions dir);
void MapChange(GameData& gd, bool isCave);
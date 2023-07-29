#pragma once
#include "GameData.h"

void RockDraw(Rock rock, MapType mapType, HANDLE handle);
void RockUpdate(Rock& rock, TileMap mapOfTiles[32][97], bool& hasShooted);
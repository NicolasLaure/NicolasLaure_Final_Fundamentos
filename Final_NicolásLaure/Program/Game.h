#pragma once
#include "PlayerUtilities.h"
#include "EnemyUtilities.h"

void Play();
void GameLoop(GameData& gd);

void Menu(GameData& gd);
void MenuStart(GameData& gd);
void MenuUpdate(GameData& gd);
void MenuDraw(GameData& gd);
void Rules(GameData& gd);

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

void ClearPreviousPlayerPos(GameData& gd);
void MapsSetup(GameData& gd, Map maps[], int mapQty, int mapSize);
void MapChange(GameData& gd, Directions dir);
void MapChange(GameData& gd, bool isCave);


//void TakeItem(GameData& gd);

void EnemyUpdate(GameData& gd);
void EnemyDraw(GameData& gd);


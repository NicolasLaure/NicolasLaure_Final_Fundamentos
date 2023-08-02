#pragma once
#include "PlayerUtilities.h"
#include "EnemyUtilities.h"
#include "MapHandler.h"

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
void EnemyUpdate(GameData& gd);
void EnemyDraw(GameData& gd);

//utilities
void Initialize(GameData gd);
void SetConsoleFontSize(int size);
void PrintUpperBar(GameData gd);
void CleanUpperBar(GameData gd);
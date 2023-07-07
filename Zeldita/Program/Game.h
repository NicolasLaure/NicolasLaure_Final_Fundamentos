#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

enum class Scenes
{
	Menu,
	Game,
	Credits,
	End
};

struct GameData
{
	// Global Variables
	Scenes scene = Scenes::Menu;
	Scenes prevScene;
	const int ConsoleFontSize = 30;

	bool enteredNewScene = false;
	// Game
	bool isMenuFirstPhase = true;
};

void Play();
void GameLoop(GameData& gd);


void Menu(GameData& gd);
void MenuStart();
void MenuUpdate(GameData& gd);
void MenuDraw(GameData gd);

void Game(GameData& gd);
void GameStart();
void GameUpdate();
void GameDraw();


//utilities
void SetConsoleFontSize(int size);

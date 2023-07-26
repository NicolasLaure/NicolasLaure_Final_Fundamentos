#pragma once
#include "Player.h"
enum class Scenes
{
	Menu,
	Game,
	GameOver,
	Credits,
	End
};

struct Map
{
	MapNames name{};
	string* mapGraphic{};
	bool isCaveItemTaken = false;
	MapType mapType{};
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
	Sword masterSword;
	const static int MAPS_QUANTITY = static_cast<int>(MapNames::Count);
	const int MAP_SIZE = 25;
	//Map Size = [25][93] added 4 and 2 to make the offset
	TileMap mapOfTiles[32][97];

	Map maps[MAPS_QUANTITY];
	Map actualMap;
	Map previousMap;

	int width;
	int height;

	// Game
	bool isMenuFirstPhase = true;
	bool firstScreen = true;

	int playerLivesPrevFrame;

	const static int MAX_ENEMIES = 10;
	Enemy deadEnemy;
	Enemy enemies[MAX_ENEMIES];
	
	Directions playerLastDirection;
	Vector2 storedPosition;
};

void Play();
void GameLoop(GameData& gd);

void Menu(GameData& gd);
void MenuStart(GameData& gd);
void MenuUpdate(GameData& gd);
void MenuDraw(GameData& gd);

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

//PlayerFunctions
void PlayerAttack(GameData& gd);
void SwordUpdate(GameData& gd);

void PlayerParry(GameData& gd);
void TakeItem(GameData& gd);
void RangedAttackExplosion(GameData& gd, Vector2 lastAttackedPosition);
void CleanExplosion(GameData& gd, Vector2 lastAttackedPosition);
bool isEnemyHitted(GameData& gd, Vector2 attackedPosition);

void EnemyUpdate(GameData& gd);
void EnemyDraw(GameData& gd);


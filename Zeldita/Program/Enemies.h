#pragma once
#include "Utilities.h"
enum class EnemyStates
{
	Move,
	Attack,
	Rotate,
	Idle,
	Count
};

struct Rock
{
	Directions direction{};
	Vector2 position{};
	Vector2 previousPosition{};
	bool isFlying{ false };

	int moveTimer{};
	int moveCoolDown{ 30 };
	void RockUpdate(TileMap mapOfTiles[32][97], MapType mapType, HANDLE handle)
	{

		previousPosition = position;
		switch (direction)
		{
		case Directions::North:
			position.y--;
			break;
		case Directions::South:
			position.y++;
			break;
		case Directions::East:
			position.x++;
			break;
		case Directions::West:
			position.x--;
			break;
		}
		if (!mapOfTiles[position.y][position.x].hasCollision)
		{
			RockDraw(mapType, handle);
			CleanTrail(handle, previousPosition);
		}
		else
			isFlying = false;
	}
	void RockDraw(MapType mapType, HANDLE handle)
	{
		if (mapType == MapType::OverWorld || mapType == MapType::Mountain)
			SetConsoleTextAttribute(handle, 236);
		else
			SetConsoleTextAttribute(handle, 12);

		SetConsoleCursorPosition(handle, { static_cast<short>(position.x), static_cast<short>(position.y) });
		cout << "O";
	}
};

enum class EnemyType
{
	Octorok,
	Spider,
	Boss
};
struct Enemy
{
	int HealthPoints{};
	bool isAlive{ false };
	Vector2 position{};
	Vector2 previousPosition{};
	bool isActiveEnemy{ false };
	bool isMoving{ false };
	int moveCoolDown{ 80 };
	int moveTimer{};
	bool hasChangedOnLastFrame{ false };
	EnemyType enemyType{ EnemyType::Spider };
	EnemyStates state{ EnemyStates::Idle };
	int stateChangeTime{};
	int timer{ 0 };
	void TakeDamage(int damage)
	{
		HealthPoints -= damage;
		if (HealthPoints <= 0)
			isAlive = false;
	}

};
struct Octorok : Enemy
{

	Directions dir{ Directions::North };
	int rotationCoolDown{ 250 };
	int rotationTimer{};
	int qtyOfMoves{ 0 };
	Rock rock;

	void Move(TileMap mapOfTiles[32][97])
	{
		previousPosition = position;
		switch (dir)
		{
		case Directions::North:
			if (!mapOfTiles[position.y - 1][position.x].hasCollision)
				position.y--;
			else
				qtyOfMoves = 0;
			break;
		case Directions::South:
			if (!mapOfTiles[position.y + 1][position.x].hasCollision)
				position.y++;
			else
				qtyOfMoves = 0;
			break;
		case Directions::West:
			if (!mapOfTiles[position.y][position.x - 1].hasCollision)
				position.x--;
			else
				qtyOfMoves = 0;
			break;
		case Directions::East:
			if (!mapOfTiles[position.y][position.x + 1].hasCollision)
				position.x++;
			else
				qtyOfMoves = 0;
			break;
		default:
			break;
		}
		hasChangedOnLastFrame = true;
	}
	void Rotate()
	{
		int newDir = rand() % 4;
		dir = static_cast<Directions>(newDir);
		hasChangedOnLastFrame = true;
		rotationTimer = clock() + rotationCoolDown;
	}
	void Shoot()
	{
		rock.direction = dir;
		switch (dir)
		{
		case Directions::North:
			rock.position = { position.x, position.y - 1 };
			break;
		case Directions::East:
			rock.position = { position.x + 1, position.y };
			break;
		case Directions::West:
			rock.position = { position.x - 1, position.y };
			break;
		case Directions::South:
			rock.position = { position.x, position.y + 1 };
			break;
		default:
			break;
		}
		rock.moveTimer = clock() + rock.moveCoolDown;
		//rock.position = position;
		rock.isFlying = true;
	}


};

struct Spider : Enemy
{
	Vector2 newPos{};
	void Move(TileMap mapOfTiles[32][97])
	{
		previousPosition = position;
		newPos = { (rand() % 5) - 2, (rand() % 5) - 2 };
		if (!mapOfTiles[position.y + newPos.y][position.x + newPos.x].hasCollision)
		{
			position.x += newPos.x;
			position.y += newPos.y;
		}
		hasChangedOnLastFrame = true;
	}
};

//void RockUpdate(Rock& rock, TileMap mapOfTiles[32][97], MapType mapType, HANDLE handle);
//void RockDraw(Rock& rock, MapType mapType, HANDLE handle);

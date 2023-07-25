#pragma once
#include "Utilities.h"
enum class EnemyStates
{
	Move,
	Idle,
	Attack,
	Rotate,
	Count
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
	EnemyType enemyType{};
	EnemyStates state{ EnemyStates::Idle };
	int stateChangeTime{ 0 };
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
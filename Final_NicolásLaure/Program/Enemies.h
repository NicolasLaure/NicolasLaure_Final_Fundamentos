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
	Vector2 position{ 0,0 };
	Vector2 previousPosition{ 0,0 };
	bool isFlying{ false };

	int moveTimer{};
	int moveCoolDown{ 40 };
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
	Vector2 newPos{};
	Vector2 previousPosition{};
	bool isActiveEnemy{ false };
	bool isMoving{ false };
	int moveCoolDown{ 80 };
	int moveTimer{};
	bool hasChangedOnLastFrame{ true };
	EnemyType enemyType{ EnemyType::Spider };
	EnemyStates state{ EnemyStates::Idle };
	int stateChangeTime{};
	int timer{ 0 };

	//octorok
	int rotationCoolDown{ 150 };
	Rock rock{};
	Directions dir{ Directions::North };
	int rotationTimer = 0;
	int qtyOfMoves{ 0 };
	bool hasShooted{ false };

	void TakeDamage(int damage)
	{
		HealthPoints -= damage;
		if (HealthPoints <= 0)
			isAlive = false;
	}
};
struct Octorok : Enemy
{
	void Move(TileMap mapOfTiles[32][97])
	{
		previousPosition = position;
		switch (dir)
		{
		case Directions::North:
			if (!mapOfTiles[position.y - 1][position.x].hasCollision)
			{
				position.y--;
				qtyOfMoves--;
			}
			else
			{
				qtyOfMoves = 0;
				isMoving = false;
			}
			break;
		case Directions::South:
			if (!mapOfTiles[position.y + 1][position.x].hasCollision)
			{
				position.y++;
				qtyOfMoves--;
			}
			else
			{
				qtyOfMoves = 0;
				isMoving = false;
			}
			break;
		case Directions::West:
			if (!mapOfTiles[position.y][position.x - 1].hasCollision)
			{
				position.x--;
				qtyOfMoves--;
			}
			else
			{
				qtyOfMoves = 0;
				isMoving = false;
			}
			break;
		case Directions::East:
			if (!mapOfTiles[position.y][position.x + 1].hasCollision)
			{
				position.x++;
				qtyOfMoves--;
			}
			else
			{
				qtyOfMoves = 0;
				isMoving = false;
			}
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
	}
	void Shoot(TileMap mapOfTiles[32][97])
	{
		hasChangedOnLastFrame = true;
		hasShooted = true;
		rock.direction = dir;
		switch (dir)
		{
		case Directions::North:
			if (!mapOfTiles[position.y - 1][position.x].hasCollision)
			{
				rock.position = { position.x, position.y - 1 };
				rock.moveTimer = clock() + rock.moveCoolDown;
				rock.isFlying = true;
			}
			break;
		case Directions::South:
			if (!mapOfTiles[position.y + 1][position.x].hasCollision)
			{
				rock.position = { position.x, position.y + 1 };
				rock.moveTimer = clock() + rock.moveCoolDown;
				rock.isFlying = true;
			}
			break;
		case Directions::East:
			if (!mapOfTiles[position.y][position.x + 1].hasCollision)
			{
				rock.position = { position.x + 1, position.y };
				rock.moveTimer = clock() + rock.moveCoolDown;
				rock.isFlying = true;
			}
			break;
		case Directions::West:
			if (!mapOfTiles[position.y][position.x - 1].hasCollision)
			{
				rock.position = { position.x - 1, position.y };
				rock.moveTimer = clock() + rock.moveCoolDown;
				rock.isFlying = true;
			}
			break;
		}
	}
};

struct Spider : Enemy
{
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


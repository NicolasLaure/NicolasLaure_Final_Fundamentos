#pragma once
#include "Utilities.h"

struct Enemy
{
	char graphic;
	int HealthPoints{};
	bool isAlive{};
	Vector2 position;
	bool isActiveEnemy{};
	
	void TakeDamage(int damage)
	{
		HealthPoints -= damage;
		if (HealthPoints <= 0)
			isAlive = false;
	}
};
struct Octorok : Enemy
{
	void Move()
	{

	}
	void Shoot()
	{

	}
};

struct Spider : Enemy
{
	void Move()
	{

	}
};
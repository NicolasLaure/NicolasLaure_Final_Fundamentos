#pragma once
#include "Enemies.h"

struct Player
{
	int maxHealthPoints = 3;
	int healthPoints = 3;
	char graphic = 'C';
	int attackDamage = 1;
	bool hasSword{ false };
	bool hasShield{ false };
	bool isAlive{ true };
	bool canTakeDamage{ true };
	int receiveDamageCoolDown{1500};
	int timer = 0;
	Directions direction{};
	Vector2 position{};

	void TakeDamage()
	{
		healthPoints--;
		canTakeDamage = false;
		if (healthPoints <= 0)
			isAlive = false;
		timer = clock() + receiveDamageCoolDown;
	}
};
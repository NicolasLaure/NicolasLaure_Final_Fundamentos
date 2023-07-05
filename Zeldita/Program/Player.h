#pragma once

enum class Directions {
	North,
	East,
	West,
	South
};

struct Vector2 {
	int x;
	int y;
};

struct player
{
	char graphic = 'C';
	Directions direction{};
	Vector2 position{};
	int HealthPoints;
};
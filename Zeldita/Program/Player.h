#pragma once

enum class Directions
{
	North,
	East,
	West,
	South
};

struct Vector2
{
	int x;
	int y;
};

struct Player
{
	int HealthPoints;
	char graphic = 'C';
	Directions direction{};
	Vector2 position{};
};
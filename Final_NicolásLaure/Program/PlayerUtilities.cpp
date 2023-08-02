#include "PlayerUtilities.h"

void PlayerAttack(GameData& gd)
{
	if (gd.actualMap.mapType == MapType::OverWorld || gd.actualMap.mapType == MapType::Mountain || gd.actualMap.mapType == MapType::CastleEntrance)
		SetConsoleTextAttribute(gd.handle, 233);
	else
		SetConsoleTextAttribute(gd.handle, 9);

	Vector2 attackedPosition = { 0,0 };
	if (gd.player.healthPoints == gd.player.maxHealthPoints && !gd.masterSword.isFlying)
	{
		gd.masterSword.direction = gd.player.direction;
		gd.masterSword.position = gd.player.position;
		gd.masterSword.isFlying = true;
	}
	else if (gd.player.healthPoints != gd.player.maxHealthPoints)
	{
		switch (gd.player.direction)
		{
		case Directions::North:
			attackedPosition = { gd.player.position.x , gd.player.position.y - 1 };
			break;
		case Directions::South:
			attackedPosition = { gd.player.position.x , gd.player.position.y + 1 };
			break;
		case Directions::East:
			attackedPosition = { gd.player.position.x + 1 , gd.player.position.y };
			break;
		case Directions::West:
			attackedPosition = { gd.player.position.x - 1 , gd.player.position.y };
			break;
		}
		SetConsoleCursorPosition(gd.handle, { static_cast<short>(attackedPosition.x),  static_cast<short>(attackedPosition.y) });
		if (attackedPosition.x != gd.player.position.x && !gd.mapOfTiles[attackedPosition.y][attackedPosition.x].hasCollision)
			cout << static_cast<char>(45);
		else if (!gd.mapOfTiles[attackedPosition.y][attackedPosition.x].hasCollision)
			cout << static_cast<char>(124);
		Sleep(40);

		SetConsoleTextAttribute(gd.handle, 7);

		isEnemyHitted(gd, attackedPosition);
	}

	gd.player.canAttack = true;
}

void SwordUpdate(GameData& gd)
{
	if (gd.actualMap.mapType == MapType::OverWorld || gd.actualMap.mapType == MapType::Mountain || gd.actualMap.mapType == MapType::CastleEntrance)
		SetConsoleTextAttribute(gd.handle, 233);
	else
		SetConsoleTextAttribute(gd.handle, 9);

	switch (gd.masterSword.direction)
	{
	case Directions::North:
		if (gd.masterSword.position.y - 1 > 0 && !gd.mapOfTiles[gd.masterSword.position.y - 1][gd.masterSword.position.x].hasCollision)
		{
			gd.masterSword.position.y--;
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.masterSword.position.x),  static_cast<short>(gd.masterSword.position.y) });
			cout << static_cast<char>(124);
			if (gd.masterSword.position.y != gd.player.position.y - 1)
				CleanTrail(gd.handle, gd.masterSword.position, 15);;
		}
		else
			gd.masterSword.isFlying = false;
		break;
	case Directions::South:
		if (gd.masterSword.position.y < 30 && !gd.mapOfTiles[gd.masterSword.position.y + 1][gd.masterSword.position.x].hasCollision)
		{
			gd.masterSword.position.y++;
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.masterSword.position.x),  static_cast<short>(gd.masterSword.position.y) });
			cout << static_cast<char>(124);

			if (gd.masterSword.position.y != gd.player.position.y + 1)
				CleanTrail(gd.handle, gd.masterSword.position, 15);
		}
		else
			gd.masterSword.isFlying = false;
		break;
	case Directions::East:
		if (gd.masterSword.position.x + 1 < 95 && !gd.mapOfTiles[gd.masterSword.position.y][gd.masterSword.position.x + 1].hasCollision)
		{
			gd.masterSword.position.x++;
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.masterSword.position.x),  static_cast<short>(gd.masterSword.position.y) });
			cout << static_cast<char>(45);

			if (gd.masterSword.position.x != gd.player.position.x + 1)
				CleanTrail(gd.handle, gd.masterSword.position, 15);
		}
		else
			gd.masterSword.isFlying = false;
		break;
	case Directions::West:
		if (gd.masterSword.position.x - 1 > 0 && !gd.mapOfTiles[gd.masterSword.position.y][gd.masterSword.position.x - 1].hasCollision)
		{
			gd.masterSword.position.x--;
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.masterSword.position.x),  static_cast<short>(gd.masterSword.position.y) });
			cout << static_cast<char>(45);

			if (gd.masterSword.position.x != gd.player.position.x - 1)
				CleanTrail(gd.handle, gd.masterSword.position, 15);
		}
		else
			gd.masterSword.isFlying = false;
		break;
	}
	if (gd.masterSword.isFlying)
		isEnemyHitted(gd, gd.masterSword.position);
	else
	{
		RangedAttackExplosion(gd, gd.masterSword.position);
		CleanTrail(gd.handle, gd.masterSword.position, 15);
	}
}

bool isEnemyHitted(GameData& gd, Vector2 attackedPosition)
{
	for (int i = 0; i < gd.MAX_ENEMIES; i++)
	{
		if (gd.enemies[i].position.x == attackedPosition.x && gd.enemies[i].position.y == attackedPosition.y)
		{
			gd.enemies[i].TakeDamage(gd.player.attackDamage);
			return true;
		}
	}
}

void RangedAttackExplosion(GameData& gd, Vector2 lastAttackedPosition)
{
	for (int i = 1; i <= 2; i++)
	{
		if (!gd.mapOfTiles[lastAttackedPosition.y - i][lastAttackedPosition.x - i].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(lastAttackedPosition.x - i),  static_cast<short>(lastAttackedPosition.y - i) });
			cout << static_cast<char>(92);
			isEnemyHitted(gd, { lastAttackedPosition.x - i, lastAttackedPosition.y - i });
		}
		if (!gd.mapOfTiles[lastAttackedPosition.y - i][lastAttackedPosition.x + i].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(lastAttackedPosition.x + i),  static_cast<short>(lastAttackedPosition.y - i) });
			cout << static_cast<char>(47);
			isEnemyHitted(gd, { lastAttackedPosition.x + i, lastAttackedPosition.y - i });
		}
		if (!gd.mapOfTiles[lastAttackedPosition.y + i][lastAttackedPosition.x - i].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(lastAttackedPosition.x - i),  static_cast<short>(lastAttackedPosition.y + i) });
			cout << static_cast<char>(47);
			isEnemyHitted(gd, { lastAttackedPosition.x - i, lastAttackedPosition.y + i });
		}
		if (!gd.mapOfTiles[lastAttackedPosition.y + i][lastAttackedPosition.x + i].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(lastAttackedPosition.x + i),  static_cast<short>(lastAttackedPosition.y + i) });
			cout << static_cast<char>(92);
			isEnemyHitted(gd, { lastAttackedPosition.x + i, lastAttackedPosition.y + i });
		}
	}
	CleanExplosion(gd, lastAttackedPosition);
}
void CleanExplosion(GameData gd, Vector2 lastAttackedPosition)
{
	float time;
	float timer;
	for (int i = 1; i <= 2; i++)
	{
		time = clock();
		timer = time + 50;
		while (time < timer)
		{
			time = clock();
		}
		if (!gd.mapOfTiles[lastAttackedPosition.y - i][lastAttackedPosition.x - i].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(lastAttackedPosition.x - i),  static_cast<short>(lastAttackedPosition.y - i) });
			cout << ' ';
		}
		if (!gd.mapOfTiles[lastAttackedPosition.y - i][lastAttackedPosition.x + i].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(lastAttackedPosition.x + i),  static_cast<short>(lastAttackedPosition.y - i) });
			cout << ' ';
		}
		if (!gd.mapOfTiles[lastAttackedPosition.y + i][lastAttackedPosition.x - i].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(lastAttackedPosition.x - i),  static_cast<short>(lastAttackedPosition.y + i) });
			cout << ' ';
		}
		if (!gd.mapOfTiles[lastAttackedPosition.y + i][lastAttackedPosition.x + i].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(lastAttackedPosition.x + i),  static_cast<short>(lastAttackedPosition.y + i) });
			cout << ' ';
		}
	}
}

void TakeItem(GameData& gd)
{
	if (gd.actualMap.name == MapNames::Cave1)
	{
		gd.maps[static_cast<int>(MapNames::Cave1)].isCaveItemTaken = true;
		gd.maps[static_cast<int>(MapNames::Cave1)].mapGraphic[13] = R"(%&@%%%%@%%%%                                                                     %@%@%@%@%@%)";

		gd.player.hasSword = true;
		SetConsoleCursorPosition(gd.handle, { 46,17 });
		for (int i = 0; i < 5; i++)
		{
			gd.mapOfTiles[17][46 + i].hasCollision = false;
		}
		cout << "     ";
	}
	else if (gd.actualMap.name == MapNames::Cave2)
	{
		gd.maps[static_cast<int>(MapNames::Cave2)].isCaveItemTaken = true;

		for (int i = 11; i < 16; i++)
		{
			if (i == 11)
				gd.maps[static_cast<int>(MapNames::Cave2)].mapGraphic[i] = R"(@@@%%&@@@&%@            #$                                           #$          &@@@%@@@@@%)";
			else
				gd.maps[static_cast<int>(MapNames::Cave2)].mapGraphic[i] = R"(%&@%%%%@%%%%                                                                     %@%@%@%@%@%)";
		}

		gd.player.hasTriforce = true;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 15; j < 20; j++)
			{
				gd.mapOfTiles[j][46 + i].hasCollision = false;
				SetConsoleCursorPosition(gd.handle, { 44,static_cast<short>(j) });
				cout << "           ";
			}
		}
	}
	else if (gd.actualMap.name == MapNames::FairysFountain)
	{
		SetConsoleTextAttribute(gd.handle, 233);
		gd.player.healthPoints = gd.player.maxHealthPoints;
		for (int i = 11; i <= 13; i++)
		{
			SetConsoleCursorPosition(gd.handle, { 17, static_cast<short>(i + 4) });
			cout << "    ";
			SetConsoleCursorPosition(gd.handle, { 76, static_cast<short>(i + 4) });
			cout << "    ";
		}

		for (int i = 17; i <= 19; i++)
		{
			SetConsoleCursorPosition(gd.handle, { 47, static_cast<short>(i + 4) });
			cout << "    ";
		}
		SetConsoleTextAttribute(gd.handle, 7);
	}
}

void PrintPlayer(GameData& gd)
{
	if (gd.actualMap.mapType == MapType::OverWorld || gd.actualMap.mapType == MapType::Mountain || gd.actualMap.mapType == MapType::CastleEntrance)
		SetConsoleTextAttribute(gd.handle, 233);
	else
		SetConsoleTextAttribute(gd.handle, 9);

	SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y) });
	cout << gd.player.graphic;
	switch (gd.player.direction)
	{
	case Directions::North:
		if (!gd.mapOfTiles[gd.player.position.y - 1][gd.player.position.x].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y - 1) });
			cout << '.';
		}
		break;
	case Directions::South:
		if (!gd.mapOfTiles[gd.player.position.y + 1][gd.player.position.x].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y + 1) });
			cout << '.';
		}
		break;
	case Directions::East:
		if (!gd.mapOfTiles[gd.player.position.y][gd.player.position.x + 1].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x + 1), static_cast<short>(gd.player.position.y) });
			cout << '.';
		}
		break;
	case Directions::West:
		if (!gd.mapOfTiles[gd.player.position.y][gd.player.position.x - 1].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x - 1), static_cast<short>(gd.player.position.y) });
			cout << '.';
		}
		break;
	default:
		break;
	}
	SetConsoleTextAttribute(gd.handle, 7);
}

void ClearPreviousPlayerPos(GameData& gd)
{
	if (gd.actualMap.mapType == MapType::OverWorld || gd.actualMap.mapType == MapType::Mountain || gd.actualMap.mapType == MapType::CastleEntrance)
		SetConsoleTextAttribute(gd.handle, 233);
	else
		SetConsoleTextAttribute(gd.handle, 7);
	SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y) });
	cout << ' ';
	switch (gd.player.direction)
	{
	case Directions::North:
		if (!gd.mapOfTiles[gd.player.position.y - 1][gd.player.position.x].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y - 1) });
			cout << ' ';
		}
		break;
	case Directions::South:
		if (!gd.mapOfTiles[gd.player.position.y + 1][gd.player.position.x].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x), static_cast<short>(gd.player.position.y + 1) });
			cout << ' ';
		}
		break;
	case Directions::East:
		if (!gd.mapOfTiles[gd.player.position.y][gd.player.position.x + 1].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x + 1), static_cast<short>(gd.player.position.y) });
			cout << ' ';
		}
		break;
	case Directions::West:
		if (!gd.mapOfTiles[gd.player.position.y][gd.player.position.x - 1].hasCollision)
		{
			SetConsoleCursorPosition(gd.handle, { static_cast<short>(gd.player.position.x - 1), static_cast<short>(gd.player.position.y) });
			cout << ' ';
		}
		break;
	default:
		break;
	}
	SetConsoleTextAttribute(gd.handle, 7);
}
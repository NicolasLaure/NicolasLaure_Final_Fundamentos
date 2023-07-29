#include "Enemies.h"

void RockUpdate(Rock& rock, TileMap mapOfTiles[32][97], bool& hasShooted)
{

	rock.previousPosition = rock.position;
	switch (rock.direction)
	{
	case Directions::North:
		if (!mapOfTiles[rock.position.y - 1][rock.position.x].hasCollision)
			rock.position.y--;
		else
		{
			rock.isFlying = false;
			hasShooted = false;
		}
		break;
	case Directions::South:
		if (!mapOfTiles[rock.position.y + 1][rock.position.x].hasCollision)
			rock.position.y++;
		else
		{
			rock.isFlying = false;
			hasShooted = false;
		}
		break;
	case Directions::East:
		if (!mapOfTiles[rock.position.y][rock.position.x + 1].hasCollision)
			rock.position.x++;
		else
		{
			rock.isFlying = false;
			hasShooted = false;
		}
		break;
	case Directions::West:
		if (!mapOfTiles[rock.position.y][rock.position.x - 1].hasCollision)
			rock.position.x--;
		else
		{
			rock.isFlying = false;
			hasShooted = false;
		}
		break;
	}
}
void RockDraw(Rock rock, MapType mapType, HANDLE handle)
{
	if (mapType == MapType::OverWorld || mapType == MapType::Mountain)
		SetConsoleTextAttribute(handle, 236);
	else
		SetConsoleTextAttribute(handle, 12);

	if (rock.isFlying)
	{
		SetConsoleCursorPosition(handle, { static_cast<short>(rock.position.x), static_cast<short>(rock.position.y) });
		cout << "O";
	}
}
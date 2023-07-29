#include "Utilities.h"

void CleanTrail(HANDLE handle, Vector2 attackedPosition, float timeToMove)
{
	float time = clock();
	float timer = time + timeToMove;
	while (time < timer)
	{
		time = clock();
	}

	SetConsoleCursorPosition(handle, { static_cast<short>(attackedPosition.x),  static_cast<short>(attackedPosition.y) });
	cout << ' ';
}
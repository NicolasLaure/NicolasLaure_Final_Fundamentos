#include "Utilities.h"

void CleanTrail(HANDLE handle, Vector2 attackedPosition)
{
	float time = clock();
	float timer = time + 20;
	while (time < timer)
	{
		time = clock();
	}

	SetConsoleCursorPosition(handle, { static_cast<short>(attackedPosition.x),  static_cast<short>(attackedPosition.y) });
	cout << ' ';
}
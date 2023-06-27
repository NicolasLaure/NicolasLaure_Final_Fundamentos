#include <iostream>

using namespace std;



enum class Scenes
{
	Menu,
	Game,
	GameData,
	Credits,
	End
};

struct GameData
{
	// Global Variables
	Scenes scene = Scenes::Menu;
	// Game

};
void main()
{
	Play();
}

void Play()
{

}

void GameLoop()
{
	GameData gd{};

	do
	{
		system("cls");

		switch (gd.scene)
		{
		case Scenes::End:
			break;
		case Scenes::Menu:
			break;
		case Scenes::GameData:
			break;
		case Scenes::Credits:
			break;
		default:
			break;
		}

	} while (gd.scene != Scenes::End);
}

void Menu(GameData& gd)
{

}

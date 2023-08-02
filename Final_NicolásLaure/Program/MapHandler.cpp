#include "MapHandler.h"

void PrintMap(GameData& gd, Map map, int MAP_HEIGHT)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	gd.width = csbi.dwSize.X;
	gd.height = csbi.srWindow.Bottom - csbi.srWindow.Top;

	int mapWidth = 93;
	COORD coordinates;
	coordinates.X = gd.width / 2 - (mapWidth / 2) + 1;
	coordinates.Y = gd.height / 2 - (MAP_HEIGHT / 2);

	int leftBorder = 2;
	int upperBorder = 4;
	for (int i = 0; i < gd.height; i++)
	{
		for (int j = 0; j < gd.width; j++)
		{
			if (i < upperBorder || j < leftBorder || j >= mapWidth + 1 || i >= MAP_HEIGHT + upperBorder)
			{
				gd.mapOfTiles[i][j].hasCollision = true;
				gd.mapOfTiles[i][j].isEndOfMap = true;
			}
		}
	}

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		SetConsoleCursorPosition(handle, coordinates);
		bool isBetweenBrackets = false;
		bool isBetweenBraces = false;
		for (int j = 0; j < mapWidth; j++)
		{
			gd.mapOfTiles[i + 4][j + 2].isItem = false;
			gd.mapOfTiles[i + 4][j + 2].isTriforceLogo = false;

			if (map.mapGraphic[i][j] == 91)
				isBetweenBrackets = true;
			if (map.mapGraphic[i][j] == 93)
				isBetweenBrackets = false;

			if (gd.actualMap.name == MapNames::CastleEntrance && map.mapGraphic[i][j] == 123)
				isBetweenBraces = true;
			if (gd.actualMap.name == MapNames::CastleEntrance && map.mapGraphic[i][j] == 125)
				isBetweenBraces = false;

			if (map.mapGraphic[i][j] != ' ')
			{
				gd.mapOfTiles[i + 4][j + 2].isCaveEntrance = false;
				gd.mapOfTiles[i + 4][j + 2].hasCollision = true;
			}
			else if (map.mapGraphic[i][j] == ' ' && isBetweenBrackets)
			{
				gd.mapOfTiles[i + 4][j + 2].hasCollision = true;
				gd.mapOfTiles[i + 4][j + 2].isCaveEntrance = true;
			}
			else if (map.mapGraphic[i][j] == ' ' && isBetweenBraces)
			{
				gd.mapOfTiles[i + 4][j + 2].hasCollision = true;
				gd.mapOfTiles[i + 4][j + 2].isCastleEntrance = true;
			}
			else
				gd.mapOfTiles[i + 4][j + 2].hasCollision = false;

			if (gd.actualMap.name == MapNames::Cave1)
			{
				if (map.mapGraphic[i][j] == '>' || map.mapGraphic[i][j] == '-')
					gd.mapOfTiles[i + 4][j + 2].isItem = true;
			}
			else if (gd.actualMap.name == MapNames::Cave2)
			{
				if (map.mapGraphic[i][j] == '_' || (map.mapGraphic[i][j] == 92 || map.mapGraphic[i][j] == '/') && i >= 12)
					gd.mapOfTiles[i + 4][j + 2].isItem = true;
			}
			else if (gd.actualMap.name == MapNames::FairysFountain)
			{
				if (i == 11 || i == 12)
				{
					if (j >= 15 && j <= 18)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
					else if (j >= 74 && j <= 77)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
				}
				else if (i == 13)
				{
					if (j == 16 || j == 17)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
					else if (j == 75 || j == 76)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
				}
				else if (i == 17 || i == 18)
				{
					if (j >= 45 && j <= 48)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
				}
				else if (i == 19)
				{
					if (j == 46 || j == 47)
						gd.mapOfTiles[i + 4][j + 2].isItem = true;
				}
			}
			else if (gd.actualMap.name == MapNames::CastleEntrance)
			{
				if (map.mapGraphic[i][j] == '_' || map.mapGraphic[i][j] == 92 || map.mapGraphic[i][j] == '/')
					gd.mapOfTiles[i + 4][j + 2].isTriforceLogo = true;
			}

			if (gd.mapOfTiles[i + 4][j + 2].hasCollision)
			{
				if (gd.mapOfTiles[i + 4][j + 2].isCaveEntrance)
					SetConsoleTextAttribute(gd.handle, 7);
				else if (gd.actualMap.name == MapNames::CastleEntrance && gd.mapOfTiles[i + 4][j + 2].isCastleEntrance)
				{
					if (gd.player.hasTriforce)
						SetConsoleTextAttribute(gd.handle, 7);
					else
						SetConsoleTextAttribute(gd.handle, 135);
				}
				else
				{
					if (map.mapType == MapType::OverWorld)
					{
						if (gd.actualMap.name == MapNames::WesternRiver && map.mapGraphic[i][j] == '.')
							SetConsoleTextAttribute(gd.handle, 27);
						else
							SetConsoleTextAttribute(gd.handle, 32);
					}
					else if (map.mapType == MapType::Cave)
						SetConsoleTextAttribute(gd.handle, 4);
					else if (map.mapType == MapType::Mountain)
					{
						if (gd.actualMap.name == MapNames::FairysFountain)
						{
							if (map.mapGraphic[i][j] == '.')
								SetConsoleTextAttribute(gd.handle, 27);
							else if (i == 10 && j == 46)
								SetConsoleTextAttribute(gd.handle, 22);
							else if (i == 11 && j >= 44 && j <= 48)
								SetConsoleTextAttribute(gd.handle, 22);
							else if (i == 12 && (j == 45 || j == 47))
								SetConsoleTextAttribute(gd.handle, 22);
							else
								SetConsoleTextAttribute(gd.handle, 6);
						}
						else
							SetConsoleTextAttribute(gd.handle, 6);
					}
					else if (map.mapType == MapType::CastleEntrance)
					{
						if (i < 10)
							SetConsoleTextAttribute(gd.handle, 135);
						else
							SetConsoleTextAttribute(gd.handle, 6);
					}
					else if (map.mapType == MapType::CastleEntrance)
						SetConsoleTextAttribute(gd.handle, 128);
				}
			}
			else
			{
				if (map.mapType == MapType::OverWorld || map.mapType == MapType::Mountain || map.mapType == MapType::CastleEntrance)
					SetConsoleTextAttribute(gd.handle, 238);
				else if (map.mapType == MapType::Cave)
					SetConsoleTextAttribute(gd.handle, 7);
				else if (map.mapType == MapType::CastleEntrance)
					SetConsoleTextAttribute(gd.handle, 128);
			}

			if (gd.mapOfTiles[i + 4][j + 2].isItem)
			{
				if (gd.actualMap.name == MapNames::Cave1)
					SetConsoleTextAttribute(gd.handle, 9);
				if (gd.actualMap.name == MapNames::Cave2)
					SetConsoleTextAttribute(gd.handle, 14);
				else if (gd.actualMap.name == MapNames::FairysFountain)
					SetConsoleTextAttribute(gd.handle, 192);
			}

			if (gd.mapOfTiles[i + 4][j + 2].isTriforceLogo)
			{
				if (gd.player.hasTriforce)
					SetConsoleTextAttribute(gd.handle, 142);
				else
					SetConsoleTextAttribute(gd.handle, 135);
			}

			cout << map.mapGraphic[i][j];
			SetConsoleTextAttribute(gd.handle, 7);
		}
		//cout << map[i];
		coordinates.Y++;
	}
}
void MapsSetup(GameData& gd, Map maps[], int mapQty, int mapSize)
{
	for (int i = 0; i < mapQty; i++)
	{
		switch (static_cast<MapNames>(i))
		{
		case MapNames::StartValley:
			maps[i].name = MapNames::StartValley;
			maps[i].mapGraphic = new string[25]{
			R"(#&#&&#&#&&#&#&&#&&#&&#&#&&#&#&&#&#&&#@#               #@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%)",
			R"(#@#*##@#*##@#*##@#*##@#*#@#@#*##@#*##@#               #@##@#*##@#*##@#*##@#*##@#*##@#*##@#*#)",
			R"(#&#&&#&#&&#&#&&#&#&&[    ]#&#&&.#%(@#@#               #@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%)",
			R"(#@#*##@#*##@#*##@#*#[    ]#@#*#.%%                    #@##@#*##@#*##@#*##@#*##@#*##@#*##@#*#)",
			R"(#&#&&#&#&&#&#&&.#%(@                                  #@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%)",
			R"(#@#*##@#*##@#*#.%%                                    #@##@#*##@#*##@#*##@#*##@#*##@#*##@#*#)",
			R"(#&#&&#&#&&.#%/@                                       #@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%)",
			R"(#@#*##@#*#.%%                                         #@##@#*##@#*##@#*##@#*##@#*##@#*##@#*#)",
			R"(#&#&&.#%/@                                            #@##(#@##&#&%#&#&%#&%&%#&%&%#&%&%#&%&%)",
			R"(#@#*#.%%                                               #@#@#&*#@#*##@#*##@#*##@#*##@#*##@#*#)",
			R"(                                                                                            )",
			R"(                                                                                            )",
			R"(                                                                                            )",
			R"(                                                                                            )",
			R"(                                                                                            )",
			R"( %                                                                                 %    %   )",
			R"(##/#####%@                                                                        ##/####/##)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&.%     %     %     %     %     %     %     %     %     %     %     %    #&%&%#&%&%)",
			R"(#@#*##@#*###/####/####/####/####/####/####/####/####/####/####/####/###@#*##@#*#@#/####/####)",
			R"(#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&%#&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%@##&#&&#&#&&)",
			R"(#@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*#@#*##@#*##@#)"
			};
			maps[i].mapType = MapType::OverWorld;
			break;
		case MapNames::WesternRiver:
			maps[i].name = MapNames::WesternRiver;
			maps[i].mapGraphic = new string[25]{
			R"(......{/(,@(&((,((@(/*@(((*%*(%%*@((*(,@(#((,%(@(/,,(%(/#,(,(*&((,(,@@           (@(//,(/(*%)",
			R"(......{/(,@(&((,((@(/*@(((*%*(%(*@((*(,@(#((,%(@(/,,(%(/#,(,(*&((,(,@@           (@(//,(/(*%)",
			R"(......}((@(@&(#@((%(&((,@(@,(/,(@*#(/(@(@%((@(%&(%%(**(@,(*&(@*#(*(@/&           ((@*(,&(@,()",
			R"(......{(/(((/&(((%(@((#@((((&/(%((#(/(@(@%#(((#(@(((@(%((%#(,((&%((@/&           (@((#&(/((&)",
			R"(......}%@%(@/@@@((#@@/(@@@&@(@%@#(@(((@(%(%@@(%(%@#(,&&@&(&@&#,(@((@             %&@*(&@&%&()",
			R"(......{                                                                          (@/(@&(@((@)",
			R"(......}                              ,,                                          (@(,(@(/(&()",
			R"(......{                             /(/*         %                               /,#@(%(#*@@)",
			R"(......}                              /,(       (@((&,                            @&(@(((/(,#)",
			R"(......{                                        ((#&%(                                /(*(&(%)",
			R"(......}                                                                                (/(@()",
			R"(......}                                         ,         ,(#((&                            )",
			R"(......{                                       ,*(,*       ,(((#&                            )",
			R"(......}     /(%(*             ,@(@            /(#(,                                         )",
			R"(......{    /&(@((             (%@%@           (@(&(,                                        )",
			R"(......{                                                   ,(,&#@                        /@(()",
			R"(......}                                                    (((@@                       ((@(&)",
			R"(......{                   /**/         /***        &/(#                            @(#@(/((#)",
			R"(......}                  */,,//       ,(,,**      (@(#@,                          @@((&/*%@()",
			R"(......{                                                                          (@/(&&(@((@)",
			R"(......}                                                                          #@(,(&%/(&()",
			R"(......{(*,*,,%,,*,,@,,*,(@,*,,(@,,,,((,,*,#,*,,,@,,*,/@,,,,(@,,*,(%,,*,(*,,*,&,*,(*,&(/(%*@@)",
			R"(......{(@(#@#(&(@@((*(@@(%,(#@(@((#@(@((@%(@(&@((/(@@(##(%@(@/((@(@((&&(@(%@((#@@*((@#&((%@@)",
			R"(......}(&*(@#(%((@((,((&((@((&((@(#&(%,(@#(&/(@((/((&((@((&((#((@(#,(&%(@/(@((#(&(@(,(*(/(@()",
			R"(......{(@(#@#(&(@@((*(@@(%,(#@(@((#@(@((@%(@(&@((/(@@(##(%@(@/((@(@((&&(@(%@((#@@*((@#&((%@@)"
			};
			maps[i].mapType = MapType::OverWorld;
			break;
		case MapNames::HyruleField:
			maps[i].name = MapNames::HyruleField;
			maps[i].mapGraphic = new string[25]{
			R"(#&##@&#&           &##@&#&##@&#&##@&#&##@&#&##@&#&##@&#&##@&#&##@&#&##@&###@&#&##@&#&##@&#&#)",
			R"(#&##@&#&           &####@#&##@&#&##@&####@#&##@&#&##@&####@#&##@&#&##@&###@#&##@&#&##@&####@)",
			R"(.,#@,,#&           &.##@,.,#@,,#&##@&.##@,.,#@,,#&##@&.##@,.,#@,,#&##@&.#@,.,#@,,#&##@&.##@,)",
			R"(.###@%#&           &####@.###@%#&##@&####@.###@%#&##@&####@.###@%#&##@&###@.###@%#&##@&####@)",
			R"(#@###%#&           &####@#@###%#&##@&####@#@###%#&##@&####@#@###%#&##@&###@#@###%#&##@&####@)",
			R"(#%##@&                                                                            ##@&.###@.)",
			R"(.,#@,,                                                                             ##@.####@)",
			R"(#%##@&                                                                              #@.####@)",
			R"(.,#@,,                                                     &##&@                     &.&##&@)",
			R"(.###@%                                                      #&#,                     #&##%#,)",
			R"(#%##@&      ####@                   ###@       ####@                                   @@@@#)",
			R"(.,#@,,      ####@                  #####       ####@                                   @#@#.)",
			R"(.###@%                                                     ###@                        @@@@#)",
			R"(#%##@&                                                     ####@       ***             ####@)",
			R"(.,#@,,                                                                 ###*            ####@)",
			R"(.###@%      ####@/                 ####@#      ####@                                   &##&@)",
			R"(#%##@&       ##@,,                  (#@,,       ##@,,                                  ##%#,)",
			R"(.,#@,,                                                     ####@                       ####@)",
			R"(.###@%                                                     @##@@                       @##@@)",
			R"(#%##@&                     #*#*###*      /.#&                                    ,##@&.###@.)",
			R"(.,#@,,                      #,,###*      /.#&                                    #@##@.####@)",
			R"(.###@%                                                                           #@##@.####@)",
			R"(#%##@&####@#####@/###%@.&##&@*&##@@####@#####@#####@.%##&@.&##&@                 ###%@.&##&@)",
			R"(.,#@,,.(#@,,.##@,,.##&,,.###,..#@/,.(#@,,.(#@,,.##@,,.###,,.#&#,                 .##%,,.#%#,)",
			R"(.###@%.###@.####@.####@.####@.###&@.###@./###@.####@.####@.####@                 ####@.####@)"
			};
			maps[i].mapType = MapType::OverWorld;
			break;
		case MapNames::KokiriForest:
			maps[i].name = MapNames::KokiriForest;
			maps[i].mapGraphic = new string[25]{
			R"(#%.#&%#@/(@/#@((@*#@(#@*#@##@/#@##@(#@#(@##&#(&##*((&##.(%&#%.(&%#@,#@/(@((@*#@##@*#@##@/#@#)",
			R"(#@##(##@###&#@#/(@#&#.#@(/#.#&(.#,###.#*((&,#(##@(##(#@###(#@#####@#(#&#@#/#@#@#.#@(/#.#&(.()",
			R"(./,@.%&#(@.*,#&@..*#@@(.##%@&*##*&@&/(.(@@,(..@&.,*.@#..%.@.*.@.&.#*@.*.#%@../#@@/.##&@&/##()",
			R"(#%##.%#@##.*#@##..#&##(.#/#(&,#.#(@(#.#*@[     ]#/#.@####.@#%##.&#@##.*#@##..#@#((.#/##&*#.#)",
			R"(@##@#%@#%@#*&#%##.(#%.#..#&.#,.(@,((,(@/#[     ]#(@#@%#(@#@@##@#&@##&#*&#%%#.*#%,#..#&.#*.#@)",
			R"(#&,###.@#@#,                                         #@##,#.%#@#&                  (/#@#/#&#)",
			R"(#@@@#@&@&                                              @@@#.%#                      (@@,/@.#)",
			R"(###@#@             ##          (@                                       ##              *###)",
			R"(#%#,              #&((&       #,&#@                                    #@(##             ,##)",
			R"(%#                %%%@&#     ,%%#@@,                                   #%%%@%              @)",
			R"(#%                                                                                         #)",
			R"(%#                                                                                         #)",
			R"(#%                *###(      ,(@##                                     ,((#&               @)",
			R"(%#                #&##%       #,&#@                                    #@#&(               #)",
			R"(#%                                                                                         #)",
			R"(%#                                                                                         @)",
			R"(#%                                                                                         #)",
			R"(###               *%#(&      ,#,##@                                     &(##               ()",
			R"(##&##%            #&##@      ,#(##&                                    #@(%@             #(#)",
			R"((&.#%#.(                                                ##@,(                         (#*#@#)",
			R"((@######(##                                           #(#####@(#                   #%@##*(.#)",
			R"((/&#*##.(#.#,@    *@    #@    #@    #&               #@@#%###@#*(&      @    /@    ##,@&#(@*)",
			R"(#&##/%#@##/*(#(##@#(/##@##*##&#(,##%#(.##            ####/@#%##/&##&##@##(##@##/##@#/#*%*#.#)",
			R"(%%,.(&%#%@(/#(%(%@##%&#@###&#&##*&#%(%,&#            ###@(@%##@#&(#@*%@##%/%@(#%%#@,#&*%/,#@)",
			R"(#&#####@###&#@###@#%##%@#/##&%#.##@,#.##&            *####((%#####@###&#@###@#@##%@#/##@&,,#)"
			};
			maps[i].mapType = MapType::OverWorld;
			break;
		case MapNames::Cave1:
			maps[i].name = MapNames::Cave1;
			maps[i].mapGraphic = new string[25]{
			R"(%&@%@@%@@%@%%@@%@%%@@&@%%@@@@%%@%@@%@@%@%%@%@%%@@%@%%@@@@%%@&@@%@@%@&%@@%@%%@@%@%%@@@@%%@@@@)",
			R"(%%@%&&%%%%&@%&%%&@%@%&&@%@%&&&%@%&&%%&%&@%%%&@%@%%&@%@%&&@%@%&&%%@%&@%%%%&@%@%%&@%@%&&@%@%&&)",
			R"(%&%@%&%%%@%@@%%@%@@%@@%@@%@@&&@%@&&%%%@%@&%@%@@%&@%@@%@@&@@%@@&%&%@%@%%%@%@@%&@%@@%@@%@@%@@&)",
			R"(@%@%%@@%%%%%%&%%%&%@%%%@%@%%@@%@%%@@%&%%%&%%%%%@%%%@%@%%@@%@%%@@%@%%&@%%%%%%@%%%@%@%%&@%@%%@)",
			R"(@@@%%&@@@&%@%@@@%@%@@@%@@@@@%@@@%&%@@@%%@&@@%@%@@@%@&@@@%@@@&@%@@@%%@@@@@%@%@@@%@&@@@%@@@@@%)",
			R"(%%@%%@%%@%%%                                                                     %@%%@@%@%%@)",
			R"(%&@%%%%@%%%%       IT'S    DANGEROUS    TO    GO    ALONE!    TAKE    THIS.      %@%@%@%@%@%)",
			R"(%&@%@@%@@%@%                                                                     %@@@@%%@@@@)",
			R"(%%@%&&%%%%&@                                  A                                  %@%&&@%@%&&)",
			R"(%&%@%&%%%@%@            /\                   MMM                     /\          @%@@%@@%@@&)",
			R"(@%@%%@@%%%%%           /\\\                  / \                    /\\\         %@%%&@%@%%@)",
			R"(@@@%%&@@@&%@            \/                                           \/          &@@@%@@@@@%)",
			R"(%%@%%@%%@%%%                                                                     %@%%@@%@%%@)",
			R"(%&@%%%%@%%%%                                ->---                                %@%@%@%@%@%)",
			R"(%&@%@@%@@%@%                                                                     %@@@@%%@@@@)",
			R"(%%@%&&%%%%&@                                                                     %@%&&@%@%&&)",
			R"(%&%@%&%%%@%@                                                                     @%@@%@@%@@&)",
			R"(@%@%%@@%%%%%                                                                     %@%%&@%@%%@)",
			R"(@@@%%&@@@&%@                                                                     &@@@%@@@@@%)",
			R"(%%@%%@%%@%%%                                                                     %@%%@@%@%%@)",
			R"(%&@%%%%@%%%%                                                                     %@%@%@%@%@%)",
			R"(%&@%@@%@@%@%                                                                     %@@@@%%@@@@)",
			R"(%%@%&&%%%%&@%%@%%@%%@%%@%%@%%@%%@%%@%&@%&            %@%%@%%@%%@%%@%&@%@&%&%%@%%@%@%&&@%@%&&)",
			R"(%&%@%&%%%@%@%%@@&&%%@@&@%%@@%&%&@@%&%&@@&            %@@%@%&@@%&%&@@&&%@@@&%%@@&@@%@@%@@%@@&)",
			R"(@%@%%@@%%%%%%&%%%&%@%%%@%@%%@@%@%%@@%&%%%            %%%@@%@%%@@%@%%&@%%%%%%@%%%@%@%%&@%@%%@)"
			};
			maps[i].mapType = MapType::Cave;
			break;
		case  MapNames::Cave2:
			maps[i].name = MapNames::Cave2;
			maps[i].mapGraphic = new string[25]{
			R"(%&@%@@%@@%@%%@@%@%%@@&@%%@@@@%%@%@@%@@%@%%@%@%%@@%@%%@@@@%%@&@@%@@%@&%@@%@%%@@%@%%@@@@%%@@@@)",
			R"(%%@%&&%%%%&@%&%%&@%@%&&@%@%&&&%@%&&%%&%&@%%%&@%@%%&@%@%&&@%@%&&%%@%&@%%%%&@%@%%&@%@%&&@%@%&&)",
			R"(%&%@%&%%%@%@@%%@%@@%@@%@@%@@&&@%@&&%%%@%@&%@%@@%&@%@@%@@&@@%@@&%&%@%@%%%@%@@%&@%@@%@@%@@%@@&)",
			R"(@%@%%@@%%%%%%&%%%&%@%%%@%@%%@@%@%%@@%&%%%&%%%%%@%%%@%@%%@@%@%%@@%@%%&@%%%%%%@%%%@%@%%&@%@%%@)",
			R"(@@@%%&@@@&%@%@@@%@%@@@%@@@@@%@@@%&%@@@%%@&@@%@%@@@%@&@@@%@@@&@%@@@%%@@@@@%@%@@@%@&@@@%@@@@@%)",
			R"(%%@%%@%%@%%%                                                                     %@%%@@%@%%@)",
			R"(%&@%%%%@%%%%                  Take           The         Triforce,               %@%@%@%@%@%)",
			R"(%&@%@@%@@%@%    It'll   allow   you   to   save   Zelda   at   Hyrule  Castle    %@@@@%%@@@@)",
			R"(%%@%&&%%%%&@                                  A                                  %@%&&@%@%&&)",
			R"(%&%@%&%%%@%@            #$                   MMM                     #$          @%@@%@@%@@&)",
			R"(@%@%%@@%%%%%           &%&%                  / \                    &%&%         %@%%&@%@%%@)",
			R"(@@@%%&@@@&%@            #$                                           #$          &@@@%@@@@@%)",
			R"(%%@%%@%%@%%%                                 /\                                  %@%%@@%@%%@)",
			R"(%&@%%%%@%%%%                                /__\                                 %@%@%@%@%@%)",
			R"(%&@%@@%@@%@%                               /\  /\                                %@@@@%%@@@@)",
			R"(%%@%&&%%%%&@                              /__\/__\                               %@%&&@%@%&&)",
			R"(%&%@%&%%%@%@                                                                     @%@@%@@%@@&)",
			R"(@%@%%@@%%%%%                                                                     %@%%&@%@%%@)",
			R"(@@@%%&@@@&%@                                                                     &@@@%@@@@@%)",
			R"(%%@%%@%%@%%%                                                                     %@%%@@%@%%@)",
			R"(%&@%%%%@%%%%                                                                     %@%@%@%@%@%)",
			R"(%&@%@@%@@%@%                                                                     %@@@@%%@@@@)",
			R"(%%@%&&%%%%&@%%@%%@%%@%%@%%@%%@%%@%%@%&@%&            %@%%@%%@%%@%%@%&@%@&%&%%@%%@%@%&&@%@%&&)",
			R"(%&%@%&%%%@%@%%@@&&%%@@&@%%@@%&%&@@%&%&@@&            %@@%@%&@@%&%&@@&&%@@@&%%@@&@@%@@%@@%@@&)",
			R"(@%@%%@@%%%%%%&%%%&%@%%%@%@%%@@%@%%@@%&%%%            %%%@@%@%%@@%@%%&@%%%%%%@%%%@%@%%&@%@%%@)"
			};
			maps[i].mapType = MapType::Cave;
			break;
		case MapNames::Mountain1:
			maps[i].name = MapNames::Mountain1;
			maps[i].mapGraphic = new string[25]{
			R"((#@(@&(@@(@((#@(.((..%.(((.@@((@(@@(@@(@((@@(/(./(.((..@%((@/@@(&@(@#(@@(@((,@(.((..@,((@,@@)",
			R"(((.(/%((((/@(#((/#(@(//.(#(,#*(.(*#((*(/@((((/(@((/.(@(,(.(.(,#((.(/@((((/@(@((/,(@(,/.(.(,#)",
			R"((*(@(%(((@(@#((@(&#(&%(/,(&/%(,(@(%(((@(@(((@(#(%@(//(&/#/,(@/%(/(@(@(((@(@#((@((#(&((/,(&/%)",
			R"(.(.((&.((((((#(((%(@(((@(#((@#(.((@.(*(((*(((((@(((@(@((&@(.((@.(.((#.((((((@(((@(@(((@(.((@)",
			R"(.%.((#..@#(@(.@@(#(.@#(.@.@.(.@.(*(..#((@*.@@((.@@(.&.@.(.@.#.(.*.((@..@@(@(.@@(,(.@,(.@.@.()",
			R"(.@(@(#(@((.((&(@(@                                                               (.(@(@(@((@)",
			R"(.((@....@#@((#(                                                                   @(@&((.(.()",
			R"(                            (@                                (@                       (@,@@)",
			R"(                         *@((.(((@                         (@((.(((@                   (.(.()",
			R"(                        ((@(@*((.%@                       ((@(@(((.(@                  ((#@@)",
			R"(                    @((@(#(((%(.(((.((                @(&@(.(((((.(((.((               (((@()",
			R"(                  (@@((@*/#.(,*/&*(%((.(@           (@@((@*/&.(///&(@%(#/(@                 )",
			R"(                  (@((%@(@((@#(@((@*(((((           (@((@@(@((@*(@((#*(.(((                 )",
			R"(                  (@(/(@(#(.(%(.(*(/@*(((           (@(.(@(.(.(/@.(((/@((((                 )",
			R"(                  (.(@(@((.@@%@@@@@.((@(@           (.(@(@(@/@@(&@(@#.((@(@               (@)",
			R"(                  @.(%@((#(.((@@@@@.((@             @.(@/((.(.(((.((@.((@               (@(()",
			R"(                       ((((@@@@@@@@@                    %(((&@@(((@(@@                 ((@(@)",
			R"(                                                                                       (.((()",
			R"(                                                                                        (#.()",
			R"( ((      ,(@((@                                                                     ((@(@((@)",
			R"(((@((#.((((@((@((#                                                               ((@((.@.(.()",
			R"(((@(#@(#*(#&(#*(&#/#..&.(%....(@.,..(&./.*(&.#/#*.&./#..*.(@....(@./..(&././#%.&.(&/#&,(@/#@)",
			R"(((.((((%(((%(&(((#((.(((((.((#((*((%(#*(@#(%((((*(((((.(((((,((%((*(@%(%/(@((%((#(@(.(((.(.()",
			R"(#((&/@#//@/@.//@/@((.(@@#%.((@#@(((@#@(#@%#@(&((/(@@((.(#@#@/((@#@(#&@#@(#@((@(@@.(#@(&((#@@)",
			R"(((.((((((((((#(((%(@(((@(#(((%(.(((((*(((((((((@(((@(@(((@(.(((((.((((((((((@(((@(@(((@(.((()"
			};
			maps[i].mapType = MapType::Mountain;
			break;
		case MapNames::FairysFountain:
			maps[i].name = MapNames::FairysFountain;
			maps[i].mapGraphic = new string[25]
			{
				R"((/(#@(#,(#@(#%(%@(%%(%&(%,(&%(&,(&#(&*(@((@*(@/(@/(@*(@((@,(@((@%(@((@%(@((@,(@((@*(@((@*(@()",
				R"(@/((#(@(((#(@(((#(@(((#(@(((%(@(((%(@(((%(@(/(%(@(/(%(&(*(%(%(*(&(#(,(%(((@(%(/(@(%#*(@(##,()",
				R"(*/%*@(**%*@//*&*@*/*&*@,//@*&*(/@*&@((@*%,(#@*%,(#@*#*(%@/(*(%@((/(&@#(((%@%(((%@%#((#@&#((#)",
				R"((/(/%(#((/%(#((/%(%((/%(%((/%(&((/%(@((/%(@((/%(@((/%(&((/%(%(((%(#(((%((((##(/((##(*((##(,()",
				R"(((@(&%((@(@&((@(@&((@(&@((@(%@(#@(#@(#&((&(#%(/%(##(*#(#((,((#/(@/(#*(@*(%,(,@(%@(*@(%@(*,(&)",
				R"((/((#@#(@(@                                                                       *#/(&(/(@()",
				R"(@##(%(#((                                                                           %&@*/&,()",
				R"(&%(&&                           ...............................                         *#@/)",
				R"(#/((&                         ..................................                        *#,()",
				R"(((@(@                        ...................................                        *((&)",
				R"((/((#                        .................O.................                        *(,()",
				R"(*#&(@          /\/\          ...............\\W//...............          /\/\          ,(*%)",
				R"((/(##          \  /          ................/.\................          \  /          ,(@()",
				R"(@/((#           \/           ...................................           \/           *#,()",
				R"(&&(&%                        ...................................                        *#&/)",
				R"((/(/@                        ...................................                        *(,()",
				R"(((@(@                         ..................................                        **(@)",
				R"((/((#                                        /\/\                                       *(,()",
				R"(,%%(&                                        \  /                                       *&&%)",
				R"((/(#%@#,                                      \/                                     ,(#*(@()",
				R"(@/(((((@%(,                                                                        *#&((*#,()",
				R"(*//*@(@#(@*                                                                        (#&@#((#/)",
				R"((/(@@(#((@@*(@/((/(@/(#((@((#((@((%((@((%            ((@((@((@((@((@((&((&((%((%((&(*((&*(,()",
				R"(((@(@%((@(@#(@,&(#(@,%##(@,%#((@,#%((@*#%            ((@((@((@#(@((@%(@((&&(@((%@(&@(@@(*,(@)",
				R"((/((#*#/((#*#*(((/%/((#(%/((#(&/((%(&/((%            (@((#@(&((%@(&((%&(%((&%(#((&#(#((@(((()"
			};
			maps[i].mapType = MapType::Mountain;
			break;
		case MapNames::CastleEntrance:
			maps[i].name = MapNames::CastleEntrance;
			maps[i].mapGraphic = new string[25]{
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@##@####/\@#*@#*##@#*##@#*##@#*##@#*##@##@#*##@#*##*#)",
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&#/__\&#&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@##@##/\--/\#@#*##@#*##@#*##@#*##@#*##@##@#*##@#*##*#)",
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&#/__\/__\&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@##@#*##@#*##*#)",
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@#{            }%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#{            }##@#*##@#*##@#*##@#*##@##@#*##@#*##*#)",
			R"(#@##(#@##&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@#{            }%#&%&%#&%&%#&%&%#&%&%#@##(#@##&#&%%&%)",
			R"(##@#@#&*#@#*##@#*##@#*##@#*##@#*##@#*###@{            }##@#*##@#*##@#*##@#*###@#@#&*#@#*##*#)",
			R"(                                                                                  ##@####@##)",
			R"(                                                                                  #&%&%#&%&%)",
			R"(                                                                                  #@#*##@#*#)",
			R"(                                                                                  #&%&%#&%&%)",
			R"(                                                                                  #@#*##@#*#)",
			R"(                                                                                  #&%&%#&%&%)",
			R"(##@#####%@                                                                        ##@####@##)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&.%     %     %     %     %     %     %     %     %     %     %     %    #&%&%#&%&%)",
			R"(#@#*##@#*###@####@####@####@####@####@####@####@####@####@####@####@###@#*##@#*#@#@####@####)",
			R"(#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&%#&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%@##&#&&#&#&&)",
			R"(#@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*#@#*##@#*##@#)"
			};
			maps[i].mapType = MapType::CastleEntrance;
			break;
		case MapNames::HyruleCastle:
			maps[i].name = MapNames::HyruleCastle;
			maps[i].mapGraphic = new string[25]{
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&&%#&#&%#&&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@##@###/\@#*@@#*##@#*##@#*##@#*##@#*##@##@#*##@#*##*#)",
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&&#/__\&#&&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@#*##@#*##@#*##@#*##@#*##@#*##@##@#/\--/\#@@#*##@#*##@#*##@#*##@#*##@##@#*##@#*##*#)",
			R"(#@##&#&%#&#&%#&#&%#&%&%#&%&%#&%&%#&%&%#@##&/__\/__\&&#&%#&%&%#&%&%#&%&%#&%&%#@##&#&%#&#&%%&%)",
			R"(#@##@#*##@                                                                        *##@#*##*#)",
			R"(#@##&#&%#&         Thanks  for  opening  the  gate  Link  You  saved  me!         &%#&#&%%&%)",
			R"(#@##@#*##@                                                                        *##@#*##*#)",
			R"(##@#####%@                                                                        @##&#&%%&%)",
			R"(#&#&&#&#&&                                    A                                   &*#@#*##*#)",
			R"(#@#*##@#*#                                   ZZZ                                  ##@####@##)",
			R"(#&#&&#&#&&                                   / \                                  #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        ##@####@##)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*#                                                                        #@#*##@#*#)",
			R"(#&#&&#&#&&                                                                        #&%&%#&%&%)",
			R"(#@#*##@#*###@####@####@####@####@####@####          #####@####@####@###@#*##@#*#@#@####@####)",
			R"(#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&#&#&&##          &&%#&#&%#&%&%#&%&%#&%&%#&%&%@##&#&&#&#&&)",
			R"(#@#*##@#*##@#*##@#*##@#*##@#*##@#*##@#*###          @@##@#*##@#*##@#*##@#*##@#*#@#*##@#*##@#)"
			};
			maps[i].mapType = MapType::Castle;
			break;
		default:
			break;
		}

	}
}
void MapChange(GameData& gd, Directions dir)
{
	switch (gd.actualMap.name)
	{
	case MapNames::StartValley:
		if (dir == Directions::East)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::Mountain1)];
			gd.storedPosition = gd.player.position;
			gd.player.position = { 2, 17 };
		}
		else if (dir == Directions::North)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::HyruleField)];
			gd.storedPosition = gd.player.position;
			gd.player.position = { 74, 28 };
		}
		else if (dir == Directions::West)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::WesternRiver)];
			gd.storedPosition = gd.player.position;
			gd.player.position = { 93, 17 };
		}
		break;
	case MapNames::Cave1:
	case MapNames::Cave2:
	case MapNames::FairysFountain:
		if (dir == Directions::South)
		{
			gd.actualMap = gd.previousMap;
			gd.player.position = gd.storedPosition;
		}
		break;
	case MapNames::Mountain1:
		for (int i = 0; i < gd.MAX_ENEMIES; i++)
		{
			gd.enemies[i].isActiveEnemy = false;
			gd.enemies[i].isAlive = false;
		}

		if (dir == Directions::West)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::StartValley)];
			gd.player.position = { 93, 17 };
		}
		else if (dir == Directions::East)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::CastleEntrance)];
			gd.player.position = { 2, 17 };
		}
		break;
	case MapNames::WesternRiver:
		if (dir == Directions::East)
		{
			gd.player.position = { 2, 17 };
			gd.actualMap = gd.maps[static_cast<int>(MapNames::StartValley)];
		}
		else if (dir == Directions::North)
		{
			gd.previousMap = gd.actualMap;
			gd.storedPosition = gd.player.position;
			gd.actualMap = gd.maps[static_cast<int>(MapNames::FairysFountain)];
			gd.player.position = { 45, 28 };
		}
		break;
	case MapNames::HyruleField:
		if (dir == Directions::North)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::KokiriForest)];
			gd.storedPosition = gd.player.position;
			gd.player.position = { 45, 28 };
		}
		else if (dir == Directions::South)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::StartValley)];
			gd.player.position = { 48, 4 };
		}
		break;
	case MapNames::KokiriForest:
		gd.actualMap = gd.maps[static_cast<int>(MapNames::HyruleField)];
		gd.player.position = { 15, 4 };
		break;
	case MapNames::CastleEntrance:
		if (dir == Directions::West)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::Mountain1)];
			gd.player.position = { 93, 17 };
		}
		else if (dir == Directions::North)
		{
			gd.actualMap = gd.maps[static_cast<int>(MapNames::HyruleCastle)];
			gd.player.position = { 48, 28 };
		}
		break;
	default:
		break;
	}

	for (int i = 0; i < gd.actualEnemies; i++)
	{
		gd.enemies[i] = gd.deadEnemy;
	}

	switch (gd.actualMap.name)
	{
	case MapNames::Mountain1:
	case MapNames::HyruleField:
	case MapNames::WesternRiver:
	case MapNames::KokiriForest:
	{
		int counter = 0;

		const int spidersQty = 5;
		Enemy spider[spidersQty];
		for (int i = 0; i < spidersQty; i++)
		{
			spider[i].HealthPoints = 1;
			spider[i].isActiveEnemy = true;
			spider[i].enemyType = EnemyType::Spider;
			spider[i].isAlive = true;

			switch (i)
			{
			case 0:
				spider[i].position = { 14, 20 };
				break;
			case 1:
				if (gd.actualMap.name == MapNames::Mountain1)
					spider[i].position = { 45, 12 };
				else
					spider[i].position = { 15, 12 };
				break;
			case 2:
				spider[i].position = { 76, 14 };
				break;
			case 3:
				spider[i].position = { 65, 23 };
				break;
			case 4:
				spider[i].position = { 80, 22 };
				break;
			default:
				break;
			}
			spider[i].previousPosition = spider[i].position;
			gd.enemies[counter] = spider[i];
			counter++;
		}

		Octorok octorok;
		octorok.HealthPoints = 1;
		octorok.isActiveEnemy = true;
		octorok.enemyType = EnemyType::Octorok;
		octorok.isAlive = true;

		if (gd.actualMap.name == MapNames::Mountain1)
			octorok.position = { 5, 20 };
		else if (gd.actualMap.name == MapNames::HyruleField)
			octorok.position = { 60, 20 };
		else
			octorok.position = { 80, 12 };


		octorok.previousPosition = octorok.position;
		gd.enemies[counter] = octorok;

		gd.actualEnemies = spidersQty + 1;
	}
	break;
	default:
		break;
	}

}
void MapChange(GameData& gd, bool isCave)
{
	for (int i = 0; i < gd.actualEnemies; i++)
	{
		gd.enemies[i] = gd.deadEnemy;
	}

	switch (gd.actualMap.name)
	{
	case MapNames::StartValley:
		gd.previousMap = gd.actualMap;
		gd.actualMap = gd.maps[static_cast<int>(MapNames::Cave1)];
		gd.storedPosition = gd.player.position;
		gd.player.position = { 48, 28 };
		break;
	case MapNames::KokiriForest:
		gd.previousMap = gd.actualMap;
		gd.actualMap = gd.maps[static_cast<int>(MapNames::Cave2)];
		gd.storedPosition = gd.player.position;
		gd.player.position = { 48, 28 };
		break;
	}
}
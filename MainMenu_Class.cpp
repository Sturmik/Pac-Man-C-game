#include "MainMenu_Class.h"

void MainMenu::Menu()
{
	// Player menu choice;
	char choice = '1';

	int Paragraph = 1;

	// Position of arrow (choosing arrow)
	int ChoicePos_x = 50;
	int ChoicePos_y;

	Gotoxy Pos;
	Color MenuColor;
	User_Window Tabs;

	while (5)
	{
		MenuColor.SetColor(14, 0);
		system("cls");

		Pos.gotoxy(20, 3);
		cout << "###############################################################################################";
		Pos.gotoxy(20, 4);
		cout << "#####        ########  #########          #########    ####    ########  ########  #####  #####";
		Pos.gotoxy(20, 5);
		cout << "#####  ####  #######    ########  #################  #  ##  #  #######    #######    ###  #####";
		Pos.gotoxy(20, 6);
		cout << "#####  ####  ######  ##  #######  #################  ##    ##  ######  ##  ######  #  ##  #####";
		Pos.gotoxy(20, 7);
		cout << "#####        #####  ####  ######  ###########    ##  ###  ###  #####  ####  #####  ##  #  #####";
		Pos.gotoxy(20, 8);
		cout << "#####  ##########          #####  #################  ########  ####          ####  ###    #####";
		Pos.gotoxy(20, 9);
		cout << "#####  #########  ########  ####  #################  ########  ###  ########  ###  ####   #####";
		Pos.gotoxy(20, 10);
		cout << "#####  ########  ##########  ###          #########  ########  ##  ##########  ##  #####  #####";
		Pos.gotoxy(20, 11);
		cout << "###############################################################################################";
		MenuColor.SetColor(15, 0);

		Tabs.CreateUserWindow(0, 12, ChoicePos_x, 17, "New Game", "", 14, 15);
		Tabs.CreateUserWindow(0, 12, ChoicePos_x, 20, "Statistics", "", 14, 15);
		Tabs.CreateUserWindow(0, 12, ChoicePos_x, 23, "About", "", 14, 15);
		Tabs.CreateUserWindow(0, 12, ChoicePos_x, 26, "Exit", "", 14, 15);

		if (Paragraph == 1)
			ChoicePos_y = 17;
		if (Paragraph == 2)
			ChoicePos_y = 20;
		if (Paragraph == 3)
			ChoicePos_y = 23;
		if (Paragraph == 4)
			ChoicePos_y = 26;

		MenuColor.SetColor(15, 0);
		Pos.gotoxy(ChoicePos_x + 20, ChoicePos_y);
		cout << " <============\t^ - W     v - S     confirm - SPACE";
		MenuColor.SetColor(15, 0);

		choice = _getch();

		if (choice == 'w' || choice == 'W')
		{
			if (Paragraph - 1 >= 1)
				Paragraph--;
			else
				Paragraph = 5;
		}
		if (choice == 's' || choice == 'S')
		{
			if (Paragraph + 1 <= 4)
				Paragraph++;
			else
				Paragraph = 1;
		}

		if (choice == ' ')
		{
			if (Paragraph == 1)
				Start();
			if (Paragraph == 2)
				Statistics();
			if (Paragraph == 3)
				About();
			if (Paragraph == 4)
				return;
		}
	}
}

void MainMenu::Start()
{
	system("cls");

	PacMan Pac;

	Pac.ChangeMap(rand() % 2 + 1);

	Pac.Set_Score(0);
	Pac.Set_Life(3);

	Ghost* Enemy = new Ghost[4];

	User_Window Show;

	Color GameColor;
	Gotoxy Windows;

	// Here user will enter his name

	char temp[15];
	Show.CreateUserWindow(1, 40, 50, 20, "ENTER YOUR NAME", "", 14, 15);
	GameColor.SetColor(0, 14);
	Windows.gotoxy(51, 21);
	cin.getline(temp, 15);
	string player_name = temp;
	GameColor.SetColor(15, 0);

	// Fisrt type of ghost - It will try to reach your position ( It will get it with Get_Pac_Pos)

	// Second type of ghost - It will try to reach your last twentieth position
	int LastPacPos_Timer = 0;
	int LastPacPos_x;
	int LastPacPos_y;
	// Third type of ghost - It will try to reach your last third position
	int LastLastPacPos_Timer = 0;
	int LastLastPacPos_x;
	int LastLastPacPos_y;
	// Fourth type of ghost - It will try to get ahead of you
	int FuturePacPos_x;
	int FuturePacPos_y;

	while (Pac.Get_Life() > 0)
	{
		system("cls");
		if (Pac.GetLevel() == 1)
		{
			Pac.Spawn(1, 40);
			Enemy[0].Ghost_Spawn(9, 35, Pac.GetMap());
			Enemy[1].Ghost_Spawn(9, 36, Pac.GetMap());
			Enemy[2].Ghost_Spawn(9, 37, Pac.GetMap());
			Enemy[3].Ghost_Spawn(9, 38, Pac.GetMap());
		}
		if (Pac.GetLevel() == 2)
		{
			Pac.Spawn(13, 25);
			Enemy[0].Ghost_Spawn(1, 10, Pac.GetMap());
			Enemy[1].Ghost_Spawn(1, 15, Pac.GetMap());
			Enemy[2].Ghost_Spawn(1, 20, Pac.GetMap());
			Enemy[3].Ghost_Spawn(1, 25, Pac.GetMap());
		}

		char move = 'w';
		while (5)
		{
			Windows.gotoxy(0, 0);
			Pac.ShowMap();

			if (LastPacPos_Timer == 0)
			{
				LastPacPos_x = Pac.Get_X();
				LastPacPos_y = Pac.Get_Y();
				LastPacPos_Timer = 20;
			}

			if (LastLastPacPos_Timer == 0)
			{
				LastLastPacPos_x = Pac.Get_X();
				LastLastPacPos_y = Pac.Get_Y();
				LastLastPacPos_Timer = 30;
			}

			Show.CreateUserWindow(1, 20, 10, row + 5, "SCORE", Pac.Get_Score(), 15, 2);
			Show.CreateUserWindow(1, 20, 40, row + 5, "LIFES", Pac.Get_Life(), 15, 4);

			Sleep(50);

			if (_kbhit())
				move = _getch();

			if (move == 'w' || move == 'W')
				Pac.Move(1);
			if (move == 's' || move == 'S')
				Pac.Move(2);
			if (move == 'a' || move == 'A')
				Pac.Move(3);
			if (move == 'd' || move == 'D')
				Pac.Move(4);
			if (move == 27)
			{
				Pac.Set_Score(0);
				return;
			}

			for (int i = 0; i < 4; i++)
			{
				if (i == 0)		// Ghost type one - Straight forward to pac-man position
					Enemy[i].Ghost_Form_Way(Pac.Get_Y(), Pac.Get_X(), Pac.GetMap(), Pac.GetRow(), Pac.GetCol());
				if (i == 1)		// Ghost type two - Last tenth pac-man position
					Enemy[i].Ghost_Form_Way(LastPacPos_y, LastPacPos_x, Pac.GetMap(), Pac.GetRow(), Pac.GetCol());
				if (i == 2)		// Ghost type three - Last third pac-man position
					Enemy[i].Ghost_Form_Way(LastLastPacPos_y, LastLastPacPos_x, Pac.GetMap(), Pac.GetRow(), Pac.GetCol());
				if (i == 3)		// Ghost type four - Tries to predict pac-man position
				{
					Enemy[i].Ghost_Predict(Pac.Get_Y(), Pac.Get_X(), FuturePacPos_y, FuturePacPos_x, Pac.GetMap(), move, 10);
					Enemy[i].Ghost_Form_Way(FuturePacPos_y, FuturePacPos_x, Pac.GetMap(), Pac.GetRow(), Pac.GetCol());
				}
				if (Pac.Ghost_Collide() == true)
				{
					Pac.Set_Life(Pac.Get_Life() - 1);
					system("cls");
					Windows.gotoxy(0, 0);
					Pac.ShowMap();
					GameColor.SetColor(4, 0);
					Sleep(1000);
					GameColor.SetColor(0, 4);
					Sleep(300);
					if (Pac.Get_Life()== 0)
					{
						system("cls");
						Data.AddNewNode(__DATE__, __TIME__, player_name, Pac.Get_Score());
						Data.SaveData();
						GameColor.SetColor(15, 0);
						Show.CreateUserWindow(2, 30, col / 2 + 10, row / 2, "GAME OVER", Pac.Get_Score(), 15, 4);
						Windows.gotoxy(col / 2, row / 2 + 4);
						system("pause");
						return;
					}
					system("pause");
					break;
				}
			}

			if (Pac.Ghost_Collide() == true)
			{
				GameColor.SetColor(15, 0);
				Pac.CleanGhosts();
				break;
			}

			if (Pac.CheckForPoints() == true)
			{
				Pac.Set_Life(Get_Life() + 1);
				Pac.ChangeMap(rand() % 2 + 1);
				GameColor.SetColor(15, 0);
				break;
			}

			LastPacPos_Timer--;
			LastLastPacPos_Timer--;
		}
	}
}

void MainMenu::Statistics()
{
	system("cls");

	Gotoxy Pos;
	User_Window Show;
	Color Color_Set;

	char choice;

	Show.CreateUserWindow(32, 157, 1, 0, "STATISTICS", "", 14, 4, 'C');

	Color_Set.SetColor(4, 14);
	cout << "\n\t DATE\t\t\t TIME\t\t\t NAME \t\t SCORE" <<  endl;
	Data.ShowAllNodes();
	Color_Set.SetColor(15, 0);

	Show.CreateUserWindow(1, 15, 20, 29, "EXIT", "ESC", 15, 4);
	Show.CreateUserWindow(1, 15, 40, 29, "CLEAR ALL", "P", 15, 4);
	while (5)
	{
		choice = _getch();
		if (choice == 27)
			return;
		if (choice == 'p' || choice == 'P')
		{
			Data.ClearAllNodes();
			return;
		}
	}
}

void MainMenu::About()
{
	Gotoxy Pos;
	Color GameColor;
	GameColor.SetColor(14, 0);
	system("cls");
	Pos.gotoxy(20, 3);
	cout << "###############################################################################################";
	Pos.gotoxy(20, 4);
	cout << "#####        ########  #########          #########    ####    ########  ########  #####  #####";
	Pos.gotoxy(20, 5);
	cout << "#####  ####  #######    ########  #################  #  ##  #  #######    #######    ###  #####";
	Pos.gotoxy(20, 6);
	cout << "#####  ####  ######  ##  #######  #################  ##    ##  ######  ##  ######  #  ##  #####";
	Pos.gotoxy(20, 7);
	cout << "#####        #####  ####  ######  ###########    ##  ###  ###  #####  ####  #####  ##  #  #####";
	Pos.gotoxy(20, 8);
	cout << "#####  ##########          #####  #################  ########  ####          ####  ###    #####";
	Pos.gotoxy(20, 9);
	cout << "#####  #########  ########  ####  #################  ########  ###  ########  ###  ####   #####";
	Pos.gotoxy(20, 10);
	cout << "#####  ########  ##########  ###          #########  ########  ##  ##########  ##  #####  #####";
	Pos.gotoxy(20, 11);
	cout << "###############################################################################################";
	GameColor.SetColor(15, 0);

	cout << "\n\n\t\t\t In this game you play as C-like character - "; GameColor.SetColor(14, 0); cout << " C "; GameColor.SetColor(15, 0); cout << " - it's pacman";
	cout << "\n\t\t\t Your objective is to collect all points, which look like this - "; GameColor.SetColor(14, 0);  cout << " * "; GameColor.SetColor(15, 0); 
	cout << "\n\t\t\t Each one gives you +100 points";
	cout << "\n\n\t\t\t However, it won't be that easy, you are going to confront ghosts. They look like these - "; GameColor.SetColor(rand() % 15 + 1, 0); cout << " Ï "; GameColor.SetColor(15, 0); 
	cout << "\n\n\t\t\t Ghost can differ in their behaviour, try to analyze what they're doing.";

	cout << "\n\n\t\t\t By the way, there are portals on the map, which you can use!";

	cout << "\n\n\t\t\t Good luck and try to get the best score!";

	cout << "\n\n\t\t\t Movement: | W - UP | S - DOWN | A - LEFT | D - RIGHT |" << endl << endl << endl;
	cout << "\t";
	system("pause");
}

void MainMenu::Save()
{
	Data.SaveData();
}

void MainMenu::Load()
{
	Data.LoadData();
}

MainMenu::MainMenu()
{
	Load();
}

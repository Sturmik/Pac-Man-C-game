#include "Ghost_Class.h"

void Ghost::Ghost_Move(char**& Map_Check)
{
	if (Way.GetCount() > 0)
	{
		int Where_To_Go = Way.GetFirst();

		// These variables remember las position of the ghost to avoid deleting previous element
		int Fill_y = Ghost_Pos_y;
		int Fill_x = Ghost_Pos_x;		

		// This variable will remember the symbol which ghost will go through
		char temp = NULL;

		// The ghost will finally move and change it position
		switch (Where_To_Go)
		{
		case 1:
			if (Map_Check[Ghost_Pos_y - 1][Fill_x] != 'Ï')
			{
				Ghost_Pos_y--;
				temp = Map_Check[Ghost_Pos_y][Fill_x];
			}
			break;
		case 2:
			if (Map_Check[Ghost_Pos_y + 1][Fill_x] != 'Ï')
			{
				Ghost_Pos_y++;
				temp = Map_Check[Ghost_Pos_y][Fill_x];
			}
			break;
		case 3:
			if (Map_Check[Ghost_Pos_y][Fill_x - 1] != 'Ï')
			{
				Ghost_Pos_x--;
				temp = Map_Check[Fill_y][Ghost_Pos_x];
			}
			break;
		case 4:
			if (Map_Check[Ghost_Pos_y][Fill_x + 1] != 'Ï')
			{
				Ghost_Pos_x++;
				temp = Map_Check[Fill_y][Ghost_Pos_x];
			}
			break;
		}

		if (temp == 'C')
			Map_Check[Fill_y][Fill_x] = ' ';
		else
			Map_Check[Fill_y][Fill_x] = temp;

		Map_Check[Ghost_Pos_y][Ghost_Pos_x] = 'Ï';
	}
}

Ghost::Ghost()
{
	this->Ghost_Pos_y = 0;
	this->Ghost_Pos_x = 0;
}

Ghost::Ghost(int type, int Ghost_StartPos_y, int Ghost_StartPos_x)
{
	this->Ghost_Pos_y = Ghost_StartPos_y;
	this->Ghost_Pos_x = Ghost_StartPos_x;
}

void Ghost::Ghost_Spawn(int Pos_y, int Pos_x, char**& Map_)
{
	Ghost_Pos_y = Pos_y;
	Ghost_Pos_x = Pos_x;
	Map_[Pos_y][Pos_x] = 'Ï';
}

void Ghost::Ghost_Form_Way(int where_to_go_y, int where_to_go_x, char**& Map_, int rows, int cols)
{
	if (Way.GetCount() > 0)
		Way.DeleteAll();

	// We will create Map to use wave algorithm
	Map Wave;

	int** Way_Finder;
	Wave.Wave_Algorithm_Seek_Way(Ghost_Pos_y, Ghost_Pos_x, where_to_go_y, where_to_go_x, Map_, Way_Finder, rows, cols);

	// Furthermore, we are going to work with 2D array and pave the way

	// We are creating variables to seek the way to the pacman
	int Pos_Go_y = where_to_go_y;
	int Pos_Go_x = where_to_go_x;
	Way_Finder[Ghost_Pos_y][Ghost_Pos_x] = 0;
	// We are going to start from pacman position and go back to ghost position, to find the shortest way

	// First, we're going to analyze our position
	// Also, it is important to know! We are paving the path to the ghost in vice versa 

	// First, we check if the final destination is near us
	if (Pos_Go_y - 1 == Ghost_Pos_y && Pos_Go_x == Ghost_Pos_x)
		Way.AddToHead(2);	// Down
	else
	if (Pos_Go_y + 1 == Ghost_Pos_y && Pos_Go_x == Ghost_Pos_x)
		Way.AddToHead(1);	// Up
	else
	if (Pos_Go_y == Ghost_Pos_y && Pos_Go_x - 1 == Ghost_Pos_x)
		Way.AddToHead(4);	// Right
	else
	if (Pos_Go_y == Ghost_Pos_y && Pos_Go_x + 1 == Ghost_Pos_x)
		Way.AddToHead(3);	// Left
	
	// If the destination is near us, we will jump into "Ghost_Move" immediately
	if (Way.GetCount() > 0)
		Ghost_Move(Map_);
	else
	{
		// Otherwise, we are going to analyze the whole way to our destination

		// First we need to find where we will start

		// These variables will help us to pave the path to the pacman
		int first_Go = NULL;
		int count = FindMaxElemArr2D(Way_Finder, rows, cols);

		if (Way_Finder[Pos_Go_y - 1][Pos_Go_x] < count && Way_Finder[Pos_Go_y - 1][Pos_Go_x] != 0 && Way_Finder[Pos_Go_y - 1][Pos_Go_x] != -5)
		{
			first_Go = 2;	// Down
			count = Way_Finder[Pos_Go_y - 1][Pos_Go_x];
			Pos_Go_y--;
		}
		if (Way_Finder[Pos_Go_y + 1][Pos_Go_x] < count && Way_Finder[Pos_Go_y + 1][Pos_Go_x] != 0 && Way_Finder[Pos_Go_y + 1][Pos_Go_x] != -5)
		{
			first_Go = 1;	// Up
			count = Way_Finder[Pos_Go_y + 1][Pos_Go_x];
			Pos_Go_y++;
		}
		if (Way_Finder[Pos_Go_y][Pos_Go_x - 1] < count && Way_Finder[Pos_Go_y][Pos_Go_x - 1] != 0 && Way_Finder[Pos_Go_y][Pos_Go_x - 1] != -5)
		{
			first_Go = 4;	// Right
			count = Way_Finder[Pos_Go_y][Pos_Go_x - 1];
			Pos_Go_x--;
		}
		if (Way_Finder[Pos_Go_y][Pos_Go_x + 1] < count && Way_Finder[Pos_Go_y][Pos_Go_x + 1] != 0 && Way_Finder[Pos_Go_y][Pos_Go_x + 1] != -5)
		{
			first_Go = 3;	// Left
			count = Way_Finder[Pos_Go_y][Pos_Go_x + 1];
			Pos_Go_x++;
		}
		
		Way.AddToHead(first_Go);

		while (count != 0)
		{

			if (Way_Finder[Pos_Go_y - 1][Pos_Go_x] == count - 1)
			{
				Pos_Go_y -= 1;
				Way.AddToHead(2);	// Down
			}
			else
				if (Way_Finder[Pos_Go_y + 1][Pos_Go_x] == count - 1)
				{
					Pos_Go_y += 1;
					Way.AddToHead(1);	// Up
				}
			else
				if (Way_Finder[Pos_Go_y][Pos_Go_x - 1] == count - 1)
				{
					Pos_Go_x -= 1;
					Way.AddToHead(4);	// Left
				}
				else
					if (Way_Finder[Pos_Go_y][Pos_Go_x + 1] == count - 1)
					{
						Pos_Go_x += 1;
						Way.AddToHead(3);	// Right
					}
			count--;
		}

		Ghost_Move(Map_);
	}
}

// Last parameter defines how far ghost should go
void Ghost::Ghost_Predict(int Pac_Pos_y, int Pac_Pos_x, int& where_to_go_y, int& where_to_go_x, char**& Map_, char Pac_Route, int Forehead_Go)
{
	if (Pac_Route == 'w' || Pac_Route == 'W')	// Defines where ghost should go ahead
	{
		for (int i = 0; i < Forehead_Go; i++)
		{
			if (Map_[Pac_Pos_y + 1][Pac_Pos_x] != '#')
				Pac_Pos_y++;
			else
				if (Map_[Pac_Pos_y][Pac_Pos_x + 1] != '#')
					Pac_Pos_x++;
				else
					if (Map_[Pac_Pos_y][Pac_Pos_x - 1] != '#')
						Pac_Pos_x--;
		}
	}
	if (Pac_Route == 's' || Pac_Route == 'S')
	{
		for (int i = 0; i < Forehead_Go; i++)
		{
			if (Map_[Pac_Pos_y - 1][Pac_Pos_x] != '#')
				Pac_Pos_y--;
				else
					if (Map_[Pac_Pos_y][Pac_Pos_x + 1] != '#')
						Pac_Pos_x++;
					else
						if (Map_[Pac_Pos_y][Pac_Pos_x - 1] != '#')
							Pac_Pos_x--;
		}
	}
	if (Pac_Route == 'a' || Pac_Route == 'A')
	{
		for (int i = 0; i < Forehead_Go; i++)
		{
			if (Map_[Pac_Pos_y + 1][Pac_Pos_x] != '#')
				Pac_Pos_y++;
			else
				if (Map_[Pac_Pos_y - 1][Pac_Pos_x] != '#')
					Pac_Pos_y--;
				else
					if (Map_[Pac_Pos_y][Pac_Pos_x - 1] != '#')
						Pac_Pos_x--;
		}
	}
	if (Pac_Route == 'd' || Pac_Route == 'D')
	{
		for (int i = 0; i < Forehead_Go; i++)
		{
			if (Map_[Pac_Pos_y + 1][Pac_Pos_x] != '#')
				Pac_Pos_y++;
			else
				if (Map_[Pac_Pos_y - 1][Pac_Pos_x] != '#')
					Pac_Pos_y--;
				else
					if (Map_[Pac_Pos_y][Pac_Pos_x + 1] != '#')
						Pac_Pos_x++;
		}
	}

	where_to_go_y = Pac_Pos_y;
	where_to_go_x = Pac_Pos_x;
}

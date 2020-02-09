#include "PacMan_Class.h"

PacMan::PacMan(int PacMan_Pos_y, int PacMan_Pos_x, int life)
{
	this->PacMan_Pos_y = PacMan_Pos_y;
	this->PacMan_Pos_x = PacMan_Pos_x;
	this->life = life;
	this->score = 0;
}

int PacMan::Get_X()
{
	return PacMan_Pos_x;
}

int PacMan::Get_Y()
{
	return PacMan_Pos_y;
}

int PacMan::Get_Life()
{
	return life;
}

int PacMan::Get_Score()
{
	return score;
}

void PacMan::Set_Life(int NewLife)
{
	this->life = NewLife;
}

void PacMan::Set_Score(int NewScore)
{
	this->score = NewScore;
}

void PacMan::Spawn(int NewPac_Pos_y, int NewPac_Pos_x)
{
	if (Recent_Map[NewPac_Pos_y][NewPac_Pos_x] != '#')
	{
		Recent_Map[NewPac_Pos_y][NewPac_Pos_x] = 'C';
		PacMan_Pos_y = NewPac_Pos_y;
		PacMan_Pos_x = NewPac_Pos_x;
	}
}

//  1 - Up |  2 - Down | 3 - Left | 4 - Right
bool PacMan::Move(int Move_To)
{
	if (Ghost_Collide() == true)
		return false;

	// New PacMan positions
	int y = PacMan_Pos_y;
	int x = PacMan_Pos_x;

	if (Move_To == 1)
		y--;	// Up
	if (Move_To == 2)
		y++;	// Down
	if (Move_To == 3)
		x--;	// Left
	if (Move_To == 4)
		x++;	// Right


	// These are portals for our pacman
	if (Recent_Map[y][x] == '0')
	{
		if (Move_To == 1)
			Recent_Map[y + 1][x] = ' ';
		if (Move_To == 2)
			Recent_Map[y - 1][x] = ' ';
		if (Move_To == 3)
			Recent_Map[y][x + 1] = ' ';
		if (Move_To == 4)
			Recent_Map[y][x - 1] = ' ';

		for (int i = 0; i < col; i++)
		{
			if (Recent_Map[y][i] == '0' && i != x)
			{
				if (Move_To == 1)
				{
					y--;
					if (Recent_Map[y][i] == '*')
						score += 100;
					Recent_Map[y][i] = 'C';
					x = i;
					break;
				}
				if (Move_To == 2)
				{
					y++;
					if (Recent_Map[y][i] == '*')
						score += 100;
					Recent_Map[y][i] = 'C';
					x = i;
					break;
				}
				if (Move_To == 3)
				{
					i--;
					if (Recent_Map[y][i] == '*')
						score += 100;
					Recent_Map[y][i] = 'C';
					x = i;
					break;
				}
				if (Move_To == 4)
				{
					i++;
					if (Recent_Map[y][i] == '*')
						score += 100;
					Recent_Map[y][i] = 'C';
					x = i;
					break;
				}
			}
		}

		for (int i = 0; i < row; i++)
		{
			if (Recent_Map[i][x] == '0' && i != y)
			{
				if (Move_To == 1)
				{
					i--;
					if (Recent_Map[i][x] == '*')
						score += 100;
					Recent_Map[i][x] = 'C';
					y = i;
					break;
				}
				if (Move_To == 2)
				{
					i++;
					if (Recent_Map[i][x] == '*')
						score += 100;
					Recent_Map[i][x] = 'C';
					y = i;
					break;
				}
				if (Move_To == 3)
				{
					x--;
					if (Recent_Map[i][x] == '*')
						score += 100;
					Recent_Map[i][x] = 'C';
					y = i;
					break;
				}
				if (Move_To == 4)
				{
					x++;
					if (Recent_Map[i][x] == '*')
						score += 100;
					Recent_Map[i][x] = 'C';
					y = i;
					break;
				}
			}
		}


		PacMan_Pos_y = y;
		PacMan_Pos_x = x;
	}
	else
	if (Recent_Map[y][x] == ' ' || Recent_Map[y][x] == '*')
	{
		if (Recent_Map[y][x] == '*')
			score += 100;
		Recent_Map[y][x] = 'C';
		Recent_Map[PacMan_Pos_y][PacMan_Pos_x] = ' ';

		PacMan_Pos_y = y;
		PacMan_Pos_x = x;
	}

	return true;
}

bool PacMan::Ghost_Collide()
{
	if (Recent_Map[PacMan_Pos_y][PacMan_Pos_x] == 'Ï')
		return true;
	return false;
}

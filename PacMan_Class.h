#pragma once

#include "Map_Class.h"

// This class contains information about our main character
class PacMan : public Map	// We inherit map class to allow us move pacman on it.
{
protected:
	int PacMan_Pos_y;	// PacMan position in 2D array	
	int PacMan_Pos_x;	
	
	int life;		// PacMan lifes
	int score;		// PacMan score
public:
	PacMan() : PacMan(1) {}
	PacMan(int PacMan_Pos_y) : PacMan(PacMan_Pos_y, 1) {}
	PacMan(int PacMan_Pos_y, int PacMan_Pos_x) : PacMan(PacMan_Pos_y, PacMan_Pos_x, 3) {}
	PacMan(int PacMan_Pos_y, int PacMan_Pos_x, int life);

	int Get_X();	// Allows us to get PacMan x position
	int Get_Y();	// Allows us to get PacMan y position

	int Get_Life();		// Allow us to get PacMan life
	int Get_Score();	// Allow us to get PacMan score

	void Set_Life(int NewLife);
	void Set_Score(int NewScore);

	void Spawn(int NewPac_Pos_y, int NewPac_Pos_x);		// This function spawn our pacman on the map

	bool Move(int Move_To);		// This function moves pacman through the map. It return false, if PacMan collides with ghost.

	bool Ghost_Collide();
};
#pragma once

#include "Map_Class.h"

// This class is going to represent ghosts
class Ghost
{
	// Ghost will have unique behaviour
			// 1. Going straight to the player position
			// 2 - 3. Going further to the penultimate position
			// 4. Going on further positon

	int Ghost_Pos_x;
	int Ghost_Pos_y;

	// Ghosts will store their movement in list structure
	TwoWayList<int> Way;
	// List will store integer values, which will mean: 
	//	1 - Go up
	//	2 - Go down
	//	3 - Go left
	//	4 - Go right


	void Ghost_Move(char**& Map_Check);	// Ghost movement on the map
public:
	Ghost();
	Ghost(int type, int Ghost_StartPos_y, int Ghost_StartPos_x);

	// This function places our ghost on the map
	void Ghost_Spawn(int Pos_y, int Pos_x, char**& Map_);

	// This function will coloborate with wave algorithm from "Map_Class.h"
	void Ghost_Form_Way(int where_to_go_y, int where_to_go_x, char**& Map_, int rows, int cols);

	// This function/
	void Ghost_Predict(int Pac_Pos_y, int Pac_Pos_x, int& where_to_go_y , int& where_to_go_x, char**& Map_, char Pac_Route, int Forehead_Go = 5);
};
#pragma once

#include "Functions.h"

// This class will show us the map and allow to change it.
class Map
{
	// Here we will store levels of this game.
private:
	char Map1[11][80]		//  Level - 1
	{
		"###############################################################################",
		"#                                                                             #",
		"# ###### ############## ############ #############      ####################  #",
		"# ###### ####    ###### #######           ######## ####                       #",
		"#      #       # ####           #### ####               ###### ## ###### #### #",
		"# ## # # 0 ## ## ###   ## ########## ############# ########### ##       0     #",
		"# ## # #      ## #   ####                                      ## ###### #### #",
		"# ## #   ## ####   ########################################### ##             #",
		"# ## ###### #### ############################################# ############## #",
		"#                                                                             #",
		"###############################################################################",
	};

	char Map2[15][50]		//  Level - 2
	{
		"#################################################",
		"#                       0                       #",
		"# ## #### # ######################### # #### ## #",
		"# ## #### #                           # #### ## #",
		"# ## #### # ############  ########### # #### ## #",
		"#                                               #",
		"# ## #### #############   ############  #### ## #",
		"# ## ####                              ##### ## #",
		"# ## #####  ###########   ##########  ###### ## #",
		"# #                                           # #",
		"# # ######################################### # #",
		"# #                                           # #",
		"# # #### ############################### #### # #",
		"#                       0                       #",
		"#################################################",
	};
protected:
	int row;
	int col;

	int Level;		// Game level

	char** Recent_Map;	// Map, on which we will play
public:
	~Map();	// Destructor

	Map() : Map (1) {}
	Map(int choice);

	char**& GetMap(); 

	int GetRow() const;
	int GetCol() const;

	int GetLevel() const;
	
	bool CheckForPoints() const;
	void CleanGhosts(); // This function deletes all ghosts from the map. We will use it to remove ghosts, after pacman dies

	void ShowMap();

	// Function to change the map, we play on
	void ChangeMap(int choice);

	// Wave algorithm is functional part of this class and can work separately
	// Function will analyze if it is possible to get to certain position.
	// At same time it will build the way to that position.
	bool Wave_Algorithm_Seek_Way(int startPosY, int startPosX, int finalPosY, int finalPosX, char**& MapToAnalyze, int**& CheckMap, int  row, int col);
};

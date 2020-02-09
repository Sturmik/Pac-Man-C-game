#pragma once

#include "Ghost_Class.h"
#include "PacMan_Class.h"
#include "BinaryTree_Class.h"

// This class will serve as main menu.
// Here we will control the process of the game
// Setup the settings and save our score
class MainMenu : protected PacMan, protected Ghost
{
private:
	BinaryTree Data;

	void Start();

	void Statistics(); // Info about player's scores

	void About(); // Short info about game mechanics

	void Save();
	void Load();
public:
	MainMenu();

	void Menu();
};
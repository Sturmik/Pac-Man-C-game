#include "MainMenu_Class.h"

int main()
{
	// This part of the code allows us to change window size 
	system("mode con cols=159 lines=40");

	// Here we will open game menu
	setlocale(LC_ALL, "");
	MainMenu PacMan;
	PacMan.Menu();
}

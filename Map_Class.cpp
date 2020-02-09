#include "Map_Class.h"

Map::~Map()
{
	DeleteArr2D(Recent_Map, row);
}

// You can choose which map you want to upload.
Map::Map(int choice)
{
	ChangeMap(choice);
}

char**& Map::GetMap() 
{
	return Recent_Map;
}

int Map::GetRow() const
{
	return row;
}

int Map::GetCol() const
{
	return col;
}

int Map::GetLevel() const
{
	return Level;
}

bool Map::CheckForPoints() const
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (Recent_Map[i][j] == '*')
				return false;
	return true;
}

void Map::CleanGhosts()
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (Recent_Map[i][j] == 'Ï')
				Recent_Map[i][j] = ' ';
}

void Map::ShowMap()
{
	ShowDynArr2D(Recent_Map, row, col);
}

void Map::ChangeMap(int choice)
{
	if (Recent_Map)
		DeleteArr2D(Recent_Map, row);


	if (choice == 1)
	{
		this->row = 11;
		this->col = 80;
	}

	if (choice == 2)
	{
		this->row = 15;
		this->col = 50;
	}

	CreateArr2D(Recent_Map, this->row, this->col);

	for (int i = 0; i < this->row; i++)
		for (int j = 0; j < this->col; j++)
		{
			if (choice == 1)
			{
				if (Map1[i][j] == ' ')
					Recent_Map[i][j] = '*';
				else
					Recent_Map[i][j] = Map1[i][j];
			}
			if (choice == 2)
			{
				if (Map2[i][j] == ' ')
					Recent_Map[i][j] = '*';
				else
					Recent_Map[i][j] = Map2[i][j];
			}
		}

	Level = choice;
}

bool Map::Wave_Algorithm_Seek_Way(int startPosY, int startPosX, int finalPosY, int finalPosX, char**& MapToAnalyze, int**& CheckMap, int row, int col)
{
	// Firstly, we will convert two-dimensional char array in int form.

	CreateArr2D(CheckMap, row, col);

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			CheckMap[i][j] = 0;


	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (MapToAnalyze[i][j] == '#')
				CheckMap[i][j] = -5;
			else
				CheckMap[i][j] = 0;

		}
	cout << endl;

	// Now we're going to analyze our starting position

	if (CheckMap[startPosY + 1][startPosX] == 0)
		CheckMap[startPosY + 1][startPosX] = 1;

	if (startPosY + 1 == finalPosY)
		if (startPosX == finalPosX)
			return true;

	if (CheckMap[startPosY - 1][startPosX] == 0)
		CheckMap[startPosY - 1][startPosX] = 1;

	if (startPosY - 1 == finalPosY)
		if (startPosX == finalPosX)
			return true;

	if (CheckMap[startPosY][startPosX + 1] == 0)
		CheckMap[startPosY][startPosX + 1] = 1;

	if (startPosY == finalPosY)
		if (startPosX == finalPosX + 1)
			return true;

	if (CheckMap[startPosY][startPosX - 1] == 0)
		CheckMap[startPosY][startPosX - 1] = 1;

	if (startPosY == finalPosY)
		if (startPosX == finalPosX - 1)
			return true;

	// Start of analyzing

	// - This variable is our main construction element. It will put number through all the way and help us to find the shortest path to our destination
	int wave = 2;
	// - Wave analyzer. It will stop the cycle, if there is no way to reach our destination
	bool waveCheck = false;

	while (5)
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
			{
				if (CheckMap[i][j] == wave - 1)
				{

					if (CheckMap[i + 1][j] == 0)
					{
						CheckMap[i + 1][j] = wave;
						waveCheck = true;
					}

					if (CheckMap[i - 1][j] == 0)
					{
						CheckMap[i - 1][j] = wave;
						waveCheck = true;
					}
			
					if (CheckMap[i][j + 1] == 0)
					{
						CheckMap[i][j + 1] = wave;
						waveCheck = true;
					}


					if (CheckMap[i][j - 1] == 0)
					{
						CheckMap[i][j - 1] = wave;
						waveCheck = true;
					}

					if (i + 1 == finalPosY)
						if (j == finalPosX)
							return true;

					if (i - 1 == finalPosY)
						if (j == finalPosX)
							return true;

					if (i == finalPosY)
						if (j == finalPosX + 1)
							return true;

					if (i == finalPosY)
						if (j == finalPosX - 1)
							return true;
				}
			}

		if (waveCheck == false)
			break;
		else
		{
			waveCheck = false;
			wave++;
		}
	}

	return false;
}

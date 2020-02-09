#pragma once

// This file will help us to work with two dimensional array which will serve us as map

#include "Functions_Class.h"

template <class T>
void CreateArr2D(T**& arr, int row, int col)
{
	arr = new T * [row];
	for (int i = 0; i < row; i++)
	{
		arr[i] = new T[col];
	}
}

template <class T>
void DeleteArr2D(T**& arr, int row)
{
	for (int i = 0; i < row; i++)
		delete[] arr[i];
	delete[] arr;
	arr = nullptr;
}

template <class T>
void ShowDynArr2D(T**& Arr2D, int row, int col)
{
	Color temp;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			 //This is modified version of ShowArr2D to paint our objects on "map"
			if (Arr2D[i][j] == '#')
				temp.SetColor(15, 15);
			if (Arr2D[i][j] == '0')
				temp.SetColor(9, 0);
			if (Arr2D[i][j] == 'C' || Arr2D[i][j] == '*')
				temp.SetColor(14, 0);
			if (Arr2D[i][j] == 'Ï')
				temp.SetColor(rand() % 15 + 1, 0);
			cout << setw(2) << Arr2D[i][j];
			temp.SetColor(15, 0);
		}
		cout << endl;
	}
}

// This show functions work for presentation of wave algorithm work. 
// I have been using it to see how algorithm builds its way.
template <class T>
void ShowAnalyzeArr2D(T**& Arr2D, int row, int col)
{
	Color temp;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (Arr2D[i][j] == -5)
				temp.SetColor(15, 15);
			cout << setw(2) << Arr2D[i][j];
			temp.SetColor(15, 0);
		}
		cout << endl;
	}
}

template <class T>
T FindMaxElemArr2D(T**& Arr2D, int row, int col)
{
	int max = Arr2D[0][0];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (Arr2D[i][j] > max)
				max = Arr2D[i][j];
		}
	}
	return max;
}
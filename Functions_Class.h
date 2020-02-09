#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <Windows.h>
using namespace std;

// This will alow us to play with color
class Color
{
private:
	enum ConsoleColor
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};
public:
	// Sets Color
	static void SetColor(int text, int background)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	}

	static void SetColor(int text, ConsoleColor/*int*/ background)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
	}
};

// This function works instead of "system clean screen" to avoid blinking of the screen.
class Gotoxy
{
public:
	static void gotoxy(int x, int y)
	{
		COORD coordinates;     // coordinates is declared as COORD
		coordinates.X = x;     // defining x-axis
		coordinates.Y = y;     //defining  y-axis
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
	}
};

// This class helps us to create windows for our main menu
class User_Window
{
public:
	// This function creates windows for menu
	void CreateUserWindow(int width, int length, int x, int y, const char* windowname = 0, const char* innertext = 0, int WithinColor = 15, int OuterColor = 1, char symb = '#')
	{
		Gotoxy pos;
		Color color;
		bool howlong = 0;
		if (windowname)
		{
			if (strlen(windowname) > length)
				windowname = 0;
			else
				howlong = 1;
		}
		for (int i = 0; i < length; i++)
		{
			pos.gotoxy(x + i, y);
			color.SetColor(OuterColor, 0);
			cout << symb;
		}
		if (windowname)
		{
			if (howlong == 1)
			{
				color.SetColor(WithinColor, 0);
				pos.gotoxy(x + (length / 2) - strlen(windowname) / 2, y);
				cout << windowname;
			}
		}
		y++;
		for (int i = 0; i < width; i++)
		{
			color.SetColor(OuterColor, 0);
			pos.gotoxy(x, y + i);
			cout << symb;
			for (int j = 1; j < length - 1; j++)
			{
				pos.gotoxy(x + j, y + i);
				color.SetColor(0, WithinColor);
				cout << " ";
			}
			pos.gotoxy(x + length - 1, y + i);
			color.SetColor(OuterColor, 0);
			cout << symb;
		}
		y += width;
		for (int i = 0; i < length; i++)
		{
			color.SetColor(OuterColor, 0);
			pos.gotoxy(x + i, y);
			cout << symb;
		}
		if (innertext)
		{
			color.SetColor(OuterColor, 15);
			pos.gotoxy(x + length / 2 - 3, y - width);
			cout << innertext;
		}
	}

	template <class T>
	void CreateUserWindow(int width, int length, int x, int y, const char* windowname = 0, T innertext = 0, int WithinColor = 15, int OuterColor = 1, char symb = '#')
	{
		Gotoxy pos;
		Color color;
		bool howlong = 0;
		if (windowname)
		{
			if (strlen(windowname) > length)
				windowname = 0;
			else
				howlong = 1;
		}
		for (int i = 0; i < length; i++)
		{
			pos.gotoxy(x + i, y);
			color.SetColor(OuterColor, 0);
			cout << symb;
		}
		if (windowname)
		{
			if (howlong == 1)
			{
				color.SetColor(WithinColor, 0);
				pos.gotoxy(x + (length / 2) - strlen(windowname) / 2, y);
				cout << windowname;
			}
		}
		y++;
		for (int i = 0; i < width; i++)
		{
			color.SetColor(OuterColor, 0);
			pos.gotoxy(x, y + i);
			cout << symb;
			for (int j = 1; j < length - 1; j++)
			{
				pos.gotoxy(x + j, y + i);
				color.SetColor(0, WithinColor);
				cout << " ";
			}
			pos.gotoxy(x + length - 1, y + i);
			color.SetColor(OuterColor, 0);
			cout << symb;
		}
		y += width;
		for (int i = 0; i < length; i++)
		{
			color.SetColor(OuterColor, 0);
			pos.gotoxy(x + i, y);
			cout << symb;
		}
		if (innertext)
		{
			color.SetColor(OuterColor, 15);
			pos.gotoxy(x + length / 2 - 3, y - width);
			cout << innertext;
		}
	}
};


// This class will help us to store our ghost movement
template <class T>
class TwoWayList
{
public:
	template <class T>
	class TwoWayInfo
	{
		T elem;
		TwoWayInfo* prev, * next;

		TwoWayInfo<T>() : TwoWayInfo(0) {}
		TwoWayInfo<T>(T elem) : TwoWayInfo(elem, nullptr) {}
		TwoWayInfo<T>(T elem, TwoWayInfo* prev) : TwoWayInfo(elem, prev, nullptr) {}
		TwoWayInfo<T>(T elem, TwoWayInfo* prev, TwoWayInfo* next)
		{
			this->elem = elem;
			this->prev = prev;
			this->next = next;
		}
		friend class TwoWayList;
	};

	TwoWayList();

	~TwoWayList();

	void AddToHead(T elem);
	void AddToTail(T elem); 

	void AddElemOnPos(T elem, int pos); 
	void DelElemOnPos(int pos); 

	T GetFirst();

	void DeleteFromHead();
	void DeleteFromTail(); 

	int FindElemPos(T elem); 
	int FindAndChange(T findElem, T newElem);	

	void DeleteAll();

	void Reverse();

	int GetCount();

	void Show() const; 
private:
	int count;	
	TwoWayInfo<T>* first, * last;
};

template<class T>
inline TwoWayList<T>::TwoWayList()
{
	count = 0;
	first = nullptr;
	last = nullptr;
}

template<class T>
inline TwoWayList<T>::~TwoWayList()
{
	DeleteAll();
}

template<class T>
inline void TwoWayList<T>::AddToHead(T elem)
{
	if (first == nullptr)
	{
		first = new TwoWayInfo<T>(elem);
		last = first;
		count = 1;
	}
	else
	{
		TwoWayInfo<T>* temp = new TwoWayInfo<T>(elem, nullptr, first);
		first->prev = temp;
		first = temp;
		count++;
	}
}

template<class T>
inline void TwoWayList<T>::AddToTail(T elem)
{
	if (last == nullptr)
	{
		AddToHead(elem);
	}
	else
	{
		TwoWayInfo<T>* temp = new TwoWayInfo<T>(elem, last);
		last->next = temp;
		last = last->next;
		count++;
	}
}

template<class T>
inline void TwoWayList<T>::AddElemOnPos(T elem, int pos)
{
	pos--;
	if (first == nullptr)
		AddToHead(elem);
	else
	{
		if (pos == 0)
			AddToHead(elem);
		else
			if (pos == count - 1)
				AddToTail(elem);
			else
			{
				int tempCount = 0;
				TwoWayInfo<T>* temp = first;
				while (tempCount != pos - 1)
				{
					temp = temp->next;
					tempCount++;
				}

				count++;

				TwoWayInfo<T>* newElem = new TwoWayInfo<T>{ elem };
				temp->next->prev = newElem;
				newElem->next = temp->next;
				temp->next = newElem;
				newElem->prev = temp;
			}
	}
}

template<class T>
inline void TwoWayList<T>::DelElemOnPos(int pos)
{
	pos--;
	if (first != nullptr)
	{
		if (pos == 0)
			DeleteFromHead();
		else
			if (pos == this->count - 1)
				DeleteFromTail();
			else
				if (pos >= 0 && pos < this->count)
				{
					int tempCount = 0;
					TwoWayInfo<T>* temp = first;
					while (tempCount != pos - 1)
					{
						temp = temp->next;
						tempCount++;
					}

					count--;

					TwoWayInfo<T>* forDelete = temp->next;
					temp->next = temp->next->next;
					temp->next->prev = temp;
					forDelete->next = nullptr;
					forDelete->prev = nullptr;
					delete forDelete;
				}
	}
}

template<class T>
inline T TwoWayList<T>::GetFirst()
{
	T elem;
	if (first == nullptr)
		return NULL;
	else
	{
		TwoWayInfo<T>* temp = first;
		if (temp != nullptr && temp->next != nullptr)
		{
			elem = temp->elem;
			first = first->next;
			first->prev = nullptr;
		}
		else
		{
			elem = temp->elem;
			first = nullptr;
			last = nullptr;
		}
		delete temp;
		count--;
	}
	return elem;
}

template<class T>
inline void TwoWayList<T>::DeleteFromHead()
{
	if (first == nullptr)
		return;
	else
	{
		TwoWayInfo<T>* temp = first;
		if (temp != nullptr && temp->next != nullptr)
		{
			first = first->next;
			first->prev = nullptr;
		}
		else
		{
			first = nullptr;
			last = nullptr;
		}
		delete temp;
		count--;
	}
}

template<class T>
inline void TwoWayList<T>::DeleteFromTail()
{
	if (first == nullptr)
		return;
	else
	{
		TwoWayInfo<T>* temp = last;
		if (temp != nullptr && temp->prev != nullptr)
		{
			last = last->prev;
			last->next = nullptr;
		}
		else
		{
			first = nullptr;
			last = nullptr;
		}
		delete temp;
		count--;
	}
}

template<class T>
inline int TwoWayList<T>::FindElemPos(T elem)
{
	if (first != nullptr)
	{
		int pos = 1;
		TwoWayInfo<T>* temp = first;
		while (temp != nullptr)
		{
			if (temp->elem == elem)
				return pos;
			temp = temp->next;
			pos++;
		}
	}
	return NULL;
}

template<class T>
inline int TwoWayList<T>::FindAndChange(T findElem, T newElem)
{
	int changeElemCount = 0;
	if (first != nullptr)
	{
		TwoWayInfo<T>* temp = first;
		while (temp != nullptr)
		{
			if (temp->elem == findElem)
			{
				temp->elem = newElem;
				changeElemCount++;
			}
			temp = temp->next;
		}
	}
	if (changeElemCount == 0)
		return -1;
	else
		return changeElemCount;
}

template<class T>
inline void TwoWayList<T>::DeleteAll()
{
	if (first == nullptr)
		return;
	else
	{
		while (count != 0)
			DeleteFromHead();
	}
}

template<class T>
inline void TwoWayList<T>::Reverse()
{
	if (first != nullptr)
	{
		int countDown = count;
		TwoWayInfo<T>* temp = last;
		TwoWayInfo<T>* swapper;
		while (countDown != 0)
		{
			swapper = last->next;
			last->next = last->prev;
			last->prev = swapper;
			if (last->next != nullptr)
				last = last->next;
			countDown--;
		}

		first = temp;
	}
}

template<class T>
inline int TwoWayList<T>::GetCount()
{
	return count;
}

template<class T>
inline void TwoWayList<T>::Show() const
{
	if (first == nullptr)
		return;
	else
	{
		TwoWayInfo<T>* temp = first;
		while (temp != nullptr)
		{
			cout << temp->elem << " ";
			temp = temp->next;
		}
	}
}
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// This class will serve us as very helpful sort system of player's scores
// We will sort score by fall
class BinaryTree
{
private:
	class Node
	{
	public:
		Node* left, *right;
		string date;
		string time;
		string name;
		int score;

		Node(string date, string time, string name, int score)
		{
			this->date = date;
			this->time = time;
			this->name = name;
			this->score = score;
		}
	};
	Node* head;

	Node* AddNewNode_P(Node*& head, string date, string time,string name, int score)
	{
		if (!head)
			head = new Node(date, time, name, score);
		else
			if (score < head->score)
				AddNewNode_P(head->left, date, time, name, score);
			else
				if (score >= head->score)
					AddNewNode_P(head->right, date, time, name, score);
		
		return head;
	}

	void ShowAllNodes_P(Node*& head)
	{
		if (!head)
			return;
		else
		{
			ShowAllNodes_P(head->right);
			cout << "\n\t" << head->date << setw(20) << head->time << setw(22) << head->name << setw(17) << head->score << endl;
			ShowAllNodes_P(head->left);
		}
	}

	Node* DeleteNode(Node*& head)
	{
		Node* temp = head;	
		Node* next; 
		if (!head)
		{
			return nullptr;
		}
		else
		{
			temp = head;
			if (!head->left)
				head = head->right;
			else
				if (!head->right)
					head = head->left;
				else
				{
					next = head->left;
					if (next->right)
					{
						while (next->right->right)
							next = next->right;
						head->date = next->right->date;
						head->time = next->right->time;
						head->name = next->right->name;
						head->score = next->right->score;
						temp = next->right;
						next->right = next->right->left;
					}
					else
					{
						head->date = next->date;
						head->time = next->time;
						head->name = next->name;
						head->score = next->score;
						temp = next;
						head->left = head->left->left;
					}
					delete temp;
				}	
		}
	}

	void ClearAllNodes(Node*& head)
	{
		DeleteNode(head);
	}

	void SaveData_P(Node*& head, ofstream& Save)
	{
		if (head)
		{
			SaveData_P(head->left, Save);

			size_t Date_Length = head->date.length() + 1;
			Save.write((char*)& Date_Length, sizeof(Date_Length));
			Save.write((char*)head->date.c_str(), Date_Length);

			size_t Time_Length = head->time.length() + 1;
			Save.write((char*)& Time_Length, sizeof(Time_Length));
			Save.write((char*)head->time.c_str(), Time_Length);

			size_t Name_Length = head->name.length() + 1;
			Save.write((char*)& Name_Length, sizeof(Name_Length));
			Save.write((char*)head->name.c_str(), Name_Length);

			Save.write((char*)& head->score, sizeof(head->score));

			SaveData_P(head->right, Save);
		}
	}

	void LoadData_P(ifstream& Load)
	{
		if ((Load.is_open()))
		{
			do
			{
				if (Load.peek() == EOF) break;

				string Temp_Date;
				string Temp_Time;
				string Temp_Name;
				int Temp_Score;

				size_t Temp_Length;
				char* Temp;

				Load.read((char*)& Temp_Length, sizeof(Temp_Length));
				Temp = new char[Temp_Length];
				Load.read(Temp, Temp_Length);
				Temp_Date = Temp;
				delete[] Temp;


				Load.read((char*)& Temp_Length, sizeof(Temp_Length));
				Temp = new char[Temp_Length];
				Load.read(Temp, Temp_Length);
				Temp_Time = Temp;
				delete[] Temp;

				Load.read((char*)& Temp_Length, sizeof(Temp_Length));
				Temp = new char[Temp_Length];
				Load.read(Temp, Temp_Length);
				Temp_Name = Temp;
				delete[] Temp;

				Load.read((char*)& Temp_Score, sizeof(Temp_Score));

				AddNewNode(Temp_Date, Temp_Time, Temp_Name, Temp_Score);
			} while (5);
		}
	}
public:
	BinaryTree();

	void AddNewNode(string date, string time, string name, int score);

	void ClearAllNodes();

	void ShowAllNodes();

	void SaveData();
	void LoadData();
};
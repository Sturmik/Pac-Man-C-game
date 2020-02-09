#include "BinaryTree_Class.h"

BinaryTree::BinaryTree()
{
	head = nullptr;
}

void BinaryTree::AddNewNode(string date, string time, string name, int score)
{
	head = AddNewNode_P(head, date, time, name, score);
}

void BinaryTree::ClearAllNodes()
{
	while(head)
		ClearAllNodes(head);
	ofstream out("PAC-MAN_SCORES.bin", ios::binary, ios::trunc);
	out.close();
}

void BinaryTree::ShowAllNodes() 
{
	ShowAllNodes_P(head);
}

void BinaryTree::SaveData()
{
	ofstream out("PAC-MAN_SCORES.bin", ios::binary);
	SaveData_P(head, out);
	out.close();
}

void BinaryTree::LoadData()
{
	ifstream in("PAC-MAN_SCORES.bin", ios::binary);
	if (in.is_open())
		LoadData_P(in);
	in.close();
}

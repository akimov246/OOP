// pch.cpp: �������� ����, ��������������� �������������������� ���������; ����� ��� ����������

#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;
void plane::InData(ifstream& ifst) {
	ifst >> c >> range;
}
void traine::InData(ifstream& ifst) {
	ifst >> count;
}
void ship::InData(ifstream& ifst)
{
	int type;
	ifst >> water_displacement;
	ifst >> type;
	if (type == 1)
		type = LINER;
	else if (type == 2)
		type = TANKER;
	else if (type == 3)
		type = TUG;
}
void plane::Out(ofstream& ofst) {
	ofst << "It is Plane: ���������������� = " << c
		<< ", ��������� ������ = " << range;
	OutCommon(ofst);

}
void traine::Out(ofstream& ofst) {
	ofst << "It is Traine: count = " << count;
	OutCommon(ofst);
}
void ship::Out(ofstream& ofst)
{
	ofst << "It is Ship: ������������� = " << water_displacement;
	if (type == LINER)
		ofst << ", ��� ����� = " << LINER;
	else if (type == TANKER)
		ofst << ", ��� ����� = " << TANKER;
	else if (type == TUG)
		ofst << ", ��� ����� = " << TUG;
}
transport* transport::In(ifstream& ifst)
{
	transport* s;
	int key;
	ifst >> key;
	if (key == 1) {
		s = new plane;
	}
	else if (key == 2)
	{
		s = new traine;
	}
	else if (key == 3) {
		s = new ship;
	}
	else
		return 0;
	s->InData(ifst);
	ifst >> s->distance >> s->spead;
	return s;
}
void transport::OutCommon(ofstream& ofst)
{
	ofst << ", ���������� ����� �������� = " << distance << ", �������� = " << spead << endl;
}
container::Node::Node()
{
	this->Next = nullptr;
	this->Prev = nullptr;
	this->data = nullptr;
}

container::container()
{
	Top = nullptr;
	count = 0;
}
void container::Clear()
{
	Node* current = Top;
	for (int i = 1; i < count; i++)
	{
		current = current->Next;
		delete current->Prev;
	}
	delete current;
	count = 0;
}
void container::In(ifstream& ifst)
{
	int flag;
	while (!ifst.eof()) {
		if (count == 0)
		{
			Top = new Node;
			Top->Next = Top;
			Top->Prev = Top;
			if ((Top->data = transport::In(ifst)) != 0)
				flag = 1;
			else
				flag = 0;

		}
		else
		{
			Node* current = Top;
			for (int j = 1; j < count; j++)
			{
				current = current->Next;
			}
			current->Next = new Node;
			if ((current->Next->data = transport::In(ifst)) != 0)
			{
				Top->Prev = current->Next;
				current->Next->Prev = current;
				current->Next->Next = Top;
				flag = 1;
			}
			else
			{
				flag = 0;
			}
		}
		if (flag != 0)
			count++;
	}
}

void container::Out(ofstream& ofst)
{
	Node* current = Top;
	ofst << " Container contains " << count
		<< " elements." << endl;
	for (int j = 0; j < count; j++) {
		ofst << j << ": ";
		current->data->Out(ofst);
		current = current->Next;
	}
}

// � ����� ���� ���� ����� ����������, �� �� �������� ���, ���� �� ����������� ������������������� ���������.

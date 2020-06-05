// pch.cpp: исходный файл, соответствующий предкомпилированному заголовку; нужен для компиляции

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
	void plane::InData(ifstream &ifst) {
		this->c=this->from_file_to_int(ifst);
		this->range = this->from_file_to_int(ifst);
		this->cargo = this->from_file_to_int(ifst);
		//ifst >> c  >> range >> cargo;
	}
	void traine::InData(ifstream &ifst) {
		this->count = this->from_file_to_int(ifst);
		//ifst >> count ;
	}
	void ship::InData(ifstream & ifst)
	{
		int typ;
		this->water_displacement = this->from_file_to_int(ifst);
		//ifst >> water_displacement;
		//ifst >> typ;
		typ = this->from_file_to_int(ifst);
		if (typ == 1)
			type = LINER;
		else if (typ == 2)
			type = TANKER;
		else if (typ == 3)
			type = TUG;
		else
		{
			cout << "ERROR IN FAILIN.TXT";
			exit(0);
		}
	}

	void plane::Out(ofstream &ofst) {
		ofst << "It is Plane: грузоподъемность = " << c
			<< ", дальность полета = " << range << ", груз в данный момент = " << cargo;
		OutCommon(ofst);
		ofst << "идеальное время пути = " <<
			this->Travel_time() << endl;

	}
	void traine::Out(ofstream &ofst) {
		ofst << "It is Traine: count = " << count ;
		OutCommon(ofst);
		ofst << "идеальное время пути = " <<
			this->Travel_time() << endl;
	}
	void ship::Out(ofstream & ofst)
	{
		ofst << "It is Ship: водоизмещение = " << water_displacement;
		if (type == LINER)
			ofst << ", тип судна = LINER";
		else if (type == TANKER)
			ofst << ", тип судна = TANKER";
		else if (type == TUG)
			ofst << ", тип судна = TUG";
		OutCommon(ofst);
		ofst << "идеальное время пути = " <<
			this->Travel_time() << endl;

	}
	transport* transport::In(ifstream &ifst)
	{
		transport *s;
		int key;
		key = transport::from_file_to_int(ifst);
		//key = s->from_file_to_int(ifst);
		//ifst >> key;
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
		{
			cout << "ERROR IN FAILIN.TXT";
			exit(0);
		};
		s->InData(ifst);
		s->distance = transport::from_file_to_int(ifst);
		s->spead = transport::from_file_to_int(ifst);
		//ifst >> s->distance >> s->spead;
		return s;
	}
	void transport::OutCommon(ofstream & ofst)
	{
		ofst << ", расстояние между пунктами = " << distance << ", скорость = " << spead << endl;
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
	void container::In(ifstream & ifst)
	{
		int flag;
		while (!ifst.eof()) {
			if (count == 0)
			{
				Top = new Node;
				Top->Next = Top;
				Top->Prev = Top;
				if ((Top->data= transport::In(ifst)) != 0)
					flag = 1;
				else
					flag = 0;
				
			}
			else
			{
				Node *current = Top;
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
			if (flag  != 0)
				count++;
		}
	}

	void container::Out(ofstream & ofst)
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

	float transport::Travel_time()
	{
		float time;
		time = static_cast<float>(this->distance) / static_cast<float>(this->spead);
		return time;
	}
	bool transport::Compare(transport & other)
	{
		return Travel_time() < other.Travel_time();
	}
	void container::Sort()
	{
		Node* current;
		current = Top;
		Node* currentnext = current->Next;
		for (int i = 1; i < count; i++) {
			for (int j = 1; j < count; j++) {
				if (current->data->Compare(*current->Next->data)) {
					current->castl();
					current = current->Next;
				}
				else
					current = current->Next;
			}
			current = Top;
		}
	}
	void container::Node::castl()
	{
		Node* currentnext = this->Next;
		//Создаем копии, для смены местами
		transport* q1 = this->data;
		transport* q2 = currentnext->data;
		this->data = q2;
		currentnext->data = q1;
	}

	void transport::Out_only_plane(ofstream & ofst)
	{
		ofst << endl;
	}
	void plane::Out_only_plane(ofstream &ofst)
	{
		Out(ofst);
	}
	void container::Out_only_plane(ofstream & ofst)
	{
		ofst << "Only planes" << endl;
		Node* current = Top;
		for (int i = 0; i < count; i++) {
			ofst << i << ": ";
			current->data->Out_only_plane(ofst);
			current = current->Next;
		}
	}
	//дальше функции для тестов
	int transport::get_distance()
	{
		return this->distance;
	}
	int transport::get_spead()
	{
		return this->spead;
	}
	string plane::getall()
	{
		return to_string(this->c) + to_string(this->range) + to_string(this->cargo);
	}
	string traine::getall()
	{
		return to_string(this->count);
	}
	string ship::getall()
	{
		return to_string(this->water_displacement) + to_string(this->type);
	}
	void transport::set_distance(int distance)
	{
		this->distance = distance;
	}
	void transport::set_spead(int spead)
	{
		this->spead = spead;
	}

	int transport::from_file_to_int(ifstream & ifst)
	{

			string str;
			bool flag = true;
			ifst >> str;
			if (str == "")
			{
				flag = false;
			}
			else
			{

				for (int i = 0; i < str.length(); i++)
				{
					if (isdigit(str[i]))
					{
					}
					else
						flag = false;

				}
			}
			if (flag == false)
			{
				cout << "ERROR IN FAILIN.TXT";
				exit(0);
			}
			else
			return stoi(str);
		}
	
	int container::get_count()
	{
		return this->count;
	}

// В целом этот файл можно пропустить, но не удаляйте его, если вы используете предкомпилированные заголовки.
	
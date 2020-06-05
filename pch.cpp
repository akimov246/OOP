// pch.cpp: исходный файл, соответствующий предкомпилированному заголовку; нужен для компиляции

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//мультиметоды
	void container::MultiMethod(ofstream & ofst)
	{
		ofst << "Multimethod." << endl;
		node* current_i = top;
		for (int i = 0; i < count - 1; i++) {
			node* current_j = current_i->next;
			for (int j = i + 1; j < count; j++) {
				current_i->data->MultiMethod(current_j->data, ofst);
				current_i->data->Out(ofst);
				current_j->data->Out(ofst);
				current_j = current_j->next;
			}
			current_i = current_i->next;
		}
	}
	void plane::MultiMethod(transport * other, ofstream & ofst)
	{
		other->MMplane(ofst);
	}
	void plane::MMplane(ofstream & ofst)
	{
		ofst << "Plane and Plane" << endl;
	}
	void plane::MMtraine(ofstream & ofst)
	{
		ofst << "Traine and Plane" << endl;
	}
	void plane::MMship(ofstream & ofst)
	{
		ofst << "Ship and Plane" << endl;
	}
	void traine::MultiMethod(transport*other, ofstream & ofst)
	{
		other->MMtraine(ofst);
	}
	void traine::MMplane(ofstream & ofst)
	{
		ofst << "Plane and Traine" << endl;
	}
	void traine::MMtraine(ofstream & ofst)
	{
		ofst << "Traine and Traine" << endl;
	}
	void traine::MMship(ofstream & ofst)
	{
		ofst << "Ship and Traine" << endl;
	}
	void ship::MultiMethod(transport*other, ofstream & ofst)
	{
		other->MMship(ofst);
	}
	void ship::MMplane(ofstream & ofst)
	{
		ofst << "Plane and Ship" << endl;
	}
	void ship::MMtraine(ofstream & ofst)
	{
		ofst << "Traine and Ship" << endl;
	}
	void ship::MMship(ofstream & ofst)
	{
		ofst << "Ship and Ship" << endl;
	}
	void plane::InData(ifstream &ifst) 
	{
		this->c=this->From_file_to_int(ifst);
		this->range = this->From_file_to_int(ifst);
		this->cargo = this->From_file_to_int(ifst);
	}
	void traine::InData(ifstream &ifst) 
	{
		this->count = this->From_file_to_int(ifst);
	}
	void ship::InData(ifstream & ifst)
	{
		int typ;
		this->water_displacement = this->From_file_to_int(ifst);
		typ = this->From_file_to_int(ifst);
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

	void plane::Out(ofstream &ofst) 
	{
		ofst << "It is Plane: грузоподъемность = " << c 
		<< ", дальность полета = " << range << ", груз в данный момент = " << cargo;
		OutCommon(ofst);
		ofst << "идеальное время пути = " <<
		this->Travel_time() << endl;
	}
	void traine::Out(ofstream &ofst) 
	{
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
		key = transport::From_file_to_int(ifst);
		if (key == 1) 
		{
			s = new plane;
		}
		else if (key == 2)
		{
			s = new traine;
		}
		else if (key == 3) 
		{
			s = new ship;
		}
		else
		{
			cout << "ERROR IN FAILIN.TXT";
			exit(0);
		};
		s->InData(ifst);
		s->distance = transport::From_file_to_int(ifst);
		s->spead = transport::From_file_to_int(ifst);
		return s;
	}
	void transport::OutCommon(ofstream & ofst)
	{
		ofst << ", расстояние между пунктами = " << distance << ", скорость = " << spead << endl;
	}
	container::node::node()
	{
		this->next = nullptr;
		this->prev = nullptr;
		this->data = nullptr;
	}
	
	container::container()
	{
		top = nullptr;
		count = 0;
	}
	void container::Clear()
	{
		node* current = top;
		for (int i = 1; i < count; i++)
		{
			current = current->next;
			delete current->prev;
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
				top = new node;
				top->next = top;
				top->prev = top;
				if ((top->data= transport::In(ifst)) != 0)
					flag = 1;
				else
					flag = 0;
			}
			else
			{
				node *current = top;
				for (int j = 1; j < count; j++)
				{
					current = current->next;
				}
				current->next = new node;
				if ((current->next->data = transport::In(ifst)) != 0)
				{
					top->prev = current->next;
					current->next->prev = current;
					current->next->next = top;
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
		node* current = top;
		ofst << " Container contains " << count
			<< " elements." << endl;
		for (int j = 0; j < count; j++) 
		{
			ofst << j << ": ";
			current->data->Out(ofst);	
			current = current->next;
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
		node* current;
		current = top;
		node* currentnext = current->next;
		for (int i = 1; i < count; i++) 
		{
			for (int j = 1; j < count; j++) 
			{
				if (current->data->Compare(*current->next->data)) 
				{
					current->castl();
					current = current->next;
				}
				else
					current = current->next;
			}
			current = top;
		}
	}
	void container::node::castl()
	{
		node* currentnext = this->next;
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
		node* current = top;
		for (int i = 0; i < count; i++) 
		{
			ofst << i << ": ";
			current->data->Out_only_plane(ofst);
			current = current->next;
		}
	}

	//дальше функции для тестов
	int transport::Get_distance()
	{
		return this->distance;
	}
	int transport::Get_spead()
	{
		return this->spead;
	}
	string plane::Getall()
	{
		return to_string(this->c) + to_string(this->range) + to_string(this->cargo);
	}
	string traine::Getall()
	{
		return to_string(this->count);
	}
	string ship::Getall()
	{
		return to_string(this->water_displacement) + to_string(this->type);
	}
	void transport::Set_distance(int distance)
	{
		this->distance = distance;
	}
	void transport::Set_spead(int spead)
	{
		this->spead = spead;
	}

	int transport::From_file_to_int(ifstream & ifst)
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
	
	int container::Get_count()
	{
		return this->count;
	}

// В целом этот файл можно пропустить, но не удаляйте его, если вы используете предкомпилированные заголовки.
	
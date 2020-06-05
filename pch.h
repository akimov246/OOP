// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.


#ifndef PCH_H
#define PCH_H
#include <fstream>
using namespace std;
class transport
{
private:
	int spead;
	int distance;
public:
	//для тестов
	int Get_distance();//получить поле distance
	int Get_spead();//получить поле spead
	void Set_distance(int distance);//"положить" в поле distance значение
	void Set_spead(int spead);//"положить" в поле spead значение
	static int From_file_to_int(ifstream &ifst);//проверка корректности информации считываемой с файла
	virtual string Getall() = 0;

	static transport* In(ifstream &ifst);//ввод
	virtual void InData(ifstream &ifst) = 0; // ввод
	virtual void Out(ofstream &ofst) = 0; // вывод
	float Travel_time();//подсчет времени передвижения объекта
	virtual void Out_only_plane(ofstream &ofst);//вывод только plane
	void OutCommon(ofstream &ofst);//вывод общих полей
	bool Compare(transport &other);//сравнение
};
class container
{
private:
	class node {
	public:
		node();
		node* next;// указатель на следующий элемент списка
		node* prev;// указатель на предыдущий элемент списка
		transport* data;//указатель на информацию
		void castl();//меняет местами 2 элемента 
	};
	node* top;//указатель на  верхушку списка
	int count;//кол-во элементов списка
public:
	node* Get_Top()//возвращает указатель на верхушку списка
	{
		return this->top;
	};
	int Get_count();// получить count
	void Out_only_plane(ofstream &ofst);//вывод только plane 
	void In(ifstream &ifst); // ввод
	void Out(ofstream &ofst); // вывод
	void Clear(); // очистка контейнера от фигур
	container(); // инициализация контейнера
	void Sort();// сортировка
	~container()
	{
		Clear();
	}
};
class plane : public transport {
	int range;
	int c;
	int cargo;
public:
	string Getall();//функция для тестов

	void InData(ifstream &ifst); // ввод
	void Out(ofstream &ofst); // вывод
	void Out_only_plane(ofstream &ofst);// вывод только plane
	plane()// создание без инициализации.
	{
	}
};
class traine : public transport
{
	int count;
public:
	string Getall();
	void InData(ifstream &ifst); // ввод
	void Out(ofstream &ofst); // вывод
	traine()// создание без инициализации.
	{
	}
};
enum type_of_ship { LINER, TUG, TANKER };
struct ship : public transport 
{
	int water_displacement;
	type_of_ship type;
public:
	string Getall();
	void InData(ifstream &ifst);//ввод
	void Out(ofstream &ofst);//вывод
	ship() 
	{
	}
};
// TODO: add headers that you want to pre-compile here
#endif //PCH_H
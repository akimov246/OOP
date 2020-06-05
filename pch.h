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
class transport {
private:
	int spead;
	int distance;
public:
	//для тестов
	int get_distance();
	int get_spead();
	void set_distance(int distance);
	void set_spead(int spead);
	static int from_file_to_int(ifstream &ifst);
	virtual string getall() = 0;

	static transport* In(ifstream &ifst);
	virtual void InData(ifstream &ifst) = 0; // ввод
	virtual void Out(ofstream &ofst) = 0; // вывод
	float Travel_time();
	virtual void Out_only_plane(ofstream &ofst);
	void OutCommon(ofstream &ofst);
	bool Compare(transport &other);
};
class container
{
private:
	class Node {		
	public:
		Node();
		Node* Next;
		Node* Prev;
		transport* data;
		//void Processsort(Node* &Top);//вызывает функцию castl и изменяет верхушку списка
		void castl();//меняет местами 2 элемента 
	};
	Node* Top;
	int count;
public:
	Node* get_Top()
	{
		return this->Top;
	};
	int get_count();
	void Out_only_plane(ofstream &ofst);
	void In(ifstream &ifst); // ввод
	void Out(ofstream &ofst); // вывод
	void Clear(); // очистка контейнера от фигур
	container(); // инициализация контейнера
	void Sort();
	~container() { Clear(); }
};
class plane : public transport {
	int range;
	int c;
	int cargo;
public:
	string getall();

	void InData(ifstream &ifst); // ввод
	void Out(ofstream &ofst); // вывод
	void Out_only_plane(ofstream &ofst);
	plane() {} // создание без инициализации.
};
class traine : public transport {
	int count;

public:
	string getall();
	void InData(ifstream &ifst); // ввод
	void Out(ofstream &ofst); // вывод
	traine() {} // создание без инициализации.
};
enum type_of_ship { LINER, TUG, TANKER };
struct ship : public transport {
	int water_displacement;
	type_of_ship type;
public:
	string getall();
	void InData(ifstream &ifst);
	void Out(ofstream &ofst);
	ship() {}
};
// TODO: add headers that you want to pre-compile here
#endif //PCH_H
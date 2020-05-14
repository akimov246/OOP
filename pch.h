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
	static transport* In(ifstream& ifst);
	virtual void InData(ifstream& ifst) = 0; // ввод
	virtual void Out(ofstream& ofst) = 0; // вывод
	void OutCommon(ofstream& ofst);
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
	};
	Node* Top;
	int count;
public:
	void In(ifstream& ifst); // ввод
	void Out(ofstream& ofst); // вывод
	void Clear(); // очистка контейнера от фигур
	container(); // инициализация контейнера
	~container() { Clear(); }
};


class plane : public transport {
	int range;
	int c;

public:
	void InData(ifstream& ifst); // ввод
	void Out(ofstream& ofst); // вывод
	plane() {} // создание без инициализации.
};
class traine : public transport {
	int count;

public:
	void InData(ifstream& ifst); // ввод
	void Out(ofstream& ofst); // вывод
	traine() {} // создание без инициализации.
};

// TODO: add headers that you want to pre-compile here

#endif //PCH_H
enum type_of_ship { LINER, TUG, TANKER };
struct ship : public transport {
	int water_displacement;
	type_of_ship type;
public:
	void InData(ifstream& ifst);
	void Out(ofstream& ofst);
	ship() {}
};

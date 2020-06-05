// Program.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char* argv[])
{
	int a;
	if (argc != 3) 
	{
		cout << "incorrect command line! "
		"Waited: command in_file out_file"
		<< endl;
		system("pause");
		exit(1);
	}
	ifstream ifst(argv[1]);
	if (!ifst)
	{
		cout << "No input file found!" << endl;
		return 0;
	}
	ofstream ofst(argv[2]);
	cout << "Start" << endl;
	setlocale(LC_ALL, "Russian");
	container c;
	c.In(ifst); //заполнение котейнера
	ofst << "Filled container. " << endl;
	c.Out(ofst); //вывод контейнера
	ofst << endl;
	
	c.MultiMethod(ofst);//мультиметоды

	c.Sort();// сортировка контейнера
	ofst << endl;
	c.Out(ofst);// вывод отсортированного контейнера
	ofst << endl;
	c.Out_only_plane(ofst);// вывод только plane
	ofst << endl;
	c.Clear();// отчистка контейнера
	ofst << "Empty container. " << endl;
	c.Out(ofst); //вывод пустого контейнера
	cout << "Stop" << endl;
	system("pause");
	cin >> a;
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

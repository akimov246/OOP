// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.


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
	virtual void InData(ifstream& ifst) = 0; // ����
	virtual void Out(ofstream& ofst) = 0; // �����
	float Travel_time();
	void OutCommon(ofstream& ofst);
	bool Compare(transport& other);
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
		void Processsort(Node*& Top);//������ ������� 2 �������� � �������� �������� ������
		void castl();
	};
	Node* Top;
	int count;
public:
	void In(ifstream& ifst); // ����
	void Out(ofstream& ofst); // �����
	void Clear(); // ������� ���������� �� �����
	container(); // ������������� ����������
	void Sort();
	~container() { Clear(); }
};


class plane : public transport {
	int range;
	int c;

public:
	void InData(ifstream& ifst); // ����
	void Out(ofstream& ofst); // �����
	plane() {} // �������� ��� �������������.
};
class traine : public transport {
	int count;

public:
	void InData(ifstream& ifst); // ����
	void Out(ofstream& ofst); // �����
	traine() {} // �������� ��� �������������.
};

// TODO: add headers that you want to pre-compile here

#endif //PCH_H

//2_�̱���
#include<iostream>
using namespace std;

// ���� : ���� �ϳ��� ��ü�� �����ϰ�, �ý��� ��𼭿�����
//		  ������ ������� ��ü�� �����Ҽ� �ְ� �ϴ� ����.


// "Meyer's Singleton" : ���� �ϳ��� ��ü�� static �޸𸮿� �ִ� ����
//	Effective-C++�� ������ Scott Meyer�� ó������ ����..!
class Cursor
{
private:
	// ��Ģ 1. private ������
	Cursor(){}
	// ��Ģ 2. ����� ���� ����
	Cursor(const Cursor&);			// = delete; //C++11
	void operator=(const Cursor&);	// = delete;
	Cursor(Cursor&&);
	void operator=(Cursor&&);
public:
	// ��Ģ 3. ���� �ϳ��� ��ü�� ���� �����ϴ� static �Լ�
	static Cursor& getInstance()
	{
		static Cursor instance;
		return instance;
	}
};


int main()
{
	Cursor& c1 = Cursor::getInstance();
	Cursor& c2 = Cursor::getInstance();
	
	cout << &c1 << endl;
	cout << &c2 << endl;
}
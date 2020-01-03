#include<iostream>

using namespace std;

// C++ ���� �̱��� �ڵ带 �����ϴ� ��ǥ�� ���
// 1. CRTP�� ����� ���
// 2. ��ũ�θ� ����� �ڵ� ����

#define MAKE_SINGLETON(classname)			\
	private:								\
		classname(){}						\
		classname(const classname &);		\
		void operator=(const classname&);	\
	public:									\
		static classname& getInstance()		\
		{									\
			static classname instance;		\
			return instance;				\
		}							

class Cursor
{
	MAKE_SINGLETON(Cursor);
};

int main()
{
	Cursor::getInstance();
}
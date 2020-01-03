#include<iostream>

using namespace std;

// C++ 에서 싱글톤 코드를 재사용하는 대표적 기법
// 1. CRTP를 사용한 상속
// 2. 매크로를 사용한 코드 생성

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
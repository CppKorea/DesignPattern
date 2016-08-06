
//2_싱글톤
#include<iostream>
using namespace std;

// 개념 : 오직 하나의 객체만 존재하고, 시스템 어디서에서도
//		  동일한 방법으로 객체에 접근할수 있게 하는 패턴.


// "Meyer's Singleton" : 오직 하나의 객체가 static 메모리에 있는 버전
//	Effective-C++의 저자인 Scott Meyer가 처음으로 제안..!
class Cursor
{
private:
	// 규칙 1. private 생성자
	Cursor(){}
	// 규칙 2. 복사와 대입 금지
	Cursor(const Cursor&);			// = delete; //C++11
	void operator=(const Cursor&);	// = delete;
	Cursor(Cursor&&);
	void operator=(Cursor&&);
public:
	// 규칙 3. 오직 하나의 객체만 만들어서 리턴하는 static 함수
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
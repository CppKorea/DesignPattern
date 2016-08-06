#include<iostream>

using namespace std;

// 1. CRTP를 사용한 상속

template<typename T>
class Singleton
{
private:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton &) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton &&) = delete;

protected:
	Singleton() = default;
	virtual ~Singleton() = default;
public:
	static T& getInstance()
	{
		static T instance;
		return instance;
	}
};

class Cursor : public Singleton<Cursor>
{
	friend class Singleton<Cursor>;
private:
	Cursor() = default;
public:
	virtual ~Cursor() = default;

};


int main()
{
	Cursor& c1 = Cursor::getInstance();
	Cursor& c2 = Cursor::getInstance();

	cout << &c1 << endl;
	cout << &c2 << endl;
}
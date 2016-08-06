//4_빌더


//"Builder"  : 동일 공정으로 다른 표현의 객체 생성
#include<iostream>
#include<string>

using namespace std;

// 동일한 공정에 따라 객체를 만드는데....
// 각 공정의 표햔이 달라 질떄...
typedef string Hat;		//Hat이라는 클래스가 있다고 가정.
typedef string Uniform;
typedef string Shoes;
typedef string Character;

// 캐릭터의 종류에 따라 모자, 유니폼의 모양이 달라집니다.
// 변하는 것을 다른 클래스로, 교체가능하게 인터페이스!
struct IBuilder
{
	virtual Hat makeHat() = 0;
	virtual Uniform makeUniform() = 0;
	virtual Shoes makeShoes() = 0;
	virtual ~IBuilder() {}
};

// 캐릭터를 만들때 모자, 유니폼,신발이 있다는 사실은
// 변하지 않습니다.
class Director //동일한 공정의 정의한 클래스
{
	IBuilder* builder;
public:
	void setBuilder(IBuilder* p)
	{
		builder = p;
	}
	Character Construct()
	{
		Character c;
		c += builder->makeHat();
		c += builder->makeUniform();
		c += builder->makeShoes();
		return c;
	}
};

// 사용자가 선택하는 나라에 따라 모자, 유니폼, 신발을 만드는 
// 빌더들...
class Spain : public IBuilder
{
public:
	Hat makeHat() { return "스페인 모자\n"; };
	Uniform makeUniform() { return "스페인 유니폼\n"; };
	Shoes makeShoes() { return "스페인 신발\n"; };

};

class Korea : public IBuilder
{
public:
	Hat makeHat() { return "갓\n"; };
	Uniform makeUniform() { return "한복\n"; };
	Shoes makeShoes() { return "짚신\n"; };

};

int main()
{
	Director d; //GoF 패턴에서 감독관
	Korea k;
	Spain s; // 빌더들.. 각 나라들!!

	d.setBuilder(&s); //사용자가 캐릭터 변경 화살표 키를
					  // 누를때...

	Character c = d.Construct();
	cout << c << endl;

}
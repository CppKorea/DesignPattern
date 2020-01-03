//4_����


//"Builder"  : ���� �������� �ٸ� ǥ���� ��ü ����
#include<iostream>
#include<string>

using namespace std;

// ������ ������ ���� ��ü�� ����µ�....
// �� ������ ǥ�h�� �޶� ����...
typedef string Hat;		//Hat�̶�� Ŭ������ �ִٰ� ����.
typedef string Uniform;
typedef string Shoes;
typedef string Character;

// ĳ������ ������ ���� ����, �������� ����� �޶����ϴ�.
// ���ϴ� ���� �ٸ� Ŭ������, ��ü�����ϰ� �������̽�!
struct IBuilder
{
	virtual Hat makeHat() = 0;
	virtual Uniform makeUniform() = 0;
	virtual Shoes makeShoes() = 0;
	virtual ~IBuilder() {}
};

// ĳ���͸� ���鶧 ����, ������,�Ź��� �ִٴ� �����
// ������ �ʽ��ϴ�.
class Director //������ ������ ������ Ŭ����
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

// ����ڰ� �����ϴ� ���� ���� ����, ������, �Ź��� ����� 
// ������...
class Spain : public IBuilder
{
public:
	Hat makeHat() { return "������ ����\n"; };
	Uniform makeUniform() { return "������ ������\n"; };
	Shoes makeShoes() { return "������ �Ź�\n"; };

};

class Korea : public IBuilder
{
public:
	Hat makeHat() { return "��\n"; };
	Uniform makeUniform() { return "�Ѻ�\n"; };
	Shoes makeShoes() { return "¤��\n"; };

};

int main()
{
	Director d; //GoF ���Ͽ��� ������
	Korea k;
	Spain s; // ������.. �� �����!!

	d.setBuilder(&s); //����ڰ� ĳ���� ���� ȭ��ǥ Ű��
					  // ������...

	Character c = d.Construct();
	cout << c << endl;

}
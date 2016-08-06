#include <iostream>
using namespace std;

#define N_UNIT    100

class GameUnit 
{
public:
	static void InitUnitArray() 
	{
		for (int i = 0; i < N_UNIT; i++)
			pUnitArray_[i] = 0;
	}

	static GameUnit* CreateInstance() { return 0; }

	static void DestroyUnit(GameUnit* pUnit) 
	{
		for (int i = 0; i < N_UNIT; i++) 
		{
			if (pUnitArray_[i] == pUnit) 
			{
				delete pUnitArray_[i];
				pUnitArray_[i] = 0;
				return;
			}
		}
	}

	virtual void Display(int x, int y) = 0;
	virtual void DoAction() = 0;
protected:
	GameUnit() {}
	GameUnit(const GameUnit& rhs) {}
	static GameUnit* pUnitArray_[N_UNIT];
};

// -- 클래스 변수 정의
GameUnit* GameUnit::pUnitArray_[N_UNIT];

class AttackUnit : public GameUnit 
{
public:
	static GameUnit* CreateInstance() 
	{
		for (int i = 0; i < N_UNIT; i++) 
		{
			if (pUnitArray_[i] == 0) 
			{
				pUnitArray_[i] = new AttackUnit;
				return pUnitArray_[i];
			}
		}

		return 0;
	}

	void Display(int x, int y) {}
	void DoAction() {}
protected:
	AttackUnit() {}
	AttackUnit(const AttackUnit& rhs) {}
};

class ProtectUnit : public GameUnit 
{
public:
	static GameUnit* CreateInstance() 
	{
		for (int i = 0; i < N_UNIT; i++) 
		{
			if (pUnitArray_[i] == 0) 
			{
				pUnitArray_[i] = new ProtectUnit;
				return pUnitArray_[i];
			}
		}

		return 0;
	}

	void Display(int x, int y) {}
	void DoAction() {}
protected:
	ProtectUnit() {}
	ProtectUnit(const ProtectUnit& rhs) {}
};

void main()
{
	GameUnit::InitUnitArray();

	GameUnit *pUnit1 = AttackUnit::CreateInstance();
	if (pUnit1 == 0)
		cout << "No More Create Unit" << endl;

	GameUnit *pUnit2 = ProtectUnit::CreateInstance();
	if (pUnit2 == 0)
		cout << "No More Create Unit" << endl;

	GameUnit::DestroyUnit(pUnit1);
	GameUnit::DestroyUnit(pUnit2);
}

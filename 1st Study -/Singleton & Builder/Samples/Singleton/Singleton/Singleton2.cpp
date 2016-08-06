#include <iostream>
using namespace std;

#define N_UNIT    100

#define ATTACK_UNIT   1
#define PROTECT_UNIT  2

class GameUnit 
{
public:
	virtual void Display(int x, int y) = 0;
	virtual void DoAction() = 0;
};

class AttackUnit : public GameUnit
{
public:
	void Display(int x, int y) {}
	void DoAction() {}
};

class ProtectUnit : public GameUnit 
{
public:
	void Display(int x, int y) {}
	void DoAction() {}
};

// ------------------------
// Global Variable 
// ------------------------
GameUnit *pUnitArray[N_UNIT];

void InitUnitArray()
{
	for (int i = 0; i < N_UNIT; i++)
		pUnitArray[i] = 0;
}

GameUnit* CreateNewUnit(int unitType)
{
	for (int i = 0; i < N_UNIT; i++)
	{
		if (pUnitArray[i] == 0) {
			if (unitType == ATTACK_UNIT)
				pUnitArray[i] = new AttackUnit;
			else
				pUnitArray[i] = new ProtectUnit;
			return pUnitArray[i];
		}
	}

	return 0;
}

void DestroyUnit(GameUnit* pUnit)
{
	for (int i = 0; i < N_UNIT; i++) 
	{
		if (pUnitArray[i] == pUnit) 
		{
			delete pUnitArray[i];
			pUnitArray[i] = 0;
			return;
		}
	}
}

void main()
{
	InitUnitArray();

	GameUnit *pUnit1 = CreateNewUnit(ATTACK_UNIT);
	if (pUnit1 == 0)
		cout << "No More Create Unit" << endl;

	GameUnit *pUnit2 = CreateNewUnit(PROTECT_UNIT);
	if (pUnit2 == 0)
		cout << "No More Create Unit" << endl;

	DestroyUnit(pUnit1);
	DestroyUnit(pUnit2);
}

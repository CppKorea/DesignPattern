#include "CandidateRegion.h"
#include "ThaadDeployManager.h"

#include <random>
#include <iostream>
#include <thread>
#include <chrono>

CandidateRegion::CandidateRegion(string timestamp, string name, string location, string rejectMeant, int winNum)
	: timestamp_(timestamp), name_(name), location_(location), rejectMeant_(rejectMeant), winNum_(winNum)
{
}

CandidateRegion::~CandidateRegion()
{
}

bool CandidateRegion::determine()
{
	cout << "�ڱ��� ������� " << location_ << "�� �湮�ؼ� �ֹε��� �����ϰ� �ִ�." << endl;
	random_device randomDevice;
	mt19937 generator(randomDevice());
	int n = ThaadDeployManager::getInstance()->getNumOfCandidateRegions();
	uniform_int_distribution<int> dist(1, n);

	this_thread::sleep_for(chrono::milliseconds(1500));
	
	// Mersenne Twister(mt19937)�� �̿��Ͽ� ������ n��ü�� �ֻ����� ���� ����� �����Ѵ�.
	int diceNum = dist(generator);
	
	if (diceNum == winNum_)
	{
		printAcceptMeant();
		return true;
	}

	printRejectMeant();
	return false;
}

void CandidateRegion::printAcceptMeant()
{
	cout << location_ << " �ֹε� : �� �˰ڽ��ϴ� �Ф�" << endl;
	this_thread::sleep_for(chrono::milliseconds(1500));
	cout << "�ڱ��� ������� " << location_ << "���� �ֹε��� �����ϴµ� �����ߴ�. �ƽ�! ȣ����Ҵ�!" << endl;
	cout << "===================================================" << endl;
}

void CandidateRegion::printRejectMeant()
{
	cout << location_ << " �ֹε� : " << rejectMeant_ << endl;
	this_thread::sleep_for(chrono::milliseconds(1500));
	cout << "�ڱ��� ������� " << location_ << "���� �ֹε鿡�� �ϰ��� �������ߴ�." << endl;
	cout << "===================================================" << endl;
}
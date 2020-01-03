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
	cout << "박근혜 대통령은 " << location_ << "에 방문해서 주민들을 설득하고 있다." << endl;
	random_device randomDevice;
	mt19937 generator(randomDevice());
	int n = ThaadDeployManager::getInstance()->getNumOfCandidateRegions();
	uniform_int_distribution<int> dist(1, n);

	this_thread::sleep_for(chrono::milliseconds(1500));
	
	// Mersenne Twister(mt19937)를 이용하여 가상의 n면체의 주사위를 굴려 운명을 결정한다.
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
	cout << location_ << " 주민들 : 네 알겠습니다 ㅠㅠ" << endl;
	this_thread::sleep_for(chrono::milliseconds(1500));
	cout << "박근혜 대통령은 " << location_ << "에서 주민들을 설득하는데 성공했다. 아싸! 호구잡았다!" << endl;
	cout << "===================================================" << endl;
}

void CandidateRegion::printRejectMeant()
{
	cout << location_ << " 주민들 : " << rejectMeant_ << endl;
	this_thread::sleep_for(chrono::milliseconds(1500));
	cout << "박근혜 대통령은 " << location_ << "에서 주민들에게 완강히 거절당했다." << endl;
	cout << "===================================================" << endl;
}
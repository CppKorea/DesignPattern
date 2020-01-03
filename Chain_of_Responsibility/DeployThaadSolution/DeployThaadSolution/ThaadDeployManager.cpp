#include "ThaadDeployManager.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

ThaadDeployManager::ThaadDeployManager()
{
}

ThaadDeployManager::~ThaadDeployManager()
{
}

ThaadDeployManager* ThaadDeployManager::getInstance()
{
	if (instance_ == nullptr)
		instance_ = new ThaadDeployManager();
	
	return instance_;
}

void ThaadDeployManager::releaseInstance()
{
	if (instance_ != nullptr)
		delete instance_;
}

bool ThaadDeployManager::parseFile(string txtFileName)
{
	ifstream ifs(txtFileName);

	if (ifs.fail())
		return false;

	string line;

    // 첫 번째 라인은 컬럼명이므로 제끼고 나머지 레코드들을 파싱한다.
	getline(ifs, line);

	while (!ifs.eof() && getline(ifs, line))
	{
		if (line.empty())
			break;

		vector<string> splitedString = split(line, '\t');

		CandidateRegion region(splitedString[0], splitedString[1], splitedString[2], splitedString[3], (stoi(splitedString[4])));
		candidateRegions_.push_back(region);
	}

	ifs.close();

	return true;
}

bool ThaadDeployManager::pickRegion()
{
	if (candidateRegions_.empty())
		return false;

	// 책임사슬로 묶인 이들의 운명의 연쇄가 지금 시작된다! 뚜둥!
	for (auto& region : candidateRegions_)
	{
		this_thread::sleep_for(chrono::milliseconds(3000));

		if (region.determine())
			return true;
	}

	return false;
}

int ThaadDeployManager::getNumOfCandidateRegions()
{
	return candidateRegions_.size();
}

// C++ string에는 왜 split 함수가 없을까요?
vector<string> ThaadDeployManager::split(string str, char delimiter)
{
	vector<string> elems; stringstream ss(str); string item;

	while (getline(ss, item, delimiter))
		elems.push_back(item);

	return elems;
}
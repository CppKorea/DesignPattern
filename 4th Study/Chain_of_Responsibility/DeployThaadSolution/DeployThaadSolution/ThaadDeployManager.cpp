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

    // ù ��° ������ �÷����̹Ƿ� ������ ������ ���ڵ���� �Ľ��Ѵ�.
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

	// å�ӻ罽�� ���� �̵��� ����� ���Ⱑ ���� ���۵ȴ�! �ѵ�!
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

// C++ string���� �� split �Լ��� �������?
vector<string> ThaadDeployManager::split(string str, char delimiter)
{
	vector<string> elems; stringstream ss(str); string item;

	while (getline(ss, item, delimiter))
		elems.push_back(item);

	return elems;
}
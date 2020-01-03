#pragma once

#include <string>
#include <vector>

#include "CandidateRegion.h"

using namespace std;

class ThaadDeployManager
{
public:
	static ThaadDeployManager* getInstance();
	static void releaseInstance();

	bool parseFile(string txtFileName);
	bool pickRegion();
	int getNumOfCandidateRegions();

private:
	ThaadDeployManager();
	~ThaadDeployManager();
	vector<string> split(string str, char delimeter);

	vector<CandidateRegion> candidateRegions_;
	static ThaadDeployManager* instance_;
};
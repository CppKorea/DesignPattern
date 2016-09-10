#pragma once

#include <string>

#include "IDeployable.h"

using namespace std;

class CandidateRegion : public IDeployable
{
public:
	CandidateRegion(string timestamp, string name, string location, string rejectMeant, int winNum);
	virtual ~CandidateRegion();
	// Deployable��(��) ���� ��ӵ�
	virtual bool determine() override;

	void printAcceptMeant();
	void printRejectMeant();

private:
	string timestamp_;
	string name_;
	string location_;
	string rejectMeant_;
	int winNum_;
};
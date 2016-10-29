#include <iostream>

#include "ThaadDeployManager.h"

using namespace std;

ThaadDeployManager* ThaadDeployManager::instance_ = nullptr;

int main()
{
	ThaadDeployManager* manager = ThaadDeployManager::getInstance();

	manager->parseFile("C:/Users/Minegi/Desktop/result.txt");

	cout << "===================================================" << endl;
	cout << "���ݺ��� �ѹݵ� Thaad ��ġ �ùķ��̼��� �����մϴ�." << endl;
	cout << "===================================================" << endl;
	
	if (manager->pickRegion())
		cout << "Thaad ��ġ �Ϸ�! �� ���߾�� :)" << endl;
	else
		cout << "Thaad ��ġ ����! ���� ���� �����ϼ���! :(" << endl;

	ThaadDeployManager::releaseInstance();

	return 0;
}
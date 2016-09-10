#include <iostream>

#include "ThaadDeployManager.h"

using namespace std;

ThaadDeployManager* ThaadDeployManager::instance_ = nullptr;

int main()
{
	ThaadDeployManager* manager = ThaadDeployManager::getInstance();

	manager->parseFile("C:/Users/Minegi/Desktop/result.txt");

	cout << "===================================================" << endl;
	cout << "지금부터 한반도 Thaad 배치 시뮬레이션을 시작합니다." << endl;
	cout << "===================================================" << endl;
	
	if (manager->pickRegion())
		cout << "Thaad 배치 완료! 참 잘했어요 :)" << endl;
	else
		cout << "Thaad 배치 실패! 다음 생에 도전하세요! :(" << endl;

	ThaadDeployManager::releaseInstance();

	return 0;
}
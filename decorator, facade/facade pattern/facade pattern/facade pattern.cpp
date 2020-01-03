// facade pattern.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;


struct HeadWare
{
	virtual void on()=0 ;
	virtual void off()= 0;
};

struct Bios : HeadWare  {
	void on() {
		cout << "BIOS ON" << endl;
	}
	void off() {
		cout << "BIOS OFF" << endl;
	}

};


struct Cpu : HeadWare {
	void on() {
		cout << "CPU ON" << endl;
	}
	void off() {
		cout << "CPU OFF" << endl;
	}

};

struct Graph : HeadWare {
	void on() {
		cout << "GRAPH ON" << endl;
	}
	void off() {
		cout << "GRAPH OFF" << endl;
	}
};

class Computer {
private:
	Bios bios;
	Cpu cpu;
	Graph graph;
public:
	void on() {
		bios.on();
		cpu.on();
		graph.on();
	}
	void off() {
		bios.off();
		cpu.off();
		graph.off();
	}

};
int main()
{
	Computer computer;
	computer.on();
	computer.off();
    return 0;
}


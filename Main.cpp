#define DEBUG

#include <iostream>
#include "Simulation.h"

int main() {
	Simulation simulation(5, 10);
	for (int i = 0; i < 100; ++i) {
		simulation.process();
	}
	simulation.process();
	std::cout << simulation.report();
	system("pause");
}
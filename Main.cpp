#define DEBUG

#include <iostream>
#include "Simulation.h"

int main() {
	/*std::cout << "Stability test...";
	for (int i = 0;;++i) {
		if (!(i % 100))
			std::cout << "ITERATION " << i << "\n";
		Simulation simulation(3, 10);
		for (int j = 0; j < 50; j++) {
			simulation.process();
		}
		//system("cls");
	}*/
	std::cout << "Passed!\n";
	Simulation simulation(3, 6);
	for (int i = 0; i < 50; ++i) {
		simulation.process();
		std::cout << simulation.report();
		system("pause");
		system("cls");
	}
}
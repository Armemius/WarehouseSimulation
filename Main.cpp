#include <iostream>
#include "Package.h"
#include "TransferService.h"

int main() {
	TransferService::addTrans(Transmission(Package(), 20, nullptr, 8));
	TransferService::addTrans(Transmission(Package(), 20, nullptr, 7));
	TransferService::addTrans(Transmission(Package(), 20, nullptr, 0));

	for (auto it = TransferService::packages_.begin(); it != TransferService::packages_.end();) {
		std::cout << it->time << "\n\r";
		it++;
	}
	TransferService::process();

	for (auto it = TransferService::packages_.begin(); it != TransferService::packages_.end();) {
		std::cout << it->time << "\n\r";
		it++;
	}


	Package pack = Package(MEAT, 10);
	pack.rot();
	std::cout << pack.weightAll();
}
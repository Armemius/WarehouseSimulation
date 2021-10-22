#include <iostream>
#include "Package.h"
#include "TransferService.h"

int main() {
	TransferService::process();
	Package pack = Package(MEAT, 10);
	pack.rot();
	std::cout << pack.weightAll();
}
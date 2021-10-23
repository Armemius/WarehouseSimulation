#include <iostream>
#include "Package.h"
#include "TransferService.h"
#include "Storage.h"

int main() {
	Package pack = Package(Product::list["meat"], 10);
	//std::cout << pack.weightAll() << std::endl;
	Storage store = Storage(std::list<Package>{pack}, 10000);
	//pack.rot();
	store.add(pack);
	std::cout << store.count();
}
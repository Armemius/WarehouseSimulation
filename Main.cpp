#include <iostream>
#include "Package.h"
#include "TransferService.h"
#include "Storage.h"
#include "Warehouse.h"

int main() {
	Warehouse warehouse;
	warehouse.test();

	std::cout << TransferService::packages_.size() << "\n";

	for (auto it = TransferService::packages_.begin(); it != TransferService::packages_.end(); ++it) {
		for (auto sus : it->packs) {
			std::cout << sus.count() << " ";
		}
		std::string str = it->dest->name();
		std::cout << "\n" << it->time << " " << str;
	}

	

	TransferService::process();
	TransferService::process();
	TransferService::process();
	TransferService::process();
	TransferService::process();
	TransferService::process();
	
	std::cout << warehouse.cash_ << "\n";
	std::cout << warehouse.storages_["egg"].cargo();


	Package pack = Package(Product::list["meat"], 10);
	Storage store = Storage(std::list<Package>{pack}, 1);
	store.add(pack);
	//std::cout << store.count();
}
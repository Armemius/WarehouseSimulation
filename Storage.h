#pragma once
#include "Package.h"
#include <string>
#include <list>

class Storage {
public:
	Storage();
	Storage(std::string id, int maxCargo);
	Storage(std::list<Package> store, int maxCargo);

	// True if added, false if not
	bool add(Package pack);
	Package& get(int index);
	int free();
	int cargo();
	int maxCargo();
	int count();

	void setVCargo(int value);
	int getVCargo();

	const Package& operator[](int index);
private:
	int cargo_ = 0;
	int virtualCargo_ = 0;
	int maxCargo_ = 0;
	std::string id_ = "N/A";
	std::list<Package> store_;
};
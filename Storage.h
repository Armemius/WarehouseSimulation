#pragma once
#include "debug.h"
#include "Package.h"
#include <string>
#include <list>

class Report;

class Storage {
public:
	Storage();
	Storage(std::string id, int maxCargo);
	Storage(std::vector<Package> store, int maxCargo);

	// True if added, false if not
	bool add(Package pack);
	Package get(int index);
	int free() const;
	int cargo() const;
	int maxCargo() const;
	int count() const;
	int prodCount() const;

	void setVCargo(int value);
	void addVCargo(int value);
	int getVCargo();

	const Package& operator[](int index);

	friend class Warehouse;
	friend std::ostream& operator<<(std::ostream& out, const Report& rep);
private:
	int cargo_ = 0;
	int virtualCargo_ = 0;
	int maxCargo_ = 0;
	std::string id_ = "N/A";
	std::vector<Package> store_;
};
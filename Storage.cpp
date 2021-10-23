#include "Storage.h"
#include <iterator>

Storage::Storage() = default;

Storage::Storage(std::string id, int maxCargo) :
	id_(id),
	maxCargo_(maxCargo){}

Storage::Storage(std::list<Package> store, int maxCargo) :
	store_(store),
	id_(store.begin()->name()),
	maxCargo_(maxCargo) {
	if (store.size() == 0)
		throw std::exception("Storage: store size must be greater than 0");
	for (auto it = store.begin(); it != store.end(); ++it) {
		cargo_ += it->weightAll();
		if (cargo_ > maxCargo_)
			throw std::exception("Storage: packages weight is too big to hold");
	}
}

bool Storage::add(Package pack) {
	if (cargo_ + pack.weightAll() > maxCargo_ && pack.name() == id_)
		return false;
	cargo_ += pack.weightAll();
	store_.push_back(pack);
	return true;
}

Package& Storage::get(int index) {
	if (index < 0 || store_.size() - 1 < index)
		throw std::exception("Storage: index out of bounds");
	std::list<Package>::iterator it = store_.begin();
	std::advance(it, index);
	cargo_ -= it->weightAll();
	Package& pack = *it;
	store_.erase(it);
	return pack;
}

int Storage::free() {
	return maxCargo_ - cargo_;
}

int Storage::cargo() {
	return cargo_;
}

int Storage::maxCargo() {
	return maxCargo_;
}

int Storage::count() {
	return store_.size();
}

void Storage::setVCargo(int value) {
	virtualCargo_ = value;
}

int Storage::getVCargo() {
	return virtualCargo_;
}

const Package& Storage::operator[](int index) {
	if (index < 0 || store_.size() - 1 < index)
		throw std::exception("Storage: index out of bounds");
	std::list<Package>::iterator it = store_.begin();
	std::advance(it, index);
	return *it;
}
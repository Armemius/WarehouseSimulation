#include "Package.h"

Package::Package() = default;

Package::Package(Product type, int count) : Product(type),
	count_(count) {}

int Package::priceAll() {
	return this->price() * this->count_;
}

int Package::count() {
	return count_;
}
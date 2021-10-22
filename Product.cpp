#include "Product.h"

Product::Product() = default;

Product::Product(std::string name, int weight, int price) : 
	name_(name),
	weight_(weight),
	price_(price) {}

Product::Product(std::string name, int weight, int price, int expiryTime) :
	name_(name),
	weight_(weight),
	price_(price),
	expiryTime_(expiryTime),
	maxExpiryTime_(expiryTime),
	isRottable_(true) {
	if (expiryTime <= 0)
		throw std::exception("Product: expiry time must be greater than 1");
}

const std::string& Product::name() {
	return name_;
}

int Product::weight() {
	return weight_;
}

int Product::price() {
	return price_;
}

double Product::freshness() {
	return isRottable_ ? expiryTime_ * 1.0 / maxExpiryTime_ : 1;
}

void Product::rot() {
	if (isRottable_)
		expiryTime_--;
	return;
}

bool Product::isRotten() {
	return freshness() <= 0;
}
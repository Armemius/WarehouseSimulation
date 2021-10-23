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

std::tr1::unordered_map<std::string, const Product> Product::list = {
	{"egg", Product("egg", 300, 50, 14)},
	{"fish", Product("fish", 500, 750, 18)},
	{"meat", Product("meat", 500, 600, 20)},
	{"apple", Product("apple", 400, 30, 9)},
	{"pear", Product("pear", 400, 40, 9)},
	{"milk", Product("milk", 500, 100, 8)},
	{"water", Product("water", 500, 25, 30)},
	{"bread", Product("bread", 300, 80, 8)},
	{"cake", Product("cake", 500, 500, 16)},
	{"napkins", Product("napkins", 100, 150)},
	{"soap", Product("soap", 100, 250)},
	{"shampoo", Product("shampoo", 200, 400)},
	{"coal", Product("coal", 500, 200)}
};
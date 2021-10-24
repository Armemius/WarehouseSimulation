#include "Product.h"

Product::Product() = default;

Product::Product(std::string name, int price) : 
	name_(name),
	price_(price) {}

Product::Product(std::string name, int price, int expiryTime) :
	name_(name),
	price_(price),
	expiryTime_(expiryTime),
	maxExpiryTime_(expiryTime),
	isRottable_(true) {
	if (expiryTime <= 0)
		throw std::exception("Product: expiry time must be greater than 1");
}

const std::string& Product::name() const {
	return name_;
}

int Product::price() const {
	return price_;
}

double Product::freshness() const {
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

std::vector<std::string> Product::names = {
	"egg",
	"fish",
	"meat",
	"apple",
	"pear",
	"milk",
	"water",
	"bread",
	"cake",
	"napkins",
	"soap",
	"shampoo",
	"coal"
};

std::tr1::unordered_map<std::string, const Product> Product::list = {
	{"egg", Product("egg", 50, 14)},
	{"fish", Product("fish", 750, 18)},
	{"meat", Product("meat", 600, 20)},
	{"apple", Product("apple", 30, 9)},
	{"pear", Product("pear", 40, 9)},
	{"milk", Product("milk", 100, 8)},
	{"water", Product("water", 25, 30)},
	{"bread", Product("bread", 80, 8)},
	{"cake", Product("cake", 500, 16)},
	{"napkins", Product("napkins", 150)},
	{"soap", Product("soap", 250)},
	{"shampoo", Product("shampoo", 400)},
	{"coal", Product("coal", 200)}
};
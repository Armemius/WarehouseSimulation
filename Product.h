#pragma once
#include <string>

class Product {
public:
	// Default
	Product();
	// For non-rottable
	Product(std::string name, int weight, int price);
	// For rottable
	Product(std::string name, int weight, int price, int expiryTime);
	const std::string& name();
	int weight();
	int price();
	double freshness();
	void rot();
	bool isRotten();
private:
	std::string name_ = "N/A";
	int weight_ = 0;
	int price_ = 0;
	int expiryTime_ = 0;
	int maxExpiryTime_ = 0;
	bool isRottable_ = false;
};

#define EGG Product("egg", 300, 50, 14)
#define FISH Product("fish", 500, 750, 18)
#define MEAT Product("meat", 500, 600, 20)
#define APPLE Product("apple", 400, 30, 9)
#define PEAR Product("pear", 400, 40, 9)
#define MILK Product("milk", 500, 100, 8)
#define WATER Product("water", 500, 25, 30)
#define BREAD Product("bread", 300, 80, 8)
#define CAKE Product("cake", 500, 500, 16)

#define NAPKINS Product("napkins", 100, 150)
#define SOAP Product("soap", 100, 250)
#define SHAMPOO Product("shampoo", 200, 400)
#define COAL Product("coal", 500, 200)
#pragma once
#include <string>
#include <unordered_map>

class Product {
public:
	// Default
	Product();
	// For non-rottable
	Product(std::string name, int price);
	// For rottable
	Product(std::string name, int price, int expiryTime);
	const std::string& name() const;
	int price() const;
	double freshness() const;
	void rot();
	bool isRotten();
	
	static std::vector<std::string> names;
	static std::tr1::unordered_map<std::string, const Product> list;
private:
	std::string name_ = "N/A";
	int price_ = 0;
	int expiryTime_ = 0;
	int maxExpiryTime_ = 0;
	bool isRottable_ = false;
};
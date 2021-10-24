#pragma once
#include "Product.h"

class Package : public Product {
public:
	Package();
	Package(Product type, int count);
	int priceAll();
	int count();
private:
	int count_ = 0;
};
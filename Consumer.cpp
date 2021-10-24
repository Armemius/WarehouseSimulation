#include "Consumer.h"
#include <random>

Consumer::Consumer(Warehouse* warehouse, int types) : 
	warehouse_(warehouse), 
	types_(types) {
	for (int i = 0; i < types; ++i) {
		std::uniform_int_distribution<int> randx(0, 250);
		std::random_device rand_dev;
		std::mt19937 rand_engine(rand_dev());
		weights_.insert({ Product::names[i], randx(rand_engine) });
		products_.insert({ Product::names[i], 1000 });
		virtualProducts_.insert({ Product::names[i], 0 });
	}
}

void Consumer::reloadWeights() {
	for (auto it = weights_.begin(); it != weights_.end(); ++it) {
		std::uniform_int_distribution<int> randx(-30, 30);
		std::random_device rand_dev;
		std::mt19937 rand_engine(rand_dev());
		it->second += randx(rand_engine);
	}
}

void Consumer::process() {
	for (int i = 0; i < types_; ++i) {
		const std::string& name = Product::names[i];
		products_[name] -= weights_[name];
		int diff = 1000 - products_[name];
		if (diff < 0 && diff > 300) {
			request(Request(name, diff * 2, this), warehouse_);
		}
	}
}

// Implementation
const std::string& Consumer::name() {
	return "consumer";
}

void Consumer::processRequest(Request req) {
	// Not needed
}

void Consumer::processAnswer(Answer ans) {
	if (!ans.affirmative) {
		products_[ans.type] = 1300;
		return;
	}
	std::uniform_real_distribution<double> randx(1.05, 1.3);
	std::random_device rand_dev;
	std::mt19937 rand_engine(rand_dev());
	order(Order(ans.type, ans.count * Product::list[ans.type].price() * randx(rand_engine), ans.count, this), warehouse_);
}

void Consumer::processOrder(Order ord) {
	// Not needed
}

void Consumer::processTransmission(Transmission trans) {
	std::string name = trans.packs[0].name();
	for (auto& pack : trans.packs) {
		products_[name] += pack.count();
	}
}

void Consumer::request(Request req, ITransferPoint* dest) {
	dest->processRequest(req);
}

void Consumer::answer(Answer ans, ITransferPoint* dest) {
	dest->processAnswer(ans);
}

void Consumer::order(Order ord, ITransferPoint* dest) {
	dest->processOrder(ord);
}

void Consumer::transmit(Transmission trans) {
	TransferService::addTrans(trans);
}
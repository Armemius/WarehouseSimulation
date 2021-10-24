#include "Warehouse.h"
#include <random>

Warehouse::Warehouse() {}

// Implementation
const std::string& Warehouse::name() {
	return "warehouse";
}

void Warehouse::processRequest(Request req) {
	requests_.push_back(req);
}

void Warehouse::processAnswer(Answer ans) {
	std::uniform_real_distribution<double> priceKoef(0.75, 0.9);
	std::random_device rand_dev;
	std::mt19937 rand_engine(rand_dev());
	int price = ans.count * Product::list[ans.type].price() * priceKoef(rand_engine);
	if (price > cash_)
		return;
	order(Order(ans.type, price, ans.count, this), ans.dest);
}

void Warehouse::processOrder(Order ord) {

}

void Warehouse::processTransmission(Transmission trans) {
	for (auto& pack : trans.packs) {
		if (!storages_[pack.name()].add(pack)) {
			break;
		}
		storages_[pack.name()].setVCargo(storages_[pack.name()].getVCargo() - 1);
	}
}

void Warehouse::request(Request req, ITransferPoint* dest) {
	dest->processRequest(req);
}

void Warehouse::answer(Answer ans, ITransferPoint* dest) {
	dest->processAnswer(ans);
}

void Warehouse::order(Order ord, ITransferPoint* dest) {
	cash_ -= ord.price;
	dest->processOrder(ord);
}

void Warehouse::transmit(Transmission trans) {
	TransferService::addTrans(trans);
}
#include "Warehouse.h"

Warehouse::Warehouse() {}

// Implementation
const std::string& Warehouse::name() {
	return "warehouse";
}

void Warehouse::processRequest(Request req) {
	requests_.push_back(req);
}

void Warehouse::processAnswer(Answer ans) {

}

void Warehouse::processOrder(Order ord) {

}

void Warehouse::processTransmission(Transmission trans) {
	for (auto& pack : trans.packs) {
		if (!storages_[pack.name()].add(pack)) {
			break;
		}
		storages_[pack.name()].setVCargo(storages_[pack.name()].getVCargo() - pack.weight());
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
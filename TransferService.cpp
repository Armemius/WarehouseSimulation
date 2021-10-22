#include "Commands.h"
#include "TransferService.h"

std::list<Transmission> TransferService::packages_;

void TransferService::addTrans(Transmission trans) {
	packages_.push_back(trans);
}

void TransferService::process() {
	for (auto it = packages_.begin(); it != packages_.begin();) {
		if (it->count == 0) {
			it->dest->processTransmission(*it);
			packages_.erase(it++);
			continue;
		}
		it->time--;
		it++;
	}
}
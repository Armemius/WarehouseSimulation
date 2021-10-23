#include "Commands.h"
#include "TransferService.h"

std::list<Transmission> TransferService::packages_;

void TransferService::addTrans(Transmission trans) {
	if (trans.dest == nullptr)
		return;
	packages_.push_back(trans);
}

void TransferService::process() {
	for (auto it = packages_.begin(); it != packages_.end();) {
		if (it->time == 0) {
			if (it->dest != nullptr)
			it->dest->processTransmission(*it);
			packages_.erase(it++);
			continue;
		}
		it->time--;
		it++;
	}
}
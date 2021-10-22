#pragma once
#include <list>
#include "Commands.h"
#include "ITransferPoint.h"

class Transmission;

class TransferService {
public:
	static void addTrans(Transmission trans);
	static void process();
private:
	TransferService();
	static std::list<Transmission> packages_;
};
#pragma once
#include <list>
#include <iostream>
#include "Commands.h"
#include "ITransferPoint.h"

class Transmission;
class Report;

class TransferService {
public:
	static void addTrans(Transmission trans);
	static void process();
	friend class Report;
	friend std::ostream& operator<<(std::ostream& out, const Report& rep);
private:
	TransferService();
	static std::list<Transmission> packages_;
};
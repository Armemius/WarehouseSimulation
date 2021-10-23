#pragma once
#include "Package.h"
#include "ITransferPoint.h"
#include <vector>

class ITransferPoint;

/*
* Commands are used to control products transimission between two spots
* Consumer sends a request what it wants to get
* Producer sends an answer how much it can sent 
* Consumer sends(or not) an order based on answer
* Producer sends package to transfer service
* Transfer service deliver package to consumer
*/

class Request {
public:
	Request(std::string type, int count, ITransferPoint* dest);
	std::string type;
	int count = 0;
	ITransferPoint* dest = nullptr;
};

class Answer {
public:
	Answer(std::string type, bool affirmative, int count, ITransferPoint* dest);
	bool affirmative = false;
	std::string type;
	int count = 0;
	ITransferPoint* dest = nullptr;
};

class Order {
public:
	Order(std::string type, int price, int count, ITransferPoint* dest);
	int price = 0;
	int count = 0;
	std::string type;
	ITransferPoint* dest = nullptr;
};

class Transmission {
public:
	Transmission(std::vector<Package> packs, ITransferPoint* dest, int time);
	std::vector<Package> packs;
	ITransferPoint* dest = nullptr;
	int time = 0;
};
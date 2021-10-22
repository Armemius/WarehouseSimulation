#pragma once
#include "Package.h"
#include "ITransferPoint.h"

class ITransferPoint;

/*
* How it works?
* Commands are used to control products transimission between two spots
* Consumer sends a request what it wants to get
* Producer sends an answer how much it can sent 
* Consumer sends(or not) an order based on answer
* Producer sends package to transfer service
* Transfer service deliver package to consumer
*/

class Request {
public:
	Request(Product type, int count, ITransferPoint* dest);
	Product type;
	int count = 0;
	ITransferPoint* dest = nullptr;
};

class Answer {
public:
	Answer(bool affirmative, int count, ITransferPoint* dest);
	bool affirmative = false;
	int count = 0;
	ITransferPoint* dest = nullptr;
};

class Order {
public:
	Order(int price, int count, ITransferPoint* dest);
	int price = 0;
	int count = 0;
	ITransferPoint* dest = nullptr;
};

class Transmission {
public:
	Transmission(Package pack, int count, ITransferPoint* dest, int time);
	Package pack;
	int count = 0;
	ITransferPoint* dest = nullptr;
	int time = 0;
};
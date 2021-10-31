#include "Commands.h"

Request::Request(std::string type, int count, ITransferPoint* dest) :
	type(type),
	count(count),
	dest(dest){}

Answer::Answer(std::string type, bool affirmative, int count, ITransferPoint* dest) :
	type(type),
	affirmative(affirmative),
	count(count),
	dest(dest) {}

Order::Order(std::string type, int price, int count, ITransferPoint* dest) :
	type(type),
	price(price),
	count(count),
	dest(dest) {}

Transmission::Transmission(std::vector<Package> packs, const ITransferPoint* dest, int time) :
	packs(packs),
	dest(dest),
	time(time) {}
#pragma once

#include "Address.h"

class Building {
private:
	Address address;
	int vehicleCapacity;
	int cost;

private:
	std::istream& read(std::istream& in);

public:
	Building(std::istream& in);

	friend std::ostream& operator<<(std::ostream& out, const Building& place);

	const Address& getAddress() const { return address; }
	int getCapacity() const { return vehicleCapacity; }
	int getCost() const { return cost; }
};
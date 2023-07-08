#include "Building.h"

Building::Building(std::istream& in) : address(in)
{
	read(in);
}

std::ostream& operator<<(std::ostream& out, const Building& place)
{
	if (typeid(out) == typeid(std::ofstream))
	{
		out << place.address << " " << place.vehicleCapacity << " " << place.cost << " ";
	}
	else {
		out << place.address << "Capacity (max vehicles): " << place.vehicleCapacity
			<< ", Cost: " << place.cost << std::endl;
	}
	return out;
}

std::istream& Building::read(std::istream& in)
{
	if (typeid(in) == typeid(std::ifstream))
	{
		in >> vehicleCapacity >> cost;
	}
	else {
		std::cout << "Enter building capacity (max vehicles, minimum 1): ";
		in >> vehicleCapacity;
		if (vehicleCapacity < 1)
			throw std::invalid_argument("Building initialization failed: no space for vehicles");
		std::cout << "Enter building cost (non negative): ";
		in >> cost;
		if (cost < 0)
			throw std::invalid_argument("Building initialization failed: negative building cost");
	}
	return in;
}
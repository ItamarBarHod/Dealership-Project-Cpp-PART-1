#include "Boat.h"

Boat::Boat(std::istream& in) : Vehicle(in)
{
	read(in);
}

Boat::~Boat()
{
}

std::ostream& Boat::print(std::ostream& out) const
{
	Vehicle::print(out);
	if (typeid(out) == typeid(std::ofstream))
	{
		out << sailingSpeed << " " << numOfSails << std::endl;
	}
	else {
		out << "Boat speed: " << sailingSpeed << ", number of sails: " << numOfSails << "\n\n";
	}
	return out;
}

std::istream& Boat::read(std::istream& in)
{
	if (typeid(in) == typeid(std::ifstream))
	{
		in >> sailingSpeed >> numOfSails;
	}
	else {
		std::cout << "Enter sailing speed (non negative): ";
		in >> sailingSpeed;
		if (sailingSpeed < 0)
			throw std::invalid_argument("Vehicle initialization failed: cant have negative speed");
		std::cout << "Enter number of sails (non negative): ";
		in >> numOfSails;
		if (numOfSails < 0)
			throw std::invalid_argument("Vehicle initialization failed: cant have negative number of sails");

	}
	return in;
}

void Boat::raisePrice()
{
	price *= factorArr[eBoat];
}
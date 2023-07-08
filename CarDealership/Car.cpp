#include "Car.h"

Car::Car(std::istream& in) : Vehicle(in)
{
	read(in);
}

Car::~Car()
{
}

void Car::raisePrice()
{
	price *= factorArr[eCar];
}


std::ostream& Car::print(std::ostream& out) const
{
	Vehicle::print(out);
	if (typeid(out) == typeid(std::ofstream))
	{
		out << drivingSpeed << " " << numOfWheels << std::endl;
	}
	else {
		out << "Car speed: " << drivingSpeed << ", number of wheels: " << numOfWheels << "\n\n";
	}
	return out;
}

std::istream& Car::read(std::istream& in)
{
	if (typeid(in) == typeid(std::ifstream))
	{
		in >> drivingSpeed >> numOfWheels;
	}
	else {
		std::cout << "Enter driving speed (non negative): ";
		in >> drivingSpeed;
		if (drivingSpeed < 0)
			throw std::invalid_argument("Vehicle initialization failed: cant have negative speed");
		std::cout << "Enter number of wheels (non negative): ";
		in >> numOfWheels;
		if (numOfWheels < 0)
			throw std::invalid_argument("Vehicle initialization failed: cant have negative number of wheels");
	}
	return in;
}

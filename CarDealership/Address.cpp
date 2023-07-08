#include "Address.h"

Address::Address(std::istream& in) : city(nullptr), street(nullptr), houseNum(0)
{
	in >> *this;
}

Address::Address(const Address& other) : street(nullptr), city(nullptr)
{
	*this = other;
}

Address::Address(Address&& other) noexcept : city(nullptr), street(nullptr)
{
	std::swap(city, other.city);
	std::swap(street, other.street);
	houseNum = other.houseNum;
}

const Address& Address::operator=(const Address& other)
{
	if (this != &other)
	{
		setCity(other.city);
		setStreet(other.street);
		houseNum = other.houseNum;
	}
	return *this;
}

const Address& Address::operator=(Address&& other) noexcept
{
	if (this != &other)
	{
		std::swap(city, other.city);
		std::swap(street, other.street);
		houseNum = other.houseNum;
	}
	return *this;
}

Address::~Address()
{
	if (city)
		delete[] city;
	if (street)
		delete[] street;
}

void Address::setStreet(const char* str)
{
	if (street)
		delete[] street;
	street = nullptr;
	if (str)
		street = _strdup(str);
}


void Address::setCity(const char* str)
{
	if (city)
		delete[] city;
	city = nullptr;
	if (str)
		city = _strdup(str);
}

std::istream& operator>>(std::istream& in, Address& address)
{
	char buffer[BUFFER_SIZE];
	if (typeid(in) == typeid(std::ifstream))
	{
		in.getline(buffer, BUFFER_SIZE);
		address.city = _strdup(buffer);
		in.getline(buffer, BUFFER_SIZE);
		address.street = _strdup(buffer);
		in >> address.houseNum;
		in.get();
	}
	else {
		std::cout << "Creating address!" << std::endl;
		std::cout << "Enter city: ";
		in.getline(buffer, BUFFER_SIZE);
		address.city = _strdup(buffer);
		std::cout << "Enter street: ";
		in.getline(buffer, BUFFER_SIZE);
		address.street = _strdup(buffer);
		std::cout << "Enter house number (non negative) ";
		in >> address.houseNum;
		if (address.houseNum < 0)
			throw std::invalid_argument("Address initialization failed: cant have negative house number");
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Address& address)
{
	if (typeid(out) == typeid(std::ofstream))
	{
		out << address.city << std::endl;
		out << address.street << std::endl;
		out << address.houseNum << std::endl;
	}
	else {
		out << "Address: " << address.city << ", " << address.street << ", " << address.houseNum << std::endl;
	}
	return out;
}
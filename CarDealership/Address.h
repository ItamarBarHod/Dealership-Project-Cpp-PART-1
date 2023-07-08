#pragma once

#include "General.h"

class Address {
private:
	const char* city;
	const char* street;
	int houseNum;

private:
	void setStreet(const char* street);
	void setCity(const char* street);
public:
	Address(std::istream& in);
	Address(const Address& other);
	Address(Address&& other) noexcept;
	const Address& operator=(const Address& other);
	const Address& operator=(Address&& other) noexcept;
	~Address();

	friend std::istream& operator>>(std::istream& in, Address& address);
	friend std::ostream& operator<<(std::ostream& out, const Address& address);

	const char* getCity() const { return city; }
	const char* getStreet() const { return street; }
	int getHouseNum() const { return houseNum; }

};
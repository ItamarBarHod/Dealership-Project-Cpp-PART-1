#pragma once

#include "Vehicle.h"

class Boat : virtual public Vehicle {
protected:
	int sailingSpeed;
	int numOfSails;

protected:
	std::ostream& print(std::ostream& out) const override;
	std::istream& read(std::istream& in) override;

public:
	Boat(std::istream& in);
	virtual ~Boat();

	virtual int getNumOfSails() const { return numOfSails; }
	virtual int getSpeed() const { return sailingSpeed; }

	virtual void raisePrice() override;
	virtual int getType() const override { return eBoat; }
};
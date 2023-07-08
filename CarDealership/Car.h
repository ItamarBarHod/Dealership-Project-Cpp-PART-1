#pragma once

#include "Vehicle.h"

class Car : virtual public Vehicle {
protected:
	int drivingSpeed;
	int numOfWheels;

protected:
	virtual std::ostream& print(std::ostream& out) const override;
	virtual std::istream& read(std::istream& in) override;

public:
	Car(std::istream& in);
	virtual ~Car();

	virtual int getNumOfWheels() const { return numOfWheels; }
	virtual int getSpeed() const { return drivingSpeed; }

	virtual void raisePrice() override;
	virtual int getType() const override { return eCar; }
};
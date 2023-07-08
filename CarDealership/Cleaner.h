#pragma once

#include "Worker.h"
#include "Vehicle.h"

class Cleaner : public Worker {
private:
	int numOfCleanedVehicles;

private:
	std::ostream& print(std::ostream& out) const override;
	std::istream& read(std::istream& in) override;

public:
	Cleaner(std::istream& in);

	void cleanVehicle(Vehicle& vec); // non const
};
#pragma once 

#include "General.h"
#include "SuperBoatCar.h"
#include "Salesman.h"

class DSFactory
{
public:
	static Vehicle* const createVehicle(std::istream& in);
	static Salesman* const createSalesman();
	static VehicleDealership* const createDealershipManually();
private:
	static Vehicle* const createVehicleHelper(std::istream& in, int type);
};
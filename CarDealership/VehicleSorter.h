#pragma once

#include "Vehicle.h"

class VehicleSorter {
public:
	typedef enum { eBubbleDown, eBubbleUp, eNofStrategy } sortType;
	static const char* strategyName[eNofStrategy];

	VehicleSorter(sortType type);
	virtual ~VehicleSorter();

	const char* getStrategyName() const { return strategyName[type]; }

	virtual int getType() const = 0;
	virtual void sortVehicles(Vehicle** vehicleArr, int size) const = 0;
private:
	sortType type;
};
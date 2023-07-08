#pragma once

#include "VehicleSorter.h"

class VehicleBubbleUp : public VehicleSorter {
	int getType() const override { return eBubbleUp; }
	virtual void sortVehicles(Vehicle** vehicleArr, int size) const override;
public:
	VehicleBubbleUp(sortType type);
};
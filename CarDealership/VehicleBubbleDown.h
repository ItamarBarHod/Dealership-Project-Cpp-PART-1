#pragma once

#include "VehicleSorter.h"

class VehicleBubbleDown : public VehicleSorter {
	int getType() const override { return eBubbleDown; }
	virtual void sortVehicles(Vehicle** vehicleArr, int size) const override;
public:
	VehicleBubbleDown(sortType type);
};
#include "VehicleBubbleDown.h"

void VehicleBubbleDown::sortVehicles(Vehicle** vehicleArr, int size) const
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (*vehicleArr[j] < *vehicleArr[j + 1])
				std::swap(vehicleArr[j], vehicleArr[j + 1]);
		}
	}
}

VehicleBubbleDown::VehicleBubbleDown(sortType type) : VehicleSorter(type)
{
}

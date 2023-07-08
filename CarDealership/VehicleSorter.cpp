#include "VehicleSorter.h"

const char* VehicleSorter::strategyName[VehicleSorter::eNofStrategy] = { "BubbleDown", "BubbleUp" };

VehicleSorter::VehicleSorter(sortType type) : type(type)
{
}

VehicleSorter::~VehicleSorter()
{
}

#include "VehicleDealership.h"
#include "DSFactory.h"

Vehicle* const DSFactory::createVehicle(std::istream& in)
{
	int type;
	Vehicle* newVehicle = nullptr;
	if (typeid(in) == typeid(std::ifstream))
	{
		in >> type;
		newVehicle = DSFactory::createVehicleHelper(in, type);
	}
	else {
		VehicleDealership* vd = VehicleDealership::getInstance();
		if (vd->isMaxVehicles())
			throw std::out_of_range("Maximum Vehicles, cannot add more");
		type = chooseVehicleType();
		newVehicle = DSFactory::createVehicleHelper(in, type);
	}
	return newVehicle;
}

Salesman* const DSFactory::createSalesman()
{
	VehicleDealership* vd = VehicleDealership::getInstance();
	if (vd->isMaxSalesman())
		throw std::out_of_range("Maximum salesmen, cannot add more");
	return new Salesman(std::cin);
}

VehicleDealership* const DSFactory::createDealershipManually()
{
	char buffer[BUFFER_SIZE];
	std::cout << "Enter dealership name: ";
	std::cin.getline(buffer, BUFFER_SIZE);
	Building building(std::cin);
	std::cout << "Enter max salesmen (minimum 1): ";
	int maxSalesmen;
	std::cin >> maxSalesmen;
	if (maxSalesmen < 1)
		throw std::invalid_argument("Dealership initialization failed: no salesman in dealership");
	std::cin.get();
	std::cout << "Initializing cleaner: " << std::endl;
	Cleaner cleaner = Cleaner(std::cin);
	return new VehicleDealership(buffer, building, maxSalesmen, cleaner);
}

Vehicle* const DSFactory::createVehicleHelper(std::istream& in, int type)
{
	switch (type)
	{
	case Vehicle::eCar:
		return new Car(in);
	case Vehicle::eBoat:
		return new Boat(in);
	case Vehicle::eSuperBoatCar:
		return new SuperBoatCar(in);
	default:
		throw std::exception("Error: createVehicle type (should never print)");
	}
}
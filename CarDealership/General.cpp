#include "General.h"
#include "VehicleDealership.h"
#include "DSFactory.h"
#include "VehicleSorter.h"

enum { ePrintDealership = 1, eAddSalesman, eAddVehicle, eSellVehicle, eCleanVehicle, eSellCollection, eBestSalesman, eBestVehicle, eSortVehicles, eExitProgram = 0 };

bool mainMenu(int option)
{
	VehicleDealership* dealership = VehicleDealership::getInstance();
	try {
		int cleanIndex, vehicleIndex, salesmanIndex, strategy;
		switch (option)
		{
		case ePrintDealership:
			dealership->printDealership();
			break;
		case eAddSalesman:
			dealership->addSalesman(DSFactory::createSalesman());
			std::cout << "Salesman Added\n" << std::endl;
			break;
		case eAddVehicle:
			dealership->addVehicle(DSFactory::createVehicle(std::cin));
			std::cout << "Vehicle Added\n" << std::endl;
			break;
		case eSellVehicle:
			vehicleIndex = getVehicleIndexFromUser();
			salesmanIndex = getSalesmanIndexFromUser();
			dealership->sellVehicle(salesmanIndex, vehicleIndex);
			std::cout << "Vehicle sold!\n" << std::endl;
			break;
		case eCleanVehicle:
			cleanIndex = getCleanIndexFromUser();
			dealership->getCleaner().cleanVehicle(dealership->getVehicle(cleanIndex));
			std::cout << "Vehicle was cleaned!\n" << std::endl;
			break;
		case eSellCollection:
			dealership->sellAllCollectionRandomly();
			std::cout << "Collection sold!\n" << std::endl;
			break;
		case eBestSalesman:
			std::cout << "The best salesman is (highest average profit): " << std::endl;
			dealership->getBestSalesman().printSalesman();
			break;
		case eBestVehicle:
			std::cout << "The best vehicle is (highest price): ";
			dealership->getBestVehicle().printVehicle();
			break;
		case eSortVehicles:
			std::cout << "Please choose sort strategy:\n1: bubbleSortDown\n2: bubbleSortUp" << std::endl;
			std::cin >> strategy;
			dealership->sortVehicles(--strategy);
			std::cout << "Changed sort to: " << dealership->getVehicleSorter().getStrategyName() << std::endl;
			std::cout << "Sorted vehicles!" << std::endl;
			break;
		case eExitProgram:
			return false;
		default:
			throw std::invalid_argument("No such option!\n");
		}
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		VehicleDealership::releaseInstance();
		terminate();
	}
	return true;
}

void printOptions()
{
	std::cout
		<< "\nAvailable options:" << std::endl
		<< "1: Print dealership" << std::endl
		<< "2: Add salesman" << std::endl
		<< "3: Add Vehicle" << std::endl
		<< "4: Sell vehicle" << std::endl
		<< "5: Clean a vehicle" << std::endl
		<< "6: Sell all available vehicles randomly" << std::endl
		<< "7: Show best salesman" << std::endl
		<< "8: Show best vehicle" << std::endl
		<< "9: Sort vehicles by strategy" << std::endl
		<< "0: Save & Exit dealership\n" << std::endl;
}


void printVehicleTypes()
{
	for (int i = 0; i < Vehicle::eNofType; i++)
	{
		std::cout << i + 1 << ": " << Vehicle::vehicleTypeArr[i] << std::endl;
	}
	std::cout << std::endl;
}

int chooseVehicleType()
{
	std::cout << "Please enter a vehicle type: " << std::endl;
	printVehicleTypes();
	int type;
	do {
		std::cin >> type;
		if (type <= 0 || type > Vehicle::eNofType)
			std::cout << "Please enter a valid type" << std::endl;
	} while (type <= 0 || type > Vehicle::eNofType);
	return --type;
}

int getVehicleIndexFromUser()
{
	VehicleDealership* dealership = VehicleDealership::getInstance();
	int vehicleIndex;
	dealership->printVehicles();
	std::cout << "\nPlease choose vehicle: " << std::endl;
	std::cin >> vehicleIndex;
	return --vehicleIndex;
}

int getSalesmanIndexFromUser()
{
	VehicleDealership* dealership = VehicleDealership::getInstance();
	int salesmanIndex;
	dealership->printSalesmen();
	std::cout << "\nPlease choose salesman: " << std::endl;
	std::cin >> salesmanIndex;
	return --salesmanIndex;
}

int getCleanIndexFromUser()
{
	VehicleDealership* dealership = VehicleDealership::getInstance();
	dealership->printVehicles();
	std::cout << "\nPlease choose vehicle number to clean: " << std::endl;
	int index;
	std::cin >> index;
	return --index;
}

void terminateDealership()
{
	std::cout << "Fatal error in dealership, exiting" << std::endl;
	exit(1);
}
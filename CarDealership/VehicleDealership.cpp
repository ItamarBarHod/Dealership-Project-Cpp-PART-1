#include "VehicleDealership.h"
#include "DSFactory.h"
#include "VehicleBubbleDown.h"
#include "VehicleBubbleUp.h"

VehicleDealership* VehicleDealership::vecDealership = nullptr;

VehicleDealership::VehicleDealership(std::istream& in) : place(in), cleaner(in), name(nullptr), maxSalesman(0), salesmanArr(nullptr), vehicleArr(nullptr), salesmanCount(0), vehicleCount(0), monthlyProfit(0), vSorter(nullptr)
{ //building and cleaner require initlist
	read(in);
}

void VehicleDealership::setSortStrategy(int strategy)
{
	if (strategy < 0 || strategy > 1)
		throw std::out_of_range("No such sort available");
	delete vSorter;
	VehicleSorter::sortType type = (VehicleSorter::sortType)strategy;
	if (strategy == (int)VehicleSorter::eBubbleDown)
		vSorter = new VehicleBubbleDown(type);
	else
		vSorter = new VehicleBubbleUp(type);
}

VehicleDealership::VehicleDealership(const char* name, const Building& place, int maxSalesman, const Cleaner& cleaner)
	: place(place), maxSalesman(maxSalesman), salesmanArr(nullptr), vehicleArr(nullptr),
	salesmanCount(0), vehicleCount(0), monthlyProfit(0), name(nullptr), cleaner(cleaner),
	vSorter(new VehicleBubbleDown(VehicleSorter::eBubbleDown))
{
	if (name)
		this->name = _strdup(name);
	else
		this->name = "Default Dealership";

	monthlyProfit -= place.getCost();
	monthlyProfit -= cleaner.getSalary();
	maxVehicles = place.getCapacity();

	vehicleArr = new Vehicle * [maxVehicles];
	salesmanArr = new Salesman * [maxSalesman];
}

VehicleDealership* VehicleDealership::getInstance()
{
	if (!vecDealership) {
		std::ifstream inFile(fileName);
		if (!inFile) {
			vecDealership = DSFactory::createDealershipManually();
		}
		else {
			vecDealership = new VehicleDealership(inFile);
			inFile.close();
		}
	}
	return vecDealership;
}

void VehicleDealership::releaseInstance()
{
	if (vecDealership) {
		std::ofstream outFile(fileName);
		if (outFile)
		{
			outFile << *vecDealership;
			outFile.close();
		}
		delete vecDealership;
	}
}

VehicleDealership::~VehicleDealership()
{
	if (name)
		delete[] name;
	if (vehicleArr)
	{
		for (int i = 0; i < vehicleCount; i++)
		{
			delete vehicleArr[i];
		}
		delete[] vehicleArr;
	}
	if (salesmanArr)
	{
		for (int i = 0; i < salesmanCount; i++)
		{
			delete salesmanArr[i];
		}
		delete[] salesmanArr;
	}
	delete vSorter;
}

void VehicleDealership::addVehicle(Vehicle* const vehicle)
{
	if (vehicleCount == maxVehicles)
		throw std::invalid_argument("Maximum amount of vehicles");
	vehicleArr[vehicleCount] = vehicle;
	monthlyProfit -= vehicle->getPrice();
	vehicleArr[vehicleCount]->raisePrice();
	vehicleCount++;
}

void VehicleDealership::addSalesman(Salesman* const salesman)
{
	if (salesmanCount == maxSalesman)
		throw std::invalid_argument("Maximum amount of salesmen");
	salesmanArr[salesmanCount] = salesman;
	salesmanCount++;
	monthlyProfit -= salesman->getSalary();
}

void VehicleDealership::printDealership() const
{
	std::cout << "\n\nDealership name: " << name << " | " << place
		<< "Monthly profit: " << monthlyProfit << "\nSorting vehicle strategy is: " << vSorter->getStrategyName() << "\nThe cleaner is: \n\n" << cleaner << "\n\n";
	try {
		printSalesmen();
	}
	catch (std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}
	printVehicles();
}

void VehicleDealership::printSalesmen() const
{
	if (salesmanCount == 0)
		throw std::out_of_range("No salesmen exist yet");

	std::cout << "There are " << salesmanCount << " salesmen\n\n";
	for (int i = 0; i < salesmanCount; i++)
	{
		std::cout << "Salesman number " << i + 1 << ": " << *salesmanArr[i] << std::endl;
	}
}

void VehicleDealership::printVehicles() const
{
	if (vehicleCount == 0)
		throw std::out_of_range("No vehicles exist yet");

	std::cout << "There are " << vehicleCount << " vehicles\n\n";
	for (int i = 0; i < vehicleCount; i++)
	{
		std::cout << "Vehicle number " << i + 1 << ": " << *vehicleArr[i] << std::endl;
	}
}

void VehicleDealership::sellAllCollectionRandomly()
{
	if (salesmanCount == 0)
		throw std::out_of_range("No salesman available to sell collection");
	if (vehicleCount == 0)
		throw std::out_of_range("No vehicles available to sell");

	for (int vehicleIndex = vehicleCount - 1; vehicleIndex >= 0; vehicleIndex--)
	{
		int randomSalesmanIndex = rand() % salesmanCount;
		const Salesman& salesman = *salesmanArr[randomSalesmanIndex];
		std::cout << "Salesman " << salesman.getName() << " sold vehicle number: "
			<< vehicleIndex << " for " << vehicleArr[vehicleIndex]->getPrice() << " dollars" << std::endl;
		sellVehicle(randomSalesmanIndex, vehicleIndex);
	}
}

void VehicleDealership::sellVehicle(int salesmanIndex, int vehicleIndex)
{
	if (salesmanIndex < 0 || salesmanIndex >= salesmanCount)
		throw std::out_of_range("Invalid salesman number");
	if (vehicleIndex < 0 || vehicleIndex >= vehicleCount)
		throw std::out_of_range("Invalid Vehicle number");

	const Vehicle& vehicle = getVehicle(vehicleIndex);
	Salesman& salesman = getSalesman(salesmanIndex);
	salesman.doSell(vehicle);
	monthlyProfit += vehicle.getPrice();

	delete vehicleArr[vehicleIndex];
	for (int i = vehicleIndex; i < vehicleCount; i++) // fix vehicle arr
	{
		vehicleArr[i] = vehicleArr[i + 1];
	}
	vehicleCount--;
}

void VehicleDealership::sortVehicles(int strategy)
{
	setSortStrategy(strategy);
	vSorter->sortVehicles(vehicleArr, vehicleCount);
}

Vehicle& VehicleDealership::getVehicle(int index) const
{
	if (index < 0 || index >= vehicleCount)
		throw std::out_of_range("No such vehicle index");
	return *vehicleArr[index];
}

Salesman& VehicleDealership::getSalesman(int index) const
{
	if (index < 0 || index >= salesmanCount)
		throw std::out_of_range("No such salesman index");
	return *salesmanArr[index];
}

const Vehicle& VehicleDealership::getBestVehicle() const
{
	if (vehicleCount == 0)
		throw std::out_of_range("There are no vehicles yet");
	const Vehicle* temp = vehicleArr[0];
	for (int i = 1; i < vehicleCount; i++)
	{
		if (*vehicleArr[i] > *temp)
			temp = vehicleArr[i];
	}
	return *temp;
}

const Salesman& VehicleDealership::getBestSalesman() const
{
	if (salesmanCount == 0)
		throw std::out_of_range("There are no salesmen yet");
	Salesman* temp = salesmanArr[0];
	for (int i = 1; i < salesmanCount; i++)
	{
		if (*salesmanArr[i] >= *temp)
			temp = salesmanArr[i];
	}
	return *temp;
}

std::ostream& operator<<(std::ostream& out, const VehicleDealership& dealership)
{
	if (typeid(out) == typeid(std::ofstream))
	{
		out << dealership.place << std::endl;
		out << dealership.cleaner << std::endl;
		out << dealership.name << std::endl;
		out << dealership.monthlyProfit << " " << dealership.maxSalesman << " "
			<< dealership.salesmanCount << std::endl;
		for (int i = 0; i < dealership.salesmanCount; i++)
		{
			out << *dealership.salesmanArr[i];
		}
		out << dealership.maxVehicles << " " << dealership.vehicleCount << std::endl;
		for (int i = 0; i < dealership.vehicleCount; i++)
		{
			out << dealership.vehicleArr[i]->getType() << " ";
			out << *dealership.vehicleArr[i];
		}
		out << (int)dealership.vSorter->getType();
	}
	else {
		dealership.printDealership();
	}
	return out;
}

std::istream& VehicleDealership::read(std::istream& in)
{
	char buffer[BUFFER_SIZE];
	in.get();
	in.getline(buffer, BUFFER_SIZE);
	name = _strdup(buffer);
	in >> monthlyProfit;
	in >> maxSalesman >> salesmanCount;
	salesmanArr = new Salesman * [maxSalesman];
	if (maxSalesman >= salesmanCount) {
		for (int i = 0; i < salesmanCount; i++)
		{
			salesmanArr[i] = new Salesman(in);
		}
	}
	in >> maxVehicles >> vehicleCount;
	vehicleArr = new Vehicle * [maxVehicles];
	if (maxVehicles >= vehicleCount) {
		for (int i = 0; i < vehicleCount; i++)
		{
			vehicleArr[i] = DSFactory::createVehicle(in);
		}
	}
	int strategy;
	in >> strategy;
	setSortStrategy(strategy);
	return in;
}
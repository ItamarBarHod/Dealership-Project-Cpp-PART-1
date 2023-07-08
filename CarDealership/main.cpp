#include "General.h"
#include "VehicleDealership.h"

int main()
{
	srand((unsigned int)time(nullptr));
	set_terminate(terminateDealership);

	std::cout << "Welcome to the vehicle dealership!" << std::endl;

	bool badInit = true;
	while (badInit) {
		try {
			VehicleDealership* dealership = VehicleDealership::getInstance(); // throws on manual init if 0 salesmen / vehicle space
			badInit = false;
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what() << std::endl;
			std::cin.get();
		}
		catch (const std::exception& e) { // fatal error, should never be here
			std::cout << e.what() << std::endl;
			terminate();
		}
	}

	int option;
	do {
		printOptions();
		std::cin >> option;
		std::cin.get();
	} while (mainMenu(option));

	VehicleDealership::releaseInstance();

	std::cout << "Bye bye!" << std::endl;
	return 0;
}
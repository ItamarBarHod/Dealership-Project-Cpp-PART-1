#include "Date.h"

const int Date::MAX_DAY_ARR[MAX_MONTH] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
const char* Date::MONTH_ARR[MAX_MONTH] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

Date::Date(std::istream& in)
{
	read(in);
}

Date::Date(int year, unsigned month, unsigned day) : year(year), month(month), day(day)
{
}

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	if (typeid(out) == typeid(std::ofstream))
	{
		out << date.day << " " << date.month << " " << date.year;
	}
	else {
		out << date.day << "/" << date.month << "/" << date.year;
	}
	return out;
}

std::istream& Date::read(std::istream& in)
{
	if (typeid(in) == typeid(std::ifstream))
	{
		in >> day >> month >> year;
	}
	else {
		enum { eDay, eMonth, eYear, eDateSize };
		int dateArr[eDateSize] = { 0 };

		auto validDate = [](int day, int month, int year) -> bool
		{
			return day >= MIN_DAY && day <= MAX_DAY_ARR[month - 1] && month >= MIN_MONTH && month <= MAX_MONTH
				&& year >= MIN_YEAR && year <= MAX_YEAR;
		};

		bool isValid = false;
		do {
			std::cout << "Enter year (between " << MIN_YEAR << " and " << MAX_YEAR << "): ";
			in >> dateArr[eYear];
			std::cout << "Enter month (between " << MIN_MONTH << " and " << MAX_MONTH << "): ";
			in >> dateArr[eMonth];
			if (dateArr[eMonth] < 1 || dateArr[eMonth] > 12) // protect month arr print
			{
				std::cout << "Bad month, please try again" << std::endl;
				continue;
			}
			std::cout << "Enter day [" << MONTH_ARR[dateArr[eMonth] - 1] << "] (between "
				<< MIN_DAY << " and " << MAX_DAY_ARR[dateArr[eMonth] - 1] << "): ";
			in >> dateArr[eDay];
			isValid = validDate(dateArr[eDay], dateArr[eMonth], dateArr[eYear]);
			if (!isValid)
				std::cout << "Invalid date, try again" << std::endl;
		} while (!isValid);
		day = dateArr[eDay], month = dateArr[eMonth], year = dateArr[eYear];
	}
	return in;
}

std::istream& operator>>(std::istream& in, Date& date)
{
	return date.read(in);
}
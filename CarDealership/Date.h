#pragma once

#include <iostream>
#include <fstream>

class Date {
private:
	static constexpr int MIN_DAY = 1;
	static constexpr int MIN_MONTH = 1;
	static constexpr int MAX_MONTH = 12;
	const static int MAX_DAY_ARR[MAX_MONTH];
	const static char* MONTH_ARR[MAX_MONTH];
	static constexpr int MAX_YEAR = 2023;
	static constexpr int MIN_YEAR = 1970;

private:
	int year;
	unsigned month;
	unsigned day;

	std::istream& read(std::istream& in);

public:
	Date(std::istream& in);
	Date(int year = 1995, unsigned month = 7, unsigned day = 27);

	friend std::ostream& operator<<(std::ostream& out, const Date& date);
	friend std::istream& operator>>(std::istream& in, Date& date);
};
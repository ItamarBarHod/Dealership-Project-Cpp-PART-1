#pragma once

#include "Date.h"
#include "Address.h"

class Worker {
protected:
	static unsigned id;
	unsigned workerID;
	const char* name;
	Address** address;
	int numOfAddresses;
	Date birthday;
	int salary;

protected:
	Worker(std::istream& in);
	Worker(const Worker& other);
	Worker(Worker&& other) noexcept;
	Worker& operator=(const Worker& other);
	Worker& operator=(Worker&& other) noexcept;
	virtual ~Worker();

	virtual std::ostream& print(std::ostream& out) const;
	virtual std::ostream& printToFile(std::ostream& out) const;
	virtual std::ostream& printToScreen(std::ostream& out) const;
	virtual std::istream& read(std::istream& in);
	virtual std::istream& readFromUser(std::istream& in);
	virtual std::istream& readFromFile(std::istream& in);

public:
	friend std::ostream& operator<<(std::ostream& out, const Worker& worker);

	int getSalary() const { return salary; }
	const char* getName() const { return name; }
	Address** getAddress() const { return address; }
	int getNumOfAddress() const { return numOfAddresses; }
	const Date& getBirthday() const { return birthday; }

private:
	void setName(const char* str);
};

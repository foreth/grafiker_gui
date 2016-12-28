#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

enum positions { REGULAR, ASSISTANT, CO_MANAGER, MANAGER };
enum times {QUATER, HALF, THREE, FULL};
enum days {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};


class Shop;
class Month;

class Employee
{
	short id;
	string first_name;
	string last_name;
	positions position;
	times time;
	short working_hours;
	float time_multiplier;
	vector<short> free_days;

public:

	Employee(int id, string first_name, string last_name, positions position, times time);
	short getID();
	void printToConsole();
	void setWorkingHours(short working_hours){ this->working_hours = working_hours; }
	short getWorkingHours(){ return working_hours; }
	float getTimeMultiplier(){ return time_multiplier; }
	positions getPosition(){ return position; }
	vector<short>& getFreeDays(){ return free_days; }
	string getName(){ return first_name + " " + last_name; }
	times getTimeDimension(){ return time; }
	

	friend class Shop;
};


//####################################################################################################

class Shop
{
	vector<Employee> employee_list;
	short efficiency;						// it's a ghost variable now :) just an idea
	short open_hour;
	short close_hour;
    short min_employees_at_once;
    short number_of_employees;

public:
    Shop() : open_hour(7), close_hour(22), min_employees_at_once(2), number_of_employees(0) { srand(time(NULL)); }
	void addEmployee(Employee& employee);
    void addEmployee(string first_name, string last_name, positions position, times time);
	void deleteEmployee(Employee& employee);
	void deleteEmployee(short id);
	void listEmployees();
    Month* makeSchedule(short d, days f);
	void assignFreeDays(short days_in_month, short weekend_days);
    vector<Employee>& getEmployeeList(){ return employee_list; }
};

//####################################################################################################

class Time
{
	short hour;
	short minute;

public:
	Time(short hour, short minute);
	short getHour(){ return hour; }
};

//####################################################################################################

class WorkHour : public Time
{
	vector<Employee> employee_list;
public:
	WorkHour(short hour, short minute) : Time(hour, minute){ }
	WorkHour(short hour, short minute, Employee& employee) : Time(hour, minute){ employee_list.push_back(employee); }

	void addEmployee(Employee& employee){ employee_list.push_back(employee); }
	vector<Employee>& getEmployees(){ return employee_list; }

};

//####################################################################################################

class Day
{
	days this_day;
	vector<WorkHour> time;
	short date;
	short empty_hours;

public:
	Day(days this_day);
	days getDay();
	vector<WorkHour>& getTime();
	string toString();
    void setDate(short date){ this->date = date; }
    short getDate(){ return date; }
	short getEmptyHours(){ return empty_hours; }
	void setEmptyHours(short eh){ empty_hours = eh; }
	void hourUsed() { empty_hours--; }
};

//####################################################################################################

class Month
{
	vector<Day> day_list;
	short days_in_month;
	short weekend_days;

public:
    Month(short d, days f);
	void printToConsole();
	short getWorkingHours();
	vector<Day>& getDayList(){ return day_list; }
	short getWeekendDays(){ return weekend_days; }
	short getDaysInMonth(){ return days_in_month; }
};


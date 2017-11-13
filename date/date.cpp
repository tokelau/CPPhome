#include <iostream>
#include "date.h"

//using namespace std;

Date::Date(){
	day = 0, month = 0, year = 0;
	long int buf = 0;
	std::cout << "Input day: ";
	std::cin >> buf;
	while (day == 0) {
		if (buf > 0 && buf < 32) {
			day = buf;
		}
		else {
			std::cout << "Error! Input day: ";
			std::cin >> buf;
		}
	}
	std::cout << std::endl;
	std::cout << "Input month: ";
	std::cin >> buf;
	while (month == 0) {
		if (buf > 0 && buf < 13) {
			month = buf;
		}
		else {
			std::cout << "Error! Input month: ";
			std::cin >> buf;
		}
	}
	std::cout << std::endl;
	std::cout << "Input year: ";
	std::cin >> buf;
	while (year == 0) {
		if (buf >= 0) {
			year = buf;
		}
		else {
			std::cout << "Error! Input year: ";
			std::cin >> buf;
		}
	}
	std::cout << std::endl;
	initWeek();
	initMonth();
	initYear();
	initDay();
}

Date::Date(char* d){
	day = 0, month = 0, year = 0;
	unsigned int k;
	for(int i = 0; i < 2; i++){
		k = (unsigned int)*d - 48;
		if (k >= 0 && k <= 9) {
			day = day * 10 + k;
			d++;
		}
		else break;
	}
	d++;
	for(int i = 3; i < 5; i++){
		k = (unsigned int)*d - 48;
		if (k >= 0 && k <= 9) {
			month = month * 10 + k;
			d++;
		}
		else break;
	}
	d++;
	for(int i = 6; i<10 && (*d); i++){
		k = (unsigned int)*d - 48;
		year = year * 10 + k;
		d++;
	}
	initWeek();
	initMonth();
	initYear();
	initDay();
}

Date::Date(int d, int m, int y){
	day = d;
	month = m;
	year = y;
	initWeek();
	initMonth();
	initYear();
	initDay();
}

int Date::dist(Date d2){
	return date - d2.date;
}

std::ostream& operator <<(std::ostream& out, const Date& d){
	if (d.day < 10) {
		std::cout << 0;
	}
	std::cout<<d.day<<".";
	if (d.month < 10) {
		std::cout << 0;
	}
	std::cout<< d.month<<".";
	std::cout<<d.year;
	return out;
}

char* Date::dayWeek(){
	return dayOfWeek[date%7];
}

Date& Date::operator=(const Date& d) {
	day = d.day;
	month = d.month;
	year = d.year;
	return *this;
}

Date& Date::operator += (int days){
	while (days > 0) {
		days--;
		if (day == dayInMonth[month - 1]) {
			day = 1;
			if (month == 12) {
				month = 1;
				year += 1;
				dayInMonth[1] = (year % 400 == 0 ? 29 : ((year % 4 == 0 && year % 100 != 0) ? 29 : 28));
			}
			else month++;
		}
		else day++;
	}
	return *this;
}

Date Date::operator+(int days) {
	Date res(*this);
	res += days;
	return res;
}

Date& Date::operator -= (int days) {
	while (days > 0) {
		days--;
		if (day == dayInMonth[month - 1]) {
			day = dayInMonth[month - 1];
			if (month == 1) {
				month = 12;
				year -= 1;
				dayInMonth[1] = (year % 400 == 0 ? 29 : ((year % 4 == 0 && year % 100 != 0) ? 29 : 28));
			}
			else month++;
		}
		else day--;
	}
	return *this;
}

Date Date::operator - (int days) {
	Date res(*this);
	res -= days;
	return res;
}

void Date::initWeek() {
	for (int i = 0; i < 7; i++) {
		dayOfWeek[i] = new char[12];
	}
	dayOfWeek[0] = "Sunday";
	dayOfWeek[1] = "Monday";
	dayOfWeek[2] = "Tuesday";
	dayOfWeek[3] = "Wednesday";
	dayOfWeek[4] = "Thursday";
	dayOfWeek[5] = "Friday";
	dayOfWeek[6] = "Saturday";

}

void Date::initMonth() {
	dayInMonth[0] = 31, dayInMonth[1] = (year % 400 == 0 ? 29 : ((year % 4 == 0 && year % 100 != 0) ? 29 : 28)), dayInMonth[2] = 31;
	dayInMonth[3] = 30, dayInMonth[4] = 31, dayInMonth[5] = 30;
	dayInMonth[6] = 31, dayInMonth[7] = 31, dayInMonth[8] = 30;
	dayInMonth[9] = 31, dayInMonth[10] = 30, dayInMonth[11] = 31;
}

void Date::initDay() {
	date = day;
	for (unsigned int i = month - 1; i > 0; i--) {
		date += dayInMonth[i - 1];
	}
	for (unsigned int i = year - 1; i > 0; i--) {
		date += (i % 400 == 0 ? 366 : ((i % 4 == 0 && i % 100 != 0) ? 366 : 365));
	}
}

void Date::initYear() {
	if (year >= 0 && year <= 20) {
		year += 2000;
		dayInMonth[1] = (year % 400 == 0 ? 29 : ((year % 4 == 0 && year % 100 != 0) ? 29 : 28));
	}
	if (year > 20 && year < 100) {
		year += 1900;
		dayInMonth[1] = (year % 400 == 0 ? 29 : ((year % 4 == 0 && year % 100 != 0) ? 29 : 28));
		//std::cout << dayInMonth[1] << std::endl;
	}
}

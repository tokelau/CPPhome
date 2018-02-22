#ifndef DATE_H
#define DATE_H

class Date{
public:
	Date();
	Date(char * d);
	Date(int d, int m, int y);
	/*расстояние от d2 до экземпляра, который вызвал функцию*/
	int dist(Date d2);
	/*вывод дня недели*/
	char* dayWeek();
	/*прибавит дни*/
	Date& operator += (int days);
	Date operator +(int days);
	/*вычтет дни*/
	Date& operator -= (int days);
	Date operator - (int days);
	Date& operator = (const Date& d);
	friend std::ostream& operator <<(std::ostream& out, const Date& d);
private:
	unsigned int day, month, year;
	unsigned int date;
	char* dayOfWeek[7];
	int dayInMonth[12];
	void initWeek();
	void initMonth();
	void initDay();
	void initYear();
};

#endif

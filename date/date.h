#ifndef DATE_H
#define DATE_H

class Date{
public:
	Date();
	Date(char * d);
	Date(int d, int m, int y);
	unsigned int day, month, year;
	/*���������� �� d2 �� ����������, ������� ������ �������*/
	int dist(Date d2);
	/*����� ��� ������*/
	char* dayWeek();
	/*�������� ���*/
	Date& operator += (int days);
	Date& operator = (const Date& d);
	Date operator +(int days);
	friend std::ostream& operator <<(std::ostream& out, const Date& d);
private:
	unsigned int date;
	char* dayOfWeek[7];
	int dayInMonth[12];
	void initWeek();
	void initMonth();
	void initDay();
	void initYear();
};

#endif
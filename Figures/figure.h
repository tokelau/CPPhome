#ifndef FIG_H
#define FIG_H

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
 
using namespace std;

template <typename T> struct Dot {
	T x, y;
	Dot<T>(T xx, T yy) { x = xx; y = yy; };
};

class Figure {
public:
	virtual double perimeter() = 0; //почему эта функци€ была в private и все работало?
	virtual double area() = 0; 
};

/*квадрат*/
template <typename T> class Square : public Figure { //чем class отличаетс€ от typename?
	T a;
public: 
	Square<T>(T aa) { a = aa; }
	double perimeter() { return (double)4 * a; } //нужно ли здесь преобразование в double?
	double area() { return (double) a * a; }
};

/*круг*/
template <class T> class Circle : public Figure {
	T a;
public:
	Circle<T>(T aa) { a = aa; }
	double perimeter() { return (double) 2 * 3.1415 * a; }
	double area() { return (double) 3.1415 * a * a; }
};

/*пр€моугольник*/
template <class T> class Rectangle : public Figure {
	T a, b;
public:
	Rectangle<T>(T aa, T bb) { a = aa; b = bb; }
	double perimeter() { return (double)a * 2 + 2* b; }
	double area() { return (double)a * b; }
};

/*треугольник*/ //сделать Exception
template <class T> class Triangle : public Figure {
	T a, b, c;
	double p;
public:
	Triangle<T>(T aa, T bb, T cc) { a = aa; b = bb; c = cc; p = (a + b + c) / 2;  }
	double perimeter() { return (double)a + b + c; }
	double area() { return (double)sqrt(p*(p-a)*(p-b)*(p-c)); }
};

/*Ёллипс*/
template <class T> class Ellipse : public Figure {
	T a, b;
public:
	Ellipse <T>(T aa, T bb) { a = aa; b = bb; }
	double perimeter() { return (double) 2 * 3.1415 * sqrt((a*a + b*b) / 2); }
	double area() { return (double) 3.1415 * a * b; }
};

/*многоугольник*/
template <typename T> class Poligon : public Figure {
	vector<Dot<T>> d;
	void readCoordinates(const char* fileName) {
		ifstream in(fileName);
		T x, y;
		while (!in.eof())
		{
			in >> x >> y;
			d.emplace_back(x, y);
		}
	}
public:
	Poligon<T>(const char* fileName) { readCoordinates(fileName); }
	double perimeter() { 
		double per = 0;
		for (int i = 0	; i < d.size(); ++i) {
			per += sqrt(pow((d[(i+1)%d.size()].x - d[i].x),2) + pow((d[(i + 1) % d.size()].y - d[i].y),2));
		}
		return per; 
	}
	double area() { 
		double area = 0;
		for (int i = 0; i < d.size() - 1; ++i)
			area += (d[i].x + d[i + 1].x) * (d[i].y - d[i + 1].y);
		return area / 2;
	}
};

#endif // !FIG_H


#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational {
	void simplify();
public:
	long long numer;
	long long denom;
	Rational();
	Rational(long long n, long long d = 1);
	Rational& operator = (const Rational& r);
	Rational& operator += (const Rational& r);
	Rational operator + (const Rational& r) const;
	Rational operator -() const;
	Rational& operator -= (const Rational& r);
	Rational operator - (const Rational& r) const;
	Rational& operator *= (const Rational& r);
	Rational operator * (const Rational& r) const;
	Rational& operator /= (const Rational& r);
	Rational operator / (const Rational& r) const;
	Rational power(Rational r, long n); //степень
	Rational radical(Rational& r, long n); //корень любой степени
	Rational& operator ++ (); //префикс
	Rational operator ++ (int); //постфикс
	bool operator == (const Rational& r) const;
	bool operator != (const Rational& r) const;
	operator int() const;
	operator double() const;
	friend std::istream& operator >> (std::istream& in, Rational& r);
	friend std::ostream& operator << (std::ostream& out, const Rational& r);

	Rational* qEquation(Rational a, Rational b, Rational c);
};

#endif
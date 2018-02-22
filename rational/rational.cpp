#include "rational.h"
#include <iostream>

Rational::Rational() {
	numer = 0;
	denom = 1;
	simplify();
}

Rational::Rational(long long n, long long d) {
	numer = n;
	denom = d;
	simplify();
}

Rational& Rational::operator = (const Rational& r) {
	numer = r.numer;
	denom = r.denom;
	return *this;
}

Rational& Rational::operator += (const Rational& r) {
	numer = numer * r.denom + r.numer * denom;
	denom *= r.denom;
	simplify();
	return *this;
}

Rational Rational::operator + (const Rational& r) const {
	//создаем дробь res, чтобы можно было использовать +=
	Rational res(*this);
	return res += r;
}

Rational Rational::operator - () const {
	Rational r(-1*numer, denom);
	return r;
}

Rational& Rational::operator -= (const Rational& r) {
	return (*this += (-r));
}

Rational Rational::operator - (const Rational& r) const {
	Rational res(*this);
	return res -= r;
}

Rational& Rational::operator *= (const Rational& r) {
	numer *= r.numer;
	denom *= r.denom;
	simplify();
	return *this;
}

Rational Rational::operator * (const Rational& r) const {
	Rational res(*this);
	return res *= r;
}

Rational& Rational::operator /= (const Rational& r) {
	numer *= r.denom;
	denom *= r.numer;
	simplify();
	return *this;
}

Rational Rational::operator / (const Rational& r) const {
	Rational res(*this);
	return res /= r;
}

Rational Rational::power(Rational r, long n) {
	if (n == 1) return r;
	if (n < 0) {
		long long temp = r.numer;
		r.numer = r.denom;
		r.denom = temp;
		return power(r, -n);
	}
	return r*power(r, n - 1);
}

Rational Rational::radical(Rational& r, long n) {
	Rational x(*this);
	Rational n1(1, n);
	Rational n2(n - 1);
	for (int i = 0; i < 3; i++) { //после второй-третьей итерации зависает
		x = n1 * (n2 * x + r / x.power(x, n - 1));
		//std::cout << double( x )<< '\n';
	}
	return x;
}

Rational& Rational::operator ++ () {
	numer += denom;
	simplify();
	return *this;
}

Rational Rational::operator ++(int) {
	Rational r(*this);
	numer += denom;
	simplify();
	return r;
}

bool Rational::operator == (const Rational& r) const {
	return (numer == r.numer) && (denom == r.denom);
}

bool Rational::operator != (const Rational& r) const {
	return !((numer == r.numer) && (denom == r.denom));
}

Rational:: operator int() const {
	return numer / denom;
}

Rational:: operator double() const {
	return ((double) numer )/ denom;
}

std::istream& operator >> (std::istream& in, Rational& r) {
	in >> r.numer >> r.denom;    
	return in;
}

std::ostream& operator << (std::ostream& out, const Rational& r) {
	out << r.numer << "/" << r.denom;
	return out;
}

Rational* Rational::qEquation(Rational a, Rational b, Rational c) {
	Rational* x = new Rational[2];
	x[0] = x[1] = Rational(-1);
	if (double(a) == 0) return &(-c / b);
	Rational D = b*b - Rational(4) * a *c;
	if (double(D) < 0) {
		std::cout << "Discriminant is less than zero. I can't resolve it." << '\n';
		return x;
	}
	if (double(D) == 0) {
		x[0] = -b / a;
		return x;
	}
	if (double(D) > 0) {
		Rational* x = new Rational[2];
		x[0] = (b + D.radical(D, 2)) / (Rational(2) * a);
		x[1] = (b - D.radical(D, 2)) / (Rational(2) * a);
		return x;
	}
}

void Rational::simplify() {
	if (denom < 0) {
		numer *= -1;
		denom *= -1;
	}
	for (int i = 2; i <= abs(numer) && abs(denom); i++) {
		if (numer%i == 0 && denom%i == 0) {
			numer /= i;
			denom /= i;
			i--;
		}
	}
}
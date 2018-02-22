#include <iostream>
#include <stack>
#include "figure.h"

using namespace std;

int main(void) {
	Poligon<int> s("in.txt");
	cout<<s.perimeter()<<endl;
	cout << s.area() << endl;

	vector<Figure*> figs;
	double sum = 0;
	figs.push_back(new Square<int>(5));
	figs.push_back(new Triangle<int>(5, 5, 5));
	figs.push_back(new Circle<int>(5));
	figs.push_back(new Rectangle<int>(5, 4));
	figs.push_back(new Poligon<int>("in.txt"));

	for (auto it = figs.begin(); it != figs.end(); it++) {
		sum += (*it)->area();
	}
	figs.clear();

	system("pause");
	return 1;
}
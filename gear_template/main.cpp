#include <iostream>
#include <cmath>
#include <vector>
#include "file.h"
#include "bmp.h"

using namespace std;

//добавить выбор количества секторов?

int main(int argc, const char* argv[]) {
	if (argc == 1) {
		cout << "Reading TEST file..." << endl;
		Gear g("gear_template.txt");
		cout << "Finding slots..." << endl;
		g.find_slot();
		g.show_c(g.r1);
		g.show_c(g.r2);
		cout << "Writing file..." << endl;
		writeBmp(g);
	}
	else {
		cout << "Reading file..." << endl;
		Gear g(argv[1]);
		cout << "Finding slots..." << endl;
		g.find_slot();
		g.make_new(argv[2]);
		cout << "Writing file..." << endl;
		writeBmp(g);
	}
	
	system("pause");
}
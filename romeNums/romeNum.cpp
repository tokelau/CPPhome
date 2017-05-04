#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char romeNums[7] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
int romeNumsInt[7] = { 1, 5, 10, 50, 100, 500, 1000 };

bool codeTo(const char* fileName) {
	ifstream in(fileName);
	if (!in.is_open()) return 0;
	int N = 7, ch = 0;
	in >> ch;
	for (int i = 6; i>-1; i--) {
		if (ch / romeNumsInt[i] == 0) continue;
		while (ch > 3999) {
			cout << 'M';
			ch -= romeNumsInt[6];
		}
		if (romeNumsInt[i + 1] / romeNumsInt[i] == 2 && ch / romeNumsInt[i] == 1) {
			if (ch / (romeNumsInt[i + 1] - romeNumsInt[i - 1]) != 0) {
				cout << romeNums[i - 1] << romeNums[i + 1];
				ch -= (romeNumsInt[i + 1] - romeNumsInt[i - 1]);
			}
		}
		else if (romeNumsInt[i + 1] / romeNumsInt[i] == 5 && ch / romeNumsInt[i] == 4) {

			if (ch / (romeNumsInt[i + 1] - romeNumsInt[i]) != 0) {
				cout << romeNums[i] << romeNums[i + 1];
				ch -= (romeNumsInt[i + 1] - romeNumsInt[i]);
			}
		}
		while (ch / romeNumsInt[i] < 4 && ch / romeNumsInt[i] > 0) {
			cout << romeNums[i];
			ch -= romeNumsInt[i];
		}
		while (ch / romeNumsInt[i - 1] < 4 && ch / romeNumsInt[i - 1] > 0) {
			cout << romeNums[i - 1];
			ch -= romeNumsInt[i - 1];
		}
	}
	return 1;
}

bool codeFrom(const char* fileName) {
	ifstream in("in.txt");
	if (!in.is_open()) return 0;
	int N = 0, k=6;
	string str;
	in >> str;
	for (int i = 0; i < str.length(); i++) {
		while (str[i] != romeNums[k]) {
			k--;
		}
		if (str[i + 1] == romeNums[k + 1] && romeNums[k + 1] != 0) {
			N += romeNumsInt[k + 1] - romeNumsInt[k];
		}
		if (str[i + 1] == romeNums[k + 2] && romeNums[k + 2] !=0) {
			N += romeNumsInt[k + 2] - romeNumsInt[k];
		} 
		if (str[i] == romeNums[k]) {
			N += romeNumsInt[k];
		}
		cout << N;
	}
	return 1;
}

int main(void) {
	char sel;
	cout << "What are you want to do? \n To Rome - q \n From Rome - w"<< endl;
	cin >> sel;
	if (sel == 'q') {
		if (!codeTo("in.txt")) {
			cout << "Sorry, I can't do it" << endl;
		}
	}
	else if (sel == 'w') {
		if (!codeFrom("in.txt")) {
			cout << "Sorry, I can't do it" << endl;
		}
	}
	else {
		cout << "Sorry, I can't understand you"<<endl;
	}
	system("pause");
	return 1;
}

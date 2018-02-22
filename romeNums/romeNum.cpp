#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char romeNums[7] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
int romeNumsInt[7] = { 1, 5, 10, 50, 100, 500, 1000 };

bool codeTo(const char* fileName);
bool codeFrom(const char* fileName);
bool isCorrect(const string str);

bool isCorrect(const string str) {
	int* strInt = new int [str.length()];
	for (int i = 0; i < str.length(); i++) {
		for (int j = 0; j < 7; j++) {
			if (str[i] == romeNums[j]) {
				strInt[i] = romeNumsInt[j];
			}
		}
	}
	for (int i = 0; i < str.length()-1; i++) {
		if (strInt[i + 1] / strInt[i] > 10) {
			return 0;
		}
	}
	int k = 0;
	for (int i = 1; i < str.length(); i++) {
		if (strInt[i] == strInt[i - 1]) {
			k++;
		}
		else {
			k = 0;
		}
	}
	if (k >= 3) {
		return 0;
	}
	return 1;
}

bool codeTo(const char* fileName) {
	ifstream in(fileName);
	if (!in.is_open()) return 0;
	int N = 7, ch=0, i=5;
	int str[3];
	in >> ch;
	while (ch > 999) {
		cout << romeNums[6];
		ch -= romeNumsInt[6];
	}
	str[0] = ch % 10;
	str[1] = ch % 100 - str[0];
	str[2] = ch % 1000 - str[1] - str[0];
	for (int i=2; i>-1; i--){
		if (str[i] == romeNumsInt[i * 2 + 1]) {
			cout << romeNums[i * 2 + 1];
		}
		else if (str[i] == romeNumsInt[i * 2 + 1] - romeNumsInt[i * 2]) {
			cout << romeNums[i * 2] << romeNums[i * 2 + 1];
		}
		else if (str[i] == romeNumsInt[i * 2 + 2] - romeNumsInt[i * 2]) {
			cout << romeNums[i * 2] << romeNums[i * 2 + 2];
		}
		else {
			for (int k = 1; k < 4; k++) {
				if (str[i] == romeNumsInt[i * 2 + 1] + romeNumsInt[i * 2]*k) {
					cout << romeNums[i * 2 + 1];
					for (k; k > 0; k--) {
						cout << romeNums[i * 2];
					}
					break;
				}
				else if (str[i] == romeNumsInt[i * 2] * k){
					for (k; k > 0; k--) {
						cout << romeNums[i * 2];
					}
					break;
				}
			}
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
	if (!isCorrect(str)) return 0;
	for (int i = 0; i < str.length(); i++) {
		while (str[i] != romeNums[k]) {
			k--;
		}
		if (str[i + 1] == romeNums[k + 1] && romeNums[k + 1] != 0) {
			N += romeNumsInt[k + 1] - romeNumsInt[k];
			i++;
		}
		if (str[i + 1] == romeNums[k + 2] && romeNums[k + 2] !=0) {
			N += romeNumsInt[k + 2] - romeNumsInt[k];
			i++;
		} 
		if (str[i] == romeNums[k]) {
			N += romeNumsInt[k];
		}
	}
	cout << N;
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

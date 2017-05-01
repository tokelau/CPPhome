#include <iostream>
#include <fstream>

using namespace std;

char romeNums[7] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
int romeNumsInt[7] = { 1, 5, 10, 50, 100, 500, 1000 };

int main(void) {
	ifstream in("in.txt");
	if (!in.is_open()) return 0;
	int N = 7, ch = 0;
	in >> ch;
	for (int i = 6; i>-1; i--) {
		if (ch / romeNumsInt[i] == 0) continue;
		while (ch > 3999) {
			cout << 'M';
			ch -= romeNumsInt[6];
		}
		if (romeNumsInt[i+1] / romeNumsInt[i] == 2 && ch / romeNumsInt[i] == 1) {
			if (ch / (romeNumsInt[i + 1] - romeNumsInt[i - 1]) != 0) {
				cout << romeNums[i - 1] << romeNums[i + 1];
				ch -= (romeNumsInt[i + 1] - romeNumsInt[i - 1]);
			}
		} else if (romeNumsInt[i+1]/romeNumsInt[i] == 5 && ch / romeNumsInt[i] == 4) {
			
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
	system("pause");
	return 1;
}
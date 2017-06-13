#include <iostream>

using namespace std;

void sort(int* L, int m){
	/*сортировка по возрастанию*/
	int k;
	for (int i = 0; i < m - 1; i++) {
		for (int j = i + 1; j < m; j++) {
			if (L[i] > L[j]) {
				k = L[i];
				L[i] = L[j];
				L[j] = k;
			}
		}
	}
	/*отбрасываем лишние значения*/
	int* result = new int[m];
	for (int i = 0; i < m; i++) {
		result[i] = -1;
	}
	k = 0;
	for (int i = 0; i < m ; i++) {
		if (result[k] != L[i]) {
			result[++k] = L[i];
		}
		else k--;
	} 
	/*выводим результат*/
	if (result[1] == -1) {
		cout << "Arr is empty" << endl;
		return;
	}
	for (int i = 1; i < k + 1; i++) {
		//cout << *result++ << endl;
		while (result[i] != 0) {
			cout << result[i] % 2;
			result[i] >>= 1;
		}
		cout << endl;
	}
}

int main(void) {
	int m, n;
	cout << "Enter m and n: ";
	cin >> m >> n;
	int* values = new int [m];
	int k = 0;
	for (int i = 0; i < m; i++) {
		values[i] = 0;
		cout << "Enter <0> for 0 and <other numbers> for 1: ";
		for (int j = 0; j < n; j++) {
			cin >> k;
			values[i] <<= 1;
			values[i] += k;
 		}
	}
	sort(values, m);
	system("pause");
	return 1;
}
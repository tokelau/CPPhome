#include <iostream>

using namespace std;

int* FIB_function();


/*функция*/
int* FIB_fuction(int n) {
	int* arr = new int[n];
	arr[0] = arr[1] = 1;
	for (int i = 2; i < n; i++) {
		arr[i] = arr[i - 1] + arr[i - 2];
	}
	return arr;
}

int main(void) {
	int n = 0;
	while (n <= 0) {
		cout << "Input array size: ";
		cin >> n;
	}
	int* arr;
	arr = FIB_fuction(n);
	//cout << arr[6]<<endl;
	system("pause");
  return 1;
}

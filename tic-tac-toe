#include<iostream>

using namespace std;

bool check_gamer1(int arr[3][3][3][3], int x, int y) {
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (arr[x][i][y][j] == 1) {
				count++;
			}
		}
	}
	if (count != 3) {
		count = 0;
	}
	else {
		//cout << "Done!";
		return true;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (arr[x][j][y][i] == 1) {
				count++;
			}
		}
	}
	if (count != 3) {
		count = 0;
	}
	else {
		return true;
	}
	for (int i = 0; i < 3; i++) {
		if (arr[x][i][y][2-i] == 1) {
			count++;
		}
	}
	if (count != 3) {
		count = 0;
	}
	else {
		return true;
	}
	for (int i = 0; i < 3; i++) {
		if (arr[x][i][y][i] == 1) {
			count++;
		}
	}
	if(count != 3) {
		return false;
	}
	else {
		return true;
	}
}
bool check_gamer2(int arr[3][3][3][3], int x, int y) {
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (arr[x][i][y][j] == 0) {
				count++;
			}
		}
	}
	if (count != 3) {
		count = 0;
	}
	else {
		return true;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (arr[x][j][y][i] == 0) {
				count++;
			}
		}
	}
	if (count != 3) {
		count = 0;
	}
	else {
		return true;
	}
	for (int i = 0; i < 3; i++) {
		if (arr[x][i][y][2 - i] == 0) {
			count++;
		}
	}
	if (count != 3) {
		count = 0;
	}
	else {
		return true;
	}
	for (int i = 0; i < 3; i++) {
		if (arr[x][i][y][i] == 0) {
			count++;
		}
	}
	if (count != 3) {
		return false;
	}
	else {
		return true;
	}
}

void enter_gamer1(int arr[3][3][3][3], int *x, int *y) {
	for (int i1 = 0; i1 < 3; i1++) {
		for (int i2 = 0; i2 < 3; i2++) {
			cout << " ";
			for (int i3 = 0; i3 < 3; i3++) {
				for (int i4 = 0; i4 < 3; i4++) {
					cout << arr[i1][i2][i3][i4];
				}
				cout << " ";
			}
			cout << "\n";
		}
		cout << "\n";
	}
	int i, j;
	cout << "the coordinates of the square is " << *x << " " << *y << endl;
	do {
		cout << "enter the coordinates of the point: ";
		cin >> i >> j;
		if (!cin)
		{
			cin.clear();
			while (cin.get() != '\n');
		}
	} while (i < -1 || i >2 || j<-1 || j > 2);
	arr[*x][i][*y][j] = 1;
	*x = i;
	*y = j;
}
void enter_gamer2(int arr[3][3][3][3], int *x, int *y) {
	for (int i1 = 0; i1 < 3; i1++) {
		for (int i2 = 0; i2 < 3; i2++) {
			cout << " ";
			for (int i3 = 0; i3 < 3; i3++) {
				for (int i4 = 0; i4 < 3; i4++) {
					cout << arr[i1][i2][i3][i4];
				}
				cout << " ";
			}
			cout << "\n";
		}
		cout << "\n";
	}
	int i = 0, j = 0;
	cout << "the coordinates of the square is " << *x << " " << *y << endl;
	do{
		cout << "enter the coordinates of the point: ";
		cin >> i >> j;
		if (!cin)
		{
			cin.clear();
			while (cin.get() != '\n');
		}
	} while (i < -1 || i >2 || j<-1 || j > 2);
	arr[*x][i][*y][j] = 0;
	*x = i;
	*y = j;
}

int main(void) {
	int arr[3][3][3][3]; 
		for (int i2 = 0; i2 < 3; i2++) {
			for (int i3 = 0; i3 < 3; i3++) {
				for (int i4 = 0; i4 < 3; i4++) {
					arr[i1][i2][i3][i4] = 8;
				}
			}
		}
	}
	int x=0, y = 0;
	bool result = false;
	do {
		enter_gamer1(arr, &x, &y);
		result = check_gamer1(arr, x, y);
		if (result == true) {
			cout << "the first player won!";
			break;
		}
		enter_gamer2(arr, &x, &y);
		result = check_gamer2(arr, x, y);
		if (result == true) {
			cout << "the second player won!";
			break;
		}
	} while (true);
	cout << endl;
	for (int i1 = 0; i1 < 3; i1++) {
		for (int i2 = 0; i2 < 3; i2++) {
			cout << " ";
			for (int i3 = 0; i3 < 3; i3++) {
				for (int i4 = 0; i4 < 3; i4++) {
					cout << arr[i1][i2][i3][i4];
				}
				cout << " ";
			}
			cout << "\n";
		}
		cout << "\n";
	}
	system("pause");
}

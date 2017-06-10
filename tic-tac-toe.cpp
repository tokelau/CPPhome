#include <iostream>

using namespace std;

/*функция проверки хода первого игрока*/
bool check_gamer1(int arr[3][3][3][3], int x, int y) {
	int count = 0; //переменная, которая отвечает за количество крестиков в ряду, если она равна 3, то игрок победил
	/*с помощью четырех циклов проверяем есть ли по горизонтали, вертикали или диагонали три символа подряд
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

/*функция проверки хода второго игрока*/
bool check_gamer2(int arr[3][3][3][3], int x, int y) {
	//логика этой функции аналогчна, только проверяет она нолики
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

/*ход первого игрока*/
void enter_gamer1(int arr[3][3][3][3], int *x, int *y) {
	//выводим тот массив, который имеем на данный момент
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
	//просим ввести координаты квадрата
	cout << "the coordinates of the square is " << *x << " " << *y << endl;
	//просим ввести координаты точки и проверяем ввод на правильность
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

/*ход второго игрока*/
void enter_gamer2(int arr[3][3][3][3], int *x, int *y) {
	//логика функции аналогична, только вводятся другие символы
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
	/*создаем массив 4 на 4, у каждой клетки будет 4 координаты, две отвечают за местоположение квадрата, в котором находится 
	эта клетка, две - за координаты этой клетки внутр квадрата, пустые клетки заполняем символом 8*/
	int arr[3][3][3][3]; 
		for (int i2 = 0; i2 < 3; i2++) {
			for (int i3 = 0; i3 < 3; i3++) {
				for (int i4 = 0; i4 < 3; i4++) {
					arr[i1][i2][i3][i4] = 8;
				}
			}
		}
	} 
	/* логика программы такова: инициализируем начальные позиции, начальный результат (еще никто не победил -> false), далее 
	организуем бесконечный цикл, в котором по очереди ходит первый игрок, проверяется его ход, если он не победил, то ходит 
	второй игрок, проверяется его ход и если он не победил, то все начинается сначала и далее выводится конечный результат*/
	int x = 0, y = 0;
	bool result = false;
	do {
		enter_gamer1(arr, &x, &y); //ход первого игрока
		result = check_gamer1(arr, x, y); //проверка хода первого игрока
		if (result == true) { //выходим из цикла, если первый игрок подебил
			cout << "the first player won!";
			break;
		}
		enter_gamer2(arr, &x, &y); //ход второго игрока
		result = check_gamer2(arr, x, y); //проверка хода второго игрока
		if (result == true) { //выходим из цикла, если первый игрок победил
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

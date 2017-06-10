#include <iostream>
#include <fstream>

using namespace std;
const int COFF = 10000; 

bool checkNumber(ifstream& in, int* wcount, int* bcount); //подсчитывает кол-во фигур белого и черного цвета
int* readCoordinates(ifstream& in, int* number); //считывает координаты и названия точек
bool writeCoordinates(int* number1, int* number2); // записывает ответ
int getVert(int *number); //получает вертикальную координту
int getHoris(int *number); // получает горизонтальную координату
bool checkLines(int* checkFigure, int* checkArr, int* Arr); //ищет фигуру, которой угрожает по вертикали и горизонтали
bool checkDiagonals(int* checkFigure, int* checkArr, int* Arr); //ищет фигуру, которой угрожает по диагоналям
bool checkOneMove(int* checkFigure, int* Arr, char flag); //функция для хода пешки и короля
bool checkNight(int* checkFigure, int* Arr); //фунция для коня

bool checkNumber(ifstream& in, int* wcount, int* bcount) {
	if (!in.is_open()) {
		return 0;
	}
	char ch;
	while(!in.eof()){
		in >> ch; 
		if (ch == ':' && *wcount == -1) {
			in >> ch;
			*wcount = ch - '1' + 1;
		}
		else if (ch == ':' && *bcount == -1) {
			in >> ch;
			*bcount = ch - '1' + 1;
			break;
		}
	}
	in.seekg(0); //возвращаем курсор на первый символ файла
	return 1;
}
int* readCoordinates(ifstream& in, int* number) {
	if (!in.is_open()) {
		return 0;
	}
	int* arr = new int[*number];
	for (int i = 0; i < *number; i++) {
		arr[i] = 0; 
	}
	int n = 0;
	char ch;
	int coff = COFF;
	while (!in.eof()) {
		in >> ch;
		if (ch == ':') {
			in >> ch;
			while(n != *number-1) { 
				in >> ch; //находим начало списка фигур и начинаем запись в массив
				arr[n] += (int)ch * coff; //сначала первый символ (название фигуры)
				coff /= 100;
				in >> ch;
				arr[n] += (int)ch * coff;//второй символ - горизонтальная координата фигуры
				coff /= 100;
				in >> ch;
				arr[n] += (int)ch * coff; //третий - вертикальная координата
				coff = COFF;
				n++;
			}
			/*в итоге получается 6-тизначное (для пешки - 7-мизначное) число, которое сообщает нам 
			тип фигуры и ее координаты*/
			return arr;
		}
	}
}
bool writeCoordinates(int* number1, int* number2) { 
	ofstream out("out.txt", ios_base::in | ios_base::app); //не очень понимаю команды после первой запятой, но с ними файл не обновляет, а дописывает ответы
	if (!out.is_open()) {
		cout << "Can't make output file" << endl;
		return 0;
	}
	/*теперь нам нужно расшифровать фигуры обратно*/
	char ch[3];
	ch[0] = *number1 / COFF;
	ch[1] = (*number1 / 100) % 100;
	ch[2] = *number1 % 100;
	out << ch[0] << ch[1] << ch[2] << "-"<<">";
	ch[0] = *number2 / COFF;
	ch[1] = (*number2 / 100) % 100;
	ch[2] = *number2 % 100;
	out << ch[0] << ch[1] << ch[2] << endl;
	return 1;
}
int getVert(int *number) {
	return *number % 10000 / 100; 
}
int getHoris(int *number) {
	return *number % 100;
}
bool checkLines(int* checkFigure, int* checkArr, int* Arr) {
	/*у ферзя или ладьи есть четыре направления хода, наша задача - рассмотреть каждое, условно делим поле на верхнюю и нижнюю части,
	ниже приведено 4 цикла, первый рассматривает правую верхнюю часть поля для массива, из которого взята сама фигура, здесь
	мы ищем ближайшую по вертикали (Vdistance1) и горизонтали (Hdistance1) фигуру из данного массива и сохранияем расстояние до нее,
	во втором цикле мы делаем все то же самое, но для массива фигур-противников и так сохраняем не только расстояние 
	по горизонтали (Vdistance2)	и вертикали (Hdistance2) для нее, но и координаты рассматриваемой и фигуры-противника,
	в третьем и четвертом цикле делаем аналлогичные операции для левой нижней части поля*/
	int Vdistance1 = 8; 
	int Vdistance2 = 8;
	int Hdistance1 = 8;
	int Hdistance2 = 8;
	int Vfigure1 = 0;
	int Vfigure2 = 0;
	int Hfigure1 = 0;
	int Hfigure2 = 0;
		for (int j = 0; checkArr[j] != 0; j++) {
			if ((getHoris(&checkArr[j]) > getHoris(checkFigure)) && (getHoris(&checkArr[j]) - getHoris(checkFigure) < Vdistance1) && (getVert(&checkArr[j]) == getVert(checkFigure))) {
				Vdistance1 = getHoris(&checkArr[j]) - getHoris(checkFigure);
			}
			if ((getVert(&checkArr[j]) > getVert(checkFigure)) && (getVert(&checkArr[j]) - getVert(checkFigure) < Hdistance1) && (getHoris(&checkArr[j]) == getHoris(checkFigure))) {
				Hdistance1 = getVert(&checkArr[j]) - getVert(checkFigure);
			}
		}
		for (int j = 0; Arr[j] != 0; j++) {
			if ((getHoris(&Arr[j]) > getHoris(checkFigure)) && (getHoris(&Arr[j]) - getHoris(checkFigure) < Vdistance2) && (getVert(&Arr[j]) == getVert(checkFigure))) {
				Vdistance2 = getHoris(&Arr[j]) - getHoris(checkFigure);
				//cout << distance2 << endl;
				Vfigure1 = *checkFigure;
				Vfigure2 = Arr[j];
			}
			if ((getVert(&Arr[j]) > getVert(checkFigure)) && (getVert(&Arr[j]) - getVert(checkFigure) < Hdistance2) && (getHoris(&Arr[j]) == getHoris(checkFigure))) {
				Hdistance2 = getVert(&Arr[j]) - getVert(checkFigure);
				Hfigure1 = *checkFigure;
				Hfigure2 = Arr[j];
			}
		}
	if (Vdistance2 < Vdistance1) { //записываем в файл, если расстояние до противника ближе, чем до своей фигуры
		if (!writeCoordinates(&Vfigure1, &Vfigure2)) {
			return 0;
		}
	}
	if (Hdistance2 < Hdistance1) {
		if (!writeCoordinates(&Hfigure1, &Hfigure2)) {
			return 0;
		}
	}
	Vdistance1 = 8;
	Vdistance2 = 8;
	Hdistance1 = 8;
	Hdistance2 = 8;
		for (int j = 0; checkArr[j] != 0; j++) {
			if ((getHoris(&checkArr[j]) < getHoris(checkFigure)) && (getHoris(checkFigure) - getHoris(&checkArr[j]) < Vdistance1) && (getVert(&checkArr[j]) == getVert(checkFigure))) {
				Vdistance1 = getHoris(checkFigure) - getHoris(&checkArr[j]);
			}
			if ((getVert(&checkArr[j]) < getVert(checkFigure)) && (getVert(checkFigure) - getVert(&checkArr[j]) < Hdistance1) && (getHoris(&checkArr[j]) == getHoris(checkFigure))) {
				Hdistance1 = getVert(&checkArr[j]) - getVert(checkFigure);
			}
		}
		for (int j = 0; Arr[j] != 0; j++) {
			if ((getHoris(&Arr[j]) < getHoris(checkFigure)) && (getHoris(checkFigure) - getHoris(&Arr[j]) < Vdistance1) && (getVert(&Arr[j]) == getVert(checkFigure))) {
				Vdistance2 = getHoris(checkFigure) - getHoris(&Arr[j]);
				Vfigure1 = *checkFigure;
				Vfigure2 = Arr[j];
			}
			if ((getVert(&Arr[j]) < getVert(checkFigure)) && (getVert(checkFigure) - getVert(&Arr[j]) < Hdistance1) && (getHoris(&Arr[j]) == getHoris(checkFigure))) {
				Hdistance2 = getVert(checkFigure) - getVert(&Arr[j]);
				Hfigure1 = *checkFigure;
				Hfigure2 = Arr[j];
			}
		}
	if (Vdistance2 < Vdistance1) {
		if (!writeCoordinates(&Vfigure1, &Vfigure2)) {
			return 0;
		}
	}
	if (Hdistance2 < Hdistance1) {
		if (!writeCoordinates(&Hfigure1, &Hfigure2)) {
			return 0;
		}
	}
	return 1;
}
bool checkDiagonals(int* checkFigure, int* checkArr, int* Arr) {
	/*в этотй функции похожий принцип, но поле делится на правую и левую части*/
	int Tdistance1 = 8;
	int Tdistance2 = 8;
	int Bdistance1 = 8;
	int Bdistance2 = 8;
	int Tfigure1 = 0;
	int Tfigure2 = 0;
	int Bfigure1 = 0;
	int Bfigure2 = 0;
	for (int j = 0; checkArr[j] != 0; j++) {
		if ((getVert(&checkArr[j]) - getVert(checkFigure) == getHoris(&checkArr[j]) - getHoris(checkFigure)) && (getVert(&checkArr[j]) > getVert(checkFigure))) {
			if (getHoris(&checkArr[j]) - getHoris(checkFigure) < Tdistance1) {
				Tdistance1 = getHoris(&checkArr[j]) - getHoris(checkFigure);
			}
		}
		if ((getVert(&checkArr[j]) - getVert(checkFigure) == -1 * (getHoris(&checkArr[j]) - getHoris(checkFigure))) && (getVert(&checkArr[j]) > getVert(checkFigure))) {
			if (getHoris(&checkArr[j]) - getHoris(checkFigure) < Bdistance1) {
				Bdistance1 = getHoris(&checkArr[j]) - getHoris(checkFigure);
			}
		}
	}
	for (int j = 0; Arr[j] != 0; j++) {
		if ((getVert(&Arr[j]) - getVert(checkFigure) == getHoris(&Arr[j]) - getHoris(checkFigure)) && (getVert(&Arr[j]) > getVert(checkFigure))) {
			if (getHoris(&Arr[j]) - getHoris(checkFigure) < Tdistance2) {
				Tdistance2 = getHoris(&Arr[j]) - getHoris(checkFigure);
				Tfigure1 = *checkFigure;
				Tfigure2 = Arr[j];
			}
		}
		if ((getVert(&Arr[j]) - getVert(checkFigure) == -1 * (getHoris(&Arr[j]) - getHoris(checkFigure))) && (getVert(&Arr[j]) > getVert(checkFigure))) {
			if (getHoris(&Arr[j]) - getHoris(checkFigure) < Bdistance2) {
				Bdistance2 = getHoris(&Arr[j]) - getHoris(checkFigure);
				cout << 1 << endl;
				Bfigure1 = *checkFigure;
				Bfigure2 = Arr[j];
			}
		}
	}
	if (Tdistance2 < Tdistance1) {
		if (!writeCoordinates(&Tfigure1, &Tfigure2)) {
			return 0;
		}
	}
	if (Bdistance2 < Bdistance1) {
		if (!writeCoordinates(&Bfigure1, &Bfigure2)) {
			return 0;
		}
	}
	Tdistance1 = 8;
	Tdistance2 = 8;
	Bdistance1 = 8;
	Bdistance2 = 8;
	for (int j = 0; checkArr[j] != 0; j++) {
		if ((getVert(checkFigure) - getVert(&checkArr[j]) == getHoris(checkFigure) - getHoris(&checkArr[j])) && (getVert(&checkArr[j]) < getVert(checkFigure))) {
			if (getHoris(checkFigure) - getHoris(&checkArr[j]) < Tdistance1) {
				Tdistance1 = getHoris(checkFigure) - getHoris(&checkArr[j]);
			}
		}
		if ((getVert(checkFigure) - getVert(&checkArr[j]) == -1 * (getHoris(checkFigure) - getHoris(&checkArr[j]))) && (getVert(&checkArr[j]) < getVert(checkFigure))) {
			if (getHoris(checkFigure) - getHoris(&checkArr[j]) < Bdistance1) {
				Bdistance1 = getHoris(checkFigure) - getHoris(&checkArr[j]);
			}
		}
	}
	for (int j = 0; Arr[j] != 0; j++) {
		if ((getVert(checkFigure) - getVert(&Arr[j]) == getHoris(checkFigure) - getHoris(&Arr[j])) && (getVert(&Arr[j]) < getVert(checkFigure))) {
			if (getHoris(checkFigure) - getHoris(&Arr[j]) < Tdistance2) {
				Tdistance2 = getHoris(checkFigure) - getHoris(&Arr[j]);
				Tfigure1 = *checkFigure;
				Tfigure2 = Arr[j];
			}
		}
		if ((getVert(checkFigure) - getVert(&Arr[j]) == -1 * (getHoris(checkFigure) - getHoris(&Arr[j]))) && (getVert(&Arr[j]) < getVert(checkFigure))) {
			if (getHoris(checkFigure) - getHoris(&Arr[j]) < Bdistance2) {
				Bdistance2 = getHoris(checkFigure) - getHoris(&Arr[j]);
				//cout << 1 << endl;
				Bfigure1 = *checkFigure;
				Bfigure2 = Arr[j];
			}
		}
	}
	if (Tdistance2 < Tdistance1) {
		if (!writeCoordinates(&Tfigure1, &Tfigure2)) {
			return 0;
		}
	}
	if (Bdistance2 < Bdistance1) {
		if (!writeCoordinates(&Bfigure1, &Bfigure2)) {
			return 0;
		}
	}
	//int Vert = *checkFigure % 10000 / 100;
	//int Horis = (*checkFigure % 100);
	//for (int i = 0; i < 8; i++) {
	//	if ((checkArr[i] % 10000 / 100) - Vert == checkArr[i] % 100 - Horis && checkArr[i] % 100 > Horis) {
	//		//cout << 1;
	//		break;
	//	}
	//	else if ((Arr[i] % 10000 / 100) - Vert == Arr[i] % 100 - Horis && Arr[i]%100 > Horis ){
	//		if (!writeCoordinates(checkFigure, &Arr[i])) {
	//			return 0;
	//		}
	//		//cout << 8;
	//	}
	//}
	//for (int i = 8; i > 0; i--) {
	//	if ((Vert - (checkArr[i] % 10000 / 100))  == (checkArr[i] % 100 - Horis) && checkArr[i] % 100 < Horis) {
	//		break;
	//	}
	//	else if (Vert - (Arr[i] % 10000 / 100) == Arr[i] % 100 - Horis && Arr[i] % 100 < Horis) {
	//		if (!writeCoordinates(checkFigure, &Arr[i])) {
	//			return 0;
	//		}
	//	}
	//}
	return 1;
}
bool checkOneMove(int* checkFigure, int* Arr, char flag) {
	//переменная flag нужна для того, чтобы отличать короля от пешки
	for (int j = 0; Arr[j] != 0; j++) {
		//рассматриваем направление по диагонали вверх вправо и влево на одну клетку
		if ((getHoris(checkFigure) + 1 == getHoris(&Arr[j])) && ((getVert(checkFigure) + 1 == getVert(&Arr[j])) || (getVert(checkFigure) - 1 == getVert(&Arr[j])))) {
			if (!writeCoordinates(checkFigure, &Arr[j])) {
				return 0;
			}
		}
		if (flag == 'K') {
			//рассматриваем направление по диагонали вниз вправо и влево на одну клетку
			if ((getHoris(checkFigure) - 1 == getHoris(&Arr[j])) && ((getVert(checkFigure) + 1 == getVert(&Arr[j])) || (getVert(checkFigure) - 1 == getVert(&Arr[j])))) {
				if (!writeCoordinates(checkFigure, &Arr[j])) {
					return 0;
				}
			}
			//рассматриваем направление по горизонтали вправо и влево на одну клетку
			if (getHoris(checkFigure) == getHoris(&Arr[j]) && ((getVert(checkFigure) + 1 == getVert(&Arr[j])) || (getVert(checkFigure) - 1 == getVert(&Arr[j])))) {
				if (!writeCoordinates(checkFigure, &Arr[j])) {
					return 0;
				}
			}
			//рассматриваем направление по вертикали вправо и влево на одну клетку
			if (getVert(checkFigure) == getVert(&Arr[j]) && (getHoris(checkFigure) + 1 == getHoris(&Arr[j]) || getHoris(checkFigure) - 1 == getHoris(&Arr[j]))) {
				if (!writeCoordinates(checkFigure, &Arr[j])) {
					return 0;
				}
			}
		}
	}
	return 1;
}
bool checkNight(int* checkFigure, int* Arr) {
	for (int j = 0; Arr[j] != 0; j++) {
		//рассматриваем ход коня на одну клетку вправо и на две вверх и вниз
		if (getVert(checkFigure) + 1 == getVert(&Arr[j]) && ((getHoris(checkFigure) + 2 == getHoris(&Arr[j])) || (getHoris(checkFigure) - 2 == getHoris(&Arr[j])))) {
			if (!writeCoordinates(checkFigure, &Arr[j])) {
				return 0;
			}
		}
		//рассматриваем ход коня на одну клетку влево и на две вверх и вниз
		if (getVert(checkFigure) - 1 == getVert(&Arr[j]) && ((getHoris(checkFigure) + 2 == getHoris(&Arr[j])) || (getHoris(checkFigure) - 2 == getHoris(&Arr[j])))) {
			if (!writeCoordinates(checkFigure, &Arr[j])) {
				return 0;
			}
		}
		//рассматриваем ход коня на две клетки вправо и на одну вверх и вниз
		if (getVert(checkFigure) + 2 == getVert(&Arr[j]) && ((getHoris(checkFigure) + 1 == getHoris(&Arr[j])) || (getHoris(checkFigure) - 1 == getHoris(&Arr[j])))) {
			if (!writeCoordinates(checkFigure, &Arr[j])) {
				return 0;
			}
		}
		//рассматриваем ход коня на две клетки влево и на одну вверх и вниз
		if (getVert(checkFigure) - 2 == getVert(&Arr[j]) && ((getHoris(checkFigure) + 1 == getHoris(&Arr[j])) || (getHoris(checkFigure) - 1 == getHoris(&Arr[j])))) {
			if (!writeCoordinates(checkFigure, &Arr[j])) {
				return 0;
			}
		} 
	}
	return 1;
}

//	/*проверка, не стоят ли фигуры на одной клетке, я так и не решила, где его оптимальнее всего будет вписать*/
	//	if (getVert(checkFigure) == getVert(&Arr[i]) && getHoris(checkFigure) == getHoris(&Arr[i])) {
	//		cout << "Two figures occupy the same cage!" << endl;
	//		return 0;
	//	}
	//	if (getVert(checkFigure) == getVert(&checkArr[i]) && getHoris(checkFigure) == getHoris(&checkArr[i])) {
	//		cout << "Two figures occupy the same cage!" << endl;
	//		return 0;
	//	}
	//}
bool isThreaten(int* checkArr, int* Arr) {
	int n = 0;
	while (checkArr[n] != 0) { 
		if ((char)(checkArr[n] / COFF) == 'K') {
			if (!checkOneMove(&checkArr[n], Arr, 'K')) {
				return 0;
			}
		}
		if ((char)(checkArr[n] / COFF) == 'Q') {
			if (!checkLines(&checkArr[n], checkArr, Arr) || !checkDiagonals(&checkArr[n], checkArr, Arr)) {
				return 0;
			}
		}
		if ((char)(checkArr[n] / COFF) == 'R') {
			if (!checkLines(&checkArr[n], checkArr, Arr)) {
				return 0;
			}
		}
		if ((char)(checkArr[n] / COFF) == 'N') {
			if (!checkNight(&checkArr[n], Arr)) {
				return 0;
			}
		}
		if ((char)(checkArr[n] / COFF) == 'B') {
			if (!checkDiagonals(&checkArr[n], checkArr, Arr)) {
				return 0;
			}
		}
		if ((char)(checkArr[n] / COFF) == 'p') {
			if (!checkOneMove(&checkArr[n], Arr, 'p')) {
				return 0;
			}
		}
		n++;
	}
	return 1;
}

bool main(void) {
	int wcount = -1, bcount = -1;
	ifstream in("in.txt");
	if (!checkNumber(in, &wcount, &bcount)) {
		cout << "Failed to read input file" << endl;
		return 0;
	}
	int* warr = new int[wcount++]; //размерность массива на 1 больше, чем кол-во фигур,последнему мы позже присвоим 0
	int* barr = new int[bcount++]; // и таким образом будем знать, что дошли о последнего элемента
	/*if (readCoordinates(in, &wcount) == &wcount) { //а из-за этого условия у меня почему-то вылетает вся программа
		cout << "Filed to read possitions"<<endl;
		return 0;
	}*/
	warr = readCoordinates(in, &wcount);
	/*if (readCoordinates(in, &bcount) == &bcount) { 
		cout << "Filed to read possitions" << endl;
		return 0;
	}*/
	barr = readCoordinates(in, &bcount);
	if (!isThreaten(warr, barr)) { 
		cout << "Can't check threat";
		return 0;
	}
	if (!isThreaten(barr, warr)) {
		cout << "Can't check threat";
		return 0;
	}
	cout << "Did it!" << endl;
	system("pause");
}

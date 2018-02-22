#include "file.h"
#include "circuit.h"
#include <iostream>
//#include <fstream>

using namespace std;

int main(int argc, char** argv) {
	if (argc < 3) { //если на вход подано слишком мало аргументов - сообщаем об этом
		cout << "Not enough arguments" << endl;
		return -1;
	}
	File arr; //создаем структуру 
	if (!readFile(argv[1], &arr)) { //выполняем чтение файла
		cout << "I can't read file" << endl;
		return -1;
	}
	findCircuit(&arr, 0, 0); //ищем контуры
	if (!writeFile(argv[2], &arr)) { //записываем выходные данные
		cout << "I can't write file" << endl;
		return -1;
	}
	cout << "Done!" << endl;
	system("pause");
	return 1;
}

#include <iostream>
#include <fstream>
#include <map>
#include "decoder.h"

bool decoder(const char* inFile, const char* outFile) {
	ifstream in(inFile);
	ofstream out(outFile);
	if (!in.is_open() || !out.is_open()) return 0;

	in.seekg(0, ios::end);
	unsigned int size = in.tellg();
	in.seekg(0, ios::beg);

	map<unsigned int, string> m;

	unsigned int count = 0;
	char* block = new char[54];
	/*поскольку кодировщик кодирует символ конца строки своего входного файла, а потом дописыет еще один конец строки,
	  мы идем не до конца файла, а до предпоследнего символа
	*/
	while (count != size-1) {
		/*на всякий случай зануляем массив с данными*/
		for (int i = 0; !in.eof() && i < 54; i++) {
			block[i] = '/0';
		}
		/*считываем данные*/
		for (int i = 0; (count != size - 1) && i < 54; i++) {
			block[i] = in.get();
			count++;
		}
		/*нужно для корректной работы*/
		if (count == size - 1) {
			char ch = in.get();
			block[53] = ch;
		}
		/*вставляем в массив данные по полученному идентификатору*/
		m.insert(getData(block));
		//cout << block << endl;
		//cout << "- " << (int)block[51] << " " <<(int)block[52] <<" "<<(int)block[53]<< endl;
		//cout << "- " << (int)block[51] << " " << (int)block[52] << " " << (int)block[53]<<" : "<<getData(block).first<< " "<< getData(block).second << endl;
	}
	//cout << count << ' ' << size << endl;
	/*поскольку map сам упорядочивает данные, просто выводим его в файл*/
	for (map<unsigned int, string>::iterator it = m.begin(); it != m.end(); it++) {
		//cout << (*it).first << " " << (*it).second << endl;
		out << (*it).second.c_str();
	}

	in.close(); out.close();
	return 1;
}

/*функция отделения данных от идентификатора*/
pair<unsigned int, string> getData(char* block) {
	pair<unsigned int, string> temp;
	/*на всякий случай присваиваем стандартные значения*/
	temp.first = 1;
	temp.second = "1";
	string tempBlock;
	/*это действие нужно для того, чтобы в дальнейшем можно было взять подстроку*/
	tempBlock.assign(block, 54);
	/*если первый бит первого байта меньше единицы*/
	if (block[53] < RANK) {
		temp.second = tempBlock.substr(0, 53); //то записываем 53 байта данных
		temp.first = (int)tempBlock[53]; //и считаем идентификатор
		return temp;
	}
	/*иначе если первый бит второго байта */
	else if (block[52] < RANK) {
		temp.second = tempBlock.substr(0, 52);
		temp.first = RANK + RANK*(int)tempBlock[52] + ((RANK-1) &(int)tempBlock[53]);
		return temp;
	}
	/*иначе остается только третий, преобразуем его*/
	else {
		temp.second = tempBlock.substr(0, 51);
		//cout << (int)tempBlock[51] * RANK*RANK << " + " << ((RANK - 1) & (int)tempBlock[52])*RANK << " + " << ((RANK - 1) & (int)tempBlock[53]) << endl;
		temp.first = RANK*RANK + RANK + (int)tempBlock[51] * RANK*RANK + ((RANK - 1) & (int)tempBlock[52])*RANK + ((RANK - 1) &(int)tempBlock[53]);
		return temp;
	}
}


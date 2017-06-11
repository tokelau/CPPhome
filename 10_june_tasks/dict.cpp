#include <iostream>
#include <fstream>
#include <cstdio>


using namespace std;

/*ищет слова длиннее тех, которые уже в словаре*/
void search(const char* fileName);
/*проверяет слово на уникальность, то есть на наличие одинаковых букв в одном слове*/
unsigned int checkUniq(char* word, unsigned int n, char* &outDict);

unsigned int checkUniq(char* word, unsigned  int n, char* &outDict) {
	static unsigned int count = n; //количество букв в уникальном слове максимальной длины на данный момент
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (word[i] == word[j]) { //если нам попались две одинаковые буквы, то возвращаем старое значение
				return count;
			}
		}
	}
	if (n == count) { //иначе, если данное кникальное слово имеет такую же длину, что и предыдущее
		outDict[n] = '\n'; // то добавляем его в список уникальных слов
		outDict[n +1 ] = '\0';
		strcat_s(outDict, 255, word); //эту функцию посоветвал мне MVS как замену strcat
	}
	else { //если данное слово длиннее предыдущего, обнуляем список и перезаписываем заново
		*outDict = 0;
		strcpy_s(outDict, n + 1, word);
	}
	count = n;
	return n;
}

void search(const char* fileName) {
	ifstream in(fileName); //слова во входном файле должны быть разделены символом конца строки, это важно
	ofstream out("out.txt"); //во входной файл записываются все слова максимальной длины без повторяющихся букв
	if (!in || !out) {
		cout << "Program can't read or wrie file" << endl;
		return;
	}
	char** words = new char* [2]; 
	words[0] = new char; //сюда мы считываем слово из входного файла
	words[1] = new char; //здесь хранится список слов, которые мы хотим увидеть в выходном файле
	unsigned int count = 0;
	do {
		in.getline(words[0], 40, '\n'); //считываем построчно
		if (strlen(words[0]) >= count) { //если длины считанного слова больше или равна максимальной на данный момент
			count =	checkUniq(words[0], strlen(words[0]), words[1]); //то проверяем это слово на уникальность
		}
		
	} while (!in.eof());
	cout << words[1];
	out << words[1];
}

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "Input error, not enough arguments" << endl;
		return -1;
	}
	search(argv[1]);
	system("pause");
	return 1;
}
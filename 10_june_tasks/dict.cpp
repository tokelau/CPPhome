#include <iostream>
#include <fstream>
#include <cstdio>


using namespace std;

/*���� ����� ������� ���, ������� ��� � �������*/
void search(const char* fileName);
/*��������� ����� �� ������������, �� ���� �� ������� ���������� ���� � ����� �����*/
unsigned int checkUniq(char* word, unsigned int n, char* &outDict);

unsigned int checkUniq(char* word, unsigned  int n, char* &outDict) {
	static unsigned int count = n; //���������� ���� � ���������� ����� ������������ ����� �� ������ ������
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (word[i] == word[j]) { //���� ��� �������� ��� ���������� �����, �� ���������� ������ ��������
				return count;
			}
		}
	}
	if (n == count) { //�����, ���� ������ ���������� ����� ����� ����� �� �����, ��� � ����������
		outDict[n] = '\n'; // �� ��������� ��� � ������ ���������� ����
		outDict[n +1 ] = '\0';
		strcat_s(outDict, 255, word); //��� ������� ���������� ��� MVS ��� ������ strcat
	}
	else { //���� ������ ����� ������� �����������, �������� ������ � �������������� ������
		*outDict = 0;
		strcpy_s(outDict, n + 1, word);
	}
	count = n;
	return n;
}

void search(const char* fileName) {
	ifstream in(fileName); //����� �� ������� ����� ������ ���� ��������� �������� ����� ������, ��� �����
	ofstream out("out.txt"); //�� ������� ���� ������������ ��� ����� ������������ ����� ��� ������������� ����
	if (!in || !out) {
		cout << "Program can't read or wrie file" << endl;
		return;
	}
	char** words = new char* [2]; 
	words[0] = new char; //���� �� ��������� ����� �� �������� �����
	words[1] = new char; //����� �������� ������ ����, ������� �� ����� ������� � �������� �����
	unsigned int count = 0;
	do {
		in.getline(words[0], 40, '\n'); //��������� ���������
		if (strlen(words[0]) >= count) { //���� ����� ���������� ����� ������ ��� ����� ������������ �� ������ ������
			count =	checkUniq(words[0], strlen(words[0]), words[1]); //�� ��������� ��� ����� �� ������������
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
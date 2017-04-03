#include "arch.h"

bool archTo(const char* fileName) {
	ifstream in(fileName);
	if (!in.is_open()) {
		return 0;
	}
	register unsigned char wr;
	register int n = 0, num = 0;
	if (!in.is_open()) {
		return 0;
	}
	do {
		wr = in.get();
		write(&wr);
	} while (wr != '\n');
	while (!in.eof()) {
		wr = in.get();
		if (wr == '1' && num < 9) {
			num++;
			n = n++ << 1;
			cout << n << endl;
		} 
		else if (wr == '0' && num < 9){
			num++;
			n = n << 1;
			cout << n << endl;
		}
		if (wr == '\n') {
			wr = (char)n;
			write(&wr);
			wr = '\n';
			write(&wr);
			n = 0;
			num = 0;
		}
		if (num == 8) { 
			wr = (char)n;
			write(&wr);
			n = 0;
			num = 0;
		}
	}
	if (num != 8) { 
		wr = (char)n;
		write(&wr);
		wr = '\n';
		write(&wr);
	}
	return 1;
}

bool archFrom(const char* fileName) {
	ifstream in(fileName);
	if (!in.is_open()) {
		return 0;
	}
	register int n = 0;
	register unsigned char sbl[8];
	register unsigned char c;
	do {
		c = in.get();
		write(&c);
	} while (c != '\n');
	while (!in.eof()) {
		c = in.get();
		if (c != '\n') {
			n = (int)c;
			//cout << n << ' ';
			for (int i = 0; i < 8; i++) {
				if (n % 2 == 1) {
					sbl[i] = '1';
				}
				else {
					sbl[i] = '0';
				}
				n /= 2;
			}
		}
		else if (c == '\n'){
			if (!write(&c)) {
				return 0;
			}
		}
		for (int i = 7; i > -1; i--) {
			//cout << sbl[i];
			if (!write(&sbl[i])) {
				return 0;
			}
		}
	}
	return 1;
}

bool write(const register unsigned char* wr) {
	ofstream out("out.txt", ios_base::in | ios_base::app);
	if (!out.is_open()) {
		return 0;
	}
	out << *wr;
	return 1;
}

#include <iostream>
#include <fstream>
#include <math.h>
#include "file.h"

#pragma comment(linker, "/STACK:50000000")

Gear::Gear(const char* fileName) {
	std::ifstream in(fileName, std::ios::binary);
	/*остановить конструктор*/
	if (!in.is_open()) { std::cout << "Can't open file" << std::endl; }
	char ch = in.get();
	/*параметры*/
	DPI = 0, width = 0, height = 0;
	while (ch != ' ') {
		DPI = (DPI * 10) + ((int)ch - '0');
		ch = in.get();
	}
	ch = in.get();
	while (ch != ' ') {
		width = (width * 10) + ((int)ch - '0');
		ch = in.get();
	}
	ch = in.get();
	while (ch != ' ') {
		height = (height * 10) + ((int)ch - '0');
		ch = in.get();
	}
	while ((int)ch != 10 && !in.fail()) {
		ch = in.get();
	}
	//std::cout << DPI << " " << width << " " << height << " " << (int)ch << std::endl;

	/*запись в массив*/
	arr.resize(height);
	for (int i = 0; i < height; i++) {
		//if (i%100 == 0) std::cout << i << std::endl;
		std::getline(in, arr[i]);
	}
	in.close();

	r1 = width / 2 + 1;
	r2 =  width / 2 + 1;

	center = 0;
	for (int i = width / 2; ; i++) {
		if (arr[height / 2][i] == '0') center++;
		else break;
	}
	center += 10; //чтобы закрасился весь центр
	//std::cout << center << std::endl;
}

void Gear::show_r(double an) {
	double t = (int)an % 90 == 0 ? -1.00 : tan(an * PI / 180);
	if (sin(an) == sin(0.0)) {
		for (int i = 0; i < width; i++) {
			arr[height / 2][i] = arr[height / 2][i] == '0' ? '1' : '0';
		}
		return;
	} 
	if (cos(an) == cos(90.0)) {
		for (int i = 0; i < height; i++) {
			arr[i][width / 2] = arr[i][width / 2] == '0' ? '1':'0';
		}
		return;
	}
	if (sin(an  * PI / 180) > 0.0) {
		for (int i = 0; i < height / 2 + 1; i++) {
			int y = width/2 + (int)i/t; 
			//std::cout << y << std::endl;
			if (y < 0 || y >= width) return;
			if (height / 2 + i < 0 || height / 2 + i >= height) return;
			arr[height / 2 + i][y] = arr[height / 2 + i][y] == '0' ? '1' : '0';
		}
		return;
	}
	if (sin(an  * PI / 180) < 0.0) {
		for (int i = 0; i < height / 2 + 1; i++) {
			int y = width / 2 - (int)i / t;
			//std::cout << y << std::endl;
			if (y < 0 || y >= width) return;
			if (height / 2 - i < 0 || height / 2 - i >= height) return;
			arr[height / 2 - i][y] = arr[height / 2 - i][y] == '0' ? '1' : '0';
		}
		return;
	}
}

void Gear::show_p(int y, int x) {
	//arr[x][y] = arr[x][y] == '0' ? '1' : '0';
	//std::cout << x << " " << y << std::endl;

	/*for (int i = -10; y + i >= 0 && y - i < height - 1 && i < 10; i++) {
		arr[y + i][x - 5] = arr[y + i][x - 5] == '0' ? '1' : '0';
		arr[y + i][x + 5] = arr[y + i][x + 5] == '0' ? '1' : '0';
		arr[y + 5][x + i] = arr[y + 5][x + i] == '0' ? '1' : '0';
		arr[y - 5][x + i] = arr[y - 5][x + i] == '0' ? '1' : '0';
	}*/
	for (int i = 0; i < height; i++) {
		arr[y][i] = arr[y][i] == '0' ? '1' : '0';
		arr[i][x] = arr[i][x] == '0' ? '1' : '0';
	}
}

void Gear::show_c(int r){
	int h = 0;
	for (int w = 0; w < r; w++) {
		if (sin((r - w) / r * PI / 180) == 0.0) {
			arr[height / 2][width / 2 - r] = arr[height / 2][width / 2 - r] == '0' ? '1' : '0';
			arr[height / 2][width / 2 + r] = arr[height / 2][width / 2 + r] == '0' ? '1' : '0';
		}
		if (r - w == 1) {
			arr[height / 2 - r + 1][width / 2] = arr[height / 2 - r + 1][width / 2] == '0' ? '1' : '0';
			arr[height / 2 + r - 1][width / 2] = arr[height / 2 + r - 1][width / 2] == '0' ? '1' : '0';
		}
		int temp = r * sin(acos((double)(r - w) / r));
		//если вдруг для одного значения по горизонтали есть несколько значений по вертикали
		//h = temp после цикла
		for (h; h < (int)temp; h++) { 
			//std::cout << w << ": " << h << ' ' << temp << std::endl;
			arr[height / 2 + h][width / 2 + r - w] = arr[height / 2 + h][width / 2 + r - w] == '0' ? '1' : '0';
			arr[height / 2 - h][width / 2 + r - w] = arr[height / 2 - h][width / 2 + r - w] == '0' ? '1' : '0';
			arr[height / 2 + h][width / 2 - r + w] = arr[height / 2 + h][width / 2 - r + w] == '0' ? '1' : '0';
			arr[height / 2 - h][width / 2 - r + w] = arr[height / 2 - h][width / 2 - r + w] == '0' ? '1' : '0';
		}
		if (h == (int)temp) {
			arr[height / 2 + h][width / 2 + r - w] = arr[height / 2 + h][width / 2 + r - w] == '0' ? '1' : '0';
			arr[height / 2 - h][width / 2 + r - w] = arr[height / 2 - h][width / 2 + r - w] == '0' ? '1' : '0';
			arr[height / 2 + h][width / 2 - r + w] = arr[height / 2 + h][width / 2 - r + w] == '0' ? '1' : '0';
			arr[height / 2 - h][width / 2 - r + w] = arr[height / 2 - h][width / 2 - r + w] == '0' ? '1' : '0';
		}
	}
}

void Gear::find_slot() {
	(*this).fill(0, center + 30, '1');
	/*маленький радиус слота*/
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width / 2; x++) {
			/*справа от центра*/
			if (arr[y][width / 2 + x] == '1' && arr[y][width / 2 + x + 1] == '0') {
				int yy = y < height / 2 ? (height / 2 - y) : (y - height / 2); //относительное значение y
				int xx = x; //относительное значение x
				if (r1 > sqrt(xx*xx + yy*yy)) {
					r1 = sqrt(yy*yy + xx*xx);
				}
			}
			/*слева от центра*/
			if (arr[y][width / 2 - x] == '1' && arr[y][width / 2 - x - 1] == '0') {
				int yy = y < height / 2 ? (height / 2 - y) : (y - height / 2);
				int xx = x;
				if (r1 > sqrt(xx*xx + yy*yy)) {
					r1 = sqrt(xx*xx + yy*yy);
				}
			}
		}
	}
	/*большой радиус слота*/
	int h = 0, w = 0;
	for (int r = r1 + 50; r < width / 2; r++) {
		for (w = 0; w < r; w++) {
			if (sin((r - w) / r * PI / 180) == 0.0) {
				if (arr[height / 2][width / 2 - r] == '0' || arr[height / 2][width / 2 + r] == '0') break;
			}
			if (r - w == 1) {
				if (arr[height / 2 - r + 1][width / 2] == '0' || arr[height / 2 + r - 1][width / 2] == '0') break;
			}
			int temp = r * sin(acos((double)(r - w) / r));
			//если вдруг для одного значения по горизонтали есть несколько значений по вертикали
			//h = temp после цикла
			for (h; h < (int)temp; h++) {
				//std::cout << w << ": " << h << ' ' << temp << std::endl;
				if (arr[height / 2 + h][width / 2 + r - w] == '0') break;
				if (arr[height / 2 - h][width / 2 + r - w] == '0') break;
				if (arr[height / 2 + h][width / 2 - r + w] == '0') break;
				if (arr[height / 2 - h][width / 2 - r + w] == '0') break;
			}
			if (h == (int)temp) {
				if (arr[height / 2 + h][width / 2 + r - w] == '0') break;
				if (arr[height / 2 - h][width / 2 + r - w] == '0') break;
				if (arr[height / 2 + h][width / 2 - r + w] == '0') break;
				if (arr[height / 2 - h][width / 2 - r + w] == '0') break;
			}
		}
		if (w == r) {
			r2 = r;
			break;
		}
	}
	r1 += 10; //эмпирически проверено: если увеличить на 10, то окружность получается точнее
	std::cout << "R1: " << r1 << ", R2: " << r2 << std::endl;
	//show_p((height - 2*r1) / 2, width / 2);
	//if (r1 < width / 2) show_c(r1);
	//if (r2 < width / 2) show_c(r2);
	(*this).fill(0, center + 30, '0');
	(*this).fill(r1 - 30, r2 + 30, '1');
}

void Gear::fill(int dist1, int dist2, char sb) {
	for (int r = dist1; r <= dist2; r++) {
		int h = 0;
		//std::cout << r << std::endl;
		for (int w = 0; w < r; w++) {
			if (sin((r - w) / r * PI / 180) == 0.0) {
				arr[height / 2][width / 2 - r] = sb;
				arr[height / 2][width / 2 + r] = sb;
			}
			if (r - w == 1) {
				arr[height / 2 - r + 1][width / 2] = sb;
				arr[height / 2 + r - 1][width / 2] = sb;
			}
			int temp = r * sin(acos((double)(r - w) / r));
			//если вдруг для одного значения по горизонтали есть несколько значений по вертикали
			//h = temp после цикла
			for (h; h < (int)temp; h++) {
				arr[height / 2 + h][width / 2 + r - w] = sb;
				arr[height / 2 - h][width / 2 + r - w] = sb;
				arr[height / 2 + h][width / 2 - r + w] = sb;
				arr[height / 2 - h][width / 2 - r + w] = sb;
			}
			if (h == (int)temp) {
				arr[height / 2 + h][width / 2 + r - w] = sb;
				arr[height / 2 - h][width / 2 + r - w] = sb;
				arr[height / 2 + h][width / 2 - r + w] = sb;
				arr[height / 2 - h][width / 2 - r + w] = sb;
			}
		}
	}
}

void Gear::make_new(const char* fileName) {
	std::ifstream in(fileName);
	if (!in.is_open()) {
		std::cout << "!!! Can't open file with sequence" << std::endl;
		return;
	}
	if (r1 == width / 2 + 1 || r2 == width / 2 + 1) {
		std::cout << "!!! Don't have R1 or R2" << std::endl;
		return;
	}
	int count, ch = 0;
	in >> count;
	while (ch <= 0 || ch > 82) {
		std::cout << "Choose the number of sequence (1, " << count << ")" << std::endl;
		std:: cin >> ch;
	}
	int i = (ch - 1) * 29 + 4;
	std::string seq;
	in.seekg(i, std::ios::beg);
	std::getline(in, seq);
	/*записываем по секторам*/
	for (int j = 0; j < seq.length(); j++) {
		//std::cout << seq[j];
		if (seq[j] == '1') {
			(*this).fill_slot((double)360 / 28 * j, (double)360 / 28 * (j + 1));
		}
		//std::cout << seq.length() << std::endl;
		//show_r((double)360 / 28 * j);
	}
	in.close();
	return;
}

/*пока ограничение на задаваемые углы: от 0 до 360*/
void Gear::fill_slot(double an1, double an2) {
	int a1 = an1, a2 = an2;
	for (int r = r1; r <= r2; r++) {
		an1 = a1, an2 = a2;
		/*рисуем слоты справа сверху*/
		if (an1 >= 0.0 && an1 <= 90.0) {
			int w = an2 >= 90.0 ? 0 : r*cos(an2 * PI / 180);
			int h = r * sin(acos((double)w / r));
			for (w; w <= r*cos(an1 * PI / 180); w++) {
				if (w == 1) {
					arr[height / 2 + r - 1][width / 2] = '0';
				}
				int temp = r * sin(acos((double)w / r));
				//std::cout << h << " " << temp << std::endl;
				//если вдруг для одного значения по горизонтали есть несколько значений по вертикали
				//h = temp после цикла
				for (h; h > (int)temp; h--) {
					arr[height / 2 + h][width / 2 + w] = '0';
				}
				if (h == (int)temp) {
					arr[height / 2 + h][width / 2 + w] = '0';
				}
			}
		}
		/*рисуем слоты слева сверху*/
		if (an2 > 90.0 && an1 <= 90.0) an1 = 90.0;
		if (an1 >= 90.0 && an1 <= 180.0) {
			int w = r*-cos(an1 * PI / 180);
			int h = r * sin(acos((double)w / r));
			for (w; w <= (an2 >= 180 ? r : (double)r*-cos(an2 * PI / 180)); w++) {
				if (r - w == 1) {
					arr[height / 2 + r - 1][width / 2] = '0';
				}
				int temp = r * sin(acos((double)w / r));
				//std::cout << w << " " << (an2 >= 180 ? r : (double)r*-cos(an2 * PI / 180)) << std::endl;
				//если вдруг для одного значения по горизонтали есть несколько значений по вертикали
				//h = temp после цикла
				for (h; h > (int)temp; h--) {
					arr[height / 2 + h][width / 2 - w] = '0';
				}
				if (h == (int)temp) {
					arr[height / 2 + h][width / 2 - w] = '0';
				}
			}
		}
		/*рисуем слоты слева снизу*/
		if (an2 > 180.0 && an1 <= 180.0) an1 = 180.0;
		if (an1 >= 180.0 && an1 <= 270.0) {
			int w = (an2 >= 270 ? 0 : (double)r*-cos(an2 * PI / 180));
			int h = r * sin(acos((double)w / r));
			for (w; w <= -1 * (r*cos(an1 * PI / 180)); w++) {
				if (r - w == 1) {
					arr[height / 2 - r + 1][width / 2] = '0';
				}
				int temp = r * sin(acos((double)w / r));
				//std::cout << w << " " << (double)(r*cos(an1 * PI / 180)) << std::endl;
				//если вдруг для одного значения по горизонтали есть несколько значений по вертикали
				//h = temp после цикла
				for (h; h > (int)temp; h--) {
					arr[height / 2 - h][width / 2 - w] = '0';
				}
				if (h == (int)temp) {
					arr[height / 2 - h][width / 2 - w] = '0';
				}
			}
		}
		/*рисуем слоты справа снизу*/
		if (an2 > 270.0 && an1 <= 270.0) an1 = 270.0;
		if (an1 >= 270.0 && an1 <= 360.0) {
			int w = r*cos(an1 * PI / 180);
			int h = r * sin(acos((double)w / r));
			for (w; w <= r*cos(an2 * PI / 180); w++) {
				if (w == 0) {
					arr[height / 2 - r + 1][width / 2] = '0';
				}
				int temp = r * sin(acos((double)w / r));
				//std::cout << w << " " << (double)(r*cos(an1 * PI / 180)) << std::endl;
				//если вдруг для одного значения по горизонтали есть несколько значений по вертикали
				//h = temp после цикла
				for (h; h > (int)temp; h--) {
					arr[height / 2 - h][width / 2 + w] = '0';
				}
				if (h == (int)temp) {
					arr[height / 2 - h][width / 2 + w] = '0';
				}
			}
		}
	}
}


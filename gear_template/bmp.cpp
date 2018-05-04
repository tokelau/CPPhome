#include <iostream>
#include <fstream>    //подключили библиотеку для работы с map
#include "conio.h"
#include "bmp.h"

using namespace std;

//------------------- write ---------------------------------//
void writeBmp(Gear &g){
	std::ofstream os("temp.bmp", std::ios::binary);

	BmpHeader bmp;

	os.write(reinterpret_cast<char*>(bmp.signature), sizeof(bmp.signature));
	os.write(reinterpret_cast<char*>(&bmp.fileSize), sizeof(bmp.fileSize));
	os.write(reinterpret_cast<char*>(&bmp.reserved), sizeof(bmp.reserved));
	os.write(reinterpret_cast<char*>(&bmp.offset),   sizeof(bmp.offset));

	os.write(reinterpret_cast<char*>(&bmp.headerSize),  sizeof(bmp.headerSize));
	os.write(reinterpret_cast<char*>(bmp.dimensions),   sizeof(bmp.dimensions));
	os.write(reinterpret_cast<char*>(&bmp.colorPlanes), sizeof(bmp.colorPlanes));
	os.write(reinterpret_cast<char*>(&bmp.bpp),         sizeof(bmp.bpp));
	os.write(reinterpret_cast<char*>(&bmp.compression), sizeof(bmp.compression));
	os.write(reinterpret_cast<char*>(&bmp.imgSize),     sizeof(bmp.imgSize));
	os.write(reinterpret_cast<char*>(bmp.resolution),   sizeof(bmp.resolution));
	os.write(reinterpret_cast<char*>(&bmp.pltColors),   sizeof(bmp.pltColors));
	os.write(reinterpret_cast<char*>(&bmp.impColors),   sizeof(bmp.impColors));

	unsigned char x,r;

	for (int i=0; i < g.height; ++i)
	{
		//if (i % 100 == 0) cout << i << endl;
		for (int j=0; j < g.width; ++j)
		{
			x = 0;
			r = g.arr[i][j] == '1' ? 0 : 255;
			os.write(reinterpret_cast<char*>(&r),sizeof(r));
			os.write(reinterpret_cast<char*>(&r),sizeof(r));
			os.write(reinterpret_cast<char*>(&r),sizeof(r));
			os.write(reinterpret_cast<char*>(&x),sizeof(x));  
		}
	}

	os.close();
}
//-----------------------------------------------------------//


//void main(void){
//	std::ifstream os("temp.bmp", std::ios::binary);
//
//	unsigned char signature[2] = { 'B', 'M' };
//	unsigned int fileSize = 14 + 40 + 100*100*4;
//	unsigned int reserved = 0;
//	unsigned int offset = 14 + 40;
//
//	unsigned int headerSize = 40;
//	unsigned int dimensions[2] = { 100, 100 };
//	unsigned short colorPlanes = 1;
//	unsigned short bpp = 32;
//	unsigned int compression = 0;
//	unsigned int imgSize = 100*100*4;
//	unsigned int resolution[2] = { 2795, 2795 };
//	unsigned int pltColors = 0;
//	unsigned int impColors = 0;
//
//	os.read(reinterpret_cast<char*>(signature), sizeof(signature));	cout<<"signature="<<signature<<endl;
//	os.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));  cout<<"fileSize="<<fileSize<<endl;
//	os.read(reinterpret_cast<char*>(&reserved), sizeof(reserved));  cout<<"reserved="<<reserved<<endl;
//	os.read(reinterpret_cast<char*>(&offset),   sizeof(offset));
//
//	os.read(reinterpret_cast<char*>(&headerSize),  sizeof(headerSize)); cout<<"headerSize="<<headerSize<<endl;
//	os.read(reinterpret_cast<char*>(dimensions),   sizeof(dimensions)); cout<<"dimensions="<<dimensions[0]<<" "<<dimensions[1]<<endl;
//	os.read(reinterpret_cast<char*>(&colorPlanes), sizeof(colorPlanes));cout<<"colorPlanes="<<colorPlanes<<endl;
//	os.read(reinterpret_cast<char*>(&bpp),         sizeof(bpp));        cout<<"bpp="<<bpp<<endl;
//	os.read(reinterpret_cast<char*>(&compression), sizeof(compression));cout<<"compression="<<compression<<endl;
//	os.read(reinterpret_cast<char*>(&imgSize),     sizeof(imgSize));	cout<<"imgSize="<<imgSize<<endl;
//	os.read(reinterpret_cast<char*>(resolution),   sizeof(resolution)); cout<<"resolution="<<resolution[0]<<" "<<resolution[1]<<endl;
//	os.read(reinterpret_cast<char*>(&pltColors),   sizeof(pltColors));  cout<<"pltColors="<<pltColors<<endl;
//	os.read(reinterpret_cast<char*>(&impColors),   sizeof(impColors));  cout<<"impColors="<<impColors<<endl;
//
//	getch();
//}
#ifndef  BMP_H
#define BMP_H

#include "file.h"

struct BmpHeader {
	unsigned char signature[2];
	unsigned int fileSize;
	unsigned int reserved;
	unsigned int offset;

	unsigned int headerSize;
	unsigned int dimensions[2];
	unsigned short colorPlanes;
	unsigned short bpp;
	unsigned int compression;
	unsigned int imgSize;
	unsigned int resolution[2];
	unsigned int pltColors;
	unsigned int impColors;

	BmpHeader() {
		signature[0] = 'B', signature[1] = 'M';
		fileSize = 14 + 40 + 100 * 100 * 4;
		reserved = 0;
		offset = 14 + 40;

		headerSize = 40;
		dimensions[0] = 5570, dimensions[1] = 5570;
		colorPlanes = 1;
		bpp = 32;
		compression = 0;
		imgSize = 100 * 100 * 4;
		resolution[0] = 100, resolution[1] = 100;
		pltColors = 0;
		impColors = 0;
	};
};

void writeBmp(Gear &g);


#endif

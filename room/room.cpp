#include <iostream>
#include "room.h"

using namespace std;

Room::Room(){}

Room::Room(int nw, float w, float l, float h){
	n=nw;
	width = w;
	length = l;
	heigh = h;
	mywind = new Window[n];
	InitWidow(n);
}

Room::~Room() {
	delete[] mywind;
}

float Room::CalcRoom(){
	float sumSqr = 0.0;
	for(int i = 0; i < n; i++){
		if (mywind[i].CalcSqr() < 0) {
			throw sumSqr;
		}
		sumSqr += mywind[i].CalcSqr();
	}
	if (heigh < 0 || width < 0 || length < 0) {
		throw sumSqr;
		//return sumSqr;
	}
	sumSqr += 2*heigh*(width + length);
	return sumSqr;
}

void Room::InitWidow(int nw){
	for(int i = 0; i < nw; i++){
		cout<<"Input size (heigh and width) of window"<<endl;
		cin>>mywind[i].heigh>>mywind[i].width;
	}
}

float Window::CalcSqr(){
	return width*heigh;
}

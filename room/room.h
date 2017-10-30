#ifndef ROOM_H
#define ROOM_H

#include <iostream>

class Window{
	public:
		float heigh, width;
		float CalcSqr();
};

class Room{
public:
	Room();
	Room(int n, float w, float l, float h);
	int n;
	Window* mywind;
	float width, length, heigh;
	float CalcRoom();
	  
private:
	void InitWidow(int nw);
};

#endif
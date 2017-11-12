#ifndef FIELD_H
#define FIELD_H

class Field{
public:
	int field[6][6];
	Field();
	void field_out();
	Field& operator = (const Field& f);
	//Field(char* arr);

};

#endif 
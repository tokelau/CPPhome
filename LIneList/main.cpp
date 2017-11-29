#include <iostream>
#include "LineList.h"

using namespace std;

int main(void) {
	LineList<int> list;

	cout << "Start: " << list << endl;
	cout << endl;

	list.insertFirst(10);
	cout << "insertFirst(10):" << '\n' << list << endl;
	LineListElem<int>* ptr = list.getStart();
	list.insertAfter(ptr, 15);
	cout << "insertAfter(ptr, 15):" << '\n' << list << endl;
	list.insertAfter(ptr, 12);
	list.insertAfter(ptr, 12);
	cout << "insertAfter(ptr, 12)x2:" << '\n' << list << endl;
	list.insertFirst(7);
	list.insertFirst(7);
	cout << "insertFirst(7)x2:" << '\n' << list << endl;
	cout << endl;

	list.deleteFirst();
	cout << "deleteFirst():" << '\n' << list << endl;
	LineListElem<int>* index = list.getIndexPtr(1);
	list.deleteAfter(index);
	cout << "deleteAfter(1):" << '\n' << list << endl;
	list.deleteFirstIn(7);
	cout << "deleteFirstIn(7):" << '\n' << list << endl;
	cout << endl;

	cout << "search(2):" << '\n' << list.search(2) << endl;
	cout << "searchIndex(2, 15):" << '\n' << list.searchIndex(2, 15) << endl;
	cout << endl;

	cout << "getSize():" << '\n' << list.getSize() << endl;

	system("pause");
	return 1;
}
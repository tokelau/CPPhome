#ifndef LL_H
#define LL_H

#include "LineListElement.h"
#include "Exceptions.h"

using namespace std;

template <class T> class LineList {
	LineListElem<T>* start; //<T> - ?
	unsigned long size;
	LineList(const LineList& list);
	LineList<T>& operator =(const LineList<T>& list);
public:
	LineList();
	~LineList();
	LineListElem<T>* getStart();
	LineListElem<T>* getIndexPtr(const T index);
	T search(const T index);
	unsigned long searchIndex(const T start, const T data);
	unsigned long getSize();
	void deleteFirst(); //удаляет первый элемент
	void deleteFirstIn(const T data); //удаляет первое вхождение
	void deleteAfter(LineListElem<T>* ptr); 
	void insertFirst(const T& data);
	void insertAfter(LineListElem<T>* ptr, const T& data);
	template <class T> friend ostream& operator <<(ostream& out, LineList& list);
};

template <class T>
LineList<T>::LineList() {
	start = 0;
	size = 0;
}
template <class T>
LineList<T>::~LineList() {
	while (start) {
		deleteFirst();
	}
}

template <class T>
LineListElem<T>* LineList<T>::getStart() {
	return start;
}

template <class T>
unsigned long LineList<T>::getSize() {
	return size;
}

template <class T>
LineListElem<T>* LineList<T>::getIndexPtr(const T index) {
	if (start) {
		int i = 0;
		LineListElem<int>* it = start;
		for (; it && i < index; i++) {
			it = it->getNext();
		}
		return it;
	}
	else throw LineListException();
}

/*возвращает data, индекс которой равен index*/
template <class T>
T LineList<T>::search(const T index) {
	LineListElem<T>* it = getIndexPtr(index);
	return it->getData();
}

/******************************************************
*  возвращает порядковый номер элемента, равного data *
*  поиск начинается с list[start]                     *
*******************************************************/
template <class T>
unsigned long LineList<T>::searchIndex(const T start, const T data) {
	LineListElem<T>* it = getIndexPtr(start);
	unsigned long i = start;
	for (; it && it->getData() != data; it->getNext()) {
		i++;
	}
	if (it->getData() == data) {
		return i;
	}
}

template <class T>
void LineList<T>::deleteFirst() {
	if (start) {
		LineListElem<T>* temp = start->next;
		delete start;
		start = temp;
		size--;
	}
	else throw LineListException();
}

template <class T>
void LineList<T>::deleteFirstIn(const T data) { 
	LineListElem<T>* it = start;
	if (it->getData() == data) {
		deleteFirst();
		return;
	}
	else {
		it = it->getNext();
	}
	int i = 0;
	while (it && it->getData() != data && it->getNext()) {
		i++;
		it = it->getNext();
	}
	if (it->getData() == data) {
		it = getIndexPtr(i);
		deleteAfter(it);
	}
}

template <class T>
void LineList<T>::insertFirst(const T& data) {
	LineListElem<T>* second = start;
	start = new LineListElem<T>(data, second);
	size += 1;
}

template <class T>
void LineList<T>::deleteAfter(LineListElem<T>* ptr) {
	if (ptr && ptr->next) {
		LineListElem<T>* temp = ptr->next;
		try {
			ptr->next = ptr->next->next; //какую проверку поставить?
		}
		catch (...){
			ptr->next = 0;
		}
		delete temp;
		size -= 1;
	}
	else throw LineListException();
}

template <class T>
void LineList<T>::insertAfter(LineListElem<T>* ptr, const T& data) {
	if (ptr) {
		LineListElem<T>* temp = ptr->next;
		ptr->next = new LineListElem<T>(data, temp);
		size += 1;
	}
}

template <class T>
ostream& operator<<(ostream& out, LineList<T>& list) {
	LineListElem<T>* ptr = list.getStart();
	if (!ptr) out << "EMPTY ";
	else while (ptr) {
		out << ptr->getData() << ' ';
		ptr = ptr->getNext();
	}
	return out;
}

template <class T>
LineList<T>& LineList<T>::operator =(const LineList<T>& list) {
	start = list.getStart();
	return *this;
}

#endif

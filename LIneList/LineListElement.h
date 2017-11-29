#ifndef LLE_H
#define LLE_H

//using namespace std;
template <class T> class LineListElem {
	T data;
	LineListElem* next;
public:
	LineListElem(const T& adata, LineListElem* anext);
	const T& getData() const;
	LineListElem* getNext();
	template <class T> friend class LineList;
};

template <class T> 
LineListElem<T>::LineListElem(const T& adata, LineListElem* anext) {
	data = adata;
	next = anext;
}

template <class T>
const T& LineListElem<T>::getData() const {
	return data;
}

template <class T>
LineListElem<T>* LineListElem<T>::getNext() {
	return next;
}

#endif
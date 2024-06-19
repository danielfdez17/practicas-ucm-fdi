/**
 * Conjuntos gen�ricos representados por un array din�mico ordenado y sin repeticiones
 * (c) Miguel G�mez Zamalloa
 * Modificado por Ignacio F�bregas, 2022
 */

#ifndef Set_H_
#define Set_H_

#include <iostream>
#include "Error.h"
using namespace std;


template<class T>
class Set {
private:
	static const int DEFAULT_CAPACITY = 50;

	T* elems;
	int size;
	int capacity;

	bool isFull() const;
	void binSearch(const T& x, bool& found, int& pos) const;
	int binSearchAux(const T& x, int a, int b) const;
	void shiftRightFrom(int i);
	void shiftLeftFrom(int i);
	void reallocate();

public:
	Set(int initCapacity = DEFAULT_CAPACITY);
	Set(const Set<T>& set);
	~Set();
	bool isEmpty() const;
	void add(const T& x);
	bool contains(const T& x) const;
	void remove(const T& x);
	T& getMax() const;
	void removeMax();
	T& getMin() const;
	void removeMin();
	void erase();
	void write(ostream& sOut);
	void read(istream& sIn);
	// Modificaciones
	void diff(const Set<T>& set);
};


// Constructors

template<class T>
Set<T>::Set(int initCapacity) {
	size = 0;
	capacity = initCapacity;
	elems = new T[capacity];
}

template<class T>
Set<T>::Set(const Set<T>& set) {
	size = set.size;
	capacity = set.capacity;
	elems = new T[capacity];
	for (int i = 0; i < size; i++)
		elems[i] = set.elems[i];
}

template<class T>
Set<T>::~Set() {
	delete[] elems;
	elems = NULL;
}

// Public methods

template<class T>
bool Set<T>::isEmpty() const {
	return (size == 0);
}

template<class T>
void Set<T>::add(const T& x) {
	bool found;
	int pos;

	binSearch(x, found, pos);
	if (!found) {
		shiftRightFrom(pos + 1);
		elems[pos + 1] = x;
		size++;
		if (isFull()) reallocate();
	}
}

template<class T>
void Set<T>::remove(const T& x) {
	bool found;
	int pos;

	binSearch(x, found, pos);
	if (found) {
		shiftLeftFrom(pos);
		size--;
	}
}

template<class T>
bool Set<T>::contains(const T& x) const {
	bool found;
	int pos;

	binSearch(x, found, pos);
	return found;
}

template<class T>
void Set<T>::erase() {
	size = 0;
}

template<class T>
T& Set<T>::getMax() const {
	if (isEmpty()) throw Error("Cannot get the max/min: The set is empty");
	else return elems[size - 1];
}

template<class T>
void Set<T>::removeMax() {
	if (!isEmpty())
		size--;
}

template<class T>
T& Set<T>::getMin() const {
	if (isEmpty()) throw Error("Cannot get the max/min: The set is empty");
	else return elems[0];
}

template<class T>
void Set<T>::removeMin() {
	if (!isEmpty()) {
		shiftLeftFrom(0);
		size--;
	}
}

template<class T>
void Set<T>::write(ostream& sOut) {
	//sOut << "{";
	for (int i = 0; i < size - 1; i++)
		sOut << elems[i] << " ";
	if (size > 0) sOut << elems[size - 1];

	/*for (int i = size-1; i > 0; i--)
			sOut << elems[i] << " ";
	if (size > 0) sOut << elems[0];*/
	sOut << endl;
}

template<class T>
void Set<T>::read(istream& sIn) {
	int n;
	T d;
	sIn >> n;
	if (!sIn) return;
	size = 0;
	for (int i = 0; i < n; i++) {
		sIn >> d;
		add(d);
	}
}

// n = numero de elementos de set
// m = numero de elementos de this
// pos = posicion en la que se encuentra el elemento de this (que es igual al de set)
// Coste: en el peor caso es n (log(m) + m - pos), lo que indica que ambos conjuntos tengan los mismo elementos
template<class T>
void Set<T>::diff(const Set<T>& set) {
	// No entra si uno de los dos conjuntos es vacio y si el maximo de this es menor que el minimo de set
	if (!isEmpty() && !set.isEmpty() && getMax() >= set.getMin()) {
		int i = 0; bool exit = false;
		// Se busca que this este vacio o que el elemento de la posicion i de set sea mayor que el maximo de this
		while (i < set.size && !exit) {
			T e = set.elems[i];
			if (e <= getMax()) {
				bool found; int pos;
				binSearch(e, found, pos);
				if (found) {
					shiftLeftFrom(pos);
					size--;
				}
			}
			exit = (isEmpty() || e > getMax());
			i++;
		}
	}
}

template<class T>
istream& operator>>(istream& sIn, Set<T>& set) {
	set.read(sIn);
	return sIn;
}

template<class T>
ostream& operator<<(ostream& sOut, Set<T>& set) {
	set.write(sOut);
	return sOut;
}


// Private methods

template<class T>
bool Set<T>::isFull() const {
	return size == capacity;
}

template<class T>
int Set<T>::binSearchAux(const T& x, int a, int b) const {
	// Pre: elems est� ordenado entre 0 .. size-1
	//      ( 0 <= a <= size ) && ( -1 <= b <= size ) && ( a <= b+1 )
	//      todos los elementos a la izquierda de 'a' son <= x
	//      todos los elementos a la derecha de 'b' son > x

	int p, m;

	if (a == b + 1)
		p = a - 1;
	else if (a <= b) {
		m = (a + b) / 2;
		if (elems[m] <= x)
			p = binSearchAux(x, m + 1, b);
		else
			p = binSearchAux(x, a, m - 1);
	}
	return p;
	// Post: devuelve el mayor �ndice i (0 <= i <= size-1) que cumple
	//       elems[i] <= x
	//       si x es menor que todos los elementos de elems, devuelve -1
}

template<class T>
void Set<T>::binSearch(const T& x, bool& found, int& pos) const {
	// Pre: los size primeros elementos de elems est�n ordenados
	//      size >= 0

	pos = binSearchAux(x, 0, size - 1);
	found = (pos >= 0) && (pos < size) && (elems[pos] == x);

	// Post : devuelve el mayor �ndice i (0 <= i <= size-1) que cumple
	//        elems[i] <= x
	//        si x es menor que todos los elementos de elems, devuelve -1
	//        found es true si x esta en elems[0..size-1]
}

template<class T>
void Set<T>::shiftRightFrom(int i) {
	for (int j = size; j > i; j--)
		elems[j] = elems[j - 1];
}

template<class T>
void Set<T>::shiftLeftFrom(int i) {
	for (; i < size - 1; i++)
		elems[i] = elems[i + 1];
}

template<class T>
void Set<T>::reallocate() {
	capacity = capacity * 2;
	T* newElems = new T[capacity];
	for (int i = 0; i < size; i++)
		newElems[i] = elems[i];
	delete[] elems;
	elems = newElems;
}

#endif /* Set_H_ */

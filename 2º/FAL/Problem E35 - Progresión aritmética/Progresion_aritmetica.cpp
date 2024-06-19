#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
RECURRENCIA: Sea n el numero de elementos del vector
	T(n) = c si n = 1
	T(n) = T(n/2) + c si n > 1
	T(n) pertenece a O(log(n)) porque se hacen log(n) llamadas recursivas al ser una variacion del algoritmo de busqueda binaria
*/

// Intervalo cerrado [c,f]. Llamada inicial con c = 0 y f = size - 1
void progresion(vector<int>const& v, int size, int d, int c, int f, int& solucion) {
	// CB: 1 elemento
	if (c == f - 1) {
		if (c == 0) {
			solucion = v[c] + d;
		}
		else if (c == size - 1) {
			if (v[c] - d == v[c - 1]) {
				solucion = v[c] + d;
			}
			else {
				solucion = v[c] - d;
			}
		}
		else {
			if (v[c] + d == v[f]) {
				solucion = v[c] - d;
			}
			else if (v[c] - d == v[c - 1]) {
				solucion = v[c] + d;
			}
		}
	}
	// CR
	else {
		int m = (c + f) / 2;
		if (v[m] - v[c] != (m - c) * d) {
			progresion(v, size, d, c, m, solucion);
		}
		else {
			progresion(v, size, d, m, f, solucion);
		}
	}
}


void resuelveCaso() {
	int size, d, n;
	cin >> size >> d;
	vector<int> v(size);
	for (int& i : v) cin >> i;
	int solucion;
	progresion(v, size, d, 0, size, solucion);
	cout << solucion << "\n";
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("in.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i) resuelveCaso();


	// Para restablecer entrada. Comentar para acepta el reto

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
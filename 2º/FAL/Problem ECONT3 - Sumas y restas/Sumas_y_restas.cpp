#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// IMPLEMENTACION DEL ALGORITMO DE VUELTA ATRAS
// Explicaciones detalladas sobre la implementacion
// Indicacion de los marcadores utilizados

// PODA UTILIZADA
// Llevo en un vector la suma de los que me quedan por sumar o restar

void sumas_restas(vector<int>const& v, int size, int suma, int m, int k, bool& encontrado, vector<int>const& acumulados) {
	if (encontrado) return;
	if (k == size - 1) {
		encontrado = suma == m;
	}
	else {
		// if (suma + acumulados[k + 1] < m) no se hace la llamada recursiva
		if (suma + acumulados[k + 1] >= m) {
			// SUMAR
			suma += v[k + 1];
			sumas_restas(v, size, suma, m, k + 1, encontrado, acumulados);
			suma -= v[k + 1];
		}
		// if (suma - acumulados[k + 1] > m) no se hace la llamada recursiva
		if (suma - acumulados[k + 1] <= m) {
			// RESTAR
			suma -= v[k + 1];
			sumas_restas(v, size, suma, m, k + 1, encontrado, acumulados);
			suma += v[k + 1];
		}
	}
}

void resuelveCaso() {
	int numElems = 0; int m;
	cin >> m >> numElems;
	vector<int> v(numElems), acumulados(numElems, 0);
	for (int& i : v) {
		cin >> i;
	}
	bool b = false;
	//LLAMAR AQUI AL ALGORITMO DE VUELTA ATRAS
	if (numElems != 0) {
		acumulados[numElems - 1] = v[numElems - 1];
		for (int i = numElems - 2; i >= 0; i--) {
			acumulados[i] = acumulados[i + 1] + v[i];
		}
		sumas_restas(v, numElems, v[0], m, 0, b, acumulados);
	}
	else b = true;
	cout << (b ? "SI\n" : "NO\n");
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



#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}
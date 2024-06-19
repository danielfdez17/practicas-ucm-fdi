#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
ESPECIFICACIÓN: fun resolver(in vector<int>const&v, in int size) ret tsol
PRECONDICION: {
    0 <= size <= 10.000
    &&
    forall i : 0 <= i < size : -50 <= v[i] && v[i] <= 60
}
POSTCONDICION: {
    picos = #(forall u : 1 < u < size - 1 : v[u - 1] < v[u] && v[u] > v[u + 1])
    valles = #(forall w : 1 < w < size - 1 : v[w - 1] > v[w] && v[w] < v[w + 1])
}
INVARIANTE: {
    0 < i < size
    &&
    picos = #(forall u : 1 < u < i : v[u - 1] < v[u] && v[u] > v[u + 1])
    &&
    valles = #(forall w : 1 < w < i : v[w - 1] > v[w] && v[w] < v[w + 1])
}

FUNCIÓN DE COTA: size - i
ANALISIS DEL COSTE: El coste del cada iteracion del bucle es constante, y este se ejecuta size - 2 veces === size.
    Por ello, el coste del algoritmo pertenece a size * O(1) = O(size)
*/

struct tsol {
    int picos;
    int valles;
};

tsol resolver(vector<int>const& v, size_t size) {
    int picos = 0, valles = 0;
    for (size_t i = 1; i < size - 1; i++) {
        if (v[i - 1] < v[i] && v[i] > v[i + 1]) picos++;
        if (v[i - 1] > v[i] && v[i] < v[i + 1]) valles++;
    }
    return { picos, valles };
}


void resuelveCaso() {
    int size = 0;
    cin >> size;
    vector<int> v(size);
    for (int i = 0; i < size; i++) cin >> v[i];
    tsol sol = resolver(v, size);
    cout << sol.picos << " " << sol.valles << "\n";
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    ifstream in("in.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    unsigned int numCasos;
    cin >> numCasos;
    // Resolvemos
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
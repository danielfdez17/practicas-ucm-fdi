#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
ESPECIFICACIÓN: fun segmento_pares(vector<int>const& v, int size) ret (int s)

PRECONDICION: {
    0 <= size
    &&
    forall u : 0 <= u < size : v[u] >= 0
}

POSTCONDICION: {
    s = #(p,q : 0 <= p < q <= size && todosPares(v,p,q))
}

INVARIANTE: {
    0 <= i <= size
    &&
    s = #(p,q : 0 <= p < q <= i && todosPares(v,p,q))
    &&
    pos = min(j : 0 <= j <= i : todosPares(v,j,i) : j)
}

FUNCIÓN DE COTA: size - i
ANALISIS DEL COSTE: El coste de cada iteracion del bucle es constante, y este se recorre siempre size veces.
    Por tanto, el coste del algoritmo pertenece a size * O(1) = O(size)

    1. todosPares(v,p,q) = forall i : p <= i < q : v[i] % 2 == 0
*/

int segmento_pares(vector<int>const& v, int size) {
    int s = 0, pos = 0;
    for (int i = 0; i < size; i++) {
        if (v[i] % 2 == 0)
            s += (i - pos + 1);
        else
            pos = i + 1;
    }
    return s;
}

void resuelveCaso() {
    int size; cin >> size;
    vector<int>v(size);
    for (int& i : v) cin >> i;
    cout << segmento_pares(v, size) << "\n";
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    unsigned int numCasos; cin >> numCasos;
    for (int i = 0; i < numCasos; ++i) resuelveCaso();
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
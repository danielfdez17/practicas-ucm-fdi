#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
ESPECIFICACIÓN: fun segmentos_impares(vector<int>const& v, int size, int k, int l) ret (int seg)

PRECONDICION: {
    0 <= size
    &&
    k,l >= 0
    &&
    k <= size
    &&
    forall u : 0 <= u < k : v[u] % 2 == 0
}

POSTCONDICION: {
    seg = # u : k <= u < size : noMas(v,u - k,u,l) == true
}

INVARIANTE: {
    k <= i <= size
    &&
    impares = impares(v,i - k,i)
    &&
    seg = (# (u1 : k <= u1 < i : noMas(v,u1 - k,u1,l) == true)) || (size + 1 <=> k == 0)
}

FUNCIÓN DE COTA: size - i
ANALISIS DEL COSTE:

    1. noMas(v,i,j,l) = (# (u : i <= u < j : v[u] % 2 != 0) <= l)

PREDICADOS AUXILIARES
    impares(v,i,j) = # (u : i <= u < j : v[u] % 2 != 0)
*/

int segmentos_impares(vector<int>const& v, int size, int k, int l) {
    if (k == 0) return size + 1;
    int seg = 1, impares = 0;
    for (int i = k; i < size; i++) {
        if (v[i] % 2 != 0) {
            impares++;
        }
        if (v[i - k] % 2 != 0) {
            impares--;
        }
        if (impares <= l) {
            seg++;
        }
    }
    return seg;
}

void resuelveCaso() {
    int size, k, l; cin >> size >> k >> l;
    vector<int>v(size);
    for (int& i : v) cin >> i;
    cout << segmentos_impares(v, size, k, l) << "\n";
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
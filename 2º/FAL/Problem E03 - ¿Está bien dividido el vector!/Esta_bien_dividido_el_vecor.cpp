#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
ESPECIFICACIÓN: fun resolver(int vector<int>const&v, in int size, in int pos) ret bool
PRECONDICION: {
    size > 0
}
POSTCONDICION: {
    ok = true <=> max (forall u1 : 0 <= u1 <= pos) : v[u1] < min (forall u2 : pos < u2 < size) : v[u2]
}

INVARIANTE: {
    0 <= i <= size 
    && 
    max_antes_p = max(max_antes_p, max(forall w1 : 0 <= w1 < i <= pos : v[w1]))
    &&
    min_despues_p = max(min_despues_p, min(forall w2 : pos < w2 < i : v[w2]))
    &&
    ok = max_antes_p < min_despues_p
}

FUNCIÓN DE COTA: size - i
ANALISIS DEL COSTE: El coste de cada iteración del bucle es constante, y este se recorre size veces en el peor de los casos.
    Por tanto, el coste del algoritmo pertenece a size * O(1) = O(size), donde size el el numero de elementos del vector
*/

bool resolver(vector<int>const& v, int size, int pos) {
    if (pos >= size) return true;
    int max_antes_p = std::numeric_limits<int>::min(), min_despues_p = std::numeric_limits<int>::max();
    bool ok = max_antes_p < min_despues_p;
    int i = 0;
    while (i < size && ok) {
        if (i <= pos) max_antes_p = max(max_antes_p, v[i]);
        else min_despues_p = min(min_despues_p, v[i]);
        ok = max_antes_p < min_despues_p;
        i++;
    }
    return ok;
}

void resuelveCaso() {
    int size, pos; cin >> size >> pos;
    vector<int>v(size);
    for (int i = 0; i < size; i++) cin >> v[i];
    cout << (resolver(v, size, pos) ? "SI\n" : "NO\n");
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
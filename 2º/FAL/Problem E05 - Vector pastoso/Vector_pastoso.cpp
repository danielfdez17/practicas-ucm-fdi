#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

/*
ESPECIFICACIÓN: fun resolver(vector<int>const&v, int size) ret pair<bool,int>
PRECONDICION: {
    0 <= size <= 100.000
}
POSTCONDICION: {
    found = max u : 0 <= u < size : v[u] = suma(v,u)
    &&
    suma = suma(v,u)
    &&
    pos = u <=> found == true
}

INVARIANTE: {
    -1 <= i < size
    &&
    found = max u : i <= u < size : v[u] = suma(v,u)
    &&
    suma = suma(v,u)
    &&
    pos = u <=> found == true
}

PREDICADOS AUXILIARES {
    suma(v,i) = SUM (forall j : i < j < v.size() : v[j])
}

FUNCIÓN DE COTA: i
ANALISIS DEL COSTE: El coste de cada iteracion del bucle es constante, y este se recorre en el peor de los casos size veces.
    Por tanto, el coste del algoritmo pertenece a size * O(1) = O(size)
*/

pair<bool, int>resolver(vector<int>const& v, int size) {
    if (size == 0) return { false,size };
    int i = size - 1; bool found = false; int pos = -1; int suma = 0;
    while (i >= 0 && !found) {
        if (suma == v[i]) {
            found = true;
            pos = i;
        }
        suma += v[i];
        i--;
    }
    return { found,pos };
}

void resuelveCaso() {
    int size; cin >> size;
    vector<int>v(size);
    for (int& i : v)cin >> i;
    pair<bool, int>p = resolver(v, size);
    cout << (p.first ? "SI " + to_string(p.second) : "NO") << "\n";
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
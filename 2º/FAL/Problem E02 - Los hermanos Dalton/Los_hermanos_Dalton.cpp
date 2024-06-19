#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
ESPECIFICACIÓN: fun resolver(in vector<int>const&v, int int size) ret bool
PRECONDICION: { 
    2 <= size <= 100.000 
    && 
    forall i : 0 <= i < size : 1 <= v[i] <= 1.000.000 
}
POSTCONDICION: {
    hermanos = true <=> forall u : 0 <= u < size : v[u] < v[u + 1]
    ||
    hermanos = true <=> forall w : 0 <= w < size : v[w - 1] > v[w]
}
INVARIANTE: {
    0 <= i < size 
    &&
    (
        hermanos = true <=> forall u1 : 0 <= u1 < i : v[u1] < v[u1 + 1]
        ||
        hermanos = true <=> forall w1 : 0 <= w1 < size : v[w1 - 1] > v[w1]
    )
}

FUNCIÓN DE COTA: size - i || i
ANALISIS DEL COSTE: El coste de cada iteracion del bucle es constante, y este se ejecuta (en el peor de los casos) size - 1 veces === size.
    Por tanto, el coste del algoritmo (en el caso peor) pertenece a size * O(1) = O(size)
*/

bool resolver(vector<int>const& v, int size) {
    bool hermanos = true;
    int i = 0;
    while (i < size - 1 && hermanos) { // crecientes
        hermanos = (v[i] < v[i + 1]);
        i++;
    }
    if (!hermanos) {
        hermanos = true;
        i = size - 1;
        while (0 < i && hermanos) { // decrecientes
            hermanos = (v[i - 1] > v[i]);
            i--;
        }
    }
    return hermanos;
}

bool resuelveCaso() {
    int cantidad; cin >> cantidad;
    if (cantidad == 0) return false;
    vector<int>hermanos(cantidad);
    for (int i = 0; i < cantidad; i++) cin >> hermanos[i];
    cout << (resolver(hermanos, cantidad) ? "DALTON\n" : "DESCONOCIDOS\n");
    return true;
}



int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
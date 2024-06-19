#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
ESPECIFICACION: fun resolver(vector<int>const&v, int size) ret int

PRECONDICION: {
    0 <= size <= 1000
}

POSTCONDICION: {
    segMax = max p,q : 0 <= p <= q < size : forall u : p <= u < q : v[u] >= v[u + q]
    &&
    seg = p,q : 0 <= p <= q < size : forall u1 : p <= u1 < q : v[u1] >= v[u1 + q]
}

INVARIANTE: {
    0 <= i < size
    &&
    segMax = max p,q : 0 <= p <= q < i : forall w : p <= w < q : v[w] >= v[w + q]
    &&
    seg = p,q : 0 <= p <= q < i : forall w1 : p <= w1 < q : v[w1] >= v[w1 + q]
}

FUNCION DE COTA: size - i
ANALISIS DEL COSTE: El coste de cada iteracion del bucle es constante, y este se recorre size - 1 veces (=== size).
    Por tanto, el coste del algoritmo pertenece a size * O(1) = O(size)
*/

int resolver(vector<int>const& v, int size) {
    if (size == 0) return size;
    int seg = 1, segMax = 1;
    for (int i = 0; i < size - 1; i++) {
        if (v[i] >= v[i + 1]) {
            seg++;
            if (seg > segMax) {
                segMax = seg;
            }
        }
        else {
            seg = 1;
        }
    }
    return segMax;
}

bool resuelveCaso() {
    int size; cin >> size;
    vector<int> v(size);
    for (int& i : v)cin >> i;
    cout << resolver(v, size) << "\n";
    return true;
}



int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    unsigned int numCasos;
    std::cin >> numCasos;
    // Resolvemos
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
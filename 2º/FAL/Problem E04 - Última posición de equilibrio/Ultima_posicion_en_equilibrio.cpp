#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
/*
ESPECIFICACIÓN: porc equilibrio(vector<int>v) dev int p
PRECONDICION: {
    true
}
POSTCONDICION: {
    −1 <= p < v.size() 
    &&
    numUnos(v, p + 1) = numCeros(v, p + 1)
    &&
    forall k : p < k < v.size() : numUnos(v, k + 1) != numCeros(v, k + 1)
}
PREDICADOS AUXILIARES: {
    numUnos(v,j) = #i : 0 <= i < j : v[i] = 1
    numCeros(v,j) = #i : 0 <= i < j : v[i] = 0
}

INVARIANTE: {
    0 <= i <= v.size()
    && 
    numUnos = numUnos(v,i + 1)
    &&
    numCeros = numCeros(v, i + 1)
    &&
    p = max u : 0 <= u <= i : numUnos == numCeros
}

FUNCIÓN DE COTA: v.size() - i
ANALISIS DEL COSTE: El coste de cada iteración del bucle es constante, y este se recorre v.size() veces.
    Por tanto, el coste del algoritmo pertenece a v.size() * O(1) = O(v.size())
*/

int equilibrio(vector<int>v) {
    if (v.size() == 0) return -1;
    int p = -1;
    int numUnos = 0, numCeros = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == 1) numUnos++;
        else if (v[i] == 0) numCeros++;
        if (numUnos == numCeros) p = i;
    }
    return p;
}

void resuelveCaso() {
    int size; cin >> size;
    vector<int>v(size);
    for (int& i : v) cin >> i;
    cout << equilibrio(v) << "\n";
}

int main() {
    // Para la entrada por fichero.
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


#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
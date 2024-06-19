#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

/*
ESPECIFICACION: fun resolver(vector<int>const&v, int size, int d) ret bool
PRECONDICION: {
    0 <= size <= 1000
    && 
    d > 0
}

POSTCONDICION: {
    forall u : 0 <= u < size - 1 : v[u] <= v[u + 1]
    &&
    repetidos = #(forall w : 0 <= w < size - 1 : v[w] == v[w + 1])
    &&
    repetidos <= d
    &&
    repetidos >= 1
}

INVARIANTE: {
    0 <= i < size - 1
    &&
    forall u1 : 0 <= u1 < i : v[u1] <= v[u1 + 1] // creciente por los pelos
    &&
    repetidos = #(forall w1 : 0 <= w1 < i : v[w1] == v[w1 + 1]) // divertido
    &&
    repetidos <= d
    &&
    repetidos >= 1
}

FUNCION DE COTA: size - i
ANALISIS DEL COSTE: El coste de cada iteración del bucle es constante, y este se recorre en el caso peor size - 1 veces (=== size).
    Por tanto, el coste del algoritmo pertenece a size * O(1) = O(size)
*/

bool resolver(vector<int>const& v, int size, int d) {
    bool creciente = true, divertido = true;
    int i = 0, repetidos = 1;
    while(i < size - 1 && creciente) {
        if (v[i] == v[i + 1]) {
            repetidos++;
            divertido = repetidos <= d;
        }
        else if (v[i] < v[i + 1]) {
            creciente = v[i + 1] - v[i] <= 1;
            repetidos = 1;
        }
        else {
            creciente = false; divertido = false;
        }
        i++;
    }
    return creciente && divertido;
}

bool resuelveCaso() {
    int size, d;
    cin >> d >> size;
    vector<int> v(size);
    for (int& i : v)cin >> i;
    cout << (resolver(v, size, d) ? "SI\n" : "NO\n");
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
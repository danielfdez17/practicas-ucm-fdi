#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

/*
ESPECIFICACION: proc resolver(vector<long long int>&v, int size)

PRECONDICION: {
    size >= 0
}

POSTCONDICION: {
    pares = # u : 0 <= u < size : v[u] % 2 == 0
    &&
    forall w : 0 <= w < size : v[w] % 2 == 0
}

INVARIANTE: {
    0 <= i <= size
    &&
    pares = # u1 : 0 <= u1 < i : v[u1] % 2 == 0
    &&
    forall w1 : 0 <= w1 < i : v[w1] % 2 == 0
}

FUNCION DE COTA: size - i
ANALISIS DEL COSTE: El coste del bucle es constante. y este se recorre size veces. v.resize(p) es lineal en size - pares
    Por tanto el coste del algorimto pertenece a O(1) * size + O(size - pares) = O(size) + O(size - pares)
*/

void resolver(vector<long long int>& v, int size) {
    int pares = 0;
    for (int i = 0; i < size; i++) {
        if (v[i] % 2 == 0) {
            v[pares] = v[i];
            pares++;
        }
    }
    v.resize(pares);
}

bool resuelveCaso() {
    int size; cin >> size;
    vector<long long int> v(size);
    for (long long int& i : v) cin >> i;
    resolver(v, size);
    for (long long int& i : v) cout << i << " ";
    cout << "\n";
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
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
ESPECIFICACIÓN: fun resolver(vector<int>const&v, int size) ret tsol {suma, n_valores}
PRECONDICION: {
    0 < size <= 1000
}
POSTCONDICION: {
    minimo = forall u3, u4 : 0 <= u3, u4 < size : u3 != u4 && v[u3] < v[u4] : v[u3]
    &&
    repeticiones = # forall u2 : 0 <= u2 < size : v[u2] = minimo
    &&
    suma = forall u : 0 <= u < size : v[u] - (repeticiones * minimo)
    && 
    n_valores = size - repeticiones
}

INVARIANTE: {
    0 <= i <= size 
    &&
    minimo = forall w3, w4 : 0 <= w3, w4 < i : w3 != w4 && v[w3] < v[w4] : v[w3]
    &&
    repeticiones = # forall w2 : 0 <= w2 < i : v[w2] = minimo
    &&
    suma = forall u : 0 <= w < i : v[w] - (repeticiones * minimo)
    &&
    n_valores = size - repeticiones
}

FUNCIÓN DE COTA: size - i
ANALISIS DEL COSTE: El coste de cada iteracion del bucle es constante, y este se recorre size veces.
    Por tanto, el coste del algoritmo pertenece a size * O(1) = O(size)
*/

struct tsol {
    long long int suma;
    int n_valores;
};

tsol resolver(vector<int>const& v, int size) {
    long long int suma = 0; int minimo = std::numeric_limits<int>::max(), repeticiones = 0;
    for (int i = 0; i < size; i++) {
        if (minimo == v[i])
            repeticiones++;
        if (v[i] < minimo) {
            repeticiones = 1;
            minimo = v[i];
        }
        suma += v[i];
    }
    return { suma - (repeticiones * minimo), size - repeticiones };
}


void resuelveCaso() {
    int size; cin >> size;
    vector<int>v(size);
    for (int& i : v)cin >> i;
    tsol sol = resolver(v, size);
    cout << sol.suma << " " << sol.n_valores << "\n";
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
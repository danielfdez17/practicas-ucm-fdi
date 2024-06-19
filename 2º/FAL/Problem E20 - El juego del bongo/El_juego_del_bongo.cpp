#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*
RECURRENCIA: sea n el numero de elementos del vector
T(n) = c si n = 1
T(n) = T(n/2) si n > 1
T(n) pertenece a log(n)
El coste del algoritmo en el caso peor el logaritmico en n (no existe el numero a tachar o esta en uno de los extremos)
El coste del algorimto en el caso mejor es constante (el numero a tachar es el elemento del medio de la llamada inicial)
*/

void bongo(vector<int>const& v, int c, int f, int cantado, int& tachado, bool& encontrado) {
    if (!encontrado) {
        if (c == f) {
            if (v[c] - c == cantado) {
                encontrado = true;
                tachado = v[c];
            }
        }
        else {
            int m = (c + f) / 2;
            if (v[m] - m == cantado) {
                encontrado = true;
                tachado = v[m];
            }
            else if (v[m] - m < cantado)
                bongo(v, m + 1, f, cantado, tachado, encontrado);
            else
                bongo(v, c, m, cantado, tachado, encontrado);
        }
    }
}

bool resuelveCaso() {
    int size, cantado, tachado; cin >> size >> cantado;
    vector<int> v(size);
    for (int& i : v)cin >> i;
    bool encontrado = false;
    bongo(v, 0, size - 1, cantado, tachado, encontrado);
    cout << (encontrado ? to_string(tachado) : "NO") << "\n";
    return true;
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
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct tsol {
    bool equilibrado;
    int peso;
};

/*
RECURRENCIA: Sea n el numero de nodos del arbol (numero de moviles)
    T(n) = c si n = 1
    T(n) = T(n/2) si n > 1
    T(n) pertenece a O(n), ya que siempre se recorren todos los nodos del arbol
*/

tsol equilibrado() {
    int pi, di, pd, dd; cin >> pi >> di >> pd >> dd;
    if (pi != 0 && pd != 0)
        return { pi * di == pd * dd,pi + pd };
    tsol i = { pi,true }, d = { pd,true };
    if (pi == 0)
        i = equilibrado();
    if (pd == 0)
        d = equilibrado();
    return { i.equilibrado && d.equilibrado && (pi * di == pd * dd),pi + pd };
}


void resuelveCaso() {
    cout << (equilibrado().equilibrado ? "SI\n" : "NO\n");
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
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/*
RECURRENCIA: Sea m el numero de digitos del numero n
    T(m) = 0 si m = 1
    T(m) = T(m - 1) + c si m > 1
    T(m) pertenece a O(m)
    Coste: siempre es lineal en el numero de digitos del numero n
*/

long long int digitos_decrecientes(long long int n, int maximo_derecha) {
    if (n == 0) return n;
    int modulo = n % 10;
    long long int ret = digitos_decrecientes(n / 10, std::max(maximo_derecha, modulo));
    if (modulo >= maximo_derecha) {
        ret = ret * 10 + modulo;
    }
    return ret;
}

void resuelveCaso() {
    long long int n; cin >> n;
    cout << digitos_decrecientes(n, -1) << "\n";
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
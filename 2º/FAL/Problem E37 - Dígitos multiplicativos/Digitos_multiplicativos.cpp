#include <iostream>
#include <fstream>
using namespace std;

/*
RECURRENCIA: Sea m el numero de digitos del numero n
    T(m) = c si m = 1
    T(m) = T(m - 1) + c si m > 1
    T(m) pertenece a O(m)
    Coste: siempre es lineal en el numero de digitos del numero n
*/

void multiplicativo(int n, long long int& producto, int& digitos_multiplicativos) {
    if (n < 10) {
        if (n == 1) digitos_multiplicativos++;
        else digitos_multiplicativos = 0;
        producto = n;
    }
    else {
        int modulo = n % 10;
        multiplicativo(n / 10, producto, digitos_multiplicativos);
        if (producto % 10 == modulo) digitos_multiplicativos++;
        producto *= modulo;
    }
}

void resuelveCaso() {
    int n; cin >> n;
    long long int producto;
    int digitos_multiplicativos = 0;
    multiplicativo(n, producto, digitos_multiplicativos);
    cout << digitos_multiplicativos << "\n";
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
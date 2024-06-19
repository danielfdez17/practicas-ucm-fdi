#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/*
RECURRENCIA: Sea m el numero de digitos del numero n
    T(m) = c si m = 1
    T(m) = T(m - 1) + c si m > 1
    T(m) pertenece a O(m)
    Coste: siempre es lineal en el numero de digitos del numero n
*/

void complementario(long long int n, int&n_ceros, long long int&n_complementario, long long int&n_inverso_complementario) {
    if (n < 10) {
        n_complementario = 9 - n;
        n_inverso_complementario = 9 - n;
    }
    else {
        int modulo_complementario = 9 - n % 10;
        complementario(n / 10, n_ceros, n_complementario, n_inverso_complementario);
        n_inverso_complementario += (modulo_complementario * std::pow(10,n_ceros));
        n_complementario = n_complementario * 10 + modulo_complementario;
    }
    n_ceros++;
}

void resuelveCaso() {
    long long int n, n_complementario,n_inverso_complementario; cin >> n;
    int n_ceros = 0;
    complementario(n, n_ceros, n_complementario, n_inverso_complementario);
    cout << n_complementario << " " << n_inverso_complementario << "\n";
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
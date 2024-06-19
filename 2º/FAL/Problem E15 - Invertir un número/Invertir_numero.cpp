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


void invertir(int n, int&invertido, int&ceros) {
    if (n < 10) {
        invertido = n;
        ceros++;
    }
    else {
        int modulo = n % 10;
        invertir(n / 10, invertido, ceros);
        invertido = invertido + std::pow(10, ceros) * modulo;
        ceros++;
    }
}

//void invertir(int n, int& invertido) {
//    if (n < 10) {
//        invertido = invertido * 10 + n;
//    }
//    else {
//        int modulo = n % 10;
//        invertido = invertido * 10 + modulo;
//        invertir(n / 10, invertido);
//    }
//}

bool resuelveCaso() {
    int n; cin >> n;
    if (n == 0) return false;
    int invertido, ceros = 0;
    invertir(n, invertido, ceros);
    cout << invertido << "\n";
    return true;
}


int main() {
#ifndef DOMJUDGE
    ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso());
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
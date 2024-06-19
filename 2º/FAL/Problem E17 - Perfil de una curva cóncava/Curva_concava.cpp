#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

/*
RECURRENCIA: sea n el numero de elementos del vector
    T(n) = c si n 0 < n <= 2
    T(n) = T(n/2) + c si n > 2
    T(n) pertenece a log(n)
    El coste del algorimto es logaritmico en el numero de elementos del vector
*/
// Intervalo cerrado: c == f -> 1 elemento && c == f - 1 -> 0 elementos
void curvaConcava(vector<int>const& v, int c, int f, int& min) {
    if (c == f) { // CB: 1 elemento
        min = std::min(min, v[c]);
    }
    else if (c + 1 == f) { // CB: 2 elementos
        min = std::min(min, std::min(v[c], v[f]));
    }
    else { // CR
        int m = (c + f) / 2;
        if (v[m] < v[m + 1]) { // 3 4 -> Llamada con la mitad izquierda
            curvaConcava(v, c, m, min);
        }
        else { // 4 3 -> Llamada con la mitad derecha
            curvaConcava(v, m + 1, f, min);
        }
    }
}

bool resuelveCaso() {
    int size, min = std::numeric_limits<int>::max(); cin >> size;
    if (!cin) return false;
    vector<int> v(size);
    for (int&i : v) cin >> i;
    curvaConcava(v, 0, size - 1, min);
    cout << min << "\n";
    return true;
}



int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
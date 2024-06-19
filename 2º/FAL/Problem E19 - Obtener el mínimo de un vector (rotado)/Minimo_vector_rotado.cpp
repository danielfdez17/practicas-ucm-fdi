#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

/*
RECURRENCIA: Sea n el numero de elementos del vector
    T(n) = c si n = 1
    T(n) = T(n/2) si n > 1
    T(n) pertenece a log(n)
    El coste del algorimto es logaritmico en el numero de elementos del vector
*/
// Llamada inicial con c = 0 y f = size - 1, intervalo cerrado [c, f]
void minimo(vector<int>const& v, int c, int f, int& min) {
    if (c == f) // CB: 1 elemento
        min = std::min(min, v[c]);
    else if (c == f - 1) // CB: 2 elementos
        min = std::min(min, std::min(v[c], v[f]));
    else {
        int m = (c + f) / 2;
        if (v[m] <= min)
            minimo(v, m, f, min);
        else 
            minimo(v, c, m, min);
    }
}


bool resuelveCaso() {
    int size; cin >> size;
    if (!cin) return false;
    vector<int> v(size);
    for (int& i : v)cin >> i;
    int min = std::min(v[0], v[size - 1]);
    minimo(v, 0, size - 1, min);
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
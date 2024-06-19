#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/* RECURRENCIA: Sea n el numero de elementos del vector
*   T(n) = c si 0 <= n <= 1
*   T(n) = 2T(n/2) + c + n*log(n) si n > 1
*   T(n) pertenece a O(n*log(n)) ya que se recorren todos los elementos del vector haciendose una ordenacion por cada llamada recursiva != CB
*/

// Intervalo cerrado [c, f]
long long int inversiones(vector<int>& v, int c, int f) {
    if (c >= f) return 0;
    long long int m = (c + f) / 2;
    long long int izq = inversiones(v, c, m);
    long long int der = inversiones(v, m + 1, f);
    long long int i = c, j = m + 1;
    long long int cont = 0;
    while (i <= m && j <= f) {
        if (v[i] > v[j]) {
            cont += (m - i + 1);
            j++;
        }
        else i++;
    }
    std::sort(v.begin() + c, v.begin() + f + 1); // O(n log(n))
    return izq + der + cont;
}


void resuelveCaso() {
    long long int size; cin >> size;
    vector<int>v(size);
    for (int& i : v) cin >> i;
    cout << inversiones(v, 0, size - 1) << "\n";
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int casos; cin >> casos;
    for (int i = 0; i < casos; i++) { resuelveCaso(); }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
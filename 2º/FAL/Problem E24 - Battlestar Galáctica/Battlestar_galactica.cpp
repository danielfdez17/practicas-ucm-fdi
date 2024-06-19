#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/* RECURRENCIA: Sea n el numero de naves
*   T(n) = c si 0 <= n <= 1
*   T(n) = 2T(n/2) + c + n*log(n) si n > 1
*   T(n) pertenece a O(n) ya que se recorren todos los elementos del vector
*/

// Intervalo cerrado [c, f]
int battlestar(vector<int>& v, int c, int f) {
    if (c >= f) return 0;
    int m = (c + f) / 2;
    int izq = battlestar(v, c, m);
    int der = battlestar(v, m + 1, f);
    int i = c, j = m + 1;
    int cont = 0;
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


bool resuelveCaso() {
    int naves; cin >> naves;
    if (!cin) return false;
    vector<int>v(naves);
    for (int& i : v) cin >> i;
    cout << battlestar(v, 0, naves - 1) << "\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
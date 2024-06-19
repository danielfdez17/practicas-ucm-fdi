#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
* RECURRENCIA: Sea n el numero de elementos del vector
* T(n) = c si n = 1
* T(n) = T(n/2) + c si n > 1
* T(n) pertenece a log(n)
* El coste en el caso peor es logarimico en el numero de elementos del vector
* El coste en el caso mejor el constante, ya que falta el preso x1 o x2
*/

// Intervalo cerrado [c, f]
void fugaPrision(vector<char>const& v, int c, int f, char x1, char x2, char& preso_fugado) {
    if (v[0] != x1) preso_fugado = x1;
    else if (v[(int)v.size() - 1] != x2) preso_fugado = x2;
    else {
        if (c == f) { // cb: un elemento
            if (v[c] - x1 != c) // falta el de la izquierda de v[c]
                preso_fugado = v[c] - 1;
            else // falta el de la derecha de v[f]
                preso_fugado = v[f] + 1;
        }
        else if (c == f - 1) {
            if (v[f] - v[c] == 2)
                preso_fugado = v[c] + 1;
            else {
                if (v[c] - x1 != c)
                    preso_fugado = v[c] - 1;
                else
                    preso_fugado = v[f] + 1;
            }
        }
        else {
            int m = (c + f) / 2;
            // c h
            // d e f g h
            // ('f' - 'c' = 3) != (2 - 0 = 2)
            if (v[m] - v[c] != m - c) {
                fugaPrision(v, c, m, x1, x2, preso_fugado);
            }
            // a e
            // a b c e
            // ('e' - 'b' = 3) != (3 - 1 = 2)
            else if (v[f] - v[m] != f - m) {
                fugaPrision(v, m, f, x1, x2, preso_fugado);
            }
        }
    }
}

bool resuelveCaso() {
    char preso_fugado, x1, x2; cin >> x1 >> x2;
    int size = x2 - x1;
    vector<char> v(size);
    for (char&i:v) cin >> i;
    fugaPrision(v, 0, size - 1, x1, x2, preso_fugado);
    cout << preso_fugado << "\n";
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
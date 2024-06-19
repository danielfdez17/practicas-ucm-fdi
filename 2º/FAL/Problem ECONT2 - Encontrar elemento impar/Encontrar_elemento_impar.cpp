#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string>
using namespace std;

// RECURRENCIA: Sea n el numero de elementos del vector
// T(n) = c si 0 <= n <= 1
// T(n) = T(n/2) + c si n > 1
// T(n) pertenece a O(log(n))
// El coste del algoritmo es logaritmico en n ya que se hacen aproximiadamente log(n) llamadas recursivas en el caso peor

// Intervalo cerrado [c,f]. Llamada inicial con c = 0 y f = numElem - 1
void unico_impar(vector<int>const& v, int c, int f, int& impar, bool&encontrado) {
    if (encontrado) return;
    if (c == f) { // CB: 1 elemento
        if (v[c] % 2 != 0) {
            impar = v[c];
            encontrado = true;
        }
    }
    else if (c == f - 1) { // CB: 2 elementos
        if (v[c] % 2 != 0) {
            impar = v[c];
            encontrado = true;
        }
        else if (v[f] % 2 != 0) {
            impar = v[f];
            encontrado = true;
        }
    }
    else { // CR
        int m = (c + f) / 2;
        if (v[m] % 2 != 0) {
            impar = v[m];
            encontrado = true;
        }
        else {
            if (v[m] - v[c] != (m - c) * 2) {
                unico_impar(v, c, m, impar, encontrado);
            }
            else {
                unico_impar(v, m + 1, f, impar, encontrado);
            }
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // lectura de los datos
    int numElem; cin >> numElem;
    if (numElem == 0) return false;
    vector<int> v(numElem);
    for (int& i : v) cin >> i;
    int impar; bool encontrado = false;
    unico_impar(v, 0, numElem - 1, impar, encontrado);
    cout << impar << "\n";
    return true;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso());
    ;

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {

    int n; cin >> n;

    if (!std::cin) return false;

    vector<int>ataque(n), defensa(n);

    for (int i = 0; i < n * 2; i++) {
        if (i < n) cin >> ataque[i];
        else cin >> defensa[i - n];
    }

    sort(ataque.begin(), ataque.end());
    sort(defensa.begin(), defensa.end());

    int ciudades = 0;

    int i = 0, j = 0;
    while (i < n && j < n) {
        if (ataque[i] <= defensa[j]) {
            i++; j++; ciudades++;
        }
        else {
            j++;
        }

    }

    cout << ciudades << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}

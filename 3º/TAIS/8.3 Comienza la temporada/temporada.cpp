
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

    int n, m; cin >> n >> m;

    if (!std::cin) return false;

    vector<int>jugadores(n), equipaciones(m);

    for (int i = 0; i < n; i++) {
        cin >> jugadores[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> equipaciones[i];        
    }

    sort(jugadores.begin(), jugadores.end());
    sort(equipaciones.begin(), equipaciones.end());

    int i = 0, j = 0, reutilizadas = 0;
    while (i < n && j < m) {
        if (jugadores[i] == equipaciones[j] || jugadores[i] + 1 == equipaciones[j]) {
            ++reutilizadas; ++i; ++j;
        }
        else if (jugadores[i] > equipaciones[j]) ++j;
        else ++i;
    }

    cout << n - reutilizadas << "\n";

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

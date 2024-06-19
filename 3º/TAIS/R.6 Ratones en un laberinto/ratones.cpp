
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "Dijkstra.h"
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
    int n, s, t, p; cin >> n >> s >> t >> p;
    if (!cin) return false;
    DigrafoValorado<int> g(n);
    for (int i = 0; i < p; ++i) {
        int a, b, c; cin >> a >> b >> c;
        --a; --b;
        g.ponArista({a, b, c});
    }
    int mouses = 0;
    for (int i = 0; i < n; ++i) {
        if (i == s) continue;
        Dijkstra<int>dijkstra(g, i);
        if (dijkstra.distancia(i) <= t) 
            ++mouses;
    }
    cout << mouses << "\n";
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

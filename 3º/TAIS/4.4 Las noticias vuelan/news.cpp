
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include "ConjuntosDisjuntos.h"
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
   if (!cin) return false;
   ConjuntosDisjuntos sol(n);
   for (int i = 0; i < m; ++i) {
      int size; cin >> size;
      for (int j = 0; j < size; ++j) {
         int v, prev; cin >> v;
         if (j != 0) {
            if (!sol.unidos(prev, v - 1)) {
               sol.unir(prev, v - 1);
            }
         }
         prev = v - 1;
      }
   }
   for (int i = 0; i - n; ++i) 
      cout << sol.cardinal(i) << " ";
   cout << "\n";
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

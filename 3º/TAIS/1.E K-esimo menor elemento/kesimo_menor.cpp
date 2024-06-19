
/*@ <answer>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la solución.
 * Luis Rebollo Cocera: TAIS53
 * Daniel Fernandez Ortiz: TAIS21
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "TreeSet_AVL.h"
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
   
   // leer los datos de la entrada
   int n; cin >> n;
   if (n == 0) return false;
   
   Set<int> arbol;
    int x; 

    for (int i = 0; i < n; i++) {
        cin >> x;
        arbol.insert(x);
    }
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> x;
        try {
            cout << arbol.kesimo(x);
        } catch (std::out_of_range& e) {
            cout << e.what();
        }
    }
    cout << "\n\n";

   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("casos.txt");
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}

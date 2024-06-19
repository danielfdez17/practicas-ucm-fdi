
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include"Grafo.h"
#include"ConjuntosDisjuntos.h"
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

class freeTrees {
private:
    ConjuntosDisjuntos sets;
public:
    freeTrees(Grafo const&g) : sets(g.V()) {
        for (int i = 0; i < g.V(); ++i) {
            for (int w : g.ady(i)) {
                if (!sets.unidos(i, w)) {
                    sets.unir(i, w);
                }
            }
        }
    }
    bool isFree() const { return sets.num_cjtos() == 1; }
};

bool resuelveCaso() {
    int v, a; cin >> v >> a;
    if (!cin) return false;

    Grafo g(v);

    for (int i = 0; i < a; ++i) {
        int u, w; cin >> u >> w;
        g.ponArista(u, w);
    }

    freeTrees ft(g);

    cout << (ft.isFree() ? "SI\n" : "NO\n");

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos2.txt");
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

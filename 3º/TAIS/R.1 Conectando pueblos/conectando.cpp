/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include"PriorityQueue.h"
#include"GrafoValorado.h"
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

class ARM_Kruskal {
private:
    vector<Arista<int>> _ARM;
    int coste;
    int maxEdge;
    bool possible;
public:
    int costeARM() const { return coste; }
    vector<Arista<int>> const& ARM() const { return _ARM; }
    ARM_Kruskal(GrafoValorado<int> const& g) : coste(0), maxEdge(-1) {
        PriorityQueue<Arista<int>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a);
                maxEdge = max(maxEdge, a.valor());
                coste += a.valor();
                if (_ARM.size() == g.V() - 1) break;
            }
        }
        possible = cjtos.num_cjtos() == 1;
    }
    bool isPossible() const { return possible; }
    int getMaxEdge() const { return maxEdge; }
};

void resuelveCaso() {
    int n, m; cin >> n >> m;
    GrafoValorado<int> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        g.ponArista({a - 1, b - 1, c});
    }

    ARM_Kruskal arm(g);
    if (arm.isPossible()) 
        cout << arm.getMaxEdge() << "\n";
    else
        cout << "Imposible\n";
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}

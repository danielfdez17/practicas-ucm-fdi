
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include"GrafoValorado.h"
#include"PriorityQueue.h"
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

class kruskal {
private:
    vector<Arista<int>>edges;
    int cost;
    bool is_possible;
public:
    kruskal(GrafoValorado<int> const&g) : cost(0), is_possible(true) {
        PriorityQueue<Arista<int>>pq(g.aristas());
        ConjuntosDisjuntos sets(g.V());
        while (!pq.empty()) {
            Arista<int>edge = pq.top(); pq.pop();
            int s = edge.uno(), d = edge.otro(s);
            if (!sets.unidos(s, d)) {
                sets.unir(s, d);
                cost += edge.valor();
                edges.push_back(edge);
                if (edges.size() == g.V() - 1) break;
            }
        }
        is_possible = edges.size() == g.V() - 1;
    }
    bool isPossible() const { return is_possible; }
    int getCost() const { return cost; }
};

bool resuelveCaso() {
    int I, P; cin >> I >> P;
    if (!cin) return false;

    GrafoValorado<int>g(I);

    for (int i = 0; i < P; ++i) {
        int a, b, c; cin >> a >> b >> c;
        g.ponArista({a - 1, b - 1, c});
    }

    kruskal arm(g);
    if (arm.isPossible()) cout << arm.getCost() << "\n";
    else cout << "No hay puentes suficientes\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos1.txt");
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

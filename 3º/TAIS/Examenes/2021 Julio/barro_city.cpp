
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include"GrafoValorado.h"
#include"ConjuntosDisjuntos.h"
#include"PriorityQueue.h"
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


template<typename Valor>
class ARM_Kruskal {
private:
    vector<Arista<Valor>> _ARM;
    Valor coste;
    bool possible;
public:
    Valor costeARM() const { return coste; }
    vector<Arista<Valor>> const& ARM() const { return _ARM; }
    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a);
                coste += a.valor();
                if (_ARM.size() == g.V() - 1) break;
            }
        }
        possible = _ARM.size() == g.V() - 1;
    }
    bool isPossible() const { return possible; }
};

bool resuelveCaso() {
    int n, c; cin >> n >> c;
    if (!cin) return false;

    GrafoValorado<int>g(n);

    for (int i = 0; i < c; ++i) {
        int a, b, cost; cin >> a >> b >> cost;
        g.ponArista({a - 1, b - 1, cost});
    }

    ARM_Kruskal<int>arm(g);
    if (arm.isPossible()) cout << arm.costeARM() << "\n";
    else cout << "Imposible\n";

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

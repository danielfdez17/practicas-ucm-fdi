
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include"DigrafoValorado.h"
#include"IndexPQ.h"
using namespace std;

#define INF 1000000000


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Dijkstra {
private:
    int origen;
    vector<int>dist;
    IndexPQ<int>pq;
    void relajar(AristaDirigida<int>a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
public:
    Dijkstra(DigrafoValorado<int> const&g, int orig) : origen(orig), dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0; 
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    int distancia(int v) const { return dist[v]; }
};

bool resuelveCaso() {
    int n, c; cin >> n >> c;
    if (!std::cin) return false;

    DigrafoValorado<int>g(n);

    for (int i = 0; i < c; ++i) {
        int a, b, c; cin >> a >> b >> c;
        g.ponArista({a - 1, b - 1, c});
        g.ponArista({b - 1, a - 1, c});
    }

    int k; cin >> k;
    for (int i = 0; i < k; ++i) {
        int a, b; cin >> a >> b;
        Dijkstra d(g, a - 1);
        if (!d.hayCamino(b - 1)) cout << "NO LLEGA\n";
        else cout << d.distancia(b - 1) << "\n";
    }

    cout << "---\n";

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

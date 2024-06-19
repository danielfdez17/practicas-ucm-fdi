
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <deque>
#include <climits>
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
    int origen, pueblos, max_dist;
    vector<bool>visitados;
    vector<int>dist;
    IndexPQ<int>pq;
    void relajar(AristaDirigida<int>a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            if (dist[w] <= max_dist && !visitados[w]) {
                visitados[w] = true;   
                ++pueblos;
            }
            pq.update(w, dist[w]);
        }
    }
public:
    Dijkstra(int V, int d, int b) : dist(V, INF), 
    pq(V), pueblos(b), max_dist(d), visitados(V, false) {
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    int distancia(int v) const { return dist[v]; }
    void dijkstra(DigrafoValorado<int>const&g) {
        // dist[origen] = 0;
        // pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    void pushPQ(int v) {
        pq.push(v, 0);
        dist[v] = 0;
        visitados[v] = true;
    }
    int getPueblos() const {
        return pueblos;
    }
};

bool resuelveCaso() {

    int d, v, e; cin >> d >> v >> e;

    if (!std::cin) return false;

    DigrafoValorado<int>digrafo(v);

    for (int i = 0; i < e; i++) {
        int a, b, c; cin >> a >> b >> c;
        --a; --b;
        digrafo.ponArista({a, b, c});
        digrafo.ponArista({b, a, c});
    }

    int b; cin >> b;
    Dijkstra dijkstra(v, d, b);
    for (int i = 0; i < b; i++) {
        int v; cin >> v;
        dijkstra.pushPQ(v - 1);
    }
    dijkstra.dijkstra(digrafo);
    cout << dijkstra.getPueblos() << "\n";

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

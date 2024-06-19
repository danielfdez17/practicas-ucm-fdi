
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
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
    vector<int>dist, caminos, aristas;
    IndexPQ<int>pq;
    void relajar(AristaDirigida<int>a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            aristas[w] = aristas[v] + 1;
            pq.update(w, dist[w]);
        }
    }
    void bfs(DigrafoValorado<int>const&g, int origen) {
        vector<bool>visitados(g.V(), false);
        queue<int>cola; cola.push(origen); visitados[origen] = true;
        while (!cola.empty()) {
            int v = cola.front(); cola.pop();
            for (auto w : g.ady(v)) {
                if (!visitados[w.hasta()]) {
                    visitados[w.hasta()] = true;
                    caminos[w.hasta()] = caminos[v] + 1;
                    cola.push(w.hasta());
                }
            }
        }
    }
public:
    Dijkstra(DigrafoValorado<int> const&g, int orig) : origen(orig), dist(g.V(), INF), 
    caminos(g.V(), 0), aristas(g.V(), 0), pq(g.V()) {
        dist[origen] = 0; 
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
        bfs(g, origen);
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    int distancia(int v) const { return dist[v]; }
    void mostrar(int v) const {
        if (dist[v] != INF) {
            cout << dist[v] << " ";
            if (aristas[v] == caminos[v]) cout << "SI\n";
            else cout << "NO\n";
        }
        else cout << "SIN CAMINO\n";
    }
};

bool resuelveCaso() {
    int n, c; cin >> n >> c;
    if (!cin) return false;

    DigrafoValorado<int>g(n);

    for (int i = 0; i < c; ++i) {
        int a, b, c; cin >> a >> b >> c;
        g.ponArista({a - 1, b - 1, c});
        g.ponArista({b - 1, a - 1, c});
    }

    int k; cin >> k;
    for (int i = 0; i < k; ++i) {
        int origen, destino; cin >> origen >> destino;
        Dijkstra d(g, origen - 1);
        d.mostrar(destino - 1);
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

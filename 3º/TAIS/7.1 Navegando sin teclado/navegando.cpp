
/*@ <authors>
*
* Daniel Fernandez Ortiz: TAIS 21
*
*@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include"DigrafoValorado.h"
#include"IndexPQ.h"
using namespace std;
#define INF 100000000

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
    vector<int>tiempos;
    void relajar(AristaDirigida<int>a) {
    int v = a.desde(), w = a.hasta();
    if (dist[w] > dist[v] + a.valor() + tiempos[a.hasta()]) {
        dist[w] = dist[v] + a.valor() + tiempos[a.hasta()];
        pq.update(w, dist[w]);
    }
}
public:
    Dijkstra(DigrafoValorado<int> const&g, vector<int>const& t) : origen(0), dist(g.V(), INF), pq(g.V()), tiempos(t) {
        dist[origen] = tiempos[0];
        pq.push(origen, tiempos[0]);
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

    int n; cin >> n;
    if (n == 0) return false;

    vector<int>tiempos_de_carga(n);

    for (int i = 0; i < n; i++) 
        cin >> tiempos_de_carga[i];

    DigrafoValorado<int>grafo(n);

    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        grafo.ponArista({a - 1, b - 1, c});
    }

    Dijkstra d(grafo, tiempos_de_carga);

    if (d.hayCamino(n - 1)) cout << d.distancia(n - 1) << "\n";
    else cout << "IMPOSIBLE\n";


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

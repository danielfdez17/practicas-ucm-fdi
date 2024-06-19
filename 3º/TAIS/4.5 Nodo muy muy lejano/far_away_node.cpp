
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_set>
#include "Grafo.h"
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

class solution {
private:
    struct tsol {
        int node;
        int ttl;
    };
    Grafo g;
    int nodes;
public:
    solution(Grafo const&g) : g(g), nodes(g.V()) {}

    int query(int node, int ttl) {
        int unreachable = nodes - 1;
        queue<int>q;
        q.push(node);
        vector<bool>visited(nodes, false);
        visited[node] = true;
        vector<int>ttl_remaining(nodes);
        ttl_remaining[node] = ttl;
        while(!q.empty()) {
            int front = q.front(); q.pop();
            for (int i = 0; i < g.ady(front).size(); ++i) {
                int w = g.ady(front)[i];
                if (!visited[w] && ttl_remaining[front] > 0) {
                    visited[w] = true;
                    ttl_remaining[w] = ttl_remaining[front] - 1;
                    --unreachable;
                    if (ttl_remaining[front] > 0)
                        q.push(w);
                }
            }
        }
        return unreachable;
    }

    // int query(Grafo const&g, int node, int ttl) {
    //     unreachable = nodes - 1;
    //     vector<bool>visited(nodes, false);
    //     queue<tsol>q;
    //     visited[node] = true;
    //     q.push({node, ttl});
    //     while (!q.empty()) {
    //         tsol front = q.front(); q.pop();
    //         for (int w : g.ady(front.node)) {
    //             if (front.ttl > 0 && unreachable > 0) {
    //                 if (!visited[w]) {
    //                     visited[w] = true;
    //                     --unreachable;
    //                 }
    //                 q.push({w, front.ttl - 1});
    //             }
    //         }
    //     }
    //     return unreachable;
    // }
};

bool resuelveCaso() {
    int n, c; cin >> n >> c;
    if (!cin) return false;
    Grafo g(n);
    while (c--) {
        int u, v; cin >> u >> v;
        g.ponArista(u - 1, v - 1);
    }
    int k; cin >> k;
    solution sol(g);
    while (k--) {
        int node, ttl; cin >> node >> ttl;
        cout << sol.query(node - 1, ttl) << "\n";
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

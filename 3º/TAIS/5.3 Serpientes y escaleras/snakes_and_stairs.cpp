
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include "Digrafo.h"
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

class SS {
private:
    int movements;
    void bfs(Digrafo const&dg, int k, int source, int destination) {
        vector<bool>visited(dg.V(), false);
        vector<int>dist(dg.V(), 0);
        visited[source] = true;
        queue<int>q;
        q.push(source);
        while (!q.empty()) {
            int front = q.front(); q.pop();
            int cont = 0;
            while (cont < k) {
                int w = front + cont + 1;
                if (!dg.ady(w).empty()) 
                    w = dg.ady(w)[0];
                if (w == destination) {
                    movements = dist[w] = dist[front] + 1;
                    break;
                }
                if (!visited[w]) {
                    visited[w] = true;
                    dist[w] = dist[front] + 1;
                    q.push(w);
                }
                ++cont;
            }
        }
    }
public: 
    SS(Digrafo const&dg, int k) : movements(0) {
        bfs(dg, k, 0, dg.V() - 1);
    }
    int getMovements() const { return movements; }
};

bool resuelveCaso() {
    int n, k, s, e; cin >> n >> k >> s >> e;
    if (n == 0 && k == 0 && s == 0 && e == 0) return false;
    Digrafo dg(n * n);
    for (int i = 0; i < s + e; ++i) {
        int a, b; cin >> a >> b;
        dg.ponArista(a - 1, b - 1);
    }
    SS ss(dg, k);
    cout << ss.getMovements() << "\n";
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

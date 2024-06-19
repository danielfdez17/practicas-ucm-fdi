
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include"Grafo.h"
using namespace std;
const int INF = std::numeric_limits<int>::max();


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
    int cheaperPrice;
    vector<int>queries;
    // vector<bool>visited;
    void bfs(Grafo const&g, vector<int>const&supermarkets, int s) {
        queue<int>q;
        q.push(s);
        queries[s] = min(queries[s], supermarkets[s]);
        // cheaperPrice = min(INF, supermarkets[s]);
        vector<bool>visited(g.V(), false);
        visited[s] = true;
        while (!q.empty()) {
            int front = q.front(); q.pop();
            for (int w : g.ady(front)) {
                if (!visited[w]) {
                    visited[w] = true;
                    q.push(w);
                    queries[w] = min(queries[w], supermarkets[front]);
                    // cheaperPrice = min(cheaperPrice, supermarkets[w]);
                }
            }
        }
    }
    // void query(int s, vector<int>const&supermarkets) {
    // }
public:
    solution(Grafo const&g, vector<int>const&supermarkets) : queries(g.V(), INF) {
        for (int i = 0; i < g.V(); ++i) {
            bfs(g, supermarkets, i);
        }
    }
    // void print(int s, vector<int>const&supermarkets) {
    //     query(s, supermarkets);
    //     if (cheaperPrice == INF)
    //         cout << "MENUDO MARRON\n";
    //     else 
    //         cout << cheaperPrice << "\n";
    // }
    void printSol(int node) const {
        if (queries[node] == INF) 
            cout << "MENUDO MARRON\n";
        else
            cout << queries[node] << "\n";
    }
};

bool resuelveCaso() {
    int n, c; cin >> n >> c;
    if (!cin) return false;
    Grafo g(n);
    for (int i = 0; i < c; ++i) {
        int a, b; cin >> a >> b;
        --a; --b;
        g.ponArista(a, b);
    }
    int s; cin >> s;
    vector<int>supermarkets(n, INF);
    for (int i = 0; i < s; ++i) {
        int node, price; cin >> node >> price;
        --node;
        supermarkets[node] = price;
    }
    int k; cin >> k;
    solution sol(g, supermarkets);
    for (int i = 0; i < k; ++i) {
        cin >> s;
        sol.printSol(s - 1);
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

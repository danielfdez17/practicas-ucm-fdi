
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include"Grafo.h"
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

class WOF {
private:
    vector<bool>visited;
    int goldAmount;
    int getAmount(Grafo const&g, vector<int>const&gold, int s) {
        int amount = gold[s];
        queue<int>q;
        q.push(s);
        visited[s] = true;
        while (!q.empty()) {
            int front = q.front(); q.pop();
            for (int w : g.ady(front)) {
                if (!visited[w]) {
                    visited[w] = true;
                    q.push(w);
                    amount = min(amount, gold[w]);
                }
            }
        }
        return amount;
    }
public:
    WOF(Grafo const&g, vector<int>const&gold) : visited(g.V(), false), goldAmount(0) {
        for (int i = 0; i < g.V(); ++i) {
            if (!visited[i]) {
                goldAmount += getAmount(g, gold, i);
            }
        }
    }
    int getTotalAmount() const {
        return goldAmount;
    }
};

bool resuelveCaso() {
    int n, m; cin >> n >> m;
    if (!cin) return false;
    
    vector<int>gold(n);
    for (int&i : gold) 
        cin >> i;

    Grafo g(n);
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        g.ponArista(a - 1, b - 1);
    }

    WOF wof(g, gold);

    cout << wof.getTotalAmount() << "\n";

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

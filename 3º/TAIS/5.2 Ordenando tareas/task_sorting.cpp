
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include"Digrafo.h"
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

class sortingTasks {
private:
    vector<int>visited, stacked;
    bool cycle;
    deque<int>path;

    void dfs(Digrafo const&dg, int v) {
        stacked[v] = visited[v] = true;
        for (int w : dg.ady(v)) {
            if (cycle) return;
            if (!visited[w]) {
                dfs(dg, w);
            } else if (stacked[w]) {
                cycle = true;
            }
        }
        stacked[v] = false;
        path.push_back(v + 1);
    }
public:
    sortingTasks(Digrafo const&dg) : visited(dg.V(), false), stacked(dg.V(), false), cycle(false) {
        for (int v = 0; v < dg.V(); ++v) {
            if (!visited[v]) {
                dfs(dg, v);
            }
        }
    }
    bool existingCycle() const { return cycle; }
    deque<int> getPath() const { return path; }
};

bool resuelveCaso() {
    int n; cin >> n;
    if (!cin) return false;
    int m; cin >> m;
    Digrafo dg(n);
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        dg.ponArista(a - 1, b - 1);
    }
    sortingTasks tasks(dg);
    if (tasks.existingCycle()) 
        cout << "Imposible\n";
    else {
        for (int p : tasks.getPath())
            cout << p << " ";
        cout << "\n";
    }
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


/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"
using namespace std;

#define INF 1000001

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

void dfs(GrafoValorado<int> const& grafo, vector<bool>&visitados, int v, int destino, int anchura, bool&se_puede) {
    visitados[v] = true;
    for (auto arista : grafo.ady(v)) {
        if (arista.valor() >= anchura) {
            int w = arista.otro(v);
            if (w == destino) se_puede = true;
            if (!visitados[w]) dfs(grafo, visitados, w, destino, anchura, se_puede);
        }
    }
}

bool resuelveCaso() {

    int vertices; cin >> vertices;
    if (!cin) return false;

    GrafoValorado<int> grafo(vertices);
    int aristas; cin >> aristas;
    for (int i = 0; i < aristas; i++) {
        int a, b, c; cin >> a >> b >> c;
        grafo.ponArista(Arista(a - 1, b - 1, c));
    }
    int queries; cin >> queries;
    for (int i = 0; i < queries; i++) {
        int a, b, c; cin >> a >> b >> c;
        vector<bool> visitados(vertices, false);
        bool se_puede = false;
        dfs(grafo, visitados, a - 1, b - 1, c, se_puede);
        cout << (se_puede ? "SI\n" : "NO\n" );
    }
    // cout << "\n";
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

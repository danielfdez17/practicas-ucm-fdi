
/*@ <answer>
 *
 * Nombre y Apellidos: Daniel Fernandez Ortiz
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
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

int dfs(int v, vector<bool>&visitados, Grafo const& g) {
    int tam = 1; visitados[v] = true;
    for (int i : g.ady(v)) 
        if (!visitados[i]) 
            tam += dfs(i, visitados, g);
    return tam;
}

void resuelveCaso() {
    int vertices, aristas; cin >> vertices >> aristas;
    Grafo g(vertices);

    vector<bool>visitados(vertices, false);

    for (int i = 0; i < aristas; i++) {
        int a, b; cin >> a >> b;
        g.ponArista(a - 1, b - 1);
    }
    int tam = 0;
    for (int i = 0; i < vertices; i++) {
        if (!visitados[i]) 
            tam = max(tam, dfs(i, visitados, g));
    }

    cout << tam << "\n";


}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("casos.txt");
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
   
   int numCasos;
   cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}

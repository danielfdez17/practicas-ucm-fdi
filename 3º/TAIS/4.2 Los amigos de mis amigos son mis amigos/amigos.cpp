
/*@ <answer>
 *
 * Nombre y Apellidos: Daniel Fernandez Ortiz
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int MAX_CIUDADES = 20000, MAX_AMIGOS = 200000;

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int dfs(int v, vector<bool>&visitados, vector<vector<int>>const&matriz) {
    int tam = 1; visitados[v] = true;
    for (int i : matriz[v]) 
        if (!visitados[i]) 
            tam += dfs(i, visitados, matriz);
    return tam;
}

void resuelveCaso() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>>matriz(n, vector<int>(0));
    vector<bool>visitados(n, false);
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        matriz[a - 1].push_back(b - 1);
        matriz[b - 1].push_back(a - 1);
    }
    int tam = 0;
    for (int i = 0; i < n; i++)
        if (!visitados[i]) 
            tam = max(tam, dfs(i, visitados, matriz));
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

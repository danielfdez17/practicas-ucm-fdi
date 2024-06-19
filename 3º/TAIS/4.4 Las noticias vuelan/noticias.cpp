
/*@ <answer>
 *
 * Nombre y Apellidos: Daniel Fernandez Ortiz
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
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

class noticia {
   private:
   vector<bool>visitados, ya_contado;
   vector<int>conocidos;
   int dfs(Grafo const& g, int v) {
      visitados[v] = true;
      int tam = 1;
      for (int w : g.ady(v))
         if (!visitados[w])
            tam += dfs(g, w);
      return tam;
      
   }
   public:
   noticia(Grafo const& g) : visitados(g.V(), false), ya_contado(g.V(), false), conocidos(g.V(), 0) {
      for (int i = 0; i < g.V(); i++) {
         if (!visitados[i]) {
            int amigos = dfs(g, i);
            for (int j = 0; j < visitados.size(); j++) {
               if (visitados[j] && !ya_contado[j]) {
                  conocidos[j] = amigos;
                  ya_contado[j] = true;
               }
            }
         }
      }
   }
   vector<int>getConocidos() {
      return conocidos;
   }
};

// int bfs(Grafo const& g, int v) {
//    queue<int>cola;
//    cola.push(v);
//    vector<bool>visitados(g.V(), false);
//    visitados[v] = true;
//    int adyacentes = 1;
//    while (!cola.empty()) {
//       int front = cola.front(); cola.pop();
//       for (int w : g.ady(front)) {
//          if (!visitados[w]) {
//             cola.push(w);
//             visitados[w] = true;
//             adyacentes++;
//          }
//       }
//    }
//    return adyacentes;
// }

// int dfs(Grafo const& g, int v, vector<bool>&visitados) {
//    int tam = 1;
//    visitados[v] = true;
//    for (int w : g.ady(v)) 
//       if (!visitados[w])
//          tam += dfs(g, w, visitados);
//    return tam;
// }


bool resuelveCaso() {
   int vertices, aristas; cin >> vertices >> aristas;   
   if (!cin) return false;

   Grafo g(vertices);
   // cin.ignore();

   for (int i = 0; i < aristas; i++) {
      int size; cin >> size;
      if (size != 0) {
         int a, b; cin >> a;
         for (int j = 0; j < size - 1; j++) {
            cin >> b;
            g.ponArista(a - 1, b - 1);
            a = b;
         }
      }
      // string linea; getline(cin, linea);
      // stringstream ss(linea);
      // int usuarios, nodo;
      // ss >> usuarios;
      // vector<int>v;
      // while (ss >> nodo) {
      //    v.push_back(nodo);
      // }
      // for (int j = 0; j < usuarios; j++) {
      //    for (int k = j + 1; k < usuarios; k++) {
      //       g.ponArista(v[j] - 1, v[k] - 1);
      //    }
      // }
   }
   noticia n(g);
   for (int i : n.getConocidos()) 
      cout << i << " ";
   // for (int i = 0; i < vertices; i++) {
   //    vector<bool>visitados(vertices, false);
   //    cout << dfs(g, i, visitados) << " ";
   //    // cout << bfs(g, i) << " ";
   // }
   cout << "\n";



   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("casos.txt");
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}

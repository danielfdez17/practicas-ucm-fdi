
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la solución.
 * Daniel Fernandez Ortiz - TAIS21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#define MAX_BOTONES 3
#define MODULO 10000
#define LIMITE 1e9


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int siguiente(int num, int i) {
   switch(i) {
      case 0: num++; break;
      case 1: num *= 2; break;
      case 2: num /= 3; break;
   }
   return num % MODULO;
}

int bfs(int origen, int destino) {
   if (origen == destino) return 0;
   vector<bool>visitados(MODULO, false);
   vector<int>dist(MODULO, LIMITE);
   dist[origen] = 0; visitados[origen] = true;
   queue<int>cola; cola.push(origen);
   while (!cola.empty()) {
      int v = cola.front(); cola.pop();
      for (int i = 0; i < MAX_BOTONES; i++) {
         int sig = siguiente(v, i);
         if (sig == destino) return dist[v] + 1;
         if (!visitados[sig]) {
            visitados[sig] = true;
            dist[sig] = dist[v] + 1;
            cola.push(sig);
         }
      }
   }
   return 0;
}


bool resuelveCaso() {

   int origen, destino; cin >> origen >> destino;
   if (!std::cin) return false;

   cout << bfs(origen, destino) << "\n";

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

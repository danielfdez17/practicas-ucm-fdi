
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"
#include "Matriz.h"
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

struct cordel {
   int longitud, coste;
};

struct sol {
   long long int maneras;
   EntInf cordeles;
   EntInf coste;
};

long long combinaciones(int c, int l, vector<cordel>const&cordeles, Matriz<long long>&matriz) {
   // cordel inexistente
   if (c == -1) return 0;
   // longitud objetivo es cero
   if (l == 0) return 1;
   // cordel inexistente && longitud objetivo es cero
   if (c == -1 && l == 0) return 1;
   // si ya esta resuelto
   if (matriz[c][l] != -1) return matriz[c][l];

   // si la longitud del cordel c es mayor que la objetivo, se llama con el siguiente cordel
   if (cordeles[c].longitud > l) 
      return matriz[c][l] = combinaciones(c - 1, l, cordeles, matriz);
   // en caso contrario, se llama con el siguiente cordel y la longitud objetivo mas la llamada
   // al siguiente cordel y la longitud objetivo menos la longitud del cordel c
   // resumen: combinaciones en las que se usa el cordel c mas las que no
   return matriz[c][l] = combinaciones(c - 1, l, cordeles, matriz) + 
      combinaciones(c - 1, l - cordeles[c].longitud, cordeles, matriz);
}

EntInf nCuerdasMinimas(int c, int l, vector<cordel>const&cordeles, Matriz<EntInf>&matriz) {
   if (c == -1) return EntInf(Infinito);
   if (l == 0) return EntInf();
   if (c == -1 && l == 0) return EntInf();
   if (matriz[c][l] != -1) return matriz[c][l];

   if (cordeles[c].longitud > l)
      return matriz[c][l] = nCuerdasMinimas(c - 1, l, cordeles, matriz);
   
   return matriz[c][l] = min(nCuerdasMinimas(c - 1, l, cordeles, matriz), 
      nCuerdasMinimas(c - 1, l - cordeles[c].longitud, cordeles, matriz) + 1);
}
EntInf minCoste(int c, int l, vector<cordel>const&cordeles, Matriz<EntInf>&matriz) {
   if (c == -1) return EntInf(Infinito);
   if (l == 0) return EntInf();
   if (c == -1 && l == 0) return EntInf();
   if (matriz[c][l] != -1) return matriz[c][l];

   if (cordeles[c].longitud > l)
      return matriz[c][l] = nCuerdasMinimas(c - 1, l, cordeles, matriz);
   
   return matriz[c][l] = min(nCuerdasMinimas(c - 1, l, cordeles, matriz), 
      nCuerdasMinimas(c - 1, l - cordeles[c].longitud, cordeles, matriz) + cordeles[c].coste);
}

sol resolver(int longitud, vector<cordel>const&cordeles) {
   int filas = cordeles.size() + 1, columnas = longitud + 1;
   Matriz<long long int>matriz_combi(filas, columnas, -1);
   long long int maneras = combinaciones(cordeles.size() - 1, longitud, cordeles, matriz_combi);
   if (maneras == 0) return {0, EntInf(), EntInf()};
   Matriz<EntInf>matriz_cuerdas(filas, columnas, -1);
   Matriz<EntInf>matriz_coste(filas, columnas, -1);
   return {maneras, nCuerdasMinimas(cordeles.size() - 1, longitud, cordeles, matriz_cuerdas),  
      minCoste(cordeles.size() - 1, longitud, cordeles, matriz_coste)};
}

bool resuelveCaso() {
   int n, l; cin >> n >> l;
   if (!std::cin) return false;
   vector<cordel>cordeles(n);
   for (int i = 0; i < n; ++i) {
      int longitud, coste; cin >> longitud >> coste;
      cordeles[i] = {longitud, coste};
   }
   sol s = resolver(l, cordeles);
   if (s.maneras == 0) cout << "NO\n";
   else cout << "SI " << s.maneras << " " << s.cordeles << " " << s.cordeles << "\n";

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

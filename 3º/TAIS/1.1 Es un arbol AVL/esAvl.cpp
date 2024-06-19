/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Arbin.h"
#include<climits>
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

struct tsol {
    bool isAVL;
    int height;
    int maxLeft;
    int minRight;
};

tsol solve(Arbin<int>const&tree) {
   if (tree.esVacio()) 
      return {true, 0, 0, 0};
   tsol left = solve(tree.hijoIz());
   bool isLeftEmpty = tree.hijoIz().esVacio(), 
         isRightEmpty = tree.hijoDr().esVacio();
   if (left.isAVL) {
      tsol right = solve(tree.hijoDr());
      tsol sol;
      sol.isAVL = left.isAVL && 
                  right.isAVL && 
                  abs(left.height - right.height) <= 1 && 
                  (isLeftEmpty || left.maxLeft < tree.raiz()) &&
                  (isRightEmpty || tree.raiz() < right.minRight);
      sol.height = max(left.height, right.height) + 1;
      sol.maxLeft = (isLeftEmpty ? tree.raiz() : left.maxLeft);
      sol.minRight = (isRightEmpty ? tree.raiz() : right.minRight);
      return sol;
   }
   return {false, 0, 0, 0};
}


void resuelveCaso() {

    Arbin<int> tree = Arbin<int>::leerArbolInorden();

    cout << (solve(tree).isAVL ? "SI\n" : "NO\n");


}

//@ </answer>

int main() {
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();

#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}

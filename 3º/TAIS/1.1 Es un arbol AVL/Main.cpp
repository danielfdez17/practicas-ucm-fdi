
/*@ <answer>
 *
 * Nombre y Apellidos: Daniel Fernandez Ortiz
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "Arbin.h"
#include<climits>
using namespace std;

/*@ <answer>
  
 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 En el caso peor (el arbol es AVL), el coste del algoritmo es lineal en el numero de nodos que tiene el arbol, ya que hay que recorrerlo entero
 En el caso mejor (el hijo izquierdo del arbol no es AVL, y por tanto el arbol tampoco), el coste del algoritmo es logaritmico en el numero de nodos del arbol, ya que solo se recorre el hijo izquierdo (y no tiene por que recorrerse entero)
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct tsol {
    bool es_avl;
    int altura;
    int max_izq;
    int min_der;
    tsol() : es_avl(true), altura(0), max_izq(0), min_der(0)  {}
    tsol(bool avl, int h, int max, int min) : es_avl(avl), altura(h), max_izq(max), min_der(min) {}
};

tsol esAVL(const Arbin<int>&arbol) {
   if (arbol.esVacio()) return tsol();
   auto [el, hl, ml, Ml] = esAVL(arbol.hijoIz());
   if (el) {
      auto [er, hr, mr, Mr] = esAVL(arbol.hijoDr());
      return {el && er && abs(hl - hr) <= 1 && (arbol.hijoIz().esVacio() || Ml < arbol.raiz()) && (arbol.hijoDr().esVacio() || arbol.raiz() < mr), 
         max(hl, hr) + 1,
         arbol.hijoIz().esVacio() ? arbol.raiz() : ml,
         arbol.hijoDr().esVacio() ? arbol.raiz() : Mr};
   }
   // tsol i = esAVL(arbol.hijoIz());
   // if (i.es_avl) {
   //    tsol d = esAVL(arbol.hijoDr());
   //    return {d.es_avl && abs(i.altura - d.altura) <= 1 && (arbol.hijoIz().esVacio() || i.max_izq < arbol.raiz()) && (arbol.hijoDr().esVacio() || arbol.raiz() < d.min_der),
   //       max(i.altura, d.altura) + 1, 
   //       arbol.hijoIz().esVacio() ? arbol.raiz() : i.min_der, 
   //       arbol.hijoDr().esVacio() ? arbol.raiz() : d.max_izq};
   // }
   return {false, 0, 0, 0};
}

void resuelveCaso() {
   
   Arbin<int>arbol = Arbin<int>::leerArbolInorden();

   cout << (esAVL(arbol).es_avl ? "SI\n" : "NO\n");

}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}

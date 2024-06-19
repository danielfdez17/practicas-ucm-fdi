
/*@ <answer>
 *
 * Nombre y Apellidos: Daniel Fernandez Ortiz
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>
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

bool resuelveCaso() {
   
   // leer los datos de la entrada
   int primer, parejas; cin >> primer >> parejas;
   if (primer == 0 && parejas == 0) return false;
   
   priority_queue<int, vector<int>, greater<int>> der;
   priority_queue<int> izq;
   int p1, p2;
   for (int i = 0; i < parejas; i++) {
    cin >> p1 >> p2;
    if (p1 < primer) izq.push(p1);
    else der.push(p1);
    if (p2 < primer) izq.push(p2);
    else der.push(p2);

    if (izq.size() > der.size()) {
        der.push(primer);
        primer = izq.top(); izq.pop();
    }
    else if (izq.size() < der.size()) {
        izq.push(primer);
        primer = der.top(); der.pop();
    }
    cout << primer << " ";
   }
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

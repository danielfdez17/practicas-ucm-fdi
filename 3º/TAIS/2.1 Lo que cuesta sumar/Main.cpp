
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

 Se van sacando los dos elementos mas prioritarios de la cola y se almacena el esfuerzo que 
 conlleva sumarlos, es decir, la suma de esos dos elementos
 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
   
   // leer los datos de la entrada
   int n; cin >> n;
   if (n == 0) return false;
   
   priority_queue<long long int, vector<long long int>, greater<long long int>>cola_p;
   for (int i = 0; i < n; i++) {
    int x; cin >> x;
    cola_p.push(x);
   }
   long long int esfuerzo = 0, suma = 0;

   while (cola_p.size() > 1) {
      // Se sacan y se suman los dos elementos mas prioritarios
      suma = cola_p.top();
      cola_p.pop();
      suma += cola_p.top();
      cola_p.pop();
      // Y se almacena en la cola el resultado de sumar los dos elementos sacados
      cola_p.push(suma);
      esfuerzo += suma;
   }

   cout << esfuerzo << "\n";
   // resolver el caso posiblemente llamando a otras funciones
   
   // escribir la solución

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

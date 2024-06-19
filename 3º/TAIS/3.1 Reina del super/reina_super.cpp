
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

struct tcliente {
    int tiempo;
    int numero;
    tcliente() : tiempo(0), numero(0) {}
    tcliente(int t, int n) : tiempo(t), numero(n) {}
};

bool operator>(tcliente const& a, tcliente const& b) {
    if (a.tiempo == b.tiempo) return a.numero > b.numero;
    return a.tiempo > b.tiempo;
}

bool resuelveCaso() {
   
   // leer los datos de la entrada
   int n, c; cin >> n >> c;
   if (n == 0 && c == 0) return false;

    priority_queue<tcliente, vector<tcliente>, greater<tcliente>>cola;
    int t = 0;

    for (int i = 0; i < c; i++) {
        cola.push({0, i + 1});
    }

   if (n > c) {
    cout << c + 1 << "\n";
    for (int i = 0; i < c; i++) cin >> t;
   }
   else {
    tcliente cliente;
    for (int i = 0; i < c; i++) {
        cin >> t;
        cliente = cola.top(); cola.pop();
        cliente.tiempo += t;
        cola.push(cliente);
    }
    cout << cola.top().numero << "\n";

   }
   
    
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

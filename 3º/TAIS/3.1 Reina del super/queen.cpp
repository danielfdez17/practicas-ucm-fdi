
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
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

struct client {
    int time;
    int cashier;
};

bool operator<(client const&b, client const&a) {
    if (a.time == b.time)
        a.cashier < b.cashier;
    return a.time < b.time;
}

bool resuelveCaso() {
    int n, c; cin >> n >> c;
    if (n == 0 && c == 0) return false;
    priority_queue<client>q;
    for (int i = 0; i < n; ++i)
        q.push({0, i});
    for (int i = 0; i < c; ++i) {
        int x; cin >> x;
        client top = q.top(); q.pop();
        top.time += x;
        q.push(top);
    }
    cout << q.top().cashier + 1 << "\n";

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

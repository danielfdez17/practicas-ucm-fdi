
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

struct tsol {
    int id;
    int period;
    int time;
};

bool operator<(tsol const&a, tsol const&b) {
    if (a.time == b.time)
        return a.id > b.id;
    return a.time > b.time;
}

bool resuelveCaso() {
    int users; cin >> users;
    if (users == 0) return false;
    priority_queue<tsol>q;
    for (int i = 0; i < users; ++i) {
        int id, period; cin >> id >> period;
        q.push({id, period, period});
    }
    int k; cin >> k;
    while (k--) {
        tsol top = q.top(); q.pop();
        top.time += top.period;
        q.push(top);
        cout << top.id << "\n";
    }
    cout << "---\n";
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

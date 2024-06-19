
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;
using lli = long long int;


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
    int N; cin >> N;
    if (N == 0) return 0;
    priority_queue<lli, vector<lli>, greater<lli>>q;
    for (int i = 0; i < N; ++i) {
        int x; cin >> x;
        q.push(x);
    }
    lli sum = 0;
    while (q.size() > 1) {
        lli aux = q.top(); q.pop();
        aux += q.top(); q.pop();
        sum += aux;
        q.push(aux);
    }
    cout << sum << "\n";
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

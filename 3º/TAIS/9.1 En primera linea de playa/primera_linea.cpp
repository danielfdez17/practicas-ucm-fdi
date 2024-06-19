
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

struct building {
    int beginning, end;
};
bool operator<(building const& left, building const& right) {
    return left.end < right.end;
}

bool resuelveCaso() {
    int n; cin >> n;
    if (n == 0) return false;

    vector<building> buildings(n);

    for (int i = 0; i < n; i++) {
        int w, e; cin >> w >> e;
        buildings[i] = {w, e};
    }

    sort(buildings.begin(), buildings.end());

    int total_tunnels = 1, last_building_end = buildings[0].end;
    for (int i = 1; i < n; i++) {
        if (buildings[i].beginning >= last_building_end) {
            ++total_tunnels;
            last_building_end = buildings[i].end;
        }
    }

    cout << total_tunnels << "\n";

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

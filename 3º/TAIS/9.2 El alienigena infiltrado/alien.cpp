
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

struct interval {
    int beginning, end;
};
bool operator<(interval const& left, interval const& right) {
    return left.beginning < right.beginning;
}

bool resuelveCaso() {
    int b, e, n; cin >> b >> e >> n;
    if (b == 0 && e == 0 && n == 0) return false;

    vector<interval> tasks(n);

    for (int i = 0; i < n; i++) {
        int start, end; cin >> start >> end;
        tasks[i] = {start, end};
    }

    sort(tasks.begin(), tasks.end());

    int last_beginnig = b, min_tasks = 0;
    bool possible = true;
    int i = 0, best_end;

    // while interval not completely covered
    while (possible && last_beginnig < e) {
        best_end = -1;
        // if the interval can not be fully covered
        if (i >= n || tasks[i].beginning > last_beginnig) possible = false;
        while (possible && i < n && tasks[i].beginning <= last_beginnig) {
            // if exists a task whose end is the latest
            if (tasks[i].end > last_beginnig && tasks[i].end > best_end) 
                best_end = tasks[i].end;
            i++;
        }
        if (best_end == -1) possible = false;
        last_beginnig = best_end;
        ++min_tasks;
    }

    if (possible) cout << min_tasks << "\n";
    else cout << "Imposible\n";

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

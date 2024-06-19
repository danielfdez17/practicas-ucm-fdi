
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
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
    int e;
    double coefficient;
    int votes;
    int index;
};

bool operator<(tsol const&a, tsol const&b) {
    if (a.coefficient == b.coefficient) {
        if (a.votes != b.votes)
            return a.votes < b.votes;
        return a.index > b.index;
    }
    return a.coefficient < b.coefficient;
}

bool resuelveCaso() {
    int C, N; cin >> C >> N;
    if (C == 0 && N == 0) return false;
    priority_queue<tsol>q;
    vector<int>sol(C, 0);
    for (int i = 0; i < C; ++i) {
        int votes; cin >> votes;
        q.push({0, votes * 1.0, votes, i});
    }
    while (N--) {
        tsol top = q.top(); q.pop();
        top.e++;
        top.coefficient = top.votes / (1.0 + top.e);
        sol[top.index]++;
        q.push(top);
    }
    for (int i : sol) 
        cout << i << " "; cout << "\n";
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


/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#define MODULO 1000000007
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 maneras(i) = maneras de llegar desde el pivote i hasta el N
 maneras(i) = 
 maneras(N) = 1
 

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

long long int maneras(int pivotes, int saltos) {
    vector<long long int> dp(pivotes, 0);
    dp[pivotes - 1] = 1;
    for (int i = pivotes - 2; i >= 0; --i) {
        int k = 1;
        while (k <= saltos + 1 && i + k < pivotes) {
            dp[i] = (dp[i] + dp[i + k]) % MODULO;
            ++k;
        }
    }
    return dp[0];
}

bool resuelveCaso() {
    int pivotes, saltos; cin >> pivotes >> saltos;
    if (pivotes == 0 && saltos == 0) return false;
    cout << maneras(pivotes, saltos) << "\n";
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

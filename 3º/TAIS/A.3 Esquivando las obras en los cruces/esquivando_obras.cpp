
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 caminos(i, j) = nº de caminos distintos hasta llegar a la posicion calles[n - 1][m - 1]
 
 caminos(i, j) = {0 <=> i, j < 0 || i >= n || j >= m || calles[i][j] = 'X'}
 caminos(i, j) = {caminos(i + 1, j) + caminos(i, j + 1) <=> en otro caso}

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    int n, m; cin >> n >> m;
    if (!cin) return false;

    vector<int>dp(m, 0);
    dp[0] = 1;
    char c;
    // BOTTOM-UP
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> c;
            // Se encuentra en una obra
            if (c == 'X') {
                dp[j] = 0;
            }
            // Los caminos actuales + (0 si la siguiente calle esta fuera de los limites || los caminos de la siguiente calle)
            else {
                dp[j] += (j - 1 < 0 ? 0 : dp[j - 1]);
            }
        }
    }
    cout << dp[m - 1] << "\n";

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

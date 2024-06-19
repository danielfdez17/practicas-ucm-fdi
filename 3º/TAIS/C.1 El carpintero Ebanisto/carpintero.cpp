
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include"EnterosInf.h"
#define INF 1000000000


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 minEsfuerzo(i, j) = minimo esfuerzo para cortar la tabla entre los puntos i y j, no incluidos
 minEsfuerzo(i, j) = (minEsfuerzo(i, k) + minEsfuerzo(k, j)) + 2 * (cortes[j] - cortes[i]), con i < k < j
 minEsfuero(i, i + 1) = 0
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

EntInf minEsfuerzo(vector<int>const&cortes) {
    int n = cortes.size();
    vector<vector<EntInf>>dp(n, vector<EntInf>(n, 0));
    for (int diagonal = 2; diagonal < n; ++diagonal) {
        for (int i = 0; i < n - diagonal; ++i) {
            int j = i + diagonal;
            dp[i][j] = INF;
            for (int k = i + 1; k < j; ++k) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + 2 * (cortes[j] - cortes[i]));
            }
        }
    }
    return dp[0][n - 1];
}

bool resuelveCaso() {

    int L, N; cin >> L >> N;
    if (L == 0 && N == 0) return false;
    vector<int>cortes;
    cortes.push_back(0);
    for (int i = 0; i < N; ++i) {
        int x; cin >> x; cortes.push_back(x);
    }
    cortes.push_back(L);

    cout << minEsfuerzo(cortes) << "\n";

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

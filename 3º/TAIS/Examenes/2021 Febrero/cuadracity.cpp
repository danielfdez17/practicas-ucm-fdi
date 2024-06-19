
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

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool ok(int i, int j, int n, int m) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

int countWays(vector<vector<char>>cuadracity, vector<vector<int>>&dp) {
    int n = cuadracity.size(), m = cuadracity[0].size();

    dp[0][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int upper = 0, left = 0;
            if (ok(i - 1, j, n, m) && cuadracity[i - 1][j] == '.')
                upper = dp[i - 1][j];
            if (ok(i, j - 1, n, m) && cuadracity[i][j - 1] == '.')
                left = dp[i][j - 1];
            dp[i][j] += upper + left;
        }
    }

    return dp[n - 1][m - 1];
}


bool resuelveCaso() {
    int n, m; cin >> n >> m;
    if (!cin) return false;

    vector<vector<char>>cuadracity(n, vector<char>(m));
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> cuadracity[i][j];
        }
        cin.ignore(1, '\n');
    }

    cout << countWays(cuadracity, dp) << "\n";


    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos2.txt");
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

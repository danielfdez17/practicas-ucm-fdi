
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

bool ok(int j, int n) {
    return 0 <= j &&  j < n;
}

bool resuelveCaso() {
    int n; cin >> n;
    if (!cin) return false;
    vector<int>dp(n, 0);
    int valor = 0, columna = 0;
    vector<vector<int>>matriz(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int arribaIzq = 0, arriba = 0, arribaDer = 0;
            int x; cin >> x;
            if (i != 0) {
                if (ok(j - 1, n)) arribaIzq = matriz[i - 1][j - 1];
                if (ok(j, n)) arriba = matriz[i - 1][j];
                if (ok(j + 1, n)) arribaDer = matriz[i - 1][j + 1];
            }
            matriz[i][j] = x + max(arriba, max(arribaIzq, arribaDer));
            if (matriz[i][j] > valor) {
                valor = matriz[i][j];
                columna = j + 1;
            }
        }
    }
    cout << valor << " " << columna << "\n";
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

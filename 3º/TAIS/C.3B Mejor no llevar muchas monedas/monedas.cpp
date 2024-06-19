
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 minMonedas(i, j) = minimo numero de monedas para pagar la cantidad j con las monedas disponibles del 1 a la i
 minMonedas(i, j) = minMonedas(i - 1, j - valores[i] * k) + k, 0 <= k <= cantidades[i] * valores[i]
 minMonedas(0, j) = Infinito
 minMonedas(i, 0) = 0

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct moneda{
    int valor, cantidad;
};

EntInf minMonedas(vector<moneda>const&monedas, int precio) {
    int n = monedas.size();
    vector<EntInf>dp(precio + 1, Infinito);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = precio; j > 0; --j) {
            int k = 0;
            while (k <= monedas[i - 1].cantidad && k * monedas[i - 1].valor <= j) {
                dp[j] = min(dp[j], dp[j - k * monedas[i - 1].valor] + k);
                ++k;
            }
        }
    }
    return dp[precio];
}

bool resuelveCaso() {
    int N; cin >> N;
    if (!cin) return false;
    vector<moneda>monedas(N);
    for (int i = 0; i < N; ++i) {
        cin >> monedas[i].valor;
    }
    for (int i = 0; i < N; ++i) {
        cin >> monedas[i].cantidad;
    }
    int precio; cin >> precio;

    EntInf minimo = minMonedas(monedas, precio);
    if (minimo != Infinito) 
        cout << "SI " << minimo << "\n";
    else
        cout << "NO\n";
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

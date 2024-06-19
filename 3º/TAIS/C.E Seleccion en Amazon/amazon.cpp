/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la solución.
 * Luis Rebollo Cocera: TAIS53
 * Daniel Fernandez Ortiz: TAIS21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"
using namespace std;

#define MAX_CANTIDAD 10000
#define MAX_MONEDAS 50
#define INF 1000000000

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

//  minMonedas(i, C) = {monedas, formas}
//  minMonedas(i, C) = min(minMonedas(i, C - monedas[i]), minMonedas(i - 1, C - monedas[i]))
//  minMonedas(i, 0) = {0, 1}
//  minMonedas(0, C) = {0, 0}

 minMonedas(i, C) = minimo numero de monedas y de formas de pagar la cantidad C con las monedas de la 1 a la i
 minMonedas(i, j) = {minMonedas(i - 1, j), minMonedas(i - 1, j)} si monedas[i] > C
                    {min(minMonedas(i - 1, j), minMonedas(i, j - monedas[i]) + 1), 
                        minMonedas(i - 1, j) * m1 + minMonedas(i, j - monedas[i]) * m2} si monedas[i] <= C
 minMonedas(0, j) = {Infinito, 0}
 minMonedas(i, 0) = {0, 1}


 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct tsol {
    int monedas, formas;
};

int minMonedas(vector<int>const&monedas, int cantidad) {
    int n = monedas.size();
    vector<EntInf>dpMonedas(cantidad + 1, Infinito);
    vector<int>dpFormas(cantidad + 1, 0);
    dpMonedas[0] = 0;
    dpFormas[0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = monedas[i]; j <= cantidad; ++j) {
            EntInf minimo = min(dpMonedas[j], dpMonedas[j - monedas[i]] + 1);
            int m1 = ((minimo == dpMonedas[j]) ? 1 : 0);
            int m2 = ((minimo == dpMonedas[j - monedas[i]] + 1) ? 1 : 0);
            dpFormas[j] = dpFormas[j] * m1 + dpFormas[j - monedas[i]] * m2;
            dpMonedas[j] = minimo;
        }
    }
    return dpFormas[cantidad];
}


// int minMonedas(vector<int>const& monedas, int cantidad) {
//     int n = monedas.size();
//     vector<int>dp(n, 0);
//     //dp[0] = 0;
//     int sol = 0;
//     bool dejarDeBuscar = false;
//     int minimo = INF;
//     for (int i = n - 1; i >= 0 && !dejarDeBuscar; --i) { // O(n^2)
//     int cantidad_aux = cantidad;
//         int j = i;
//         while (j >= 0 && cantidad_aux != 0 && !dejarDeBuscar) {
//             if (monedas[j] <= cantidad_aux) {
//                 dp[i]++;
//                 cantidad_aux -= monedas[j];
//             }
//             else 
//                 --j;
//             dejarDeBuscar = dp[i] > minimo;
//         }
//         if (cantidad_aux == 0 && dp[i] <= minimo) {
//             if (dp[i] == minimo) {
//                 ++sol;
//             }
//             else if (dp[i] < minimo) {
//                 sol = 1;
//                 minimo = dp[i];
//             }
//         }
//     }
//     return sol;
// }

bool resuelveCaso() {

    int cantidad, n; cin >> cantidad >> n;
    if (!std::cin) return false;
    vector<int>monedas(n);
    for (int i = 0; i < n; ++i) {
        cin >> monedas[i];
    }
    cout << minMonedas(monedas, cantidad) << "\n";


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
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
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 RECURRENCIA:
 caminos(i, j) = nº de caminos posibles para ir de (0, 0) hasta (n - 1, m - 1)

 caminos(i, j) = {0 si i || j se salen de los límites de la matriz}
               = {caminos(i, j + matriz[i][j]) + caminos(i + matriz[i][j], j)}

 caminos(i, j) = {1 si i == n - 1 && j == m - 1)

 COSTE EN TIEMPO: en el caso peor (matriz llena de unos) el coste es O(n*m) siendo n el numero de filas y m el numero de columnas
 COSTE EN ESPACIO ADICIONAL: O(n*m), porque utilizamos una matriz para guardar las combinaciones que ya se han calculado, para evitar calcular la misma combinacion mas veces de las necesarias
 TIPO DE PROGRAMACION DINAMICA: descendente, ya que la matriz se recorre de izquierda a derecha y de arriba a abajo de manera recursiva

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool ok(int i, int j, int n, int m) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

int recursivo(int i, int j, vector<vector<int>>& matriz, vector<vector<int>>&dp, int n, int m) {    
    if (dp[i][j] != -1) 
        return dp[i][j];

    if (i == n - 1 && j == m - 1)
        return 1;

    int sol = 0;
    int filas = i + matriz[i][j], columnas = j + matriz[i][j];
    if (ok(i, columnas, n, m)) sol += recursivo(i, columnas, matriz, dp, n, m);
    if (ok(filas, j, n, m)) sol += recursivo(filas, j, matriz, dp, n, m);
    dp[i][j] = sol;
    //return dp[i][j] = sol;
    return dp[i][j];
}

bool resuelveCaso() {

    int n, m; cin >> n >> m;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<vector<int>>matriz(n, vector<int>(m, 0)), dp(n, vector<int>(m, -1));
    //dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matriz[i][j];
            //cin >> dp[i][j];
            //int valor; cin >> valor;
            //if (ok(i + valor, j, n, m)) {
            //    dp[i + valor][j] += dp[i][j];
            //}
            //if (ok(i, j + valor, n, m)) {
            //    dp[i][j + valor] += dp[i][j];
            //}
        }
    }
    cout << recursivo(0, 0, matriz, dp, n, m) << "\n";

    //cout << dp[n - 1][m - 1] << "\n";


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

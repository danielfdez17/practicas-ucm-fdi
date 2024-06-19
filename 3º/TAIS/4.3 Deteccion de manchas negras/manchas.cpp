/*@ <answer>
 *
 * Nombre y Apellidos: Daniel Fernandez Ortiz
 *
 *@ </answer> */

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

const int MOVS = 4;

int movimientos[4][2] = {{0,1},{-1,0},{0,-1},{1,0}};

bool ok(int i, int j, int f, int c) {
    return 0 <= i && i < f && 0 <= j && j < c;
}

int dfs(int const& F, int const&C, int fila, int columna, vector<vector<char>>const&tablero, vector<vector<bool>>&visitados) {
    int tam = 1; visitados[fila][columna] = true;
    for (int i = 0; i < MOVS; i++) {
        int f = fila + movimientos[i][0], c = columna + movimientos[i][1];
        if (ok(f, c, F, C) && tablero[f][c] == '#' && !visitados[f][c])
            tam += dfs(F, C, f, c, tablero, visitados);
    }
    return tam;
}

bool resuelveCaso() {
   
   int filas, columnas; cin >> filas >> columnas;
   
   if (!cin) return false;

    vector<vector<char>>tablero(filas, vector<char>(columnas, ' '));
    vector<vector<bool>>visitados(filas, vector<bool>(columnas, false));

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cin >> tablero[i][j];
        }
    }
    int manchas = 0, max_tam = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (!visitados[i][j] && tablero[i][j] == '#') {
                max_tam = std::max(max_tam, dfs(filas, columnas, i, j, tablero, visitados));
                manchas++;
            }
        }
    }

    cout << manchas << " " << max_tam << "\n";


   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("casos.txt");
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}

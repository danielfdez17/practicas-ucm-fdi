
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include"Matriz.h"
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 palindromo(i, j) = nº minimo de letras que se necesitan añadir para que la plabra en el intervalo [i, j] 

 palindromo(i, j) = 0 si j <= i
 palindromo(i, j) = palindromo(i + 1, j - 1) si palabra[i] == palabra[j]
 palindromo(i, j) = min(palindromo(i + 1, j), palindromo(i, j - 1)) + 1 si palabra[i] != palabra[j]

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct tsol {
    int letras;
    string palindromo;
};

string palindromo(int i, int j, string palabra, Matriz<int>&dp) {
    // misma posicion
    if (i == j) 
        return string(1, palabra[i]);
    // fuera de rango
    if (i > j) 
        return ""; 
    // misma letra
    if (palabra[i] == palabra[j])
        return palabra[i] + palindromo(i + 1, j - 1, palabra, dp) + palabra[j];
    // ambas letras son consecutivas (con respecto a la j)
    if (dp[i][j] - 1 == dp[i][j - 1])
        return palabra[j] + palindromo(i, j - 1, palabra, dp) + palabra[j];
        
    // ambas letras son consecutivas (con respecto a la j)
    return palabra[i] + palindromo(i + 1, j, palabra, dp) + palabra[i];
}

int palindromo(string palabra, Matriz<int>&dp) {
    int size = palabra.size();
    for (int i = size - 2; i >= 0; --i) {
        for (int j = i + 1; j < size; ++j) {
            if (palabra[i] == palabra[j]) 
                dp[i][j] = dp[i + 1][j - 1];
            else
                dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
        }
    }
    return dp[0][size - 1];
}

tsol palindromo(string palabra) {
    int size = palabra.size();
    Matriz<int>dp(size, size, 0);
    int letras = palindromo(palabra, dp);
    if (letras != 0)
        palabra = palindromo(0, size - 1, palabra, dp);
    return {letras, palabra};
}

bool resuelveCaso() {
    string palabra; cin >> palabra;
    if (!cin) return false;

    tsol sol = palindromo(palabra);

    cout << sol.letras << " " << sol.palindromo << "\n";

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

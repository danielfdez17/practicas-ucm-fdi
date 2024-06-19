
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

 vacas(i, j) = maxima cantidad de comida que puede comer la vaca de los cubos i al j

 vacas(i, j) = canitdad[i]
 vacas(i, j) = 0 si j < i
 vacas(i, j) = max(cantidad[i + 1] > cantidad[j] ? vacas(i + 2, j) : vacas(i + 1, j - 1),
                    cantidad[i] < cantidad[j] ? vacas(i, j - 2) : vacas(i + 1, j - 1))
                    
    si la cantidad del siguiente cubo por la izq es mayor que el actual por la dcha,
        se come los dos siguientes cubos por la izq
    en otro caso, 
        ambas vacas pasan al siguiente cubo respectivamente

    si la cantidad del cubo i es menor que la cantidad del cubo j,
        se come los dos siguientes cubos por la dcha
    en otro caso,
        ambas vacas pasan al siguiente cubo respectivamente

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int vacas(vector<int>cubos) {
    int size = cubos.size();
    Matriz<int>dp(size, size, 0);
    for (int i = 0; i < size; ++i)
        dp[i][i] = cubos[i];
    int izquierda, derecha;
    for (int i = size - 2; i >= 0; --i) {
        for (int j = i + 1; j < size; ++j) {
            if (cubos[i + 1] > cubos[j]) 
                izquierda = dp[i + 2][j];
            else
                izquierda = dp[i + 1][j - 1];
            if (cubos[i] < cubos[j - 1])
                derecha = dp[i][j - 2];
            else
                derecha = dp[i + 1][j - 1];
            dp[i][j] = max(cubos[i] + izquierda, cubos[j] + derecha);
        }
    }
    return dp[0][size - 1];
}

bool resuelveCaso() {
    int n; cin >> n;
    if (n == 0) return false;
    vector<int>cubos(n);
    for (int i = 0; i < n; ++i) {
        cin >> cubos[i];
    }

    cout << vacas(cubos) << "\n";

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

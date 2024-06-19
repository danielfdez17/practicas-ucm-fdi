
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

 dianas(i, j) = nº minimo de dardos (1 hasta i) hasta conseguir la puntuacion j. Si no se puede, return INFINITO;
 dianas(i, j) = {dianas(i - 1, j) <=> puntuaciones[i] > j}
              = {min(dianas(i - 1, j), dianas(i, j - puntuaciones[i]) + 1) <=> puntuaciones[i] <= j}

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct solucion {
    EntInf nDardos;
    vector<int>dardos;
};

solucion dianasBottonUp(int v, int s, vector<int>const&sectores) {
    EntInf nDardos;
    vector<int>dardos;
    vector<EntInf>dp(v + 1, Infinito);
    dp[0] = 0;
    for (int i = 1; i <= s; ++i) {
        for (int j = sectores[i - 1]; j <= v; ++j) {
            dp[j] = min(dp[j], dp[j - sectores[i - 1]] + 1);
        }
    }
    nDardos = dp[v];

    if (nDardos == Infinito) return {nDardos, dardos};

    int i = s, j = v;
    while (j > 0) {
        // Se tira el dardo en el sector i - 1
        if (sectores[i - 1] <= j && dp[j] == dp[j - sectores[i - 1]] + 1) {
            // Se guarda la puntuacion del sector
            dardos.push_back(sectores[i - 1]);
            // Y se actualiza el valor objetivo
            j -= sectores[i - 1];
        }
        // Se prueba con el siguiente sector
        else {
            i--;
        }
    }

    return {nDardos, dardos};
}

bool resuelveCaso() {
    int v, s; cin >> v >> s;
    if (!cin) return false;
    vector<int>sectores(s);
    for (int i = 0; i < s; ++i) {
        cin >> sectores[i];
    }

    solucion sol = dianasBottonUp(v, s, sectores);

    if (sol.nDardos == Infinito) cout << "Imposible\n";
    else {
        cout << sol.nDardos << ": ";
        for (int i : sol.dardos) cout << i << " ";
        cout << "\n";
    }

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

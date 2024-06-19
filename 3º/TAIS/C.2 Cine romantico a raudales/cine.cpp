
/*@ <authors>
 *
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 maxTiempo(i) = maximo tiempo que puede estar viendo peliculas si estan disponibles desde la i a la N - 1
 maxTiempo(i) = max(maxTiempo(i + 1), maxTiempo(j) + duracion[i]), j > i tq inicio[i] + duracion[i] < inicio[j]
 maxTiempo(N) = 0

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

#define DESCANSO 10

struct peli {
    int inicio, fin, duracion;
};

bool operator<(peli const& i, peli const& d) {
    return i.inicio < d.inicio;
}

int maxTiempo(vector<peli>&peliculas) {
    int n = peliculas.size();
    sort(peliculas.begin(), peliculas.end());
    vector<int>dp(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
        int j = lower_bound(peliculas.begin() + i, peliculas.end(), peli{ peliculas[i].fin + DESCANSO, 0, 0}) - peliculas.begin();
        dp[i] = max(dp[i + 1], dp[j] + peliculas[i].duracion);
    }
    return dp[0];
}

bool resuelveCaso() {

    int N; cin >> N;
    if (N == 0) return false;
    vector<peli>peliculas(N);
    char c; int h, m, d;
    for (int i = 0; i < N; ++i) {
        cin >> h >> c >> m >> c >> d;
        int ini = h * 60 + m;
        peliculas[i] = {ini, ini + d, d};
    }

    cout << maxTiempo(peliculas) << "\n";

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

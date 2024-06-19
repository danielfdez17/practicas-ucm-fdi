// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits> 
#include <cstring>
#include <vector>
using namespace std;

#define MAX 10000

long long dp[MAX + 1][MAX + 1];

int comb(int n, int r) {
    if (n == r || r == 0) return 1;
    if (dp[n][r] != -1) return dp[n][r];
    return dp[n][r] = comb(n - 1, r - 1) + comb(n - 1, r);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n, r; cin >> n >> r;
    if (n == 0 && r == 0) return false;
    memset(dp, -1, MAX * sizeof(long long));
    cout << comb(n, r) << "\n";

    return true;    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    memset(dp, -1, sizeof(dp));
    
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}

// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int MAX = 41;
long long cakes[MAX] = {0};

long long ways(int n) {
    if (n == 0 || n == 1) return cakes[n] = n;
    if (n == 2) return cakes[n] = 5;
    if (n == 3) return cakes[n] = 11;
    if (cakes[n] == 0) return cakes[n] = ways(n - 1) + 4 * ways(n - 2) + 2 * ways(n - 3);
    // if (cakes[n] == 0) return cakes[n] = 2 * ways(n - 1) + 3 * ways(n - 2) + 4 * ways(n - 3);
    return cakes[n];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int n; cin >> n;
    cout << ways(n) << "\n";    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}
// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <bitset>
#include <vector>
using namespace std;

using uint = unsigned int;

bitset<INT_MAX>bs;
vector<unsigned int>primes;

void sieve() {
    bs.set();
    bs[0] = bs[1] = 0;
    for (unsigned int i = 2; i <= INT_MAX; ++i) {
        if (bs[i]) {
            for (uint j = i * i; j <= INT_MAX; j += i) 
                bs[j] = 0;
            primes.push_back(i);
        }
    }
}
bool isPrime(unsigned long long n) {
    if (n <= INT_MAX) return bs[n];
    for (uint i = 0; primes[i] * primes[i] <= n; ++i) {
        if (!(n % primes[i])) return false;
    }
    return true;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int l, u; cin >> l >> u;
    if (!cin) return false;
    
    return true;    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    sieve();
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}
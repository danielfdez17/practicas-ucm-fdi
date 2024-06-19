// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <unordered_set>
using namespace std;
#define MAX 10000
int cases = 1;
int z, i, m, l;
unsigned int getNext(unsigned int x) {
    int prod = ((z % m) * (x % m)) % m;
    return ((prod % m) + (i % m)) % m;
}
typedef pair<unsigned int, unsigned int> uu;
uu floydCycleFinding(unsigned int x0) {
    int tortoise = getNext(x0), hare = getNext(getNext(x0));
    while (tortoise != hare) { // Encontrar el ciclo
        tortoise = getNext(tortoise);
        hare = getNext(getNext(hare));
    }
    // Distancia del inicio a la tortuga == tortuga a la liebre == mu * lambda 
    int mu = 0; hare = x0; // Resetear la liebre
    while (tortoise != hare) { // Encontrar la primera vez que son iguales
        tortoise = getNext(tortoise);
        hare = getNext(hare);
        mu++;
    }
    // Llevar la tortuga a la posicion de la liebre
    int lambda = 1; hare = getNext(tortoise);
    while (tortoise != hare) { // Avanzar cualquiera de ellas para encontrar el lambda
        hare = getNext(hare);
        lambda++;
    }
    return uu(mu, lambda);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    cin >> z >> i >> m >> l;
    if (z == 0 && i == 0 && m == 0 && l == 0) return false;
    int first_random = l;
    //     long long prod = ((z % m) * (l % m)) % m;
    //     next = ((prod % m) + (i % m)) % m;
    uu sol = floydCycleFinding(l);


    cout << "Case " << cases << ": " << sol.second << "\n";
    cases++;
    return true;    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}

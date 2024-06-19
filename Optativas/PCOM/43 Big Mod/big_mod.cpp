// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

int extendedEclidRec(int a, int b, int&u, int&v) {
    if (!b) {
        u = 1; v = 0; return a;
    }
    int r = extendedEclidRec(b, a % b, u, v);
    int uAux = v;
    int vAux = u - (a / b) * v;
    u = uAux;
    v = vAux;
    return r;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int b, p, m; cin >> b >> p >> m;
    if (!cin) return false;
    int u, v;
    int res = extendedEclidRec(pow(b, p), m, u, v);
    // b %= m;
    // while (p > 0) {
    //     if (p % 2 == 1) res = ((res % m) * (b % m)) % m;
    //     p = p >> 1;
    //     b = ((b % m) * (b % m)) % m;
    // }

    // int i = 1;
    // int res = b;
    // while (i <= p) {
    //     res = ((res % m) * (b % m)) % m;
    //     i += b;
    // }
    cout << res << "\n";
    
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
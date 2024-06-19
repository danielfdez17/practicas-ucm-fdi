// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

#define MAX_N 100000

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int T; cin >> T;
    if (T == 0) return false;
    
    vector<int>v(MAX_N, 0);

    for (int i = 0; i < T; i++) {
        string op; cin >> op;
        if (op == "B") {
            int a, b, y; cin >> a >> b >> y;
            for (int j = a; j <= b; j++) v[j] += y;
        }
        else {
            int a; cin >> a;
            cout << v[a] << "\n";
        }
    }

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

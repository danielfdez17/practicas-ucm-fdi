// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

struct droga {
    int pos, tiempo, frecuencia; // pos -> pos vector 'nombres'
    droga(): pos(0), tiempo(0), frecuencia(0) {}
    droga(int i, int t): pos(i), tiempo(t), frecuencia(t) {}

    bool operator<(const droga&d) const {
        if (tiempo != d.tiempo) return tiempo > d.tiempo;
        return pos > d.pos;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, k, f; cin >> n >> k;

    priority_queue<droga> cola;
    vector<string> nombres(n);
    
    for (int i = 0; i < n; i++) {
        string aux;
        cin >> aux >> f;
        nombres[i] = aux;
        cola.push({i, f});
    }


    for (int i = 0; i < k; i++) {
        droga d = cola.top();
        cout << d.tiempo << " " << nombres[d.pos] << "\n";
        d.tiempo += d.frecuencia;
        cola.pop();
        cola.push(d);
    }    
    
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
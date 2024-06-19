// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

#define MODULO 10000
#define BUTTONS 3

bool visitados[MODULO];
int dist[MODULO];

struct par {
    int num, teclas;
    par(int n, int t) : num(n), teclas(t) {}
};

int next(int u, int i) {
    switch(i) {
        case 0: u++; break;
        case 1: u *= 2; break;
        case 2: u /= 3; break;
    }
    return u % MODULO;
}

int bfs2(int origen, int destino) {
    if (origen == destino) return 0;
    queue<par>cola;
    visitados[origen] = true;
    cola.push({origen, 0});
    par p(0, 0);

    while (!cola.empty()) {
        p = cola.front(); cola.pop();
        for (int i = 0; i < BUTTONS; i++) {
            int v = next(p.num, i);
            if (v == destino) return p.teclas + 1;
            if (!visitados[v]) {
                visitados[v] = true;
                cola.push({v, p.teclas + 1});
            }
        }
    }

    return p.teclas;
}

int bfs(int origen, int destino) {
    if (origen == destino) return 0;
    int teclas_pulsadas = 0;
    queue<int>cola;
    dist[origen] = 0; visitados[origen] = true;
    cola.push(origen);

    while (!cola.empty()) {
        int u = cola.front(); cola.pop();
        for (int i = 0; i < BUTTONS; i++) {
            int v = next(u, i);
            if (v == destino) return dist[u] + 1;
            if (!visitados[v]) {
                dist[v] = dist[u] + 1;
                teclas_pulsadas = dist[v];
                visitados[v] = true;
                cola.push(v);
            }
        }
    }

    return teclas_pulsadas;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int origen, destino; cin >> origen >> destino;
    if (!cin) return false;
    memset(visitados, 0, MODULO * sizeof(bool));
    memset(dist, 0, MODULO * sizeof(int));
    // cout << bfs(origen, destino) << "\n";
    cout << bfs2(origen, destino) << "\n";

        
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     ifstream in("datos.txt");
     auto cinbuf = cin.rdbuf(in.rdbuf()); //save old buf and redirect cin to casos.txt
     #endif 
    
    
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}
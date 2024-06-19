// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>
#include <functional>
#include <climits>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAX = 999, MOVS = 4;


struct tcasilla {
    int fila, columa, coste;
    tcasilla(int f, int c, int cos) : fila(f), columa(c), coste(cos) {}

    //bool operator<(tcasilla const& c) {
    //    return coste < c.coste;
    //}
};

bool operator>(tcasilla const& ci, tcasilla const& cd) {
    return ci.coste > cd.coste;
}

int tablero[MAX][MAX];
int movimientos[4][2] = { {0,1},{-1,0},{0,-1},{1,0} };
int N, M;
priority_queue<tcasilla, vector<tcasilla>, greater<tcasilla>>cola;

bool ok(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
}

int dijkstra() {
    vvi dist(N, vector<int>(M, INT_MAX));
    dist[0][0] = tablero[0][0];
    cola.push({ 0,0,tablero[0][0] });
    while(!cola.empty()) {
        tcasilla c = cola.top(); cola.pop();
        if(c.fila == N - 1 && c.columa == M - 1) return c.coste;
        
        for(int i = 0; i < MOVS; i++) {
            int f = c.fila + movimientos[i][0], col = c.columa + movimientos[i][1];
            if(ok(f, col)) {
                int coste = c.coste + tablero[f][col];
                if(coste < dist[f][col]) {
                    dist[f][col] = coste;
                    cola.push({ f, col, coste });
                }
            }
        }
    }
    
    return -1;
}



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> tablero[i][j];
        }
    }
    cout << dijkstra() << "\n";
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
    for(int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
// Alex Bonilla y Daniel Fernandez
// pc03


#include <iostream>
#include <iomanip>
#include <fstream>
#include<queue>
#include<algorithm>
#include<vector>
#include<math.h>

using namespace std;
const int MAX_ISLA=50;
string tablero[MAX_ISLA][MAX_ISLA];
bool transitable[MAX_ISLA][MAX_ISLA];
vector<int>vi;

int h, w,pasos;
bool ok(int x, int y) {
    return 0 <= x && x < h && 0 <= y && y < w;
}
const int MOVS = 8;
int movs[MOVS][2] = { {0,1},{-1,0},{0,-1},{1,0},{1,1},{-1,1}, {1,-1},{-1-1} };
struct tcasilla {
    int fila, columna, paso;
    tcasilla() : fila(0), columna(0) {}
    tcasilla(int f, int c) : fila(f), columna(c) {}
    tcasilla(pair<int, int>q) : fila(q.first), columna(q.second) {}
};
bool operator <(tcasilla const& i, tcasilla const& d) {
    return i.paso<d.paso;
}
queue<pair<int, int>>pirate;
queue<pair<int, int>>native;
tcasilla inicio;

void marcarNoTransitableAdj() {
    while (!native.empty()) {
        tcasilla casilla = native.front(); native.pop();
        for (int i = 0; i < MOVS; i++) {
            int nf = casilla.fila + movs[i][0], nc = casilla.columna + movs[i][1];
            if (transitable[nf][nc]){
                transitable[nf][nc] = false;
                
            }
        }

    }
}

// función que resuelve el problema
using vi = vector<int>;
vi dist;
using vii = vector<vi>;
vii adjList;

int dijkstra() {
    dist.assign(adjList.size(), INF);
    dist.push_back();
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({ 0, s });
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue;
        for (auto a : adjList[u]) {
            if (dist[u] + a.first < dist[a.second]) {
                dist[a.second] = dist[u] + a.first;
                pq.push({ dist[a.second], a.second });
            }
        }
    }
    return pasos*2;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int sol;
    cin >> h >> w;
    if (!std::cin)
        return false;

    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> tablero[i][j];
            transitable[i][j] = false;
            if (tablero[i][j] == "@") {
                pirate.push(make_pair(i, j));
            }
            if (tablero[i][j] == ".") transitable[i][j] = true;
            if (tablero[i][j] == "!") transitable[i][j] = true;
            if (tablero[i][j] == "*") {
                native.push(make_pair(i, j));
                marcarNoTransitableAdj();
            }
            

        }
    }
    
    sol=dijkstra();
    // escribir sol

    cout << sol<<endl;
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
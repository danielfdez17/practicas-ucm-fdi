// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define NODES 10000
#define EDGES 100000
#define INF 1000000

using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<ii>; // <valor, nodo>
using vvi = vector<vi>;
vvi adjList;

void dijkstra(int s, vi &dist) { // O((V + E) log V)
    dist.assign(adjList.size(), {0, INF});
    dist[s] = {};
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u].first) continue;
        for (auto a : adjList[u]) {
            if (dist[u].first + a.first < dist[a.second].first) {
                dist[a.second].first = dist[u].first + a.first;
                pq.push({dist[a.second].first, a.second});
            }
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    adjList.assign(NODES, {});
    int N, M, s, t, p; cin >> N >> M >> s >> t >> p;
    for (int i = 0; i < M; ++i) {
        int u, v, c; cin >> u >> v >> c;
        adjList[u - 1].push_back({v - 1, c});
    }
    int r = -1;
    cout << (r <= p ? r : -1) << "\n";
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
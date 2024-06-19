// Alex Bonilla Taco y Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 10000;

queue<int>cola;
bool visitados[MAX];
int dist[MAX];
vector<vector<int>>adjList(MAX);
int fichas_caidas;


int bfs(int u) {
    cola.push(u); 
    dist[u] = 0;
    visitados[u] = true;

    while (!cola.empty()) {
        int v = cola.front(); cola.pop();
        for (int w : adjList[v]) {
            if (!visitados[w]) {
                visitados[w] = true;
                dist[w] = dist[v] + 1;
                fichas_caidas++;
                cola.push(w);
            }
        }
    }
    return fichas_caidas;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    int n, m, l; cin >> n >> m >> l;
    memset(visitados, 0, sizeof(visitados));
    memset(dist, 0, sizeof(dist));
    for (int i = 0; i < MAX; i++) {
        adjList[i].clear();
    }
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adjList[x-1].push_back(y-1);
        // adjList[y-1].push_back(x-1);
    }
    fichas_caidas = 0;
    for (int i = 0; i < l; i++) {
        int x; cin >> x; 
        if (!visitados[x-1]) {
            cola.push(x - 1);
            visitados[x - 1] = true;
            fichas_caidas++;
        }
    }
    int u = cola.front(); cola.pop();
    cout << bfs(u) << "\n";    
    
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
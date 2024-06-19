// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>
#include <cstring>
#include <queue>
using namespace std;

#define N 102
#define BARISAL 0
#define DHAKA(n) (2 * n + 1)
#define IN(u) (2 * u - 1)
#define OUT(u) (2 * u)

using vi = vector<int>;
using vvi = vector<vi>;


vvi adj, cap;
bool visited[N];
int parent[N];
int sol;


void bfs(int s, int t) {
    queue<int>q;
    memset(visited, 0, sizeof(visited));
    q.push(s);
    parent[s] = -1; visited[s] = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        if(u == t) break;
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if(!visited[v] && (cap[u][v] > 0)) {
                parent[v] = u;
                visited[v] = true;
                q.push(v);
            }
        }
    }
}
int sendFlow(int s, int t) {
    bfs(s, t);
    if(!visited[t]) return 0;
    int flow = INT_MAX, v = t;
    while(v != s) {
        flow = std::min(cap[parent[v]][v], flow);
        v = parent[v];
    }
    v = t;
    while(v != s) {
        cap[parent[v]][v] -= flow;
        cap[v][parent[v]] += flow;
        v = parent[v];
    }
    return flow;
}
int edmondsKarp(int s, int t) {
    int ret = 0, flow = 0;
    do {
        flow = sendFlow(s, t);
        ret += flow;
    } while(flow > 0);
    return ret;
}
void addEdge(int v, int u, int c) {
    adj[v].push_back(u);
    cap[v][u] = c;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
// Cada vertice que se lee son en realidad dos vertices (uno que recibe la energia y otro que la distribuye
// y estos dos estan conectados por una arista con el valor de la capacidad del vertice)
// BARISAL es el nodo/vertice 0; DHAKA es el nodo/vertice 2*num_vertices + 1
bool resuelveCaso() {
    int n; cin >> n;
    if(!cin) return false;

    memset(parent, 0, sizeof(parent));
    sol = 0;
    for(int i = 0; i < n + 2; i++) {

    }
    

    vector<int>capacidades(n);
    for(int i = 0; i < n; i++) {
        cin >> capacidades[i];
    }
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c;
        addEdge(IN(u), OUT(v), c);
    }

    int b, d; cin >> b >> d;
    for(int i = 0; i < b; i++) {
        int v; cin >> v;
        addEdge(BARISAL, IN(v), INT_MAX);
    }
    for(int i = 0; i < d; i++) {
        int v; cin >> v;
        addEdge(OUT(v), DHAKA(n), INT_MAX);
    }
    edmondsKarp(BARISAL, DHAKA(n));

    cout << sol << "\n";


    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while(resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}

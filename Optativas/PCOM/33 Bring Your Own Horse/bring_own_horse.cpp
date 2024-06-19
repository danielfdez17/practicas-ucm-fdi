// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define N 3000
#define R 1e5
#define L 1e6 + 1

using vi = vector<int>;
using vvi = vector<vi>;

vi adj[N];
bool visited[N];
int parent[N];
int cap[N][N];


void bfs(int s, int t) {
    queue<int> q;
    memset(visited, 0, sizeof(visited));
    q.push(s);
    parent[s] = -1; visited[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) break;
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (!visited[v] && (cap[u][v] > 0)) {
                parent[v] = u;
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int sendFlow(int s, int t) {
    // Intentamos llegar de s a t
    bfs(s, t);
    if (!visited[t])
        return 0; // No pudimos
    // Buscamos capacidad m´as peque˜na en el camino
    int flow = L, v = t;
    while (v != s) {
        flow = min(cap[parent[v]][v], flow);
        v = parent[v];
    }
    // Mandamos flujo
    v = t;
        while (v != s) {
        cap[parent[v]][v] -= flow;
        cap[v][parent[v]] += flow; // INVERSA
        v = parent[v];
    }
    return flow;
}

int edmondsKarp(int s, int t) {
    int ret = 0, flow = 0;
    do {
        flow = sendFlow(s, t);
        ret += flow;
    } while (flow > 0);
    return ret;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int n, r; cin >> n >> r;

    memset(parent, 0, sizeof(parent));
    memset(cap, 0, N * sizeof(cap[0]));

    for (int i = 0; i < r; i++) {
        int a, b, l; cin >> a >> b >> l; 
        // aristas.push_back({l, {a - 1, b - 1}});
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
        cap[a - 1][b - 1] = l;
        cap[b - 1][a - 1] = l;
    }
    int min_arista = L;
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int k, t; cin >> k >> t;
        int flow = edmondsKarp(k - 1, t - 1);
        cout << flow << "\n";
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
    for (int i = 0; i < numCasos; ++i) {
        cout << "Case " << i + 1 << "\n";
        resuelveCaso();
    }

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}
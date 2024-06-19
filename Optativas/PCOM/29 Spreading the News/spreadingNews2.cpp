// ALEX BONILLA y DANIEL FERNANDEZ
// PC03


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map> 
using namespace std;
const int MAX_E = 2505;
map<int, vector<int>>adjList;
bool visited[MAX_E];

int E, N, T;
int M, D;



struct nodo {
    int profundidad, hijos;
};


pair<int,int> bfs(int i) {
    queue<int> q;
    fill(visited, visited + MAX_E, false);
    visited[i] = true;
    N = 1; M = 0;//N es el numero de nodos y M es la profundidad
    pair<int, int> salida = { N,M };//N,M
    q.push(i);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int w : adjList[v]) {
            if (!visited[w]) {
                visited[w] = true;
                q.push(w);
            }
        }
        N--;
        if (N == 0) {
            M += 1;
            N = q.size();
            if (salida.first < N) {
                salida = { N,M };
            }
        }

    }
    return salida;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    cin >> E;
    if (!std::cin)
        return false;
    
    for (int i = 0; i < E; i++) {
        cin >> N;
        for (int j = 0; j < N; j++) {
            visited[i] = false;
            int x; cin >> x;
            adjList[i].push_back(x);
        }
    }
    cin >> T;
    vector<int>casos(T);
    for (int i = 0; i < T; i++) {
        cin >> casos[i];
    }
    
    for (int i = 0; i < T; i++) {
        pair<int,int>salida=bfs(casos[i]);
        if (salida.first == 1 && salida.second == 0) {
            cout << 0<<endl;
        }else
        cout <<salida.first <<" " << salida.second<<endl;
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
        while(resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
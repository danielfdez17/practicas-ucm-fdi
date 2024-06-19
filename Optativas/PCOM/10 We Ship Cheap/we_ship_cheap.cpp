// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
using namespace std;

unordered_map<string, vector<string>>grafo;
unordered_map<string, bool>visitados;
// pair<origen, destino>
vector<pair<string, string>>parejas;
string origen, destino;

void bfs() {
    queue<string>cola;
    cola.push(origen);
    visitados[origen] = true;
    while (!cola.empty()) {
        string front = cola.front(); cola.pop();
        for (string v : grafo[front]) {
            if (!visitados[v]) {
                visitados[v] = true;
                parejas.push_back({ front, v });
                cola.push(v);
            }
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n; cin >> n;
    if (!cin) return false;

    grafo.clear();
    visitados.clear();
    parejas.clear();

    for (int i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
    cin >> origen >> destino;

    bfs();

    if (!visitados[destino]) cout << "No route\n";
    else {
        for (pair<string, string>& p : parejas) {
            cout << p.first << " " << p.second << "\n";
        }
    }
    cout << "\n";

    // escribir sol


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
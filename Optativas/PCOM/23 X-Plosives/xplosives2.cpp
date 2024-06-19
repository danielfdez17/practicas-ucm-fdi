// Daniel Fernandez Ortiz y Alex Bonilla Taco
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;
const int MAX_IN=100005;
int V=MAX_IN;
int rechazados;


struct UFDS {
    vector<int> p;
    int numSets;
    UFDS(int n) : p(n, 0), numSets(n) {
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find(int x) {
        return (p[x] == x) ? x : p[x] = find(p[x]);
    }
    void merge(int x, int y) {
        int i = find(x), j = find(y);
        if (i == j) return;
        p[i] = j;
        --numSets;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    
    int  a=0, b;
    string linea;
    vector<pair<int, int>>grafo;

    getline(cin, linea);
    if (!cin)return false;

    while (!linea.empty()&&a!=-1) {
        istringstream stream(linea);
        stream >> a;
        
        if (a != -1){
            stream>> b;
            grafo.push_back({a,b});
            getline(cin, linea);
        }
           
    }
    if (grafo.size() > 2) {
        UFDS uf(V);
        int tam = 0;
        for (auto v : grafo) {
            
            if (v.first == v.second) { tam++; }
            if (uf.find(v.first) != uf.find(v.second)) {
                uf.merge(v.first, v.second);
                tam += 1;
                if (uf.numSets == 1) break;
            }
        }
        rechazados = grafo.size() - tam;
    }
    else
        rechazados = 0;
    
    // escribir sol
     cout << rechazados << endl;
     if (a == -1) {
            return false;
     }
            

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
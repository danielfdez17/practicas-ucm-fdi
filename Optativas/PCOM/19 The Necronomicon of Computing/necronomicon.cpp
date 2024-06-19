// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Digrafo.h"

class cicloDirigido {
private:
    vector<bool>visit, apilado;
    bool hayciclo;
    int v;

    void dfs(Digrafo const& dg, int v) { // O(V + A)
        apilado[v] = true; visit[v] = true;
        for (int w : dg.ady(v)) {
            //if (w == dg.V() - 1) haycamino = true;
           
            if (!visit[w]) dfs(dg, w);
            else if (apilado[w]) hayciclo = true;
        }
        apilado[v] = false;
    }

public:
    cicloDirigido(Digrafo const& dg) : visit(dg.V(), false), apilado(dg.V(), false), hayciclo(false), v(dg.V()) {
        dfs(dg, 0);
    }
    bool hayCiclo() const { return hayciclo; }
    bool hayCamino() const { return visit[v - 1]; }

};

void resuelveCaso() {
    int vertices; cin >> vertices;
    Digrafo dg(vertices + 1);

    for (int i = 0; i < vertices; i++) {
        char c; cin >> c;
        int salto;
        if (c == 'A') {
            dg.ponArista(i, i + 1);
        }
        else if (c == 'J') {
            cin >> salto;
            dg.ponArista(i, salto - 1);
        }
        else /*if (c == 'C')*/ {
            cin >> salto;
            dg.ponArista(i, salto - 1);
            dg.ponArista(i, i + 1);
        }
    }
    
    cicloDirigido sol(dg);
    if (!sol.hayCamino()) {
        cout << "NEVER\n";
    }
    else {
        if (sol.hayCiclo()) cout << "SOMETIMES\n";
        else cout << "ALWAYS\n";
    }

}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

        int numCasos; cin >> numCasos;
        for (int i = 0; i < numCasos; i++) resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
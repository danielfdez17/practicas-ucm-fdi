/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la solución.
 * Luis Rebollo Cocera: TAIS52
 * Daniel Fernandez Ortiz: TAIS21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Hemos construido un grafo con un vertice mas que el numero de instrucciones que nos ayuda a decir si ha finalizado la ejecucion del programa (el ultimo vertice),
 porque la ultima instruccion puede ser un salto hacia una instruccion anterior

 El problema se resuelve utilizan al algoritmo de busqueda en profundidad de los grafos (en este caso es un grafo dirigido).
 Hemos relacionado las secuencia de instrucciones de un programa con los vertices del grafo, y los vertices adyacentes son las siguientes instrucciones
 que se van a ejecutar: 
 - Si el vertice leido es una A, sale una arista dirigida del vertice actual a la siguiente instruccion leida
 - Si el vertice es una J, sale una arista dirigida del vertice actual a la instruccion que dice el salto - 1
 - Si el vertice es una C, se comporta como si el vertice leido fuese una A y una J a la vez

 Consideramos que el programa:
 - No acaba nunca si no se llega al ultimo vertice
 - Acaba a veces si puede llegar al ultimo vertice y existe un ciclo
 - Acaba siempre si se llega al ultimo vertice y no existe un ciclo


 El coste del algoritmo es el coste de la busqueda en profundidad del grafo: O(vertices + aristas)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

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

bool resuelveCaso() {
    int vertices; cin >> vertices;
    if (!cin) return false;
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
        cout << "NUNCA\n";
    }
    else {
        if (sol.hayCiclo()) cout << "A VECES\n";
        else cout << "SIEMPRE\n";
    }

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

        while(resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
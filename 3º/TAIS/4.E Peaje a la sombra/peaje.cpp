/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la solución.
 * Luis Rebollo Cocera: TAIS53
 * Daniel Fernandez Ortiz: TAIS21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Vertices claves: Alex, Lucas y el Trabajo

 El problema se resuelve con el algoritmo de busqueda en anchura en grafo ya que se necesita el coste de recorrer el camino minimo

 La solucion pasa por encontrar un nodo comun E (que puede ser cualquiera de los vertices claves) tq la disancia a cada vertice clave sea minima

 Calculamos la distancia minima (utilizando el recorrido en anchura de los grafos) que hay desde todos los vertice a los vertices claves guardandolos
 en 3 vectores para sendos vertices claves.

 Por ultimo, iteramos el numero de vertices guardandonos la suma minima de los caminos minimos desde el vertice 'i' a los vertices clave.

 El coste del algoritmo es lineal en el numero de vertices mas el numero de aristas

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void bfs(Grafo const& g, int v, vector<int>&distancias) {
    vector<bool>visitados(g.V(), false);
    queue<int>cola;
    cola.push(v); visitados[v] = true;
    distancias[v] = 0;
    while (!cola.empty()) {
        int v = cola.front(); cola.pop();
        for (int w : g.ady(v)) {
            if (!visitados[w]) {
                distancias[w] = distancias[v] + 1;
                visitados[w] = true;
                cola.push(w);
            }
        }
    }
}

bool resuelveCaso() {
       
    int vertices, aristas, alex, lucas, trabajo; cin >> vertices >> aristas >> alex >> lucas >> trabajo;
    
    if (!std::cin) return false;

    Grafo g(vertices);
    alex--; lucas--; trabajo--;
    for (int i = 0; i < aristas; i++) { //O(veritices)
        int a, b; cin >> a >> b;
        g.ponArista(a - 1, b - 1);
    }

    vector<int>dist_alex(vertices, 0);
    vector<int>dist_lucas(vertices, 0);
    vector<int>dist_trabajo(vertices, 0);
    // 3 * O(vertices + aristas) == O(vertices + aristas)
    bfs(g, alex, dist_alex);
    bfs(g, lucas, dist_lucas);
    bfs(g, trabajo, dist_trabajo);

    int coste_menor = 1e9;

    for (int i = 0; i < vertices; i++) // O(vertices)
        coste_menor = min(coste_menor, dist_alex[i] + dist_lucas[i] + dist_trabajo[i]);

    cout << coste_menor << "\n";
    
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

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
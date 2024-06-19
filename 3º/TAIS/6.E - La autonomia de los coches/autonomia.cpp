/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la solución.
 * Luis Rebollo Cocera: TAIS 53
 * Daniel Fernandez Ortiz: TAIS 21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "GrafoValorado.h" // propios o los de las estructuras de datos de clase
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema a resolver se basa en un ARM para calcular la minima autonomia de un coche para viajar a todas las ciudades conectadas por una red de carreteras. Nos hemos
 decantado por utilizar un ARM porque es una estructura que nos permite contectar todos los vertices garantizandonos una conectividad optima. y al poder repostar 
 en cada ciudad la solucion viene dada por la arista de mayor peso (si se puede recorrer esa carretera, se pueden recorrer todas)

 En este problema los vertices del grafo son las ciudades (V) y las aristas son las carreteras (A)

 Cosideramos que el programa:
 - No tiene solucion si el grafo no es conexo (todas las ciudades no estan conectadas entre sí, porque la red de carreteras no te permite llegar de una ciudad a otra)
 - Tiene solucion si el grafo es conexo (desde cualquier ciudad puedes llegar a todas las demas)

 El coste del algoritmo es el coste de la ordenacion de la cola de prioridad minimos que ordena las aristas en funcion del valor de 
 la arista (autonomia del coche para transitar dicha carretera), que en el caso peor se accede al elemento mas prioritario A veces con un coste logaritmico en A

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM;
    Valor maxima_arista;
    bool se_puede;
public:
    Valor maximaAristaARM() const { return maxima_arista; }
    bool sePuede() const { return se_puede;  }
    std::vector<Arista<Valor>> const& ARM() const { return _ARM; }
    ARM_Kruskal(GrafoValorado<Valor> const& g) : maxima_arista(0), se_puede(true) { // O(A log A)
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                maxima_arista = std::max(maxima_arista, a.valor());
                _ARM.push_back(a); 
                if (_ARM.size() == g.V() - 1) break;
            }
        }
        se_puede = cjtos.num_cjtos() == 1;
    }
};

bool resuelveCaso() {

    int n, m; cin >> n >> m;
    if (!std::cin) return false;

    GrafoValorado<int>grafo(n); 
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        grafo.ponArista({ a - 1,b - 1,c });
    }

    ARM_Kruskal<int>arm(grafo);

    if (arm.sePuede()) cout << arm.maximaAristaARM() << "\n";
    else cout << "Imposible\n";



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
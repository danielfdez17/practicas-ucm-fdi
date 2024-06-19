/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXX) de los autores de la solución.
 * Luis Rebollo Cocera: TAIS53
 * Daniel Fernandez Ortiz: TAIS21
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include <set>
#include <climits>
#include <algorithm>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Sea n el numero de vertices/ciudades y m el numero de aristas/carreteras

 El ejercicio se resuelve utilizando el algoritmo de Dijkstra para calcular el camino minimos desde los dos vertices origen (primero y ultimo, que son las ciudades donde se encuentran las
 dos centrales salinizadoras) al resto de vertices (ciudades), teniendo en cuenta que cada planta salinizadora puede suministrar agua a (n - 2) / 2 ciudades, ya que ellas se encuentran en dos ciudades distintas

 Nos guardamos los vectores de distancias minimas desde los dos vertices origen al resto (en dos llamadas distintas a Dijkstra), 
 y guardamos en un conjunto ordenado las diferencias de las distancias minimas de los vertices origen a los demas y las posiciones de los vertices destino (resto de vertices)

 Nuestro algoritmo voraz se basa en seleccionar la ruta en funcion de la maxima diferencia de los vertices origen al vertice i, de manera que no elegir el vertice de la maxima diferencia puede provocar
 que el coste sea mayor en una eleccion futura, y por tanto empeorar la solucion.

 Supongamos una solucion hipotetica voraz que hasta cierta ciudad c, la solucion es identica a la nuestra voraz, y para la ciudad c' elige la salinizadora s' mientras que nosotros elegimos la s:
 distinguimos entre dos posibilidades:
 -> Que la solucion hipotetica escoga un camino menor que la nuestra en este paso, pero supone que en un paso futuro se va a quedar sin ciudades a las que suministrar agua desde s' 
    asumiendo un coste mayor en futuros pasos
 -> Que la solucion hipotetica escoga un camino mayor que la nuestra en este paso, pero supone que no cumpla el test de optimalidad ya que existe una solucion con un coste menor (la nuestra).
    Si hacemos que la solucion hipotetica se parezca a la nuestra copiando el ultimo pasa conseguiremos que sea optima (por induccion llegariamos a la solucion optima, demostrando que la nuestra es optima
    y factible)

 COSTE: // O((n + m) log n), ya que hacemos dos llamadas al algoritmo de Dijkstra

 ESPACIO: O(n), ya que utilizamos 3 estructuras de datos lineales para poder calcular el coste minimo

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const long long INF = std::numeric_limits<long long>::max();


class Dijkstra {
private:
    int origen;
    vector<long long int>dist;
    IndexPQ<long long int>pq;
    void relajar(AristaDirigida<int>a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
public:
    Dijkstra(DigrafoValorado<int> const& g, int orig) : origen(orig), dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    vector<long long int> getDistancias() {
        return dist;
    }
};



bool resuelveCaso() {

    int n, m; cin >> n >> m;
    if (!std::cin) return false;

    DigrafoValorado<int>grafo(n); // O(n)
    for (int i = 0; i < m; i++) { // O(n)
        int a, b, c; cin >> a >> b >> c;
        grafo.ponArista({ a - 1, b - 1, c });
        grafo.ponArista({ b - 1, a - 1, c });
    }
    int norte = 0, sur = n - 1, ciudades_norte = 0, ciudades_sur = 0, mitad = (n - 2) / 2;
    vector<long long int>dist_norte, dist_sur;

    Dijkstra d_norte(grafo, norte); // O((n + m) log n)
    dist_norte = d_norte.getDistancias();
    Dijkstra d_sur(grafo, sur); // O((n + m) log n)
    dist_sur = d_sur.getDistancias();

    set<pair<long long int, int>>diferencias;
    for (int i = 0; i < n; i++) {
        diferencias.insert({ abs(dist_norte[i] - dist_sur[i]), i }); // O(log n)
    }
    long long int coste = 0;
    for (set<pair<long long int, int>>::reverse_iterator rit = diferencias.rbegin(); rit != diferencias.rend(); rit++) { // O(n)
        int pos = rit->second;
        // Si (desde el norte no se ha suministrado a la mitad de ciudades y la distancia a la ciudad pos es menor desde la del norte) o (desde el sur se ha suministrado a la mitad de ciudades)
        if ((ciudades_norte <= mitad && dist_norte[pos] < dist_sur[pos]) || ciudades_sur > mitad) {
            ciudades_norte++;
            coste += (dist_norte[pos] * 2);
        }
        // En otro caso
        else {
            ciudades_sur++;
            coste += (dist_sur[pos] * 2);
        }
    }

    cout << coste << "\n";

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
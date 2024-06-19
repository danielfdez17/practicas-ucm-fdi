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

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema se resuelve leyendo el numero de canditatos(c) y el numero de escanyos a repartir(n).
 El primer bucle lee los candidatos y los mete en la cola de prioridad segun el orden establecido en el enunciado
 El segundo bucle saca el elemento mas prioritario, actualiza su coeficiente y lo vuelve a meter en la cola segun su prioridad
 Se utiliza un vector para guardar en cada posicion de los candidatos el numero de escanyos que han recibida, 
 teniendo el orden en el que se han leido (tcandidatura.indice)

 Hemos utilizado una cola de prioridad debida a que el algoritmo nos exige una ordenacion especifica en la que
 debemos dar prioridad al elemento con mayor coeficiente, si no es asi, con mayor numero de votos, y si no es asi, se tiene en cuenta el orden en el que se
 han leido, sobrecargando el operador menor

 El bucle de la solucion hace n iteraciones, y el coste de cada iteracion es 
 logaritmico en el numero de candidatos (2*log(cola.size()) == log(cola.size())
 Entonces, el coste de la solucion es O(n * log(c))

 El problema se resuelve utilizando una cola de prioridad que ordena los elementos

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct tcandidatura {
    int num_escanyos;
    int votos;
    int indice;
    double coeficiente;
    tcandidatura(int v, int i) : votos(v), indice(i), num_escanyos(0), coeficiente(v) {}
};

bool operator<(tcandidatura const& i, tcandidatura const& d) {
    if (i.coeficiente == d.coeficiente) {
        if (i.votos != d.votos) {
            return i.votos < d.votos;
        }
        return i.indice > d.indice;
    }
    return i.coeficiente < d.coeficiente;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int c, n; cin >> c >> n;
    if (c == 0 && n == 0) return false;

    // resolver el caso posiblemente llamando a otras funciones
    priority_queue<tcandidatura>cola;
    vector<int>sol(c);

    for (int i = 0; i < c; i++) {
        int v; cin >> v;
        cola.push({ v, i });
    }

    for (int i = 0; i < n; i++) {
        tcandidatura a = cola.top(); cola.pop();
        a.num_escanyos++;
        a.coeficiente = a.votos / (a.num_escanyos + 1.0);
        sol[a.indice] = a.num_escanyos;
        cola.push(a);
    }

    for (int& i : sol) cout << i << " "; cout << "\n";

    // escribir la solución

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
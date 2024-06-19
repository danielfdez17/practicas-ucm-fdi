// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: Vector parcialmente ordenado
// Comentario general sobre la solución: Numero de casos ilimitado delimitado con un valor centinela


#include <iostream>
#include <fstream>
using namespace std;
// Constante que delimita el tamaño maximo de los arrays leidos por teclado
const int MAX_ELEMENTOS = 10;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver();

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso();

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("out.txt");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}

bool resuelveCaso() {

    // leer los datos de la entrada

    if (caso especial)
        return false;

    resolver();

    // escribir sol

    return true;
}

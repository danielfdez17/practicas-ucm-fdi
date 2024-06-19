#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
ESPECIFICACIÓN: fun resolver(vector<int>const&v, int size, int altura) ret tsol { ini,fin }

PRECONDICION: {
    0 < size
    && 
    existe u : 0 <= u < size : v[u] > altura
}

POSTCONDICION: {
    seg = p,q : 0 <= p <= q < size : (forall w1 : p <= w1 <= q : v[w1] > altura) : q - p (el que esta más a la derecha)
    &&
    maxSeg = max p,q : 0 <= p <= q < size : (forall w : p <= w <= q : v[w] > altura) : q - p
    &&
    fin = max w2 : (max p,q : 0 <= p <= q < size : (forall w3 : p <= w3 <= q : v[w3] > altura) : q - p)
}

INVARIANTE: {
    0 <= i <= size
    &&
    seg = max p,q : 0 <= p <= q < i : (forall w4 : p <= w4 <= q : v[w4] > altura) : q - p (el más a la derecha)
    &&
    maxSeg = max p,q : 0 <= p <= q < i : (forall w5 : p <= w5 <= q : v[w5] > altura) : q - p
    &&
    fin = max w6 : (max p,q : 0 <= p <= q < i : (forall w7 : p <= w7 <= q : v[w7] > altura) : q - p)
}
 
FUNCION DE COTA: size - i
ANALISIS DEL COSTE: El coste de cada iteración del bucle es constante, y este se recorre size veces.
    Por tanto, el coste del algoritmo pertenece a size * O(1) = O(size)
 */

struct tsol {
    int ini;
    int fin;
};

tsol resolver(vector<int>const& v, int size, int altura) {
    int seg = 0, maxSeg = 0, fin = 0;
    for (int i = 0; i < size; i++) {
        if (v[i] > altura) {
            seg++;
            if (seg > maxSeg) {
                maxSeg = seg;
                fin = i;
            }
        }
        else {
            seg = 0;
        }
    }
    return { fin - maxSeg + 1,fin };
}

void resuelveCaso() {
    int size, altura; cin >> size >> altura;
    vector<int> edificios(size);
    for (int& i : edificios) cin >> i;
    tsol sol = resolver(edificios, size, altura);
    cout << sol.ini << " " << sol.fin << "\n";
}


int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    unsigned int numCasos;
    std::cin >> numCasos;
    // Resolvemos
    for (int i = 0; i < numCasos; ++i) {
       resuelveCaso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}

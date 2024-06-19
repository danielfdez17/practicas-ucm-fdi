#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

/*
ESPECIFICACION: fun resolver(vector<int>const&v, int size) ret (int maxSeg)

PRECONDICION: {
    size >= 0
}

POSTCONDICION: {
    maxSeg = max p,q : 0 <= p <= q < size : (forall u : p <= u < q : abs(v[u] - v[u + 1]) == 1) q - p
}

INVARIANTE: {
    0 <= i < size
    &&
    seg =  p,q : 0 <= p <= q < i : (forall w : p <= w < q : abs(v[w] - v[w + 1]) == 1) q - p
    &&
    maxSeg = max p,q : 0 <= p <= q <= i : (forall u1 : p <= u1 < q : abs(v[u1] - v[u1 + 1]) == 1) q - p
}

FUNCION DE COTA: size - i
ANALISIS DEL COSTE: El coste de cada iteracion del bucle es constante, y este se recorre size - 1 veces (=== size).
    Por tanto, el coste del algorimto pertenece a O(1) * size = O(size)
*/

int resolver(vector<int>const& v, int size) {
    if (size == 0) return size;
    int seg = 1, maxSeg = 1;
    for (int i = 0; i < size - 1; i++) {
        if (abs(v[i] - v[i + 1]) == 1) {
            seg++;
            maxSeg = max(maxSeg, seg);
        }
        else {
            seg = 1;
        }
    }
    return maxSeg;
}


bool resuelveCaso() {
    int size;
    cin >> size;
    vector<int> v(size);
    for (int& i : v)cin >> i;
    cout << resolver(v, size) << "\n";
    return true;
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
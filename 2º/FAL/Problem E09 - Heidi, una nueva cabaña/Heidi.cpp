#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*
ESPECIFICACION: fun resolver(vector<int>const&v, int size, int length) ret vector<int> sol
PRECONDICION: {
    0 < size
    &&
    length > 1
}
POSTCONDICION: {
    iguales = p,q : 0 <= p <= q < size : forall u : p <= u < q : v[u] == v[u + 1] : q - p
    &&
    maxLlanos = max : p,q : 0 <= p <= q < size : forall w : p <= w < q : v[w] == v[w + 1] : q - p

}
INVARIANTE: {
    0 <= i < size
    &&
    iguales = p,q : 0 <= p <= q < i : forall u1 : p <= u1 < q : v[u1] == v[u1 + 1] : q - p
    &&
    maxLlanos = max : p,q : 0 <= p <= q < i : forall w1 : p <= w1 < q : v[w1] == v[w1 + 1] : q - p
}
FUNCION DE COTA: i
ANALISIS DEL COSTE: El coste de cada iteracion del bucle es constante, y este se recorre size - 1 veces (=== size).
    Por tanto, el coste del algorimo pertenece a size * O(1) + aux.size() = O(size) + aux.size() = O(size)
*/

vector<int>resolver(vector<int>const& v, int size, int length) {
    vector<int>sol, aux;
    int max = v.back(), iguales = 1, llanos = 0, maxLlanos = 0;
    for (int i = size - 1; i > 0; i--) {
        if (v[i] != v[i - 1] || v[i - 1] < max)iguales = 1;
        else iguales++;
        if (iguales > maxLlanos && iguales >= length) maxLlanos = iguales;
        if (iguales == length) {
            llanos++;
            aux.push_back(i + iguales - 2);
        }
        max = std::max(v[i - 1], max);
    }
    sol.push_back(maxLlanos);
    sol.push_back(llanos);
    for (int& i : aux) sol.push_back(i);
    return sol;
}

bool resuelveCaso() {
    int size, length;
    cin >> size >> length;
    if (!cin) return false;
    vector<int> v(size), sol;
    for (int& i : v) cin >> i;
    sol = resolver(v, size, length);
    for (int& i : sol) cout << i << " ";
    cout << "\n";
    return true;
}



int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
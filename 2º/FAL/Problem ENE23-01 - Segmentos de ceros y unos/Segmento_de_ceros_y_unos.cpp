#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
using namespace std;

//DEFINE el predicado cerosUnos(v,p,q)
// cerosUnos(v,p,q) = u : p <= u < q : (#(v[u] == 0) == #(v[u] == 1))

// PREDICADOS AUXILIARES: (p incluida y q excluida)
// UNOS(v,p,q) = #(u : p <= u < q : v[u] == 1)
// CEROS(v,p,q) = #(u : p <= u < q : v[u] == 0)

/*
ESPECIFICACIÓN: fun resolver(const vector<int>&v, int l) ret (int r)

PRECONDICION: {
    v.size() >= 0
    &&
    l >= 1
    &&
    forall u : l <= u < v.size() : v[u] >= 0
    &&
    forall w : 0 <= w < l : v[u] != 0 && v[u] != 1
}

FUNCIÓN DE COTA: v.size() - i
ANALISIS DEL COSTE: El coste de cada iteracion del bucle es constante, y este se recorre v.size() - l veces (=== v.size()).
    Por tanto, el coste del algoritmo pertenece a O(1) * v.size() = O(v.size())
*/


int resolver(const vector<int>& v, int l) {
    if (l == v.size()) return 1;
    int r = 1;
    /*
    INVARIANTE: {
        l <= i <= v.size()
        &&
        unos = UNOS(v,i - l + 1, i)
        &&
        ceros = CEROS(v,i - l + 1,i)
        &&
        r = # (u : l <= u < i : ceros == unos)
    }
    */
    //F. COTA: size - i
    int ceros = 0, unos = 0;
    for (int i = l; i < v.size(); i++) {
        // Se actualiza el numero de ceros y unos antes de comprobar que son iguales
        if (v[i] == 1)
            unos++;
        else if (v[i] == 0)
            ceros++;
        // Se comprueba que el numero de ceros y unos son iguales
        if (ceros == unos)
            r++;
        // Se actualiza el numero de ceros y unos despues de haber comprobado que sean iguales
        if (v[i - l + 1] == 1)
            unos--;
        else if (v[i - l + 1] == 0)
            ceros--;
    }
    return r;
}

/*
POSTCONDICION: {
    r = # (u : l <= u < v.size() : CEROS(v, u - l + 1, u) == UNOS(v, u - l + 1, u))
}
*/

//ANALISIS DEL COSTE: El coste de cada iteracion del bucle es constante, y este se recorre size - l veces (=== size).
// Por tanto, el coste del algoritmo pertenece a O(1)* size = O(size)

void resuelveCaso() {
    int n, l;
    cin >> l >> n;
    vector<int> v(n);
    for (int& i : v)
        cin >> i;
    int sol = resolver(v, l);
    cout << sol << endl;
}


int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    unsigned int numCasos; cin >> numCasos;
    for (int i = 0; i < numCasos; ++i) resuelveCaso();
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}

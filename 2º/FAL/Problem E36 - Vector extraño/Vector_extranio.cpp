#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct tsol {
    bool extranio;
    int sumaPares; 
    int sumaImpares;
    int productoPares;
    int productoImpares;
};


// RECURRENCIA: Sea n el numero de elementos del vector
// T(n) = c si 0 <= n <= 1
// T(n) = 2T(n/2) + c si n > 1
// T(n) pertenece a O(n) en el caso peor ya que es necesario acceder a todos los elementos

// Intervalo cerrado [c, f]. Llamada inicial con c = 0 y f = size - 1
// sumapares + prodimpares <= sumaimpares + prodpares
tsol es_extranio(vector<int>const& v, int size, int c, int f) {
    // CB: 0 elementos
    if (size == 0) return{ true,0,0,1,1 };
    // CB: 1 elemento
    if (c == f) {
        if (v[c] % 2 == 0) {
            return { true,v[c],0,v[c],1};
        }
        else {
            return { true, 0, v[c], 1, v[c] };
        }
    }
    // CR
    int m = (c + f) / 2;
    tsol i = es_extranio(v, size, c, m);
    tsol d = es_extranio(v, size, m + 1, f);
    int sumaPares = i.sumaPares + d.sumaPares;
    int sumaImpares = i.sumaImpares + d.sumaImpares;
    int productoPares = i.productoPares * d.productoPares;
    int productoImpares = i.productoImpares * d.productoImpares;
    bool extranio = (i.extranio || d.extranio) && (i.sumaPares + i.productoImpares <= d.sumaImpares + d.productoPares);

    return { extranio, sumaPares,sumaImpares,productoPares,productoImpares };
}


void resuelveCaso() {
    int size; cin >> size;
    vector<int>v(size);
    for (int& i : v) cin >> i;
    cout << (es_extranio(v, size, 0, size - 1).extranio ? "SI\n" : "NO\n");
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i) resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
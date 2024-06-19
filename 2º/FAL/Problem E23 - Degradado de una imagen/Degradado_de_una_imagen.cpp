#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct tsol {
    bool degradado;
    int suma_izq;
    int suma_der;
};

/* RECURRENCIA: sea n el numero de elementos de la fila de la matriz a procesar
    T(n) = c si 0 < n <= 2
    T(n) = 2T(n/2) si n > 2
    T(n) pertenece a O(n) en el caso peor (una imagen es un degradado)
    T(n) pertenece a O(log(n)) en el caso intermedio (la mitad izquierda de una imagen no es un degradado)
*/
// Intervalo cerrado [c, f]
tsol imagen_degradada(vector<int>const& fila, int n_columnas, int c, int f) {
    // CB: 1 elemento
    if (c == f) return{ true,fila[c],fila[f] };
    // CB: 2 elementos
    if (c == f - 1) return { fila[c] < fila[f],fila[c],fila[f] };
    // CR
    int m = (c + f) / 2;
    tsol i = imagen_degradada(fila, n_columnas, c, m);
    if (i.degradado) {
        tsol d = imagen_degradada(fila, n_columnas, m + 1, f);
        return { i.degradado && d.degradado && i.suma_izq + i.suma_der < d.suma_izq + d.suma_der, i.suma_izq + d.suma_izq,i.suma_der + d.suma_der };
    }
    return { false, i.suma_izq + i.suma_der, 0 };
}



bool resuelveCaso() {
    int n_filas, n_columnas; cin >> n_filas >> n_columnas;
    if (!cin) return false;
    vector<vector<int>> imagen(n_filas, vector<int>(n_columnas));
    for (int i = 0; i < n_filas; i++)
        for (int j = 0; j < n_columnas; j++)
            cin >> imagen[i][j];
    bool degradado = true;
    int i = 0;
    while (i < n_filas && degradado) {
        // Llamada inicial con [0, n_columnas - 1]
        tsol sol = imagen_degradada(imagen[i], n_columnas, 0, n_columnas - 1);
        degradado = sol.degradado;
        i++;
    }
    cout << (degradado ? "SI\n" : "NO\n");
    return true;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}

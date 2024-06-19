#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

const int MAX_PROD_POR_SUPER = 3, MAX_SUPERMERCADOS = 20, MAX_COSTE = std::numeric_limits<int>::max();

void comprar(vector<vector<int>>const&precios, vector<int>&productos_comprados_por_super, vector<int>const&minimos
    ,int&costeActual, int&costeMejor, int supermercados, int productos, int k) {
    for (int s = 0; s < supermercados; s++) {
        
        // Marcaje
        costeActual += precios[s][k];
        productos_comprados_por_super[s]++;

        // esValida()
        if (productos_comprados_por_super[s] <= MAX_PROD_POR_SUPER) {
            // esSolucion()
            if (k == productos - 1) {
                costeMejor = std::min(costeActual, costeMejor);
            }
            else {
                // esSolucionPrometedora()
                if (costeActual + minimos[k + 1] < costeMejor) {
                    comprar(precios,productos_comprados_por_super,minimos,costeActual,costeMejor, supermercados, productos, k + 1);
                }
            }
        }
        
        // Desmarcaje
        costeActual -= precios[s][k];
        productos_comprados_por_super[s]--;

    }
}


void resuelveCaso() {
    // Nivel: productos; Ramificacion: supermercados
    int supermercados, productos; cin >> supermercados >> productos;

    vector<vector<int>>precios(supermercados, vector<int>(productos));
    int costeMejor = MAX_COSTE, costeActual = 0;
    vector<int>minimos(productos, costeMejor), productos_comprados_por_super(supermercados, 0);

    for (int i = 0; i < supermercados; i++) {
        for (int j = 0; j < productos; j++) {
            cin >> precios[i][j];
            minimos[j] = std::min(minimos[j], precios[i][j]);
        }
    }

    // Calculo de los minimos acumulados
    for (int i = productos - 2; i >= 0; i--) {
        minimos[i] += minimos[i + 1];
    }

    comprar(precios,productos_comprados_por_super,minimos,costeActual,costeMejor, supermercados, productos, 0);
    cout << (costeMejor == MAX_COSTE ? "Sin solucion factible" : to_string(costeMejor)) << "\n";

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
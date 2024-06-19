#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

const int MIN_BENEFICIO = std::numeric_limits<int>::min();

// Nivel: posicion; Ramificacion: artista
void va_concierto(vector<int>&orden, int artistas, vector<vector<int>>const& donaciones, vector<vector<int>>const& vetos, vector<int>const& maximos, vector<bool>& seleccionados,
    int& beneficioActual, int& beneficioMejor, int k) {

    for (int i = 0; i < artistas; i++) {

        if (!seleccionados[i]) {

            // esValida() - falta implementar los vetos
            int j = 0;
            while (j < orden.size() && vetos[i][orden[j]] != 0) {
                j++;
            }
            if (j == orden.size()) {
            //if (i != k && seleccionados[k] && vetos[i][k] == 1) {

                // Marcaje
                beneficioActual += donaciones[i][k];
                seleccionados[i] = true;
                orden.push_back(i);

                // esSolucion()
                if (k == artistas - 1) {
                    beneficioMejor = std::max(beneficioActual, beneficioMejor);
                }
                else {

                    // esSolucionPrometedora()
                    if (beneficioMejor < beneficioActual + maximos[k + 1]) {
                        va_concierto(orden, artistas, donaciones, vetos, maximos, seleccionados, beneficioActual, beneficioMejor, k + 1);
                    }

                }

                // Desmarcaje
                beneficioActual -= donaciones[i][k];
                seleccionados[i] = false;
                orden.pop_back();

            }

        }

    }

}


void resuelveCaso() {
    int artistas; cin >> artistas;
    vector<vector<int>>donaciones(artistas, vector<int>(artistas)), vetos(artistas, vector<int>(artistas));
    vector<int>maximos(artistas, MIN_BENEFICIO), maximosAcumulados(artistas, 0);
    vector<bool>seleccionados(artistas, false);

    for (int i = 0; i < artistas; i++) {
        for (int j = 0; j < artistas; j++) {
            cin >> donaciones[i][j];
            maximos[i] = std::max(maximos[i], donaciones[i][j]);
        }
    }

    for (int i = 0; i < artistas; i++) {
        for (int j = 0; j < artistas; j++) {
            cin >> vetos[i][j];
        }
    }

    int beneficioActual = 0, beneficioMejor = MIN_BENEFICIO;

    vector<int>orden;

    // Calculo de los maximos acumulados
    for (int i = artistas - 2; i >= 0; i--) {
        //maximos[i] += maximos[i + 1];
        maximosAcumulados[i] = maximosAcumulados[i + 1] + maximos[i + 1];
    }
    //va_concierto(orden, artistas, donaciones, vetos, maximos, seleccionados, beneficioActual, beneficioMejor, 0);
    va_concierto(orden, artistas, donaciones, vetos, maximosAcumulados, seleccionados, beneficioActual, beneficioMejor, 0);



    cout << (beneficioMejor != MIN_BENEFICIO ? to_string(beneficioMejor) : "NEGOCIA CON LOS ARTISTAS") << "\n";

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
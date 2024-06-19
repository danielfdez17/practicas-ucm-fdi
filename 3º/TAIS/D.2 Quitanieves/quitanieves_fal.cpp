#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

const int MIN_CALIDAD = std::numeric_limits<int>::min();

void va_invernalia(int carros, int caminos, vector<int>const& anchuras_carros, vector<int>const& anchuras_caminos, vector<vector<int>>const& calidades, 
    vector<int>const& maximosAcumulados, vector<bool>& carros_usados, int& calidadActual, int& calidadMejor, int k) {

    // Asignar un carro al camino k
    for (int c = 0; c < carros; c++) {

        if (!carros_usados[c]) {

            // esValida()
            if (anchuras_carros[c] <= anchuras_caminos[k]) {

                // Marcaje
                calidadActual += calidades[c][k];
                carros_usados[c] = true;

                // esSolucion()
                if (k == caminos - 1) {
                    calidadMejor = std::max(calidadMejor, calidadActual);
                }
                else {

                    // esSolucionPrometedora
                    if (calidadMejor < calidadActual + maximosAcumulados[k + 1]) {

                        va_invernalia(carros, caminos, anchuras_carros, anchuras_caminos, calidades, maximosAcumulados, carros_usados, calidadActual, calidadMejor, k + 1);

                    }

                }

                // Desmarcaje
                calidadActual -= calidades[c][k];
                carros_usados[c] = false;

            }

        }


    }

    // No asignar un carro al camino k

    // esSolucion()
    if (k == caminos - 1) {
        calidadMejor = std::max(calidadMejor, calidadActual);
    }
    else {

        // esSolucionPrometedora
        if (calidadMejor < calidadActual + maximosAcumulados[k + 1]) {

            va_invernalia(carros, caminos, anchuras_carros, anchuras_caminos, calidades, maximosAcumulados, carros_usados, calidadActual, calidadMejor, k + 1);

        }

    }


}


void resuelveCaso() {
    int carros, caminos; cin >> carros >> caminos;
    vector<int>anchuras_carros(carros, 0), anchuras_caminos(caminos, 0); // anchuras de carros y caminos
    vector<vector<int>>calidades(carros, vector<int>(caminos)); // matriz de calidades
    vector<int>maximos(caminos, MIN_CALIDAD), maximosAcumulados(caminos, 0); // vectores de maximos para la poda
    vector<bool>carros_usados(carros, false); // marcador de carros usados
    for (int& i : anchuras_carros) cin >> i;
    for (int& i : anchuras_caminos) cin >> i;
    for (int i = 0; i < carros; i++) {
        for (int j = 0; j < caminos; j++) {
            cin >> calidades[i][j];
            maximos[j] = std::max(calidades[i][j], maximos[j]);
        }
    }

    // Si hay carros
    if (carros > 0) {
        // Calculo de los maximos acumulados
        for (int i = caminos - 2; i >= 0; i--)
            maximos[i] += maximos[i + 1];
            //maximosAcumulados[i] = maximosAcumulados[i + 1] + maximos[i + 1];


        int calidadActual = 0, calidadMejor = MIN_CALIDAD;

        // Nivel: camino; Ramificacion: carros
        va_invernalia(carros, caminos, anchuras_carros, anchuras_caminos, calidades, maximos, carros_usados, calidadActual, calidadMejor, 0);
        //va_invernalia(carros, caminos, anchuras_carros, anchuras_caminos, calidades, maximosAcumulados, carros_usados, calidadActual, calidadMejor, 0);

        cout << calidadMejor << "\n";

    }
    else
        cout << "0\n";

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
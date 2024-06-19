#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

const int MAX_COSTE = std::numeric_limits<int>::max();

// Nivel: funcionarios; Ramificacion: trabajos
void va_funcionarios(vector<vector<int>>const& tiempos, vector<int>const& minimosAcu, vector<bool>&trabajos, int& tiempoActual, int& tiempoMejor, int funcionarios, int k) {
    for (int i = 0; i < funcionarios; i++) {

        // esValida()
        if (!trabajos[i]) {

            // Marcaje
            tiempoActual += tiempos[k][i];
            trabajos[i] = true;

            if (tiempoActual + minimosAcu[k] < tiempoMejor) {
                if (k == funcionarios - 1) {
                    tiempoMejor = std::min(tiempoMejor, tiempoActual);
                }
                else {
                    va_funcionarios(tiempos, minimosAcu, trabajos, tiempoActual, tiempoMejor, funcionarios, k + 1);
                }
            }

            // Desmarcaje
            tiempoActual -= tiempos[k][i];
            trabajos[i] = false;

        }
    }
}


bool resuelveCaso() {
    int funcionarios; cin >> funcionarios;
    if (funcionarios == 0) return false;
    vector<vector<int>>tiempos(funcionarios, vector<int>(funcionarios));
    vector<int>minimos(funcionarios, MAX_COSTE), minimosAcu(funcionarios, 0);
    vector<bool>trabajos(funcionarios, false);

    for (int i = 0; i < funcionarios; i++) {
        for (int j = 0; j < funcionarios; j++) {
            cin >> tiempos[i][j];
            minimos[i] = std::min(minimos[i], tiempos[i][j]);
        }
    }

    int tiempoActual = 0, tiempoMejor = MAX_COSTE;

    // Calculo de los minimos acumulados
    for (int i = funcionarios - 2; i >= 0; i--)
        minimosAcu[i] = minimosAcu[i + 1] + minimos[i + 1];

    va_funcionarios(tiempos, minimosAcu, trabajos, tiempoActual, tiempoMejor, funcionarios, 0);
    cout << tiempoMejor << "\n";

    return true;
}


int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso());
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
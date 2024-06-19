#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int AZULES = 0, ROJAS = 1, VERDES = 2, SIN_PIEZA = -1;

bool esValida(vector<int>const& torre, vector<int>const& disponibles, vector<int>const& usadas, int k) {
    return disponibles[AZULES] >= 0 && disponibles[ROJAS] >= 0 && disponibles[VERDES] >= 0 &&
        !(torre[k - 1] == VERDES && torre[k] == VERDES) &&
        usadas[AZULES] >= usadas[VERDES];
}

bool esSolucion(int altura, int k) {
    return k == altura - 1;
}

bool esSolucionValida(vector<int>const&torre, vector<int>const&disponibles, vector<int>const&usadas, int k) {
    return torre[0] == ROJAS &&
        usadas[ROJAS] > usadas[AZULES] + usadas[VERDES];
}

void mostrar(vector<int>& torre) {
    for (int& i : torre) {
        switch (i) {
        case AZULES: cout << "azul "; break;
        case ROJAS: cout << "rojo "; break;
        case VERDES: cout << "verde "; break;
        default: cout << " "; break;
        }
    }
    cout << "\n";
}
// Profundidad: altura de la torre; Ramificacion: numero de piezas distintas
void construir(vector<int>& torre, vector<int>& disponibles, vector<int>& usadas, int altura, int&num_soluciones, int ramificacion, int k) {
    for (int i = 0; i < ramificacion; i++) {

        // Marcaje
        disponibles[i]--;
        usadas[i]++;
        torre[k] = i;

        if (esValida(torre, disponibles, usadas, k)) {
            if (esSolucion(altura, k)) {
                if (esSolucionValida(torre, disponibles, usadas, k)) {
                    mostrar(torre);
                    num_soluciones++;
                }
            }
            else {
                construir(torre, disponibles, usadas, altura, num_soluciones, ramificacion, k + 1);
            }
        }

        // Desmarcaje
        disponibles[i]++;
        usadas[i]--;
        torre[k] = SIN_PIEZA;

    }
}


bool resuelveCaso() {
    int altura, azules, rojas, verdes; cin >> altura >> azules >> rojas >> verdes;
    if (altura == 0 && azules == 0 && rojas == 0 && verdes == 0) return false;

    vector<int>disponibles(3), usadas(3, 0), torre(altura, SIN_PIEZA);
    
    disponibles[AZULES] = azules;
    disponibles[ROJAS] = rojas - 1; usadas[ROJAS] = 1;
    disponibles[VERDES] = verdes;
    torre[0] = ROJAS;
    
    int num_soluciones = 0, ramificacion = 3;
    
    construir(torre, disponibles, usadas, altura, num_soluciones, ramificacion, 1);
    
    if (num_soluciones == 0) cout << "SIN SOLUCION\n";
    cout << "\n";
    return true;
}


int main() {
#ifndef DOMJUDGE
    ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso());
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
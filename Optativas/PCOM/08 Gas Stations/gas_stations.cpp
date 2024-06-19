// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int L, G; cin >> L >> G;
    if (L == 0 && G == 0) return false;
    int x, r;
    vector<pair<int, int>>gas_stations;
    for (int i = 0; i < G; i++) {
        cin >> x >> r;
        gas_stations.push_back({x - r, x + r});
    }

    sort(gas_stations.begin(), gas_stations.end());

    int beginning = 0; bool covered = true;
    for (int i = 0; i < G; i++) {
        if (gas_stations[i].second <= beginning) continue;
        else if (gas_stations[i].first <= beginning && gas_stations[i].second > beginning)
            beginning = gas_stations[i].second;
        else {
            covered = false;
        }
    }

    if (beginning < L) covered = false;

    if (!covered) cout << "-1\n";
    else {
        int i = 0, eliminated = 0; beginning = 0;
        while (beginning < L) {
            int end = gas_stations[i].second;
            eliminated++; i++;
            while (i < G && gas_stations[i].first <= beginning) {
                end = std::max(end, gas_stations[i].second);
                i++;
            }
            beginning = end;
        }
        cout << G - eliminated << "\n";
    }

    // escribir sol
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}

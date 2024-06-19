// Daniel Fernandez Ortiz
// PC03
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

// función que resuelve el problema
double resolver(double x, double y, double c) {

    double lower = 0, higher = min(x, y), middle;

    int cont = 100;
    while (cont--) {
        middle = (lower + higher) / 2.0;
        double h1 = sqrt((y * y) - (middle * middle));
        double h2 = sqrt((x * x) - (middle * middle));
        double sol = (h1 * h2) / (h1 + h2);

        if (sol < c) higher = middle;
        else lower = middle;
    }
    return lower;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    double x, y, c;
    cin >> x >> y >> c;
    
    if (!std::cin)
        return false;

    
    cout << fixed << setprecision(3) << resolver(x, y, c) << "\n";
    
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
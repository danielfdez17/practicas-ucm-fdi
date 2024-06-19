// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: P16-PAPA NOEL
// Comentario general sobre la solución: Número de casos ilimitado


#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

const int MAXIMO = 100; // Constante que delimita el número de juguetes, proveedores y productos

typedef int tMatrix[MAXIMO][MAXIMO]; // Matriz que guarda la información

struct tMatriz { // Lista donde guardar las matrices
    tMatrix matriz;
    int filas = 0;
    int columnas = 0;
};
// Función que devuelve el resultado de multiplicar la matriz a por la matriz b
tMatriz operator* (tMatriz const& a, tMatriz const& b) {
    tMatriz matriz{};
    if (a.columnas == b.filas) {
        for (int i = 0; i < a.filas; i++) {
            for (int j = 0; j < b.columnas; j++) {
                //for (int f = 0; f < matriz.filas; f++) {
                    for (int c = 0; c < b.filas; c++) {
                        matriz.matriz[i][j] += (a.matriz[i][c] * b.matriz[c][j]);
                    }
                //}
            }
        }
    }
    matriz.filas = a.filas;
    matriz.columnas = b.columnas;
    return matriz;
}
istream& operator>> (istream& in, tMatriz& m) {
    for (int i = 0; i < m.filas; i++) {
        for (int j = 0; j < m.columnas; j++) {
            in >> m.matriz[i][j];
        }
    }
    return in;
}
ostream& operator<< (ostream& out, tMatriz const& m) {
    for (int i = 0; i < m.filas; i++) {
        for (int j = 0; j < m.columnas; j++) {
            out << m.matriz[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

bool resuelveCaso();

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("in.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("out.txt");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    tMatriz matriz1{}, matriz2{}, resultado{};
    // leer los datos de la entrada
    cin >> matriz1.filas >> matriz1.columnas;
    if (matriz1.filas <= MAXIMO && matriz1.columnas <= MAXIMO) {
        cin >> matriz1;
    }
    cin >> matriz2.filas >> matriz2.columnas;
    if (matriz2.filas <= MAXIMO && matriz2.columnas <= MAXIMO) {
        cin >> matriz2;
    }
    if (!std::cin)  // fin de la entrada
        return false;
    resultado = matriz1 * matriz2;
    // escribir sol
    cout << resultado << endl;
    return true;
}

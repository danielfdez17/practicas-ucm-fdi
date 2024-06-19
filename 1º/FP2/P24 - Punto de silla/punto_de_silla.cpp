// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: P24-PUNTO DE SILLA
// Comentario general sobre la solución: Número de casos delimitado por un valor centinela


#include <iostream>
#include <fstream>
using namespace std;

const int MAXIMO = 100; // Constante que delimita el tamaño máximo de la matriz

typedef int tMatriz[MAXIMO][MAXIMO]; // Matriz en la que guardar los valores sobre los que operar

void resolver(const tMatriz& matriz, int filas, int columnas);

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
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

void resolver(const tMatriz& matriz, int filas, int columnas) {
    bool tiene = false;
    int mayorF = 0, menorF = 0, mayorC = 0, menorC = 0;
    int i = 0, j = 0;
    // tiene=true <-> elemento >= que los de su fila && <= que los de su columna || <= que los de su fila && >= que los de su columna
    while ((i < filas) && !tiene) {
        j = 0, mayorF = 0, menorF = 0, mayorC = 0, menorC = 0;
        while ((j < columnas) && !tiene) {
            for (int f = 0; f < filas; f++) {
                if (matriz[i][j] > matriz[f][j]) {
                    mayorF++;
                }
                else if (matriz[i][j] < matriz[f][j]) {
                    menorF++;
                }
                else {
                    mayorF++;
                    menorF++;
                }
            }
            for (int c = 0; c < columnas; c++) {
                if (matriz[i][j] < matriz[i][c]) {
                    menorC++;
                }
                else if (matriz[i][j] > matriz[i][c]) {
                    mayorC++;
                }
                else {
                    menorC++;
                    mayorC++;
                }
            }
            tiene = ((mayorF == filas && menorC == columnas) || (menorF == filas && mayorC == columnas));
            if (!tiene) {
                j++;
            }
        }
        if (!tiene) {
            i++;
        }
    }
    if (tiene) {
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}

bool resuelveCaso() {
    tMatriz matriz{};
    int filas, columnas;
    // leer los datos de la entrada
    cin >> filas >> columnas;
    if ((filas == 0) || (columnas == 0))
        return false;
    if ((filas <= MAXIMO) && (columnas <= MAXIMO)) {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cin >> matriz[i][j];
            }
        }
    }
    // escribir sol
    resolver(matriz, filas, columnas);

    return true;
}

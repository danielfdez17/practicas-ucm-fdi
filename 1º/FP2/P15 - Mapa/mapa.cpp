// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: Máxima cota de un mapa topográfico
// Comentario general sobre la solución: Número de casos de prueba ilimitados


#include <iostream>
#include <fstream>
using namespace std;
// Dimension maxima de las cuadriculas/matrices
const int DIM = 100;
// Matriz que almacena la cuadricula
typedef int tMatriz[DIM][DIM];
// Estructura que contiene una posicion de la cuadricula
struct tPosicion {
    int fila, columna;
};

// función que resuelve el problema
void resolver(const tMatriz& matriz, int filas, int columnas, int& altura, tPosicion& pos);

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso();

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("input.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
   std::ofstream out("output.txt");
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

void resolver(const tMatriz& matriz, int filas, int columnas, int& altura, tPosicion& pos) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (matriz[f][c] > altura) {
                altura = matriz[f][c];
                pos.fila = f;
                pos.columna = c;
            }
        }
    }
}

bool resuelveCaso() {
    tMatriz matriz;
    tPosicion pos;
    int altura = -1000;
    int filas = 0, columnas = 0; // Representan la dimension de la matriz
    // leer los datos de la entrada
    cin >> filas >> columnas;
    if (filas > 0 && filas <= DIM && columnas > 0 && columnas <= DIM) {
        for (int f = 0; f < filas; f++) {
            for (int c = 0; c < columnas; c++) {
                cin >> matriz[f][c];
            }
        }
    }
    if (!std::cin)  // fin de la entrada
        return false;

    resolver(matriz,filas,columnas,altura,pos);

    // escribir sol
    cout << altura << " " << pos.fila << " " << pos.columna << endl;
    return true;
}

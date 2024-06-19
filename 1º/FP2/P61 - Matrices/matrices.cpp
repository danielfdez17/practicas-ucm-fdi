//Compilador y S.O. utilizado: VS 2019
//Nombre del problema: Diversión con matrices Parte 2
//Comentario general sobre la solución: Casos de prueba ilimitados acotados por un caso de prueba especial


#include <iostream>
#include <fstream>
#include<iomanip>
using namespace std;
// Constante que determina la dimension de la matriz
const int DIM = 20;
// Constante que delimita el numero maximo de transformaciones que se pueden realizar a la matriz
const int TRANSFORMACIONES = 10;
// Matriz sobre la que operar
typedef int tMatriz[DIM][DIM];


// Podria simplificar las dos funciones en una si meto como parametro de entrada la operacion 

// Procedimiento que intercambia las filas f1 y f2 de la matriz
void rotarFila(tMatriz matriz, int filas, int columnas, int operando);
// Procedimiento que intercambia las columnas c1 y c2 de la matriz
void rotarCol(tMatriz matriz, int filas, int columnas, int operando);
// Procedimiento que muestra la matriz final
void mostrar(const tMatriz& matriz, int filas, int columnas);


// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
//void resolver(Datos datos);

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
// Parece que funciona
void rotarFila(tMatriz matriz, int filas, int columnas, int operando) {
    int aux = -1; // Variable con la que poder hacer los cambios de valores
    int fila = 0; // Variable auxiliar para guardar la fila que quiero rotar
    if (operando < 0) { // Se rota la fila operando de dcha a izq
        fila = abs(operando) - 1; // Guardo en otra variable auxiliar el valor abs del operando
        //fila--; // Le resto uno para que no acceda a una pos erronea, ya que estoy recorriendo la matriz desde 0 hasta columnas (sin incluir)
        aux = matriz[fila][0]; // En aux guardo el valor de la pos oper,0
        for (int c = 0; c < columnas; c++) { // Desde la primera columnas hasta la ultima
            matriz[fila][c] = matriz[fila][c + 1]; // En la pos oper,c guardo el valor de la columna siguiente en la fila oper
        }
        matriz[fila][columnas - 1] = aux; // Guardo en la ultima columna de la fila oper el valor de aux (el valor de la primera columna de la misma fila)
    }
    else if (operando > 0) { // Se rota la fila operando de izq a decha
        fila = operando - 1;
        aux = matriz[fila][columnas - 1]; // Guardo en aux el valor de la ultima columna de la fila oper
        for (int c = columnas - 1; c > 0; c--) { // Desde la ultima columna hasta la primera
            // Hasta 0 para asegurarme que no accedo a posiciones de memoria no validas
            matriz[fila][c] = matriz[fila][c - 1]; // En la columna c guardo el valor de la columna anterior en la fila oper
        }
        matriz[fila][0] = aux; // Guardo en la primera columna el valor de aux (el valor de la ultima columna) de la fila oper
    }
}
// Parece que funciona
void rotarCol(tMatriz matriz, int filas, int columnas, int operando) {
    int aux = -1; // Variable con la que poder hacer los cambios de valores
    int oper = 0; // Variable auxiliar para guardar la columna que quiero rotar
    if (operando < 0) { // Se rota la columna operando de abajo a arriba
        oper = abs(operando);
        oper -= 1;
        aux = matriz[0][oper]; // En aux guardo el valor de la primera fila de la columna oper 
        for (int f = 0; f < filas; f++) { // Desde la primera fila hasta la ultima
            matriz[f][oper] = matriz[f + 1][oper]; // En la fila f guardo el valor de la fila siguiente en la columna oper
        }
        matriz[filas - 1][oper] = aux; // En la ultima fila guardo el valor de aux (valor de la primera fila) de la columna oper
    }
    else if (operando > 0) { // Se rota la columna operando de arriba a abajo
        oper = operando - 1;
        aux = matriz[filas - 1][oper]; // En aux guardo el valor de la ultima fila de la columna oper
        for (int f = filas - 1; f > 0; f--) { // Desde la ultima fila hasta la primera
            matriz[f][oper] = matriz[f - 1][oper]; // En la fila f guardo el valor de la fila anterior de la columna oper
        }
        matriz[0][oper] = aux; // En la primera fila guardo el valor de aux (el valor de la ultima fila) de la columna oper
    }
}

void mostrar(const tMatriz& matriz, int filas, int columnas) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (c == columnas - 1) {
                cout << matriz[f][c] << endl;
            }
            else {
                cout << matriz[f][c] << " ";
            }
        }
    }
    cout << "---" << endl;
}


bool resuelveCaso() {
    tMatriz matriz = { 0 };
    int filas = 0, columnas = 0; // Representan la dimension de la matriz
    int transformaciones = 0; // Representa el numero de transformaciones que se van a hacer sobre la matriz
    string operacion; // Operacion
    int operando = 0; // Operando segun la operacion (fila o columna)
    // leer los datos de la entrada
    cin >> filas >> columnas;
    if (filas > 0 && filas <= DIM && columnas > 0 && columnas <= DIM) {
        for (int f = 0; f < filas; f++) {
            for (int c = 0; c < columnas; c++) {
                cin >> matriz[f][c];
            }
        }
        cin >> transformaciones;
        if (transformaciones > 0 && transformaciones <= TRANSFORMACIONES) {
            for (int t = 0; t < transformaciones; t++) {
                cin >> operacion;
                if (operacion == "rotarFila") {
                    cin >> operando;
                    rotarFila(matriz, filas, columnas, operando);
                }
                else if (operacion == "rotarCol") {
                    cin >> operando;
                    rotarCol(matriz, filas, columnas, operando);
                }
            }
        }
    }

    if (filas == 0 && columnas == 0)
        return false;

    //resolver(datos);

    // escribir sol
    mostrar(matriz, filas, columnas);

    return true;
}

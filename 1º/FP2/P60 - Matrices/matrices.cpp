////RE
////Nombre del problema: Diversión con matrices Parte 1
////Comentario general sobre la solución: Casos de prueba ilimitados acotados por un caso de prueba especial

//#include <iostream>
//#include <fstream>
//using namespace std;
////Constante que determina el tamaño maximo de las filas y columnas de la matriz
//const int DIM = 20;
////Representa el numero maximo de transformaciones posibles
//const int TRANSFORMACIONES = 10;
////Matriz que almacena los datos de entrada
//typedef int tMatriz[DIM][DIM];
//
////Procedimiento para intercambiar las filas f1 y f2
//void swapF(tMatriz matriz, /*int filas,*/ int columnas, int f1, int f2);
////Procedimiento para intercambiar las columnas c1 y c2
//void swapC(tMatriz matriz, int filas, /*int columnas,*/ int c1, int c2);
////Procedimiento para rellenar las diagonales de f y c con el valor dato
//void cruz(tMatriz matriz, int filas, int columnas, int f, int c, int dato);
////Procedimiento que muestra la matriz resultante
//void mostrar(const tMatriz& matriz, int filas, int columnas);
//
////función que resuelve el problema
////comentario sobre el coste, O(f(N)), donde N es ...
////void resolver(tMatriz matriz, int filas, int columnas);
//
////resuelve un caso de prueba, leyendo de la entrada la
////configuración, y escribiendo la respuesta
//bool resuelveCaso();
//
//int main() {
//    //ajustes para que cin extraiga directamente de un fichero
//#ifndef DOMJUDGE
//    std::ifstream in("input.txt");
//    auto cinbuf = std::cin.rdbuf(in.rdbuf());
//    std::ofstream out("output.txt");
//    auto coutbuf = std::cout.rdbuf(out.rdbuf());
//#endif
//
//    while (resuelveCaso());
//
//    //para dejar todo como estaba al principio
//#ifndef DOMJUDGE
//    std::cin.rdbuf(cinbuf);
//    std::cout.rdbuf(coutbuf);
//    system("PAUSE");
//#endif
//    return 0;
//}
//
//void swapF(tMatriz matriz, /*int filas,*/ int columnas, int f1, int f2) {
//    int aux = -1; // Variable auxiliar con la que poder intercambiar las filas f1 y f2
//    for (int c = 0; c < columnas; c++) { // Solo recorro las columnas porque no me interesa recorrer todas las filas
//        aux = matriz[f1][c]; // En aux guardo el valor de la primera fila f1 y columna c
//        matriz[f1][c] = matriz[f2][c]; // En la primera fila y columna c guardo el valor de la fila f2 y columna c
//        matriz[f2][c] = aux; // En la fila f2 y la columna c guardo el valor de aux (valor de la fila f1 y columna c)
//    }
//}
//
//void swapC(tMatriz matriz, int filas, /*int columnas,*/ int c1, int c2) {
//    int aux = -1; // Variable con la que poder intercambiar las columnas c1 y c2
//    for (int f = 0; f < filas; f++) { // Solo recorro las filas porque no me interesa recorrer todas las columnas
//        aux = matriz[f][c1]; // En aux guardo el valor de la fila f y columna c1
//        matriz[f][c1] = matriz[f][c2]; // En la pos fila f y columna c1 guardo el valor de la fila f y columna c2
//        matriz[f][c2] = aux; // En la pos fila f y columna c2 guardo el valor de aux (el valor de la fila f y columna c1)
//    }
//}
//
//void cruz(tMatriz matriz, int filas, int columnas, int f, int c, int dato) {
//    int i = f, j = c; // Variables que guardan los valores de la pos f,c sobre la que operar
//     //Diagonal hacia abajo y hacia la derecha 
//    matriz[i][j] = dato;
//    while (i < filas && j < columnas) {
//        i++;
//        j++;
//        matriz[i][j] = dato;
//    }
//    i = f;
//    j = c;
//    //Diagonal hacia abajo y hacia la izquierda
//    while (i < filas && j >= 0) {
//        i++;
//        j--;
//        matriz[i][j] = dato;
//    }
//    i = f;
//    j = c;
//    //Diagonal hacia arriba y hacia la derecha
//    while (i >= 0 && j < columnas) {
//        i--;
//        j++;
//        matriz[i][j] = dato;
//    }
//    i = f;
//    j = c;
//    //Diagonal hacia arriba y hacia la izquierda
//    while (i >= 0 && j >= 0) {
//        i--;
//        j--;
//        matriz[i][j] = dato;
//    }
//}
//
//void mostrar(const tMatriz& matriz, int filas, int columnas) {
//    for (int f = 0; f < filas; f++) {
//        for (int c = 0; c < columnas; c++) {
//            if (c == columnas - 1) {
//                cout << matriz[f][c] << endl;
//            }
//            else {
//                cout << matriz[f][c] << " ";
//            }
//        }
//    }
//    cout << "---" << endl;
//}
//
////void resolver(tMatriz matriz, int filas, int columnas) {
////    int transformaciones = 0; // Representa el numero de transformaciones que se quieren realizar
////    string operacion; // Representa el tipo de operacion que se quiere realizar
////    int pos1 = 0, pos2 = 0; // Representan las filas y columnas con las que se quiere operar segun el tipo de operacion especificada
////    int dato = 0; // Representa el dato que se quiere sobreescribir en las diagonales de una posicion dada
////    cin >> transformaciones;
////    if (transformaciones >= 1 && transformaciones <= TRANSFORMACIONES) {
////        for (int t = 0; t < transformaciones; t++) {
////            cin >> operacion;
////            if (operacion == "columnas") {
////                cin >> pos1 >> pos2;
////                swapC(matriz, filas, columnas, pos1 - 1, pos2 - 1);
////            }
////            else if (operacion == "filas") {
////                cin >> pos1 >> pos2;
////                swapF(matriz, filas, columnas, pos1 - 1, pos2 - 1);
////            }
////            else if (operacion == "cruz") {
////                cin >> pos1 >> pos2 >> dato;
////                cruz(matriz, filas, columnas, pos1 - 1, pos2 - 1, dato);
////            }
////        }
////    }
////}
//
//bool resuelveCaso() {
//    tMatriz matriz = { 0 };
//    int filas = 0, columnas = 0; // Representan la dimension de la matriz
//    int transformaciones = 0; // Representa el numero de transformaciones que se quieren realizar
//    string operacion; // Representa el tipo de operacion que se quiere realizar
//    int pos1 = 0, pos2 = 0; // Representan las filas y columnas con las que se quiere operar segun el tipo de operacion especificada
//    int dato = 0; // Representa el dato que se quiere sobreescribir en las diagonales de una posicion dada
//
//    //leer los datos de la entrada
//    cin >> filas >> columnas;
//    if (filas >= 1 && filas <= DIM && columnas >= 1 && columnas <= DIM) {
//        for (int f = 0; f < filas; f++) {
//            for (int c = 0; c < columnas; c++) {
//                cin >> matriz[f][c];
//            }
//        }
//        cin >> transformaciones;
//        if (transformaciones >= 1 && transformaciones <= TRANSFORMACIONES) {
//            for (int t = 0; t < transformaciones; t++) {
//                cin >> operacion;
//                if (operacion == "columnas") {
//                    cin >> pos1 >> pos2;
//                    swapC(matriz, filas, /*columnas,*/ pos1 - 1, pos2 - 1);
//                }
//                else if (operacion == "filas") {
//                    cin >> pos1 >> pos2;
//                    swapF(matriz, /*filas,*/ columnas, pos1 - 1, pos2 - 1);
//                }
//                else if (operacion == "cruz") {
//                    cin >> pos1 >> pos2 >> dato;
//                    cruz(matriz, filas, columnas, pos1 - 1, pos2 - 1, dato);
//                }
//            }
//        }
//    }
//    
//    /*else {
//        return false;
//    }*/
//    if (filas == 0 && columnas == 0)
//        return false;
//
//    //resolver(matriz, filas, columnas);
//    //escribir sol
//    mostrar(matriz, filas, columnas);
//
//    return true;
//}

// WA
//Compilador y S.O. utilizado: VS 2019
//Nombre del problema: Diversión con matrices Parte 1
//Comentario general sobre la solución: Casos de prueba ilimitados acotados por un caso de prueba especial

#include <iostream>
#include <fstream>
using namespace std;
//Constante que determina el tamaño maximo de las filas y columnas de la matriz
const int DIM = 20;
//Representa el numero maximo de transformaciones posibles
const int TRANSFORMACIONES = 10;
//Matriz que almacena los datos de entrada
typedef int tMatriz[DIM][DIM];

// Intentar con un array cuatridimensional para guardar las operaciones, filas/columnas y el dato, segun corresponda
typedef string tOperaciones[TRANSFORMACIONES][TRANSFORMACIONES][TRANSFORMACIONES][TRANSFORMACIONES];

//Procedimiento para intercambiar las filas f1 y f2
void swapF(tMatriz matriz, int filas, int columnas, int f1, int f2);
//Procedimiento para intercambiar las columnas c1 y c2
void swapC(tMatriz matriz, int filas, int columnas, int c1, int c2);
//Procedimiento para rellenar las diagonales de f y c con el valor dato
void cruz(tMatriz matriz, int filas, int columnas, int f, int c, int dato);
//Procedimiento que muestra la matriz resultante
void mostrar(const tMatriz& matriz, int filas, int columnas);

//función que resuelve el problema
//comentario sobre el coste, O(f(N)), donde N es ...
void resolver(tMatriz matriz, int filas, int columnas);

//resuelve un caso de prueba, leyendo de la entrada la
//configuración, y escribiendo la respuesta
bool resuelveCaso();

int main() {
    //ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("input.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("output.txt");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    while (resuelveCaso());

    //para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}

void swapF(tMatriz matriz, int filas, int columnas, int f1, int f2) {
    int aux = -1; // Variable auxiliar con la que poder intercambiar las filas f1 y f2
    for (int c = 0; c < columnas; c++) { // Solo recorro las columnas porque no me interesa recorrer todas las filas
        aux = matriz[f1][c]; // En aux guardo el valor de la primera fila f1 y columna c
        matriz[f1][c] = matriz[f2][c]; // En la primera fila y columna c guardo el valor de la fila f2 y columna c
        matriz[f2][c] = aux; // En la fila f2 y la columna c guardo el valor de aux (valor de la fila f1 y columna c)
    }
}

void swapC(tMatriz matriz, int filas, int columnas, int c1, int c2) {
    int aux = -1; // Variable con la que poder intercambiar las columnas c1 y c2
    for (int f = 0; f < filas; f++) { // Solo recorro las filas porque no me interesa recorrer todas las columnas
        aux = matriz[f][c1]; // En aux guardo el valor de la fila f y columna c1
        matriz[f][c1] = matriz[f][c2]; // En la pos fila f y columna c1 guardo el valor de la fila f y columna c2
        matriz[f][c2] = aux; // En la pos fila f y columna c2 guardo el valor de aux (el valor de la fila f y columna c1)
    }
}

void cruz(tMatriz matriz, int filas, int columnas, int f, int c, int dato) {
    int i = f, j = c; // Variables que guardan los valores de la pos f,c sobre la que operar
     //Diagonal hacia abajo y hacia la derecha 
    while (i < filas && j < columnas) {
        matriz[i][j] = dato;
        i++;
        j++;
    }
    i = f;
    j = c;
    //Diagonal hacia abajo y hacia la izquierda
    while (i < filas && j >= 0) {
        matriz[i][j] = dato;
        i++;
        j--;
    }
    i = f;
    j = c;
    //Diagonal hacia arriba y hacia la derecha
    while (i >= 0 && j < columnas) {
        matriz[i][j] = dato;
        i--;
        j++;
    }
    i = f;
    j = c;
    //Diagonal hacia arriba y hacia la izquierda
    while (i >= 0 && j >= 0) {
        matriz[i][j] = dato;
        i--;
        j--;
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

void resolver(tMatriz matriz, int filas, int columnas) {
    int transformaciones = 0; // Representa el numero de transformaciones que se quieren realizar
    string operacion; // Representa el tipo de operacion que se quiere realizar
    int pos1 = 0, pos2 = 0; // Representan las filas y columnas con las que se quiere operar segun el tipo de operacion especificada
    int dato = 0; // Representa el dato que se quiere sobreescribir en las diagonales de una posicion dada
    cin >> transformaciones;
    if (transformaciones >= 1 && transformaciones <= TRANSFORMACIONES) {
        for (int t = 0; t < transformaciones; t++) {
            cin >> operacion;
            if (operacion == "columnas") {
                cin >> pos1 >> pos2;
                swapC(matriz, filas, columnas, pos1 - 1, pos2 - 1);
            }
            else if (operacion == "filas") {
                cin >> pos1 >> pos2;
                swapF(matriz, filas, columnas, pos1 - 1, pos2 - 1);
            }
            else if (operacion == "cruz") {
                cin >> pos1 >> pos2 >> dato;
                cruz(matriz, filas, columnas, pos1 - 1, pos2 - 1, dato);
            }
        }
    }

}

bool resuelveCaso() {
    tMatriz matriz = { 0 };
    int filas = 0, columnas = 0; // Representan la dimension de la matriz
    //int transformaciones = 0; // Representa el numero de transformaciones que se quieren realizar
    //string operacion; // Representa el tipo de operacion que se quiere realizar
    //int pos1 = 0, pos2 = 0; // Representan las filas y columnas con las que se quiere operar segun el tipo de operacion especificada
    //int dato = 0; // Representa el dato que se quiere sobreescribir en las diagonales de una posicion dada

    //leer los datos de la entrada
    cin >> filas >> columnas;
    if (filas >= 1 && filas <= DIM && columnas >= 1 && columnas <= DIM) {
        for (int f = 0; f < filas; f++) {
            for (int c = 0; c < columnas; c++) {
                cin >> matriz[f][c];
            }
        }
        /*cin >> transformaciones;
        if (transformaciones > 0 && transformaciones <= TRANSFORMACIONES) {
            for (int t = 1; t <= transformaciones; t++) {
                cin >> operacion;
                if (operacion == "columnas") {
                    cin >> pos1 >> pos2;
                    swapC(matriz, filas, columnas, pos1 - 1, pos2 - 1);
                }
                else if (operacion == "filas") {
                    cin >> pos1 >> pos2;
                    swapF(matriz, filas, columnas, pos1 - 1, pos2 - 1);
                }
                else if (operacion == "cruz") {
                    cin >> pos1 >> pos2 >> dato;
                    cruz(matriz, filas - 1, columnas, pos1 - 1, pos2 - 1, dato);
                }
            }
        }*/
    }

    /*else {
        return false;
    }*/
    if (filas == 0 && columnas == 0)
        return false;

    resolver(matriz, filas, columnas);
    //escribir sol
    mostrar(matriz, filas, columnas);

    return true;
}

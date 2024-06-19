//Compilador y S.O. utilizado: VS 2019
//Nombre del problema: Jaque de reina
//Comentario general sobre la solución: Numero de casos de prueba


#include <iostream>
#include <fstream>
#include <utility>
using namespace std;

// Delimitan el movimiento de la torre en sus ocho direcciones
const int NUM_DIRECCIONES = 8;
const pair <int, int > dirs8[NUM_DIRECCIONES] = { { -1 ,0} ,{1 ,0} ,{0 ,1} ,{0 , -1} , {1 ,1} , { -1 ,1} , {1 , -1} , { -1 , -1} };
// Determina las dimensiones del tablero
const int CASILLAS = 8;
// Enumerado que representa las distintas piezas del tablero
typedef enum { REINA, REY, OTRA, NADA }tPieza;
// Matriz que representa el tablero de ajedrez
typedef char tMatriz[CASILLAS][CASILLAS];


// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver(const tMatriz& matriz);

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    tMatriz matriz = { ' ' };
    for (int i = 0; i < CASILLAS; i++) {
        for (int j = 0; j < CASILLAS; j++) {
            cin >> matriz[i][j];
        }
    }
    // leer los datos de la entrada

    resolver(matriz);

    // escribir solución
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
//#ifndef DOMJUDGE
//    std::ifstream in("in.txt");
//    auto cinbuf = std::cin.rdbuf(in.rdbuf());
//    std::ofstream out("out.txt");
//    auto coutbuf = std::cout.rdbuf(out.rdbuf());
//#endif

    int numCasos;
    cout << "Num casos: ";
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
//#ifndef DOMJUDGE
//    std::cin.rdbuf(cinbuf);
//    std::cout.rdbuf(coutbuf);
//    system("PAUSE");
//#endif
    return 0;
}

/*
Buscar a la reina en la matriz y desde su posicion recorrer todas las direcciones
posibles del movimiento de la reina. Si se encuentra una pieza distinta al rey y
a la reina ('X'), se deja de buscar al rey y NO JAQUE. Si se encuentra al rey, JAQUE.
Y si no se encuentra nada, se busca en la siguiente direccion.
*/
void resolver(const tMatriz& matriz) {
    bool jaque = false; // Variable para indicar si hay jaque o no
    bool otra = false; // Variable para indicar si hay cualquier otra ficha
    bool reina = false; // Variable para indicar que he encontrado a la reina
    int f = 0, c = 0; // Contadores para recorrer la matriz hasta encontrar la reina
    int fila = 0, columna = 0; // Representa la posicion de la reina
    // Busqueda de la reina 
    while (f < CASILLAS && !reina) { // Recorro las filas
        c = 0;
        while (c < CASILLAS && !reina) { // Recorro las columnas
            if (matriz[f][c] == 'A') {
                reina = true; // Encuentro a la reina
                fila = f;
                columna = c;
            }
            else { // Si no la encuentro, paso a la siguiente columna
                c++;
            }
        }
        if (!reina) { // Si no la encuentro, paso a la siguiente fila
            f++;
        }
    }
    fila = f;
    columna = c;
    // Hacia la derecha
    while (columna < CASILLAS && (!otra && !jaque)) {
        //if (matriz[f][c] == 'R') { // Si encuentro al rey
        //    jaque = true;
        //}
        //else if (matriz[f][c] == 'X') {
        //    otra = true;
        //}
        jaque = (matriz[fila][columna] == 'R');
        otra = (matriz[fila][columna] == 'X');
        /*jaque = (dirs8[columna].second == 'R');
        otra = (dirs8[columna].second == 'X');*/
        columna++;
    }
    fila = f;
    columna = c;
    otra = false;
    // Hacia la derecha y hacia abajo
    while (fila < CASILLAS && columna < CASILLAS && (!otra && !jaque)) {
        jaque = (matriz[fila][columna] == 'R');
        otra = (matriz[fila][columna] == 'X');
       /* jaque = (dirs8[fila].first == 'R');
        jaque = (dirs8[columna].second == 'R');
        otra = (dirs8[fila].first == 'X');
        otra = (dirs8[columna].second == 'X');*/
        columna++;
        fila++;
    }
    fila = f;
    columna = c;
    otra = false;
    // Hacia abajo
    while (fila < CASILLAS && (!otra && !jaque)) {
        jaque = (matriz[fila][columna] == 'R');
        otra = (matriz[fila][columna] == 'X');
        /*jaque = (dirs8[fila].first == 'R');
        otra = (dirs8[fila].first == 'X');*/
        fila++;
    }
    fila = f;
    columna = c;
    otra = false;
    // Hacia abajo y hacia la izq
    while (fila < CASILLAS && columna >= 0 && (!otra && !jaque)) {
        jaque = (matriz[fila][columna] == 'R');
        otra = (matriz[fila][columna] == 'X');
        /*jaque = (dirs8[fila].first == 'R');
        jaque = (dirs8[columna].second == 'R');
        otra = (dirs8[fila].first == 'X');
        otra = (dirs8[columna].second == 'X');*/
        fila++;
        columna--;
    }
    fila = f;
    columna = c;
    otra = false;
    // Hacia la izq
    while (columna >= 0 && (!otra && !jaque)) {
        jaque = (matriz[fila][columna] == 'R');
        otra = (matriz[fila][columna] == 'X');
        /*jaque = (dirs8[columna].second == 'R');
        otra = (dirs8[columna].second == 'X');*/
        columna--;
    }
    fila = f;
    columna = c;
    otra = false;
    // Hacia arriba y a la izq
    while (fila >= 0 && columna >= 0 && (!otra && !jaque)) {
        /*jaque = (matriz[fila][columna] == 'R');
        otra = (matriz[fila][columna] == 'X');*/
        jaque = (dirs8[fila].first == 'R');
        jaque = (dirs8[columna].second == 'R');
        otra = (dirs8[fila].first == 'X');
        otra = (dirs8[columna].second == 'X');
        fila--;
        columna--;
    }
    fila = f;
    columna = c;
    otra = false;
    // Hacia arriba
    while (fila >= 0 && (!otra && !jaque)) {
        jaque = (matriz[fila][columna] == 'R');
        otra = (matriz[fila][columna] == 'X');
        /*jaque = (dirs8[fila].first == 'R');
        otra = (dirs8[fila].first == 'X');*/
        fila--;
    }
    fila = f;
    columna = c;
    otra = false;
    // Hacia arriba y a la dcha
    while (fila >= 0 && columna < CASILLAS && (!otra && !jaque)) {
        jaque = (matriz[fila][columna] == 'R');
        otra = (matriz[fila][columna] == 'X');
        /*jaque = (dirs8[fila].first == 'R');
        jaque = (dirs8[columna].second == 'R');
        otra = (dirs8[fila].first == 'X');
        otra = (dirs8[columna].second == 'X');*/
        fila--;
        columna++;
    }
    if (jaque) {
        cout << "JAQUE" << endl;
    }
    else {
        cout << "SIN JAQUE" << endl;
    }

}
